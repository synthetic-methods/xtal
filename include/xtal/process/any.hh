#pragma once
#include "../bond.hh"
#include "../flow/any.hh"// `_retail`
#include "../flow/bundle.hh"
#include "../occur/all.hh"
#include "../provision/all.hh"
#include "../schedule/all.hh"

XTAL_ENV_(push)
namespace xtal::process
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

namespace _retail = xtal::flow;
#include "./_entail.ii"
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
	public:
		///\brief\
		Addresses the function pointer for the given types `Xs...` and indicies `Is...`, \
		providing the kernel for the dispatch-table constructed with `occur/any.hh#dispatch`. \

		///\todo\
		Incorporate receiver at the front of `Xs...` to provide both `const` and non-`const` invocation. \

		template <class ...Xs>
		struct digest
		{
		private:
			template <auto ...Is>
			struct solve
			{
				using type =    decltype(XTAL_ANY_(T const &).template divert<Is...>(XTAL_ANY_(Xs)...)) (T::*) (Xs...) const;

			};
			template <auto ...Is>
			requires XTAL_TRY_(unless) (XTAL_ANY_(T const &).template divert<Is...>(XTAL_ANY_(Xs)...))
			struct solve<Is...>
			{
				using type =    decltype(XTAL_ANY_(T       &).template divert<Is...>(XTAL_ANY_(Xs)...)) (T::*) (Xs...);

			};
		
		public:
			template <auto ...Is>
			class index
			{
			public:
				using point_type = typename solve<Is...>::type;
				static auto constexpr point = static_cast<point_type>(&T::template divert<Is...>);

			};
		};
		///\brief\
		Provides a layer of indirection separating the types submitted/visible to `digest`, \
		and those received by `method`. \
		
		template <auto ...Is>
		XTAL_DEF_(return,inline,let)
		divert(auto &&...xs)
		noexcept -> decltype(auto)
			requires (0 == sizeof...(Is)) and requires (T       &t) {t.         method       (XTAL_REF_(xs)...);}
			or       (1 <= sizeof...(Is)) and requires (T       &t) {t.template method<Is...>(XTAL_REF_(xs)...);}
		{
			XTAL_IF0
			XTAL_0IF (0 == sizeof...(Is))               {return self().         method       (XTAL_REF_(xs)...);}
			XTAL_0IF (1 <= sizeof...(Is))               {return self().template method<Is...>(XTAL_REF_(xs)...);}
		}
		template <auto ...Is>
		XTAL_DEF_(return,inline,let)
		divert(auto &&...xs) const
		noexcept -> decltype(auto)
			requires (0 == sizeof...(Is)) and requires (T const &t) {t.         method       (XTAL_REF_(xs)...);}
			or       (1 <= sizeof...(Is)) and requires (T const &t) {t.template method<Is...>(XTAL_REF_(xs)...);}
		{
			XTAL_IF0
			XTAL_0IF (0 == sizeof...(Is))               {return self().         method       (XTAL_REF_(xs)...);}
			XTAL_0IF (1 <= sizeof...(Is))               {return self().template method<Is...>(XTAL_REF_(xs)...);}
		}

		///\brief a pointer to the digested `method` for the given parameters. \

		XTAL_DEF_(return,inline,let)
		deify(auto const &point) const
		noexcept -> decltype(auto)
		{
			return point;
		}
		template <class ...Xs>
		XTAL_DEF_(return,inline,let)
		deify(constant_q auto ...Is) const
		noexcept -> decltype(auto)
		{
			return deify(digest<Xs...>::template index<Is...>::point);
		}

	public:// OPERATE
		using S_::self;

		///\returns the lambda abstraction of `operator()`. \

		XTAL_FX2_(do) (template <class ...Xs>
		XTAL_DEF_(return,inline,let)
		reify(constant_q auto ...is),
		noexcept -> decltype(auto)
		{
			if constexpr (same_q<typename T::template digest<Xs...>, digest<Xs...>>) {
				return [this] XTAL_1FN_(function) (self().template operator()<decltype(is){}...>);
			}
			else {
				//\
				return [this, deity=self().template deify<Xs...>(is...)] XTAL_1FN_(function) ((self().*deity));
				return _std::bind_front(self().template deify<Xs...>(is...), &self());
			}
		})

		///\returns the result of applying `method`, with `dispatch`ed parameters resolved. \
		
		XTAL_FX2_(do) (template <auto ...Is>
		XTAL_DEF_(return,inline,let)
		operator() (auto &&...xs),
		noexcept -> decltype(auto)
		{
			if constexpr (same_q<typename T::template digest<decltype(xs)...>, digest<decltype(xs)...>>) {
				XTAL_IF0
				XTAL_0IF_(to) (self().template method<Is...>(XTAL_REF_(xs)...))
				XTAL_0IF_(to) (self().         method       (XTAL_REF_(xs)...))
			}
			else {
				auto &s = self();
				auto  d = self().template deify<decltype(xs)...>(constant_t<Is>{}...);
				return (s.*d) (XTAL_REF_(xs)...);
			}
		})
		
		///\returns the outcome of the current process (if defined), \
		or the result of applying the `static method_f` (only when `this` is `const`). \

		template <auto ...Is>
		XTAL_DEF_(return,inline,set)
		method(auto &&...xs) noexcept
		XTAL_TRY_(to) (T::template method_f<Is...>(XTAL_REF_(xs)...))

	public:
		///\
		Thunkifies the underlying `T` by capturing the arguments `Xs...`. \

		template <class ...Xs> requires any_q<Xs...>
		struct binding
		{
			using superkind = bond::compose<void
			,	defer<T>
			,	flow::bundle<Xs...>
			>;
			template <class R>
			class subtype : public bond::compose_s<R, superkind>
			{
				static_assert(any_q<R>);
				using R_ = bond::compose_s<R, superkind>;

			public:// CONSTRUCT
				using R_::R_;
				///\
				Initialize `arguments` using the arguments supplied. \

				XTAL_NEW_(explicit)
				subtype(Xs &&...xs)
				noexcept
				:	subtype(T{}, XTAL_REF_(xs)...)
				{}
				XTAL_NEW_(explicit)
				subtype(fungible_q<S_> auto &&t, Xs &&...xs)
				noexcept
				:	R_(XTAL_REF_(t), XTAL_REF_(xs)...)
				{}

			public:// ACCESS
				using R_::arguments;

				using process_type = T;
				XTAL_FX4_(to) (XTAL_DEF_(return,inline,get) process(), S_::head())


			public:// OPERATE
				using R_::method;
				///\
				Evaluates the lifted `method` using the bound arguments. \

				XTAL_FX2_(do) (template <auto ...Is>
				XTAL_DEF_(return,inline,let)
				method(auto &&...xs),
				noexcept -> decltype(auto)
				{
					auto constexpr M = sizeof...(Xs);
					auto constexpr N = sizeof...(xs);
					XTAL_IF0
					XTAL_0IF (M == N) {return R_::template method<Is...>(XTAL_REF_(xs) ()...);}
					XTAL_0IF (0 == N) {return arguments([this] XTAL_1FN_(function) (method));}
					XTAL_0IF_(terminate)
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
		struct binding
		{
			//\
			using superkind = confined<typename S_::template binding<typename S_::template bracelet<Xs>::type...>>;
			using superkind = confined<typename S_::template binding<process::let_t<Xs>...>>;

			template <class R>
			using subtype = bond::compose_s<R, superkind>;
			using    type = subtype<S_>;

		};
		template <class ...Xs>
		using    bind_t = typename binding<Xs...>::type;

		XTAL_DEF_(return,inline,set)
		bind_f(auto &&...xs)
		noexcept -> decltype(auto)
		{
			return bind_t<decltype(xs)...>(XTAL_REF_(xs)...);
		}
		XTAL_DEF_(return,inline,set)
		bind_f(same_q<T> auto &&t, auto &&...xs)
		noexcept -> decltype(auto)
		{
			return bind_t<decltype(xs)...>(XTAL_REF_(t), XTAL_REF_(xs)...);
		}
		
		XTAL_FX4_(to) (template <class ...Xs>
		XTAL_DEF_(return,inline,get) bind(Xs &&...xs), bind_f(S_::self(), XTAL_REF_(xs)...))

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

		template <auto ...Is>
		XTAL_DEF_(return,inline,set) S_method_f(auto &&...xs)
		noexcept -> decltype(auto)
		requires XTAL_TRY_(to)
			(S_::template method_f<Is...>(S::template method_f<Is...>(XTAL_REF_(xs)...)))

	public:// CONSTRUCT
		using S_::S_;

	public:// OPERATE
		///\
		Resolves `head` as either a function or value, \
		composed with the inherited `method` if the parent is a `defer`red `process`. \

		template <auto ...Is>
		XTAL_DEF_(return,inline,set)
		method_f(auto &&...xs)
		noexcept -> decltype(auto)
		requires XTAL_TRY_(to) (S_method_f<Is...>(XTAL_REF_(xs)...))

		template <auto ...Is>
		XTAL_DEF_(return,inline,set)
		method(auto &&...xs)
		noexcept -> decltype(auto)
		requires XTAL_TRY_(to) (S_method_f<Is...>(XTAL_REF_(xs)...))

		XTAL_FX2_(do) (template <auto ...Is>
		XTAL_DEF_(return,inline,let)
		method(auto &&...xs),
		noexcept -> decltype(auto)
		requires XTAL_TRY_(unless) (S_method_f<Is...>(XTAL_REF_(xs)...))
		{
			return S_::template method<Is...>(S::template method<Is...>(XTAL_REF_(xs)...));
		})

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
