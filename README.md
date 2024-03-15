XTAL
====

# About

XTAL is a cross-platform header-only zipper/combinator library for musical Digital Signal Processing (DSP).
It provides an extensible and performant framework for rapid prototyping and development, 
aimed at building real-time instruments and effects for both hardware and software.

The emphasis of the library is on composability and performance, accommodating dynamic message within a static framework.
It resembles the `SynthDef` subsystem of SuperCollider, fulfilling the buffer read/write cycle required by C++ frameworks like CoreAudio, JUCE, and Max/Min, while abstracting the nested iteration, state-management, and event handling used by these systems.

The `process`es within the framework comprise pure functions and stateful functors like oscillators and filters, 
which are lifted to define `processor`s that operate on blocks of samples. These `processor`s are then applied functionally to form acyclic DSP networks, accomodating both `1:N` and `1:1` connections as well as automatic sharing for suitable `rvalue` arguments.

The procession of the network is governed by a static messaging protocol, and includes the capability for scheduled and run-time resolution of `vtable`d function templates. For `processor`s, messages are resolved at the block level, which means `vtable`d architectural changes can be performed with minimal branching.

The following sections provide an overview of the usage and development of this library.
Further insight may be gleaned from the `*.ii` implementations or `*.cc` tests in [`include/xtal/**`](include/xtal/?ts=3).

# Usage

## Prelude

The following code examples use the following macros for brevity/clarity:

	#define XTAL_TN2 [[nodiscard]] constexpr decltype(auto)
	#define XTAL_TN1               constexpr decltype(auto)

	#define XTAL_DEF       auto &&
	#define XTAL_REF_(...) static_cast<decltype(__VA_ARGS__)&&>(__VA_ARGS__)

## Processing

The fundamental mechanism for defining stream-based operators is range-lifting,
whereby both pure and stateful `process`es are converted to `processor`s in order to `transform` block-based data.

	struct Mix: process::confine_t<Mix>
	{
	   template <auto...>
	   XTAL_TN2 method(XTAL_DEF ...xs)
	   {
	      return (XTAL_REF_(xs) + ... + 0);
	   }
	};

The implementation of a `process` is defined by the `template`d function `method`.
When the `template` parameter list is undefined `<auto...>`,
this `method` is aliased as the invocation `operator()`.

	Mix mix;
	auto six = mix(1.1, 2.2, 3.3);// 6.6

Range-lifting is achieved using functors like `processor::{conferred,confined}`,
which `zip` the underlying `method`.

	using Mixer = processor::conferred_t<Mix>;
	Mixer mixer;
	auto sixer = mixer(one, two, three);// mixes the ranges/processors `one`, `two`, `three`

In either case, dependencies are defined by functional application of `process(?:or)?`s,
with the inner-most components representing inputs, and the outer-most component representing the output.

## Messaging

Attributes are bound to a `process(?:or)?` using the `message` decorators `attach` and `dispatch`.
The value of an attribute is type-indexed on `this`, and can be read either by explicit conversion or by using the method `this->template head<...>()`.

	using Active = message::label_t<int, struct active>;

	struct Mix: process::confine_t<Mix, Active::template attach>
	{
	   XTAL_TN2 method(XTAL_DEF ...xs)
	   {
	      return (XTAL_REF_(xs) + ... + 0)*Active(*this);
	   // return (XTAL_REF_(xs) + ... + 0)*this->template head<Active>();
	   }
	};

Templated parameters can be bound using `dispatch` to build the `vtable` required for dynamic resolution. For `process`es the function is resolved once per sample, while for `processor`s the function is resolved only once per block, providing coarse-grained choice without branching.

	using Offset = message::label_t<int, struct offset>;
	
	struct Mix: process::confine_t<Mix
	,  Offset::template dispatch<2>
	,  Active::template dispatch<2>
	>
	{
	   template <auto offset, auto active>
	   XTAL_TN2 method(XTAL_DEF ...xs)
	   {
	      return (XTAL_REF_(xs) + ... + offset)*active;
	   }
	};

Update is managed by the `influx` and `efflux` operators and methods. The `influx` method and operator `<<=` updates the dependency graph from the outside-in, using caching to limit unnecessary propagation. The `efflux` method and operator `>>=` updates the dependency graph from the inside-out, following the functional flow of data.

	mixer <<= Active(0);// off
	mixer <<= Active(1);// on

To schedule messages within `processor` blocks, messages may be attached using `intermit` to splice them at a specific offset.

	using Mixer = processor::conferred_t<Mix, Active::template intermit<>>;
	// ...
	mixer.influx(cell::cue_s<>(123), Active(0));// `active == 0` @ offset 123

Alternatively, messages may themselves be reincorporated as `process(?:or)?`s using `hold`:

	using Gated = processor::confined_t<Gate::template hold<>>;
	Gated gated;

	gated <<= std::make_tuple(cell::cue_s<>(123), (Gate) 1);// `gated()[123] == 1`

They are often used in tandem, e.g. the global block size/step may be updated by `influx` before using `efflux` to `respan` the outcome.

	auto resize = resize_t(1024);
	auto scope = scope_t(1024);

	using Mixer = processor::monomer_t<Mix, resourced::stored<>>;
	auto sixer = Mixer::bind_f(one, two, three);

	// initialization
	{
	   // allocate all `processor`s reachable from `sixer`
	   sixer <<= resize;
	}
	
	// 1st iteration
	{
	   // activate the `sixer` for the entirety of the first block
	   sixer <<= Active(1);

	   // render the current graph, and advance the `scope` cursor
	   sixer >>= scope++;
	}
	// 2nd iteration
	{
	   // deactivate the `sixer` at an offset of `123` into the current block
	   sixer <<= sixer <<= std::make_tuple(123, Active(0));

	   // render the current graph, and advance the `scope` cursor
	   sixer >>= scope++;
	}

# Development

## Platform

Using `C++20` and `ranges-v3@0.12.0`, the following compilers have been successfully tested:
-	`clang`: 14
-	`msvc`: 19.33
-	`gcc`: 12

The transition to `C++23` ranges is limited by the lack of general support for `zip_transform` a.k.a. `zip_with`.

## Package

With the project in genesis, the only supported package manager is `conan --version` 2. The `test_package` (comprising ~1000 assertions in ~50 test cases) can be resolved/compiled/executed with:

	conan create . --build=missing

## Layout

The directories in the project are organised by namespace with the leaves representing distinct type-families.

The [`**/all.ii`](include/xtal/all.ii?ts=3) exports all implementations at a given level. At the leaves, this includes the fundamental types defined by `any.ii` and specializations like `monomer`, etc.

The [`**/any.ii`](include/xtal/cell/any.ii?ts=3) provides the key implementations of `[dr]efine` and `[dr]efer` which are scaffolded by [`cell/_kernel.hxx`](include/xtal/cell/_kernel.hxx?ts=3) to create higher-level decorators like `confine` and `confer`.

The [`**/any.hh`](include/xtal/cell/any.hh?ts=3) provides the key dependencies for the respective domain, including the identifying `concept`s.

As a header-only library, the accompanying `*.cc` are there only for testing and are ommitted from the published package.

NOTE: When browsing/editing `include`, it can be useful to toggle the visibility of the `all.*`, `any.*`, and `*.cc` files. This can be accomplished in VSCode with the plug-ins [Toggle Excluded Files](https://marketplace.visualstudio.com/items?itemName=amodio.toggle-excluded-files) and [Open Related Files](https://marketplace.visualstudio.com/items?itemName=bryanthomaschen.open-related-file).


## Macros

The macros defined in [`xtal.hh`](include/xtal.hh?ts=3) are used throughout this library in order to finesse some of the keyword combinations required by `C++`.
The most commonly encountered are those used for function definition, for example:

	#define XTAL_OP1                      constexpr decltype(auto) operator
	#define XTAL_OP2 [[nodiscard]]        constexpr decltype(auto) operator
	#define XTAL_TN1                      constexpr decltype(auto)
	#define XTAL_TN2 [[nodiscard]]        constexpr decltype(auto)
	#define XTAL_FN1               static constexpr decltype(auto)
	#define XTAL_FN2 [[nodiscard]] static constexpr decltype(auto)
	
	#define XTAL_0EX                      noexcept
	#define XTAL_0EX_(REF)            REF noexcept
	#define XTAL_0FX            const     noexcept
	#define XTAL_0FX_(REF)      const REF noexcept

This naming scheme is intended to be automnemonic...

The codes `OP1` and `OP2` respectively designate unary and binary operators. This convention is carried over to the mutative and immutative function codes `FN1` and `FN2` and their counterparts on  `this`, `FM1` and `FM2`. The codes `0EX` and `0FX` respectively designate mutative and immutative definitions with `noexcept`, the latter a mnemonic for "no effects".

## Templates

The majority of definitions in this library operate on decorators: type-level functions that map from a superclass `S` to a subclass. These decorators are expressed as a `struct` containing `class subtype`:

	template <...> struct {template <class S> class subtype;};

Typically, these `struct`ures are themselves `template`d in order to realise a specific trait. For example, `define` uses the Curiously Recursive Template Pattern (CRTP) to construct the supplied subclass `T`.

	template <class T>
	struct define
	{
	   template <class S>
	   class subtype
	   {
	      XTAL_TN2 self() XTAL_0FX {return static_cast<T const &>(*this);}
	      XTAL_TN2 self() XTAL_0EX {return static_cast<T       &>(*this);}

	   // [[nodiscard]] constexpr decltype(auto) self() const noexcept {return static_cast<T const &>(*this);}
	   // [[nodiscard]] constexpr decltype(auto) self()       noexcept {return static_cast<T       &>(*this);}

	   };
	};

The type-functions [`compose` and `compose_s`](include/xtal/bond/compose.ii?ts=3) are used to linearize the inheritance chain, apropos of Scala's trait linearization. For example, the following definitions are equivalent (noting that `A, ..., Z` are applied in order to `S`)...

	using T = compose<A, Z>::template subtype<S>;
	using T = compose<A>::template subtype<S, Z>;
	using T = compose<>::template subtype<S, Z, A>;

## Namespaces

The primary namespaces within `xtal` constitute a hierarchy linked by the namespace `_retail` designating the parent:

	namespace core   {}
	namespace flux   {namespace _retail = core;}
	namespace message   {namespace _retail = flux;}
	namespace process   {namespace _retail = flux;}
	namespace processor {namespace _retail = process;}

The [`any.ii`](include/xtal/process/any.ii?ts=3) for each namespace provides the main definitions (specializing only `[dr]efine` and `[dr]efer`), using the supplied `_retail` to refer to the parent definitions. The inclusion of [`cell/_kernel.hxx`](include/xtal/cell/_kernel.hxx?ts=3) within each namespace scaffolds the higher-order constructs based on these definitions, emulating family inheritance. For example...

The `confer` decorator reifies the supplied type `U` by composing `defer` and `refer`, respectively providing proxy management (e.g. constructors and accessors) and forwarding (e.g. operators).

	template <class U> struct defer;
	template <class U> struct refer;

	template <class U, typename ...As>
	struct confer: compose<refer<U>, As..., defer<U>> {};

The `confine` decorator constructs the supplied type `T` by composing `define` and `refine`, respectively providing initialization (e.g. providing `begin` and `end`) and finalization (e.g. applying `ranges::view_interface`).

	template <class U> struct define;
	template <class U> struct refine;

	template <class U, typename ...As>
	struct confine: compose<refine<U>, As..., define<U>> {};

## Status

### Overview

|Feature                    |Reference|
|---------------------------|---------|
|Dependency composition     |[`bond/compose.ii`](include/xtal/bond/compose.ii?ts=3)|
|Dependency management      |[`flux/any.ii`](include/xtal/flux/any.ii?ts=3) via `\.(?:de\|ef\|in)(?:flux\|fuse)`|
|Parameter bundling         |[`flux/any.ii`](include/xtal/flux/any.ii?ts=3) via `\.operator(?:<<\|>>)=` with `std::tuple`|
|Parameter handling         |[`message/any.ii`](include/xtal/message/any.ii?ts=3) via `::(?:attach\|dispatch\|hold\|intermit)`|
|Process lifting            |[`process/any.ii`](include/xtal/process/any.ii?ts=3) via `\.(?:de\|re)fer`|
|Matrix modulation          |[`process/cross.ii`](include/xtal/process/cross.ii?ts=3)|
|Processor lifting          |[`processor/any.ii`](include/xtal/processor/any.ii?ts=3) via `\.(?:de\|re)fer`|
|Processor scheduling       |[`processor/monomer.ii`](include/xtal/processor/monomer.ii?ts=3) via `::binding`|
|Processor polymorphism     |[`processor/polymer.ii`](include/xtal/processor/polymer.ii?ts=3) via `::binding`|
|Buffer sharing             |[`processor/monomer.ii`](include/xtal/processor/monomer.ii?ts=3) via `::binding` compatible `&&`arguments|
|Buffer allocation          |[`atom/store.ii`](include/xtal/atom/store.ii?ts=3) impl. static `std::vector`|
|Buffer arithmetic          |[`atom/dissector.ii`](include/xtal/atom/dissector.ii?ts=3)|
|Buffer transformation      |[`atom/series.ii`](include/xtal/atom/series.ii?ts=3) incl. convolution and iFFT/FFT|
|Numeric conditioning       |[`bond/realize.ii`](include/xtal/bond/realize.ii?ts=3) via `\.(?:truncate\|puncture)`|

## Contribution

If you would like to help or get in touch, contact @goomtrex wherever you find me.
Otherwise, feel free to submit an issue or pull-request.
