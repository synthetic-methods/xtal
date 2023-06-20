XTAL
====

# About

XTAL is a range-based header-only template-combinator library for musical Digital Signal Processing (DSP).
It provides an extensible and performant framework for rapid prototyping and development,
aimed at building real-time instruments and effects for both hardware and software.

The emphasis of the library is on composability and performance, accommodating dynamic message within a static framework. Static mechanisms like CRTP and structures like `static_vector` provide the foundation for messaging and scheduling, while dynamically-resolved function templates provide the mechanism for block-level switching between instrument architectures.

The framework resembles the `SynthDef` subsystem of SuperCollider's, fulfilling the buffer read/write cycle required by C++ frameworks like CoreAudio, JUCE, and Max/Min, while abstracting the nested iteration, state-management, and event handling used by these systems.

Within this framework, the core `process`es comprise pure functions and stateful functors like oscillators and filters,
which are then range-lifted to form `processor`s.
The functional architecture of the system is defined using template combinators,
the behaviour of which dynamically controlled by a statically dispatched messaging protocol.
This protocol functions as a temporal build-system,
accomodating both `1:N` read-only and `1:1` read-write sharing.

The following sections provide an overview of the usage and development of this library.
For now, further details may respectively be gleaned from the `*.cxx` or `*.hpp` files themselves.

# Usage

## Processing

The fundamental mechanism for defining stream-based operators is range-lifting,
whereby both pure and stateful `process`es are converted to `processor`s in order to `transform` buffer-based data.

	struct mix_t
	:	process::confine_t<mix_t
		>
	{
		template <auto...>
		XTAL_FN2 method(XTAL_DEF ...xs)
		{
			return (XTAL_REF_(xs) + ... + 0);
		}
	};

The implementation of a `process` is defined by the `template`d function `method`.
When the `template` parameter list is undefined `<auto...>`,
this `method` is aliased as the invocation `operator()`.

	mix_t mix;
	auto six = mix(1.1, 2.2, 3.3);// 6.6

Range-lifting is achieved using functors like `processor::atom` or `processor::bond`,
allowing `method` and `operator` to `zip` the underlying function across `ranges`.
(In future, the (im)purity of a function will determine the `std::execution_policy`, once supported by the relevant `ranges` library.)

	using mixer_t = processor::let_t<mix_t>;
	mixer_t mixer;
	auto sixer = mixer(one, two, three);// mixes the ranges/processors `one`, `two`, `three`

In either case, dependencies are defined by functional application of `process(?:or)?`s,
with the inner-most nodes (plural) representing inputs, and the outer-most node (singular) representing the output.

## Messaging

Attributes are bound to a `process(?:or)?` using the `message` decorators `attach` and `dispatch`.
The value of an attribute is type-indexed on `this`,
and can be read either by explicit conversion or by using the method `this->template get<...>`.

	using active_t = message::ordinal_t<struct active>;

	struct mix_t
	:	process::confine_t<mix_t
		,	active_t::template attach
		>
	{
		template <auto...>
		XTAL_FN2 method(XTAL_DEF ...xs)
		{
			return (XTAL_REF_(xs) + ... + 0)*active_t(*this);
		//	return (XTAL_REF_(xs) + ... + 0)*this->template get<active_t>();
		}
	};

Templated parameters can use `dispatch` to build the function table required for dynamic resolution.
For `process`es the function is resolved once per sample,
while for `processor`s the function is resolved only once per buffer,
providing coarse-grained choice without branching.

	struct mix_t
	:	process::confine_t<mix_t
		,	active_t::template dispatch<2>
		>
	{
		template <auto active>
		XTAL_FN2 method(XTAL_DEF ...xs)
		{
			return (XTAL_REF_(xs) + ... + 0)*active;
		}
	};

Update is managed by the `influx` and `efflux` operators and methods.
The `influx` method and operator `<<=` updates the dependency graph from the outside-in,
using caching to limit unnecessary propagation.
The `efflux` method and operator `>>=` updates the dependency graph from the inside-out,
following the functional flow of data.

	mixer <<= active_t(0);// off

When sample-accurate scheduling is required,
`interrupt` can be applied at the `processor` stage to create the `priority_queue` for delayed update.
(In future, this may be automated on lift).

	mixer.influx(123, active_t(0));// off @ offset 123

They are often used in tandem, e.g. the global buffer size may be updated by `influx` before using `efflux` to `respan` the outcome.

	auto resize = resize_t(1024);
	auto sequel = sequel_t(1024);

	using mixer_t = processor::bond_t<mix_t>;
	auto sixer = mixer_t::bind_f(one, two, three);

	//	initialization
	{
		// allocate all `atom`d `processor`s reachable from `sixer`
		sixer <<= resize;
	}
	
	// 1st iteration
	{
		// activate the `sixer` for the entirety of the first block
		sixer <<= active_t(1);

		// respan the current graph, and advance the `sequel` sequel
		sixer >>= sequel++;
	}
	// 2nd iteration
	{
		// deactivate the `sixer` at an offset of `123` into the current block
		sixer <<= sixer <<= std::make_tuple(123, active_t(0));

		// respan the current graph, and advance the `sequel` sequel
		sixer >>= sequel++;
	}

# Development

## Platform

Using `C++20` and `ranges-v3@0.12.0`, the following compilers have been successfully tested:
-	`clang`: 14
-	`msvc`: 19.33
-	`gcc`: 12

The transition to `C++23` ranges is limited by the lack of general support for the following `views`:
-	`zip_transform` cf. `range/v3/views/zip_with.hpp`
-	`repeat`
-	`generate`

## Layout

The directories in the project are organised by namespace with the leaves representing distinct type-families.

The files `**/all.hpp` export all definitions at a given level.
At the leaves, this includes fundamental types like `any` and specializations like `atom`, `bond`, etc.

The files `xtal/*/any.hpp` provide the core definitions used to construct these types.
At the leaves, this includes decorators like `define`, `defer`, etc.

Within the leaf `xtal/common`, the file `any.ipp` scaffolds higher-level decorators based on `[dr]efine` and/or `[dr]efer`,
intended to be `#include`d within a namespace in which these decorators are provided.

The definitions within `xtal/*/any.hpp` appear in the namespace `*`,
and those within `xtal/any/*.hpp` appear in the namespace `xtal`.

## Macros

The macros defined in `xtal/_.hpp` are used throughout this library in order to finesse some of the keyword combinations required by `C++`.
The most commonly encountered are those used for function definition, for example:

	#define XTAL_LET                     static constexpr          auto
	#define XTAL_OP1                            constexpr decltype(auto) operator
	#define XTAL_OP2       [[nodiscard]]        constexpr decltype(auto) operator
	#define XTAL_FN1                            constexpr decltype(auto)
	#define XTAL_FN2       [[nodiscard]]        constexpr decltype(auto)
	#define XTAL_FZ1                     static constexpr decltype(auto)
	#define XTAL_FZ2       [[nodiscard]] static constexpr decltype(auto)
	
	#define XTAL_0EX                                      noexcept
	#define XTAL_0EX_(REF)                            REF noexcept
	#define XTAL_0FX                            const     noexcept
	#define XTAL_0FX_(REF)                      const REF noexcept

This naming scheme is intended to be automnemonic.

The codes `OP1` and `OP2` respectively designate unary and binary operators.
This convention is carried over to the mutative and immutative function codes `FN1` and `FN2`,
while their `static` counterparts `FZ1` and `FZ2` use `Z` as a sideways `N` to indicate orthogonality.
Similarly, the codes `0EX` and `0FX` respectively designate mutative and immutative uses of `noexcept`,
the latter a mnemonic for "no effects".

## Templates

A majority of definitions in this library operate on decorators -
type-level functions that map from a superclass `S` to a subclass.
These decorators are expressed as a `struct` with `template`d member `subtype`:

	struct
	{
		template <typename S>
		class subtype;
	};

Typically, these `struct`ures are themselves `template`d in order to realise a specific facet of the system.
For example, `define` uses the curiously recursive template pattern (CRTP) to construct the supplied subclass `T`.

	template <typename T>
	struct define
	{
		template <typename S>
		class subtype
		{
			XTAL_FN2 self() XTAL_0FX {return static_cast<T const &>(*this);}
			XTAL_FN2 self() XTAL_0EX {return static_cast<T       &>(*this);}

		//	[[nodiscard]] constexpr decltype(auto) self() const noexcept {return static_cast<T const &>(*this);}
		//	[[nodiscard]] constexpr decltype(auto) self()       noexcept {return static_cast<T       &>(*this);}

		}
	};

The functions `compose` and `compose_s` (defined in `xtal/any/compose.hpp`)
are used to linearize the inheritence chain by applying a sequence of decorators to the supertype `S`,
similar to the linearization of Scala's traits.
For example, The following definitions are equivalent (noting that `A1, ..., A4` are applied in order to `S`):

	using T = compose<A4, A3, A2, A1>::template subtype<S>;
	using T = compose<A4, A3>::template subtype<S, A1, A2>;
	using T = compose<>::template subtype<S, A1, A2, A3, A4>;
	using T = compose_s<S, A1, A2, A3, A4>;

## Namespaces

The primary namespaces within `xtal` comprise a hierarchy linked by the namespace `_retail` designating the parent:

	namespace confect   {namespace _retail = common;}
	namespace conflux   {namespace _retail = confect;}
	namespace message   {namespace _retail = conflux;}
	namespace process   {namespace _retail = conflux;}
	namespace processor {namespace _retail = process;}

The `any.hpp` for each namespace establishes the core definitions (specializing only `[dr]efine` and `[dr]efer`),
using the supplied `_retail` to refer to the parent definitions.
The inclusion of `xtal/common/any.ipp` within each namespace then scaffolds the higher-order constructs based on these definitions, emulating family inheritance. For example...

The `confer` decorator reifies the supplied type `U` by composing `defer` and `refer`,
respectively providing proxy management (e.g. constructors and accessors)
and forwarding (e.g. operators):

	template <typename U> struct defer;
	template <typename U> struct refer;

	template <typename U, typename ...As>
	struct confer
	:	compose<refer<U>, As..., defer<U>>
	{};

The `confine` decorator constructs the supplied type `T` by composing `define` and `refine`,
respectively providing initialization (e.g. providing `begin` and `end`)
and finalization (e.g. applying `ranges::view_interface`).

	template <typename U> struct define;
	template <typename U> struct refine;

	template <typename U, typename ...As>
	struct confine
	:	compose<refine<U>, As..., define<U>>
	{};

## Status

Current implemented but not yet comprehensively tested:
-	Stream-based processing.
-	Event messaging and scheduling.

Currently supported but not yet implemented:
-	Integer-indexed and volume-controlled arrays for:
	-	Polymorphism.
	-	Modulation matricies.
	-	Temporary parameter crossfades.
-	Note on/off handling by:
	-	Detecting the response to `.influx(message::stop()) == 0`.

## Contribution

If you would like to get involved or get in techo, don't hesitate to reach out to @goomtrex wherever you find me.
Otherwise, feel free to submit an issue or pull-request if that's more your style.
