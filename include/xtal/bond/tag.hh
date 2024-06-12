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
	using subkind = tab<tag<Y>>;

	template <class S>
	class subtype : public compose_s<S, subkind>
	{
		using S_ = compose_s<S, subkind>;
	
	public:
		using S_::S_;

		template <class ...Xs>
		struct tagged
		{
			template <class R>
			using subtype = Y<Xs...>;

		};
//		template <class ...Xs> requires compose_q<Y<Xs...>>
//		struct tagged<Xs...>
//		:	Y<Xs...>
//		{
//		};
		template <class ...Xs>
		using tagged_t = compose_s<S, tagged<Xs...>>;

	};
};

template <class T, template <class ...> class ...Ys> XTAL_TYP tail_tag   :          tail_tab<T, tag<Ys>...>     {};
template <class T, template <class ...> class ...Ys> XTAL_USE tail_tag_t = typename tail_tab<T, tag<Ys>...>:: type;
template <class T, template <class ...> class ...Ys> XTAL_REQ tail_tag_q =          tail_tab<T, tag<Ys>...>::value;

template <class T, template <class ...> class ...Ys> XTAL_REQ head_tag_q = _std::conjunction_v<tail_tag<based_t<T >, Ys>...>;
template <template <class ...> class Y, class ...Ts> XTAL_REQ head_tag_p = _std::conjunction_v<tail_tag<based_t<Ts>, Y >...>;


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
