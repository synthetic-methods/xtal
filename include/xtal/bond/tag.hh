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


template <class T, template <class ...> class ...Ks_> concept       tag_as_q =       tab_as_q<T, tag<Ks_>...>;
template <class T, template <class ...> class ...Ks_> concept tag_affixed_q = tab_affixed_q<T, tag<Ks_>...>;
template <class T, template <class ...> class ...Ks_> concept       tag_in_q =       tab_in_q<T, tag<Ks_>...>;
template <class T, template <class ...> class ...Ks_> concept tag_infixed_q = tab_infixed_q<T, tag<Ks_>...>;

template <template <class ...> class K_, class ...Ts> concept       tag_as_p =       tab_as_p<tag<K_>, Ts...>;
template <template <class ...> class K_, class ...Ts> concept tag_affixed_p = tab_affixed_p<tag<K_>, Ts...>;
template <template <class ...> class K_, class ...Ts> concept       tag_in_p =       tab_in_p<tag<K_>, Ts...>;
template <template <class ...> class K_, class ...Ts> concept tag_infixed_p = tab_infixed_p<tag<K_>, Ts...>;


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
