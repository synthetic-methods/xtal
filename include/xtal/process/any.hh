#pragma once
#include "../flux/any.hh"// `_retail`

#include "../flux/bundle.hh"
#include "../occur/all.hh"
#include "../provision/all.hh"
#include "../schedule/all.hh"

XTAL_ENV_(push)
namespace xtal::process
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

#include "./_retail.ii"
#include "./_detail.ii"

////////////////////////////////////////////////////////////////////////////////

template <class T>
struct define
{
	using superkind = _retail::define<T>;

	template <class S>
	class subtype : public bond::compose_s<S, superkind>
	{
		static_assert(any_q<S>);
		using S_ = bond::compose_s<S, superkind>;
	
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
				using Y = decltype(XTAL_ANY_(T &).template divert<Is...>(XTAL_ANY_(Xs)...));

			public:
				using point_type = Y (T::*) (Xs...);
				static constexpr point_type point = &T::template divert<Is...>;

			};
			template <auto ...Is>
			requires XTAL_TRY_(XTAL_ANY_(T const &).template divert<Is...>(XTAL_ANY_(Xs)...))
			class index<Is...>
			{
				using Y = decltype(XTAL_ANY_(T const &).template divert<Is...>(XTAL_ANY_(Xs)...));

			public:
				using point_type = _std::add_const_t<Y (T::*) (Xs...) const>;// Added `const` for type-reflection...
				XTAL_SET point = static_cast<point_type>(&T::template divert<Is...>);

			};
		};
		///\brief\
		Provides a layer of indirection separating the types submitted/visible to `digest`, \
		and those received by `method`. \
		
		template <auto ...Is>
		XTAL_DEF_(short)
		XTAL_LET divert(auto &&...xs)
		noexcept -> decltype(auto)
			requires (none_n<Is...> and XTAL_TRY_(XTAL_ANY_(T       &).         method       (XTAL_REF_(xs)...)))
			or       (some_n<Is...> and XTAL_TRY_(XTAL_ANY_(T       &).template method<Is...>(XTAL_REF_(xs)...)))
		{
			XTAL_IF0
			XTAL_0IF (none_n<Is...>)                    {return self().         method       (XTAL_REF_(xs)...);}
			XTAL_0IF (some_n<Is...>)                    {return self().template method<Is...>(XTAL_REF_(xs)...);}
		}
		template <auto ...Is>
		XTAL_DEF_(short)
		XTAL_LET divert(auto &&...xs) const
		noexcept -> decltype(auto)
			requires (none_n<Is...> and XTAL_TRY_(XTAL_ANY_(T const &).         method       (XTAL_REF_(xs)...)))
			or       (some_n<Is...> and XTAL_TRY_(XTAL_ANY_(T const &).template method<Is...>(XTAL_REF_(xs)...)))
		{
			XTAL_IF0
			XTAL_0IF (none_n<Is...>)                    {return self().         method       (XTAL_REF_(xs)...);}
			XTAL_0IF (some_n<Is...>)                    {return self().template method<Is...>(XTAL_REF_(xs)...);}
		}

		///\brief a pointer to the digested `method` for the given parameters. \

		XTAL_DEF_(short)
		XTAL_LET deify(auto const &point) const
		noexcept -> decltype(auto)
		{
			return point;
		}
		template <class ...Xs>
		XTAL_DEF_(short)
		XTAL_LET deify(constant_q auto ...Is) const
		noexcept -> decltype(auto)
		{
			return deify(digest<Xs...>::template index<Is...>::point);
		}

	public:// OPERATE
		using S_::self;

		///\returns the lambda abstraction of `operator()`. \

		XTAL_DO2_(template <class ...Xs>
		XTAL_DEF_(short)
		XTAL_LET reify(constant_q auto ...Is),
		noexcept -> decltype(auto)
		{
			return [this] XTAL_1FN_(self().template operator()<XTAL_ALL_(Is)::value...>);
		})

		///\returns the result of applying `method`, with `dispatch`ed parameters resolved. \
		
		XTAL_DO2_(template <auto ...Is>
		XTAL_DEF_(short)
		XTAL_LET operator() (auto &&...xs),
		noexcept -> decltype(auto)
		{
			XTAL_IF0
			XTAL_0IF XTAL_TRY_TO_(self().template method<Is...>(XTAL_REF_(xs)...))
			XTAL_0IF XTAL_TRY_TO_(self().         method       (XTAL_REF_(xs)...))
		})
		
		///\returns the outcome of the current process (if defined), \
		or the result of applying the `function` (only when `this` is `const`). \

		template <auto ...Is>
		XTAL_DEF_(short)
		XTAL_LET method(auto &&...xs) const
		noexcept -> decltype(auto)
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
			,	defer<T>
			,	flux::bundle<Xs...>
			>;
			template <class R>
			class subtype : public bond::compose_s<R, superkind>
			{
				static_assert(any_q<R>);
				using R_ = bond::compose_s<R, superkind>;

			public:// CONSTRUCT
				using R_::R_;
				///\
				Initialize `slots` using the arguments supplied. \

				XTAL_NEW_(explicit) subtype(Xs &&...xs)
				noexcept
				:	subtype(T{}, XTAL_REF_(xs)...)
				{}
				XTAL_NEW_(explicit) subtype(fungible_q<S_> auto &&t, Xs &&...xs)
				noexcept
				:	R_(XTAL_REF_(t), XTAL_REF_(xs)...)
				{}

			public:// ACCESS
				using R_::slots;

				using process_type = T;
				XTAL_TO4_(XTAL_DEF_(alias) process(), S_::head())


			public:// OPERATE
				using R_::method;
				///\
				Evaluates the lifted `method` using the bound slots. \

				XTAL_DO2_(template <auto ...Is>
				XTAL_DEF_(short)
				XTAL_LET method(auto &&...xs),
				noexcept -> decltype(auto)
				{
					XTAL_LET M = sizeof...(Xs);
					XTAL_LET N = sizeof...(xs);
					XTAL_IF0
					XTAL_0IF (M == N) {return R_::template method<Is...>(XTAL_REF_(xs) ()...);}
					XTAL_0IF (0 == N) {return         slots().apply([this] XTAL_1FN_(method));}
					XTAL_0IF_(void)
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

	template <class S>
	class subtype : public bond::compose_s<S, superkind>
	{
		static_assert(any_q<S>);
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
		using    bind_t = typename bracket<Xs...>::type;

		XTAL_DEF_(short,static)
		XTAL_LET bind_f(auto &&...xs)
		noexcept -> decltype(auto)
		{
			return bind_t<decltype(xs)...>(XTAL_REF_(xs)...);
		}
		XTAL_DEF_(short,static)
		XTAL_LET bind_f(XTAL_SYN_(T) auto &&t, auto &&...xs)
		noexcept -> decltype(auto)
		{
			return bind_t<decltype(xs)...>(XTAL_REF_(t), XTAL_REF_(xs)...);
		}
		
		XTAL_TO4_(template <class ...Xs>
		XTAL_DEF_(alias) rebound(Xs &&...xs), bind_f(S_::self(), XTAL_REF_(xs)...))

	};
};


////////////////////////////////////////////////////////////////////////////////

template <class U>
struct defer
{
	using superkind = _detail::invoke_head<_retail::defer<U>>;

	template <class S>
	class subtype : public bond::compose_s<S, superkind>
	{
		static_assert(any_q<S>);
		using S_ = bond::compose_s<S, superkind>;

	public:// CONSTRUCT
		using S_::S_;

	};
	template <class S> requires any_q<typename S::head_type>
	class subtype<S> : public bond::compose_s<S, superkind>
	{
		static_assert(any_q<S>);
		using S_ = bond::compose_s<S, superkind>;

	public:// CONSTRUCT
		using S_::S_;

	public:// OPERATE
		///\
		Resolves `head` as either a function or value, \
		composed with the inherited `method` or `function` if the parent is a `defer`red `process`. \

		XTAL_DO2_(template <auto ...Is>
		XTAL_DEF_(short)
		XTAL_LET method(auto &&...xs),
		noexcept -> decltype(auto)
		{
			return S_::template method<Is...>(S::template method<Is...>(XTAL_REF_(xs)...));
		})
		template <auto ...Is>
		XTAL_DEF_(short,static)
		XTAL_LET function(auto &&...xs)
		noexcept -> decltype(auto)
		requires XTAL_TRY_TO_(S_::template function<Is...>(S::template function<Is...>(XTAL_REF_(xs)...)))

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
