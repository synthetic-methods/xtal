#pragma once
#include "./any.hh"
#include "./compose.hh"





XTAL_ENV_(push)
namespace xtal::bond
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
///\
Composes the supplied `template`s to define `::subtype<T, Ts...>`. \

template <template <class, class...> class ...Subtypes>
XTAL_USE compost   = compose<_detail::compost<Subtypes>...>;

template <template <class, class...> class ...Subtypes>
XTAL_ASK compost_q = (...and _detail::compost_q<Subtypes>);

template <class S, template <class, class...> class ...Subtypes>
XTAL_USE compost_s = typename compose<>::template subtype<S, _detail::compost<Subtypes>...>;


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
