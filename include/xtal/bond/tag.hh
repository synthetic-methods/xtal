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

		template <class ...Xs>
		struct tagged
		{
		//	template <class R>
		//	using subtype = Y<Xs...>;
			using    type = Y<Xs...>;

		};
//		template <class ...Xs> requires compose_q<Y<Xs...>>
//		struct tagged<Xs...>
//		:	Y<Xs...>
//		{
//		};
		template <class ...Xs>
		//\
		using tagged_t = compose_s<S, tagged<Xs...>>;
		using tagged_t = typename tagged<Xs...>::type;

	};
};

template <class T, template <class ...> class ...Ys> XTAL_TYP all_tag   :          all_tab<T, tag<Ys>...>     {};
template <class T, template <class ...> class ...Ys> XTAL_USE all_tag_t = typename all_tab<T, tag<Ys>...>:: type;
template <class T, template <class ...> class ...Ys> XTAL_REQ all_tag_q =          all_tab<T, tag<Ys>...>::value;

template <class T, template <class ...> class ...Ys> XTAL_REQ any_tag_q = _std::conjunction_v<all_tag<based_t<T >, Ys>...>;
template <template <class ...> class Y, class ...Ts> XTAL_REQ any_tag_p = _std::conjunction_v<all_tag<based_t<Ts>, Y >...>;


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
