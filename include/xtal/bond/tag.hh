#pragma once
#include "./any.hh"
#include "./tab.hh"
#include "./compose.hh"




XTAL_ENV_(push)
namespace xtal::bond
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

template <template <class ...> class K_>
struct tag
{
	using superkind = tab<tag<K_>>;

	template <class S>
	class subtype : public compose_s<S, superkind>
	{
		using S_ = compose_s<S, superkind>;
	
	public:
		using S_::S_;

		struct taboo
		:	S_::taboo
		{
			template <class ...Xs>
			using hypertype = K_<Xs...>;

		};

	};
};
template <class ..._s>
struct tagged
{
	template <class T>
	using subtype = typename T::taboo::template hypertype<_s...>;

};


template <class T, template <class ...> class ...Ks_> concept       tagged_q      =       tabbed_q     <T, tag<Ks_>...>;
template <class T, template <class ...> class ...Ks_> concept fixed_tagged_q      = fixed_tabbed_q     <T, tag<Ks_>...>;
template <class T, template <class ...> class ...Ks_> concept       tagged_with_q =       tabbed_with_q<T, tag<Ks_>...>;
template <class T, template <class ...> class ...Ks_> concept fixed_tagged_with_q = fixed_tabbed_with_q<T, tag<Ks_>...>;

template <template <class ...> class K_, class ...Ts> concept       tagged_p      =       tabbed_p     <tag<K_>, Ts...>;
template <template <class ...> class K_, class ...Ts> concept fixed_tagged_p      = fixed_tabbed_p     <tag<K_>, Ts...>;
template <template <class ...> class K_, class ...Ts> concept       tagged_with_p =       tabbed_with_p<tag<K_>, Ts...>;
template <template <class ...> class K_, class ...Ts> concept fixed_tagged_with_p = fixed_tabbed_with_p<tag<K_>, Ts...>;


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
