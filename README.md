XTAL
====

# About

XTAL is a range-based header-only template-combinator library for musical Digital Signal Processing (DSP).
It provides an extensible and performant framework for rapid prototyping and development, 
aimed at building real-time instruments and effects for both hardware and software.

The emphasis of the library is on composability and performance, accommodating dynamic message within a static framework.
It resembles the `SynthDef` subsystem of SuperCollider, fulfilling the buffer read/write cycle required by C++ frameworks like CoreAudio, JUCE, and Max/Min, while abstracting the nested iteration, state-management, and event handling used by these systems.

The `process`es within the framework comprise pure functions and stateful functors like oscillators and filters, 
which are lifted to define `processor`s that operate on blocks of samples. These `processor`s are then applied functionally to form acyclic DSP networks, accomodating both `1:N` and `1:1` connections as well as automatic sharing for suitable `rvalue` arguments.

The procession of the network is governed by a static messaging protocol, and includes the capability for scheduling and run-time resolution of `vtable`d function templates. For `processor`s, messages are resolved at the block level, which means `vtable`d architectural changes can be performed with minimal branching.

The following sections provide an overview of the usage and development of this library.
Further insight may be gleaned from the `*.hpp` implementations or `*.c++` tests in [`include/xtal/**`](include/xtal/?ts=3).

# Usage

## Prelude

The following code examples use the following macros for brevity/clarity:

	#define XTAL_FN2 [[nodiscard]] static constexpr decltype(auto)
	#define XTAL_FN1               static constexpr decltype(auto)

	#define XTAL_DEF       auto &&
	#define XTAL_REF_(...) static_cast<decltype(__VA_ARGS__)&&>(__VA_ARGS__)

## Processing

The fundamental mechanism for defining stream-based operators is range-lifting,
whereby both pure and stateful `process`es are converted to `processor`s in order to `transform` block-based data.

	struct Mix: process::confine_t<Mix>
	{
	   template <auto...>
	   XTAL_FN2 method(XTAL_DEF ...xs)
	   {
	      return (XTAL_REF_(xs) + ... + 0);
	   }
	};

The implementation of a `process` is defined by the `template`d function `method`\.
When the `template` parameter list is undefined `<auto...>`,
this `method` is aliased as the invocation `operator()`\.

	Mix mix;
	auto six = mix(1.1, 2.2, 3.3);// 6.6

Range-lifting is achieved using functors like `processor::{let,lift,monomer}`,
which `zip` the underlying `method`\.

	using Mixer = processor::lift_t<Mix>;
	Mixer mixer;
	auto sixer = mixer(one, two, three);// mixes the ranges/processors `one`, `two`, `three`

In either case, dependencies are defined by functional application of `process(?:or)?`s,
with the inner-most nodes representing inputs, and the outer-most node representing the output.

## Messaging

Attributes are bound to a `process(?:or)?` using the `control` decorators `attach` and `dispatch`\.
The value of an attribute is type-indexed on `this`, and can be read either by explicit conversion or by using the method `this->template get<...>()`\.

	using Active = control::ordinal_t<struct active>;

	struct Mix: process::confine_t<Mix, Active::template attach>
	{
	   template <auto...>
	   XTAL_FN2 method(XTAL_DEF ...xs)
	   {
	      return (XTAL_REF_(xs) + ... + 0)*Active(*this);
	   // return (XTAL_REF_(xs) + ... + 0)*this->template get<Active>();
	   }
	};

Templated parameters can be bound using `dispatch` to build the `vtable` required for dynamic resolution. For `process`es the function is resolved once per sample, while for `processor`s the function is resolved only once per block, providing coarse-grained choice without branching.

	struct Mix: process::confine_t<Mix, Active::template dispatch<2>>
	{
	   template <auto active>
	   XTAL_FN2 method(XTAL_DEF ...xs)
	   {
	      return (XTAL_REF_(xs) + ... + 0)*active;
	   }
	};

Update is managed by the `influx` and `efflux` operators and methods. The `influx` method and operator `<<=` updates the dependency graph from the outside-in, using caching to limit unnecessary propagation. The `efflux` method and operator `>>=` updates the dependency graph from the inside-out, following the functional flow of data.

	mixer <<= Active(0);// off
	mixer <<= Active(1);// on

To schedule messages within `processor` blocks, messages may be attached using `interrupt` to splice them at a specific offset.

	using Mixer = processor::lift_t<Mix, Active::template interrupt<>>;
	// ...
	mixer.influx(context::delay_s<>(123), Active(0));// `active == 0` @ offset 123

Alternatively, messages may themselves be reincorporated as `process(?:or)?`s using `hold`:

	using Gated = processor::confined_t<Gate::template hold<>>;
	Gated gated;

	biased <<= std::make_tuple(context::delay_s<>(123), (Gate) 1);// `biased()[123] == 1`

They are often used in tandem, e.g. the global block size/step may be updated by `influx` before using `efflux` to `respan` the outcome.

	auto resize = resize_t(1024);
	auto sequel = sequel_t(1024);

	using Mixer = processor::monomer_t<Mix, collect<-1>>;
	auto sixer = Mixer::binding_f(one, two, three);

	// initialization
	{
	   // allocate all `processor`s reachable from `sixer`
	   sixer <<= resize;
	}
	
	// 1st iteration
	{
	   // activate the `sixer` for the entirety of the first block
	   sixer <<= Active(1);

	   // render the current graph, and advance the `sequel` cursor
	   sixer >>= sequel++;
	}
	// 2nd iteration
	{
	   // deactivate the `sixer` at an offset of `123` into the current block
	   sixer <<= sixer <<= std::make_tuple(123, Active(0));

	   // render the current graph, and advance the `sequel` cursor
	   sixer >>= sequel++;
	}

# Development

## Platform

Using `C++20` and `ranges-v3@0.12.0`, the following compilers have been successfully tested:
-	`clang`: 14
-	`msvc`: 19.33
-	`gcc`: 12

The transition to `C++23` ranges is limited by the lack of general support for `zip_transform` a.k.a. `zip_with`\.

## Layout

The directories in the project are organised by namespace with the leaves representing distinct type-families.

The files [`**/all.hpp`](include/xtal/all.hpp?ts=3) export all definitions at a given level. At the leaves, this includes fundamental types like `any` and specializations like `monomer`, etc.

The files [`xtal/*/any.hpp`](include/xtal/concord/any.hpp?ts=3) provide the core definitions used to construct these types. At the leaves, this includes decorators like `define`, `defer`, etc.

The file [`xtal/concord/any.hxx`](include/xtal/concord/any.hxx?ts=3) scaffolds higher-level decorators based on `[dr]efine` and/or `[dr]efer`, intended to be `#include`d within a namespace in which these decorators are provided.

As a header-only library, the accompanying `*.c++` are there only for testing and are ommitted from the published package.

## Macros

The macros defined in [`xtal/etc.hpp`](include/xtal/etc.hpp?ts=3) are used throughout this library in order to finesse some of the keyword combinations required by `C++`\.
The most commonly encountered are those used for function definition, for example:

	#define XTAL_LET                 static constexpr          auto
	#define XTAL_OP1                        constexpr decltype(auto) operator
	#define XTAL_OP2   [[nodiscard]]        constexpr decltype(auto) operator
	#define XTAL_FN1                        constexpr decltype(auto)
	#define XTAL_FN2   [[nodiscard]]        constexpr decltype(auto)
	#define XTAL_CN1                 static constexpr decltype(auto)
	#define XTAL_CN2   [[nodiscard]] static constexpr decltype(auto)
	
	#define XTAL_0EX                   noexcept
	#define XTAL_0EX_(REF)         REF noexcept
	#define XTAL_0FX         const     noexcept
	#define XTAL_0FX_(REF)   const REF noexcept

This naming scheme is intended to be automnemonic...

The codes `OP1` and `OP2` respectively designate unary and binary operators. This convention is carried over to the mutative and immutative function codes `FN1` and `FN2` and their `static` counterparts `CN1` and `CN2`\. The codes `0EX` and `0FX` respectively designate mutative and immutative definitions with `noexcept`, the latter a mnemonic for "no effects".

## Templates

A majority of definitions in this library operate on decorators - type-level functions that map from a superclass `S` to a subclass.
These decorators are expressed as a `struct` with `template`d member `subtype`:

	struct {template <typename S> class subtype;};

Typically, these `struct`ures are themselves `template`d in order to realise a specific facet of the system.
For example, `define` uses the curiously recursive template pattern (CRTP) to construct the supplied subclass `T`\.

	template <typename T>
	struct define
	{
	   template <typename S>
	   class subtype
	   {
	      XTAL_FN2 self() XTAL_0FX {return static_cast<T const &>(*this);}
	      XTAL_FN2 self() XTAL_0EX {return static_cast<T       &>(*this);}

	   // [[nodiscard]] constexpr decltype(auto) self() const noexcept {return static_cast<T const &>(*this);}
	   // [[nodiscard]] constexpr decltype(auto) self()       noexcept {return static_cast<T       &>(*this);}

	   };
	};

The type-functions [`compose` and `compose_s`](include/xtal/common/compose.hpp?ts=3) are used to linearize the inheritence chain by applying a sequence of decorators to the supertype `S`, similar to the linearization of Scala's traits. For example, the following definitions are equivalent (noting that `A, ..., Z` are applied in order to `S`)...

	using T = compose<A, Z>::template subtype<S>;
	using T = compose<A>::template subtype<S, Z>;
	using T = compose<>::template subtype<S, Z, A>;

## Namespaces

The primary namespaces within `xtal` comprise a hierarchy linked by the namespace `_retail` designating the parent:

	namespace concord   {}
	namespace conflux   {namespace _retail = concord;}
	namespace context   {namespace _retail = concord;}
	namespace control   {namespace _retail = conflux;}
	namespace message   {namespace _retail = control;}
	namespace process   {namespace _retail = conflux;}
	namespace processor {namespace _retail = process;}

The [`any.hpp`](include/xtal/process/any.hpp?ts=3) for each namespace supply the core definitions (specializing only `[dr]efine` and `[dr]efer`), using the supplied `_retail` to refer to the parent definitions. The inclusion of `xtal/concord/any.hxx` within each namespace scaffolds the higher-order constructs based on these definitions, emulating family inheritance. For example...

The `confer` decorator reifies the supplied type `U` by composing `defer` and `refer`, respectively providing proxy management (e.g. constructors and accessors) and forwarding (e.g. operators).

	template <typename U> struct defer;
	template <typename U> struct refer;

	template <typename U, typename ...As>
	struct confer: compose<refer<U>, As..., defer<U>> {};

The `confine` decorator constructs the supplied type `T` by composing `define` and `refine`, respectively providing initialization (e.g. providing `begin` and `end`) and finalization (e.g. applying `ranges::view_interface`).

	template <typename U> struct define;
	template <typename U> struct refine;

	template <typename U, typename ...As>
	struct confine: compose<refine<U>, As..., define<U>> {};

## Status

Implemented:

|Feature                |Reference|
|-----------------------|---------|
|Dependency composition |[`common/compose.hpp`](include/xtal/common/compose.hpp?ts=3)|
|Dependency management  |[`conflux/any.hpp`](include/xtal/conflux/any.hpp?ts=3) via `\.(?:de\|ef\|in)(?:flux\|fuse)`|
|Parameter bundling     |[`conflux/any.hpp`](include/xtal/conflux/any.hpp?ts=3) via `\.operator(?:<<\|>>)=` with `std::tuple`|
|Parameter binding      |[`control/any.hpp`](include/xtal/control/any.hpp?ts=3) via `::(?:attach\|dispatch)`|
|Parameter sampling     |[`control/any.hpp`](include/xtal/control/any.hpp?ts=3) via `::hold`|
|Parameter scheduling   |[`control/any.hpp`](include/xtal/control/any.hpp?ts=3) via `::interrupt`|
|Parameter namespacing  |[`control/any.hpp`](include/xtal/control/any.hpp?ts=3) via `::prefix`|
|Process lifting        |[`process/any.hpp`](include/xtal/process/any.hpp?ts=3) via `\.(?:de\|re)fer`|
|Processor lifting      |[`processor/any.hpp`](include/xtal/processor/any.hpp?ts=3) via `\.(?:de\|re)fer`|
|Processor resizing     |[`processor/monomer.hpp`](include/xtal/processor/monomer.hpp?ts=3) via `::binding` and influxing [`control/resize.hpp`](include/xtal/control/resize.hpp?ts=3)|
|Processor rendering    |[`processor/monomer.hpp`](include/xtal/processor/monomer.hpp?ts=3) via `::binding` and effluxing [`control/respan.hpp`](include/xtal/control/respan.hpp?ts=3)|
|Processor streaming    |[`processor/monomer.hpp`](include/xtal/processor/monomer.hpp?ts=3) via `::binding` and effluxing [`control/sequel.hpp`](include/xtal/control/sequel.hpp?ts=3)|
|Buffer sharing         |[`processor/monomer.hpp`](include/xtal/processor/monomer.hpp?ts=3) via `::binding` compatible `&&`arguments|
|Buffer manipulation    |[`common/collate.hpp`](include/xtal/common/collate.hpp?ts=3) via `::(?:series\|serial)`, incl. convolution and iFFT/FFT|
|Numeric conditioning   |[`common/realize.hpp`](include/xtal/common/realize.hpp?ts=3) via `\.(?:truncate\|puncture)`|

Implemented but untested:

|Feature                |Reference|
|-----------------------|---------|
|Processor polymorphism |[`processor/polymer.hpp`](include/xtal/processor/polymer.hpp?ts=3)|
|Matrix modulation      |[`process/dimer.hpp`](include/xtal/process/dimer.hpp?ts=3)|

## Contribution

If you would like to help or get in touch, contact @goomtrex wherever you find me.
Otherwise, feel free to submit an issue or pull-request.
