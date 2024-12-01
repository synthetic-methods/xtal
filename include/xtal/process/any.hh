#pragma once
#include "../flux/any.hh"// `_retail`

#include "../flux/bundle.hh"
#include "../occur/all.hh"
#include "../resource/all.hh"
#include "../schedule/all.hh"

XTAL_ENV_(push)
namespace xtal::process
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

#include "./_retail.ii"
#include "./_detail.ii"

namespace _detail
{///////////////////////////////////////////////////////////////////////////////

template <class T> concept invaluable_q = _std::is_trivially_copyable_v<_std::remove_cvref_t<T>> and     _std::is_trivially_constructible_v<_std::remove_cvref_t<T>>;
template <class T> concept   valuable_q = _std::is_trivially_copyable_v<_std::remove_cvref_t<T>> and not _std::is_trivially_constructible_v<_std::remove_cvref_t<T>>;


}///////////////////////////////////////////////////////////////////////////////

template <class T>
struct define
{
	using superkind = _retail::define<T>;

	template <any_q S>
	class subtype : public bond::compose_s<S, superkind>
	{
		friend T;
		
		using S_ = bond::compose_s<S, superkind>;
		using T_ = typename S_::self_type;
	
	public:// CONSTRUCT
		using S_::S_;

	protected:// DIGEST
		///\brief\
		Addresses the function pointer for the given types `Xs...` and indicies `Is...`, \
		providing the kernel for the dispatch-table constructed with `occur/any.hh#dispatch`. \

		template <class ...Xs>
		struct digest
		{
			template <auto ...Is>
			class index
			{
				using Y = decltype(XTAL_ANY_(T &).template divest<Is...>(XTAL_ANY_(Xs)...));

			public:
				using point_type = Y (T::*) (Xs...);
				static_assert(not _std::is_const_v<point_type>);
				
				static constexpr point_type point = &T::template divest<Is...>;

			};
			template <auto ...Is>
				requires XTAL_TRY_(XTAL_ANY_(T const &).template divest<Is...>(XTAL_ANY_(Xs)...))
			class index<Is...>
			{
				using Y = decltype(XTAL_ANY_(T const &).template divest<Is...>(XTAL_ANY_(Xs)...));

			public:
				using point_type = _std::add_const_t<Y (T::*) (Xs...) const>;
				static_assert(_std::is_const_v<point_type>);
				
				XTAL_SET point = static_cast<point_type>(&T::template divest<Is...>);

			};
		};
		///\brief\
		Provides a layer of indirection separating the types submitted/visible to `digest`, \
		and those received by `method`. \
		
		template <auto ...Is>
		XTAL_DEF_(return,inline)
		XTAL_LET divest(auto &&...xs)
		noexcept -> decltype(auto)
			requires (none_n<Is...> and XTAL_TRY_(XTAL_ANY_(T        ).         method       (XTAL_REF_(xs)...)))
			or       (some_n<Is...> and XTAL_TRY_(XTAL_ANY_(T        ).template method<Is...>(XTAL_REF_(xs)...)))
		{
			XTAL_IF0
			XTAL_0IF (none_n<Is...>)                    {return self().         method       (XTAL_REF_(xs)...);}
			XTAL_0IF (some_n<Is...>)                    {return self().template method<Is...>(XTAL_REF_(xs)...);}
		}
		template <auto ...Is>
		XTAL_DEF_(return,inline)
		XTAL_LET divest(auto &&...xs)
		XTAL_0FX -> decltype(auto)
			requires (none_n<Is...> and XTAL_TRY_(XTAL_ANY_(T const &).         method       (XTAL_REF_(xs)...)))
			or       (some_n<Is...> and XTAL_TRY_(XTAL_ANY_(T const &).template method<Is...>(XTAL_REF_(xs)...)))
		{
			XTAL_IF0
			XTAL_0IF (none_n<Is...>)                    {return self().         method       (XTAL_REF_(xs)...);}
			XTAL_0IF (some_n<Is...>)                    {return self().template method<Is...>(XTAL_REF_(xs)...);}
		}

		///\brief a pointer to the digested `method` for the given parameters. \

		XTAL_DEF_(return,inline)
		XTAL_LET deify(auto const &point)
		XTAL_0FX -> decltype(auto)
		{
			return point;
		}
		template <class ...Xs>
		XTAL_DEF_(return,inline)
		XTAL_LET deify(nominal_q auto ...Is)
		XTAL_0FX -> decltype(auto)
		{
			return deify(digest<Xs...>::template index<XTAL_VAL_(Is)...>::point);
		}

	public:// OPERATE
		using S_::self;

		///\returns the lambda abstraction of `operator()`. \

		XTAL_DO2_(template <class ...Xs>
		XTAL_DEF_(return,inline)
		XTAL_LET reify(nominal_q auto ...Is)
		,	-> decltype(auto)
		{
			return [this] XTAL_1FN_(self().template operator()<XTAL_VAL_(Is)...>);
		})

		///\returns the result of applying `method`, with `dispatch`ed parameters resolved. \
		
		XTAL_DO2_(template <auto ...Is>
		XTAL_DEF_(return,inline)
		XTAL_LET operator() (auto &&...xs)
		,	->	decltype(auto)
		{
			XTAL_IF0
			XTAL_0IF XTAL_TRY_TO_(self().template method<Is...>(XTAL_REF_(xs)...))
			XTAL_0IF XTAL_TRY_TO_(self().         method       (XTAL_REF_(xs)...))
		})
		
		///\returns the outcome of the current process (if defined), \
		or the result of applying the `function` (only when `this` is `const`). \

		template <auto ...Is>
		XTAL_DEF_(return,inline)
		XTAL_LET method(auto &&...xs)
		XTAL_0FX -> decltype(auto)
			requires (none_n<Is...> and XTAL_TRY_(T::         function       (XTAL_REF_(xs)...)))
			or       (some_n<Is...> and XTAL_TRY_(T::template function<Is...>(XTAL_REF_(xs)...)))
		{
			XTAL_IF0
			XTAL_0IF (none_n<Is...>)      {return T::         function       (XTAL_REF_(xs)...);}
			XTAL_0IF (some_n<Is...>)      {return T::template function<Is...>(XTAL_REF_(xs)...);}
		}

	public:
		///\
		Thunkifies the underlying `T` by capturing the arguments `Xs...`. \

		template <class ...Xs> requires any_q<Xs...>
		struct bracket
		{
			using superkind = bond::compose<void
			,	defer<T_>
			,	flux::bundle<Xs...>
			>;
			template <any_q R>
			class subtype : public bond::compose_s<R, superkind>
			{
				using R_ = bond::compose_s<R, superkind>;

				using H0_ = typename R_::template head_t<nominal_t<0>>;
				using H1_ = typename R_::template head_t<nominal_t<1>>;

			public:// CONSTRUCT
				using R_::R_;
				///\
				Initialize `slots` using the arguments supplied. \

				XTAL_CON_(explicit) subtype(Xs &&...xs)
				noexcept
				:	subtype(T{}, XTAL_REF_(xs)...)
				{}
				XTAL_CON_(explicit) subtype(fungible_q<S_> auto &&t, Xs &&...xs)
				noexcept
				:	R_(XTAL_REF_(t), H1_(XTAL_REF_(xs)...))
				{}

			public:// OPERATE
				using R_::slots;
				using R_::method;
				///\
				Evaluates the lifted `method` using the bound slots. \

				XTAL_DO2_(template <auto ...Is>
				XTAL_DEF_(return,inline)
				XTAL_LET method(auto &&...xs), -> decltype(auto)
				{
					XTAL_LET M = sizeof...(Xs);
					XTAL_LET N = sizeof...(xs);
					XTAL_IF0
					XTAL_0IF (M == N) {return R_::template method<Is...>(XTAL_REF_(xs) ()...);}
					XTAL_0IF (0 == N) {return         slots().apply([this] XTAL_1FN_(method));}
				})

			};
		};
		template <class U>
		using bracelet = process::let<U>;

	};
};

template <class T>
struct refine
{
	using superkind = _retail::refine<T>;

	template <any_q S>
	class subtype : public bond::compose_s<S, superkind>
	{
		using S_ = bond::compose_s<S, superkind>;
	
	public:// CONSTRUCT
		using S_::S_;

	public:// BRACKET
		template <class ...Xs>
		struct bracket
		{
			//\
			using superkind = confined<typename S_::template bracket<typename S_::template bracelet<Xs>::type...>>;
			using superkind = confined<typename S_::template bracket<process::let_t<Xs>...>>;

			template <class R>
			using subtype = bond::compose_s<R, superkind>;
			using    type = subtype<S_>;

		};
		template <class ...Xs>
		XTAL_USE bind_t = typename bracket<Xs...>::type;

		XTAL_DEF_(return,inline)
		XTAL_SET bind_f(auto &&...xs)
		noexcept -> decltype(auto)
		{
			return bind_t<decltype(xs)...>(XTAL_REF_(xs)...);
		}
		XTAL_DEF_(return,inline)
		XTAL_SET bind_f(XTAL_ARG_(T) &&t, auto &&...xs)
		noexcept -> decltype(auto)
		{
			return bind_t<decltype(xs)...>(XTAL_REF_(t), XTAL_REF_(xs)...);
		}
		
		XTAL_DO4_(template <class ...Xs>
		XTAL_DEF_(return,inline)
		XTAL_LET rebound(Xs &&...xs), -> decltype(auto)
		{
			return bind_f(S_::self(), XTAL_REF_(xs)...);
		})

	};
};


////////////////////////////////////////////////////////////////////////////////

template <class U>
struct defer
{
	using superkind = _retail::defer<U>;

	template <any_q S>
	class subtype : public bond::compose_s<S, superkind>
	{
		using S_ = bond::compose_s<S, superkind>;
		using T_ = typename S_::self_type;
		using U0 = typename S_::template head_t<nominal_t<0>>;
		using U1 = typename S_::template head_t<nominal_t<1>>;
	
		///\
		Resolves `head` as either a function or value. \

		///\note\
		The value of `head` is only returned. \

		XTAL_DO2_(template <auto ...Is>
		XTAL_DEF_(return,inline)
		XTAL_LET map_method(auto &&...xs),
		->	decltype(auto)
		{
			XTAL_IF0
			XTAL_0IF XTAL_TRY_TO_(S_::head().template operator()<Is...>(XTAL_REF_(xs)...))
			XTAL_0IF XTAL_TRY_TO_(S_::head()                           (XTAL_REF_(xs)...))
			XTAL_0IF XTAL_TRY_TO_(S_::head())
			XTAL_0IF_(void)
		})
		XTAL_DO0_(template <auto ...Is>
		XTAL_DEF_(return,inline)
		XTAL_SET map_function(auto &&...xs),
		->	decltype(auto)
		{
			XTAL_IF0
			XTAL_0IF (any_q<U0>) {return U0::template function<Is...>(XTAL_REF_(xs)...);}
			XTAL_0IF_(else)      {return U0{}                        (XTAL_REF_(xs)...);}
		})

	public:// FUNC*

		///\
		Resolves `head` as either a function or value, \
		composed with the inherited `method` or `function` if `defer`red. \

		///\note\
		Only `method`s participate in parameter resolution. \

		template <auto ...Is>
		XTAL_DEF_(return,inline)
		XTAL_LET method(auto &&...xs)
		noexcept -> decltype(auto)
		{
			return map_method<Is...>(XTAL_REF_(xs)...);
		}
		template <auto ...Is>
		XTAL_DEF_(return,inline)
		XTAL_LET method(auto &&...xs) const
		noexcept -> decltype(auto)
		{
			return map_method<Is...>(XTAL_REF_(xs)...);
		}

		template <auto ...Is> requires any_q<U1>
		XTAL_DEF_(return,inline)
		XTAL_LET method(auto &&...xs)
		noexcept -> decltype(auto)
		requires in_n<XTAL_TRY_(XTAL_ANY_(S       &).template method<Is...>(XTAL_REF_(xs)...))>
		{
			return map_method<Is...>(S::template method<Is...>(XTAL_REF_(xs)...));
		}
		template <auto ...Is> requires any_q<U1>
		XTAL_DEF_(return,inline)
		XTAL_LET method(auto &&...xs) const
		noexcept -> decltype(auto)
		requires in_n<XTAL_TRY_(XTAL_ANY_(S const &).template method<Is...>(XTAL_REF_(xs)...))>
		{
			return map_method<Is...>(S::template method<Is...>(XTAL_REF_(xs)...));
		}

		template <auto ...Is>
		XTAL_DEF_(return,inline)
		XTAL_SET function(auto &&...xs)
		noexcept -> decltype(auto)
		requires un_n<XTAL_TRY_(S::template function<Is...>(XTAL_REF_(xs)...))>
		and XTAL_TRY_TO_(map_function<Is...>(XTAL_REF_(xs)...))

		template <auto ...Is>
		XTAL_DEF_(return,inline)
		XTAL_SET function(auto &&...xs)
		noexcept -> decltype(auto)
		requires in_n<XTAL_TRY_(S::template function<Is...>(XTAL_REF_(xs)...))>
		and XTAL_TRY_TO_(map_function<Is...>(S::template function<Is...>(XTAL_REF_(xs)...)))

	public:// CONSTRUCT
		using S_::S_;

	};
};

template <class U>
struct refer
:	_retail::refer<U>
{
};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
