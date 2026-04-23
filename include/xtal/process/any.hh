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

/*!
\brief   Extends `flow::define` with `method`-_vtables_ and `binding`.
*/
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

	//\
	protected:// DIGEST
	public:// DIGEST
		/*!
		\brief  	Initializes the VTable constructed with `occur/any.hh#dispatch`.
		\todo    Incorporate receiver at the front of `Xs...` to provide both `const` and non-`const` invocation.
		*/
		template <class ...Xs>
		struct digest
		{
		private:
			template <auto ...Ns>
			struct solve
			{
				using type =   decltype(XTAL_ANY_(T const &).template digress<Ns...>(XTAL_ANY_(Xs)...)) (T::*) (Xs...) const;

			};
			template <auto ...Ns>
			requires XTAL_TRY_(to_if) (XTAL_ANY_(T       &).template digress<Ns...>(XTAL_ANY_(Xs)...))
			struct solve<Ns...>
			{
				using type =   decltype(XTAL_ANY_(T       &).template digress<Ns...>(XTAL_ANY_(Xs)...)) (T::*) (Xs...);

			};
		
		public:
			template <auto ...Ns>
			class index
			{
			public:
				using point_type = typename solve<Ns...>::type;
				static auto constexpr point = static_cast<point_type>(&T::template digress<Ns...>);
				///<\brief Addresses the function pointer for the given types `Xs...` and indicies `Ns...`.

			};
		};
		/*!
		\brief  	Unifies the argument-types of the caller and callee
		         (respectively bound by `digest<Xs...>` and `method(auto &&xs...)`).
		*/
		template <auto ...Ns>
		XTAL_DEF_(return,inline,let)
		digress(auto &&...xs)
		noexcept -> decltype(auto)
			requires  none_v<Ns...> and requires (T       &t) {t.         method       (XTAL_REF_(xs)...);}
			or        some_v<Ns...> and requires (T       &t) {t.template method<Ns...>(XTAL_REF_(xs)...);}
		{
			XTAL_IF0
			XTAL_0IF (none_v<Ns...>)               {return self().         method       (XTAL_REF_(xs)...);}
			XTAL_0IF (some_v<Ns...>)               {return self().template method<Ns...>(XTAL_REF_(xs)...);}
		}
		template <auto ...Ns>
		XTAL_DEF_(return,inline,let)
		digress(auto &&...xs) const
		noexcept -> decltype(auto)
			requires  none_v<Ns...> and requires (T const &t) {t.         method       (XTAL_REF_(xs)...);}
			or        some_v<Ns...> and requires (T const &t) {t.template method<Ns...>(XTAL_REF_(xs)...);}
		{
			XTAL_IF0
			XTAL_0IF (none_v<Ns...>)              {return self().         method       (XTAL_REF_(xs)...);}
			XTAL_0IF (some_v<Ns...>)              {return self().template method<Ns...>(XTAL_REF_(xs)...);}
		}

		/*!
		\returns	The provided pointer.
		*/
		XTAL_DEF_(return,inline,let)
		deify(auto const &point) const
		noexcept -> decltype(auto)
		{
			return point;
		}
		/*!
		\returns	A pointer to the digested `method` indexed by the given constants.
		*/
		template <class ...Xs>
		XTAL_DEF_(return,inline,let)
		deify(constant_q auto ...Ns) const
		noexcept -> decltype(auto)
		{
			return deify(digest<Xs...>::template index<Ns...>::point);
		}

	public:// OPERATE
		using S_::self;

		/*!
		\returns	The lambda abstraction of `operator()`.
		*/
		XTAL_FN2_(do) (template <class ...Xs>
		XTAL_DEF_(return,inline,let)
		reify(constant_q auto ...is),
		noexcept -> decltype(auto)
		{
			if constexpr (same_q<typename T::template digest<Xs...>, digest<Xs...>>) {
				return [this] XTAL_1FN_(call) (self().template operator()<decltype(is){}...>);
			}
			else {
				//\
				return [this, deity=self().template deify<Xs...>(is...)] XTAL_1FN_(call) ((self().*deity));
				return _std::bind_front(self().template deify<Xs...>(is...), &self());
			}
		})

		/*!
		\returns	The result of applying `method`, with `dispatch`ed parameters resolved.
		*/
		XTAL_FN2_(do) (template <auto ...Ns>
		XTAL_DEF_(return,inline,let)
		operator() (auto &&...xs),
		noexcept -> decltype(auto)
		{
			if constexpr (same_q<typename T::template digest<decltype(xs)...>, digest<decltype(xs)...>>) {
				XTAL_IF0
				XTAL_0IF_(to) (self().template method<Ns...>(XTAL_REF_(xs)...))
				XTAL_0IF_(to) (self().         method       (XTAL_REF_(xs)...))
			}
			else {
				auto const _method = self().template deify<decltype(xs)...>(constant_t<Ns>{}...);
				return (self().*_method) (XTAL_REF_(xs)...);
			}
		})
		
	public:
		/*!
		\brief  	Thunkifies the underlying `T` by capturing the arguments `Xs...`.
		*/
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
				using R_::R_;//NOTE: Inherited and respecialized!
				/*!
				\brief  	Initialize `arguments` using those supplied.
				*/
				XTAL_NEW_(explicit)
				subtype(Xs &&...xs)
				noexcept
				:	subtype{T{}, XTAL_REF_(xs)...}
				{}
				XTAL_NEW_(explicit)
				subtype(fungible_q<S_> auto &&t, Xs &&...xs)
				noexcept
				:	R_(XTAL_REF_(t), XTAL_REF_(xs)...)
				{}

			public:// ACCESS
				using R_::arguments;

				using process_type = T;

				XTAL_FN1_(go) (XTAL_DEF_(return,inline,get) process, [] (auto &&o, auto &&...oo)
				XTAL_0FN_(to) (XTAL_REF_(o).head(XTAL_REF_(oo)...)))

			public:// OPERATE
				using R_::method;
				/*!
				\brief  	Evaluates the lifted `method` using the bound arguments.
				*/
				XTAL_FN2_(do) (template <auto ...Ns>
				XTAL_DEF_(return,inline,let)
				method(auto &&...xs),
				noexcept -> decltype(auto)
				{
					XTAL_IF0
					XTAL_0IF (sizeof...(Xs) == sizeof...(xs)) {return R_::template method<Ns...>(XTAL_REF_(xs) ()...);}
					XTAL_0IF (zero          == sizeof...(xs)) {return arguments([this] XTAL_1FN_(call) (method));}
					XTAL_0IF_(void)
				})

			};
		};

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
		struct combined   : confined<typename S_::template binding<Xs...>> {};

		template <class ...Xs>
		using  combined_t = bond::compose_s<S_, combined<Xs...>>;


		template <class ...Xs>
		using    bind_t = combined_t<process::let_t<Xs>...>;

		template <class ...Xs>
		using    bind_x = bind_t<bond::transpack_t<Xs>...>;

		XTAL_DEF_(return,inline,set)
		bind_f(auto &&...xs)
		noexcept -> auto
		{
			return bind_t<decltype(xs)...>{XTAL_REF_(xs)...};
		}
		XTAL_DEF_(return,inline,set)
		bind_f(same_q<T> auto &&t, auto &&...xs)
		noexcept -> auto
		{
			return bind_t<decltype(xs)...>{XTAL_REF_(t), XTAL_REF_(xs)...};
		}
		XTAL_FN1_(go) (template <class ...Xs> XTAL_DEF_(return,inline,get) bind, bind_f)

	};
};


////////////////////////////////////////////////////////////////////////////////

template <class U>
struct defer
{
	using superkind = _retail::defer<U>;

	template <class S>
	class subtype : public bond::compose_s<S, superkind>
	{
		static_assert(any_q<S>);
		using S_ = bond::compose_s<S, superkind>;

		using Head = typename S_::head_type;
		static_assert(complete_q<Head>);

	public:// CONSTRUCT
		using S_::S_;

	public:// ACCESS
		using S_::self;
		using S_::head;

	public:// OPERATE
		/*!
		\brief  	Resolves `head` as either a value or function.
		*/
		XTAL_FN2_(do) (template <auto ...Ns>
		XTAL_DEF_(return,inline,let)
		method(auto &&...xs),
		noexcept -> decltype(auto)
		{
			XTAL_IF0
			XTAL_0IF (1 <= sizeof...(Ns)) {
				XTAL_IF0
				XTAL_0IF_(to) (head().template operator()<Ns...>(XTAL_REF_(xs)...))
				XTAL_0IF_(to) (head().template method    <Ns...>(XTAL_REF_(xs)...))
				XTAL_0IF_(void)
			}
			XTAL_0IF (0 == sizeof...(Ns)) {
				XTAL_IF0
				XTAL_0IF_(to) (head().         operator()       (XTAL_REF_(xs)...))
				XTAL_0IF_(to) (head().         method           (XTAL_REF_(xs)...))
				XTAL_0IF_(to) (head())
				XTAL_0IF_(void)
			}
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
