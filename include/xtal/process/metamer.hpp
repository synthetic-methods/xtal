#pragma once
#include "./any.hpp"
#include "../control/any.hpp"





XTAL_ENV_(push)
namespace xtal::process
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
///\
Provides a common substrate for decorating both the immediate `subtype` and that of `binding`.

template <typename ...As>
struct metamer
{
	using subkind = compose<As...>;

	template <any_p S>
	class subtype: public compose_s<S, subkind>
	{
		using S_ = compose_s<S, subkind>;

		template <typename ...Xs>
		using B_ = typename S_::template binding<Xs...>;

	public:
		using S_::S_;

		template <typename ...Xs>
		struct binding: B_<Xs...>
		{
			using rebound = B_<Xs...>;
			using subkind = compose<As..., rebound>;

			template <any_p R>
			class subtype: public compose_s<R, subkind>
			{
				using R_ = compose_s<R, subkind>;

			public:
				using R_::R_;

			};
		};

	};
};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
