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


template <class T, template <class ...> class ...Ks_> concept      tag_outer_q =      tab_outer_q<T, tag<Ks_>...>;
template <class T, template <class ...> class ...Ks_> concept tag_outer_fixed_q = tab_outer_fixed_q<T, tag<Ks_>...>;
template <class T, template <class ...> class ...Ks_> concept      tag_inner_q =      tab_inner_q<T, tag<Ks_>...>;
template <class T, template <class ...> class ...Ks_> concept tag_inner_fixed_q = tab_inner_fixed_q<T, tag<Ks_>...>;

template <template <class ...> class K_, class ...Ts> concept      tag_outer_p =      tab_outer_p<tag<K_>, Ts...>;
template <template <class ...> class K_, class ...Ts> concept tag_outer_fixed_p = tab_outer_fixed_p<tag<K_>, Ts...>;
template <template <class ...> class K_, class ...Ts> concept      tag_inner_p =      tab_inner_p<tag<K_>, Ts...>;
template <template <class ...> class K_, class ...Ts> concept tag_inner_fixed_p = tab_inner_fixed_p<tag<K_>, Ts...>;


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
