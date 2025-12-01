XTAL
====

# About

XTAL is a cross-platform header-only template-combinator library for musical Digital Signal Processing (DSP).
It provides an extensible and performant framework for the rapid prototyping and development of instruments and effects targeting native and embedded platforms. Programs developed using XTAL resemble the `SynthDef` subsystem of SuperCollider, while fulfilling the event-handling and buffer-processing cycle required by C++ frameworks like CoreAudio, JUCE, and Max/Min.

Central to the design of XTAL is template composition, utilizing the class-decorator pattern to compose behaviour/state transparently. Acyclic networks comprising both pure and stateful functors are defined functional application and composition. At the sample-level and range/block-level respectively, `process`es and `processor`s can be controlled dynamically either by manipulating state directly or through `vtable`d template switching. As a result, branching and queueing is kept to a minimum, enhancing both code ergonomics and program throughput/latency.

Networks are are organized into self-contained nodes, driven by statically-routed events which can be immediate, delayed, or tweened. Nodes represent a discrete processing unit, and can be decorated with custom scheduling, storage, queues, and other resources. The functional construction determines the architecture of the network, observing `rvalue`/`lvalue` semantics to maximise data-sharing and cache performance.

The following sections provide an overview of the usage and development of this library.
Detailed usage can be found within the accompanying test`.cc` files,
an annotated example of which appears at [xtal--math](///github.com/synthetic-methods/xtal--math/).

# Usage

## Processing

The mechanism for defining stream-based operators is range-lifting,
whereby both pure and stateful `process`es are converted to `processor`s in order to `transform` block-based data.

```c++
struct Mix : process::confine_t<Mix>
{
   template <auto ...Ns>
   auto method(auto &&...xs) const
   noexcept -> auto
   {
      using X = common_t<XTAL_ALL_(xs)...>;
      return (XTAL_REF_(xs) + ... + X{});
   }
};
```

The implementation of a `process` is defined by the `template`d function `method`.
When the `template` parameter list `Ns...` is unused/undefined, the `method` is aliased as `operator()`.

```c++
Mix mix;
auto six = mix(1.1, 2.2, 3.3);// 6.6
```

Range-lifting is achieved with functors like `processor::{conferred,confined}`,
which `zip` the underlying `method`.

```c++
using Mixer = processor::conferred_t<Mix>;
Mixer mixer;
auto  sixer = mixer(one, two, three);// mixes the ranges/processors `one`, `two`, `three`
```

In either case, dependencies are defined by functional application of `process(?:or)?`s,
with the inner-most components representing inputs, and the outer-most component representing the output.

## Messaging

Attributes are bound to a `process(?:or)?` using the `occur` decorators `attach` and `dispatch`.
The value of an attribute is type-indexed on `this`, and can be read either by explicit conversion or by using the method `this->template head<...>()`.

```c++
using Active = occur::reinferred_t<union active, int>;

struct Mix : process::confine_t<Mix, Active::template attach>
{
   template <auto ...Ns>
   auto method(auto &&...xs) const
   noexcept -> auto
   {
      return (XTAL_REF_(xs) + ... + 0)*Active(*this);
   // return (XTAL_REF_(xs) + ... + 0)*this->template head<Active>();
   }
};
```

Templated parameters can be bound using `dispatch` to build the `vtable` required for dynamic resolution. For `process`es the function is resolved once per sample, while for `processor`s the function is resolved only once per block, providing coarse-grained choice without branching.

```c++
using Offset = occur::reinferred_t<union active, int>;

struct Mix : process::confine_t<Mix
,  Offset::template dispatch<2>
,  Active::template dispatch<2>
>
{
   template <auto offset, auto active>
   auto method(auto &&...xs) const
   noexcept -> auto
   {
      return (XTAL_REF_(xs) + ... + offset)*active;
   }
};
```

Update is managed by the `influx` and `efflux` operators and methods. The `influx` method and operator `<<=` updates the dependency graph from the outside-in, using caching to limit unnecessary propagation. The `efflux` method and operator `>>=` updates the dependency graph from the inside-out, following the functional flow of data.

```c++
mixer <<= Active{0};// off
mixer <<= Active{1};// on
```

To schedule messages within `processor` blocks, messages may be attached using `intermit` to splice them at a specific offset.

```c++
using Mixer = processor::conferred_t<Mix, Active::template intermit<>>;
// ...
mixer.influx(cell::cue_s<>(123), Active(0));// `active == 0` @ offset 123
```

Alternatively, messages may themselves be reincorporated as `process(?:or)?`s using `hold`:

```c++
using Gated = processor::confined_t<Gate::template hold<>>;
Gated gated;

gated <<= std::make_tuple(cell::cue_s<>(123), (Gate) 1);// `gated()[123] == 1`
```

They are often used in tandem, e.g. the global block size/step may be updated by `influx` before using `efflux` to `review` the outcome.

```c++
auto resize = resize_f(1024);
auto render = cursor_f(1024);

using Mixer = processor::monomer_t<Mix, provision::stored<>>;
auto  sixer = Mixer::binding_f(one, two, three);

// initialization
{
   // allocate all `processor`s reachable from `sixer`
   sixer <<= resize;
}

// 1st iteration
{
   // activate the `sixer` for the entirety of the first block
   sixer <<= Active(1);

   // process the current graph, and advance the render cursor
   sixer >>= cursor++;
}
// 2nd iteration
{
   // deactivate the `sixer` at an offset of `123` into the current block
   sixer <<= sixer <<= std::make_tuple(123, Active(0));

   // process the current graph, and advance the render cursor
   sixer >>= cursor++;
}
```

# Development

## Platform

Using `C++20` and `ranges-v3@0.12.0`, the following compilers have been successfully tested:
-  `clang`: 14
-  `msvc`: 19.33
-  `gcc`: 12

The transition to `C++23` ranges is limited by the lack of general support for `zip_transform` a.k.a. `zip_with`.

## Package

With the project in genesis, the only supported package manager is `conan --version` 2. The `test_package` (comprising ~1000 assertions in ~50 test cases) can be resolved/compiled/executed with:

   conan create . --build=missing


## Layout

The directories in the project are organised by namespace with the leaves representing distinct type-families.

The [`**/all.hh`](include/xtal/all.hh?ts=3) exports all implementations at a given level. At the leaves, this includes the fundamental types defined by `any.hh` and more elaborate specializations like [`monomer.hh`](include/xtal/processor/monomer.hh?ts=3) and [`polymer.hh`](include/xtal/processor/polymer.hh?ts=3).

The [`**/any.hh`](include/xtal/cell/any.hh?ts=3) provides the key implementations of `[dr]efine` and `[dr]efer` which are scaffolded by [`cell/_entail.ii`](include/xtal/cell/_entail.ii?ts=3) to create higher-level decorators like `confine` and `confer`.

As a header-only library, the accompanying `*.cc` are there to fulfil testing and are ommitted from the published package.


## Templates

The majority of definitions in this library operate on decorators: type-level functions that map from a superclass `S` to a subclass. These decorators are expressed as a `struct` containing `class subtype`:

```c++
template <auto ...Ms>
struct decorator
{
   template <class S>
   class subtype
   {
   // ...
   };
};
```

Typically, these `struct`ures are themselves `template`d in order to realise a specific trait. For example, `define` uses the Curiously Recursive Template Pattern (CRTP) to construct the supplied subclass `T`.

```c++
template <class T>
struct define
{
   template <class S>
   class subtype
   {
      XTAL_DEF_(return,inline,let) self() const noexcept -> decltype(auto) {return static_cast<T const &>(*this);}
      XTAL_DEF_(return,inline,let) self()       noexcept -> decltype(auto) {return static_cast<T       &>(*this);}

   // [[nodiscard]] __attribute__((always_inline)) constexpr auto self()...
   // [[nodiscard]] __attribute__((always_inline)) constexpr auto self()...

   };
};
```

The type-constructors `compose` and `compose_s` are used to linearize the inheritance chain, apropos of Scala's trait linearization. For example, the following definitions are equivalent (noting that `A, ..., Z` are applied in order to `S`)...

```c++   
using T = compose<A, Z>::template subtype<S>;
using T = compose<A>::template subtype<S, Z>;
using T = compose<>::template subtype<S, Z, A>;
```

## Namespaces

The primary namespaces within `xtal` constitute a hierarchy linked by the namespace `_retail` designating the parent:

```c++
namespace cell      {}
namespace flow      {namespace _retail = cell;}
namespace occur     {namespace _retail = flow;}
namespace process   {namespace _retail = flow;}
namespace processor {namespace _retail = process;}
```

The [`any.hh`](include/xtal/process/any.hh?ts=3) for each namespace provides the main definitions (specializing only `[dr]efine` and `[dr]efer`), using the supplied `_retail` to refer to the parent definitions. The inclusion of [`cell/_entail.ii`](include/xtal/cell/_entail.ii?ts=3) within each namespace scaffolds the higher-order constructs based on these definitions, emulating family inheritance. For example...

The `confer` decorator reifies the supplied type `U` by composing `defer` and `refer`, respectively providing proxy management (e.g. constructors and accessors) and forwarding (e.g. operators).

```c++
template <class U> struct defer;
template <class U> struct refer;

template <class U, typename ...As>
struct confer : compose<refer<U>, As..., defer<U>> {};
```

The `confine` decorator constructs the supplied type `T` by composing `define` and `refine`, respectively providing initialization (e.g. providing `begin` and `end`) and finalization (e.g. applying `ranges::view_interface`).

```c++
template <class U> struct define;
template <class U> struct refine;

template <class U, typename ...As>
struct confine : compose<refine<U>, As..., define<U>> {};
```

## Status

### Abridged Overview

|Reference                                                         |Features                      |
|------------------------------------------------------------------|------------------------------|
|[`bond/compose.hh`      ](include/xtal/bond/compose.hh?ts=3)      |Dependency composition        |
|[`flow/any.hh`          ](include/xtal/flow/any.hh?ts=3)          |Messaging  resolution         |
|[`flow/bundle.hh`       ](include/xtal/flow/any.hh?ts=3)          |Parameter  bundling           |
|[`occur/any.hh`         ](include/xtal/occur/any.hh?ts=3)         |Parameter  handling           |
|[`occur/cursor.hh`      ](include/xtal/occur/any.hh?ts=3)         |Transport  windowing          |
|[`process/any.hh`       ](include/xtal/process/any.hh?ts=3)       |Process    lifting            |
|[`processor/any.hh`     ](include/xtal/processor/any.hh?ts=3)     |Processor  lifting            |
|[`processor/monomer.hh` ](include/xtal/processor/monomer.hh?ts=3) |Processor  management         |
|[`processor/polymer.hh` ](include/xtal/processor/polymer.hh?ts=3) |Processor  polymorphism       |
|[`schedule/glider.hh`   ](include/xtal/schedule/glider.hh?ts=3)   |Parameter  scheduling/ramping |
|[`schedule/slicer.hh`   ](include/xtal/schedule/slicer.hh?ts=3)   |Event      scheduling/slicing |
|[`atom/spool.hh`        ](include/xtal/atom/spool.hh?ts=3)        |Event      spooling           |
|[`atom/block.hh`        ](include/xtal/atom/block.hh?ts=3)        |Buffer     management         |

## Contribution

If you would like to help or get in touch, contact @goomtrex wherever you find me.
Otherwise, feel free to submit an issue or pull-request.
