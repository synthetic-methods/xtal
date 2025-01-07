#pragma once
#include "./any.hh"
#include "./tab.hh"
#include "./compose.hh"




XTAL_ENV_(push)
namespace xtal::bond
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

template <template <class ...> class Y>
struct tag
{
	using superkind = tab<tag<Y>>;

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
			using hypertype = Y<Xs...>;

		};

	};
};

template <class T, template <class ...> class ...Ys> using    tagged_s = tabbed_s<T, tag<Ys>...>;
template <class T, template <class ...> class ...Ys> concept  tagged_q = tabbed_q<T, tag<Ys>...>;
template <class T, template <class ...> class ...Ys> concept     tag_q =    tab_q<T, tag<Ys>...>;
template <template <class ...> class Y, class ...Ts> concept     tag_p =    tab_p<tag<Y>, Ts...>;


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
