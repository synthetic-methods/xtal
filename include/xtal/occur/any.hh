#pragma once
#include "../flux/all.hh"// `_retail`

#include "../cell/mark.hh"




XTAL_ENV_(push)
namespace xtal::occur
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

#include "./_retail.ii"
#include "./_detail.ii"


////////////////////////////////////////////////////////////////////////////////

template <class T>
struct define
{
	using subkind = _retail::define<T>;

	template <class S>
	class subtype : public bond::compose_s<S, subkind>
	{
		friend T;
		using S_ = bond::compose_s<S, subkind>;
	
	public:
		using S_::S_;

		XTAL_CON_(explicit) subtype(size_t u)
		XTAL_0EX
		{
			assert(0 == u);
		};
		template <nominal_q U>
		XTAL_CON_(explicit) subtype(U &&u)
		XTAL_0EX
		{
			assert(0 == u);
		};

		///\
		Forwards anything prefixed with `N_mask`. \

		template <int N_mask=-1>
		struct address
		{
			static constexpr size_t M_mask =  N_mask;
			static constexpr size_t W_mask = ~M_mask;
			
			template <_retail::any_q R>
			class subtype : public bond::compose_s<R>
			{
				using R_ = bond::compose_s<R>;
			
			public:
				using R_::R_;
				using R_::self;
				using R_::influx;

				XTAL_TNX influx(cell::mark_s<T> o, auto &&...oo)
				XTAL_0EX
				{
					return self().influx(o.head(), o.then(), XTAL_REF_(oo)...);
				}
				XTAL_TNX influx(cell::mark_s<> m, auto &&...oo)
				XTAL_0EX
				{
					if (~m & M_mask) {
						return R_::influx();
					}
					else if (m &= W_mask) {
						return R_::influx(m, XTAL_REF_(oo)...);
					}
					else {
						return R_::influx(XTAL_REF_(oo)...);
					}
				}

			};
		};
		///\
		Attaches `T` as a member of `this`. \

		template <int N_mask=-1>
		struct attach
		:	bond::compose<address<N_mask>, typename S_::template afflux<>>
		{
		};
		///\
		Attaches `T` as a member of `this`, appending it to the arguments used to `defunctor` `functor<auto ...>`. \

		template <int N_mask=-1>
		struct dispatch
		{
			using subkind = attach<N_mask>;
			
			template <_retail::any_q R> requires bond::assay_q<T>
			class subtype : public bond::compose_s<R, subkind>
			{
				using R_ = bond::compose_s<R, subkind>;
				using K_ = typename R_::template head_t<>;
			
			public:
				using R_::R_;
				using R_::self;
				using R_::head;

				XTAL_TO2_(XTAL_DEF_(return,inline)
				XTAL_LET operator () (auto &&...xs),
					(self().*defunctor<decltype(xs)...>()) (XTAL_REF_(xs)...)
				)

				XTAL_TO4_(template <class ...Xs>
				XTAL_DEF_(return,inline)
				XTAL_REF refunctor(nominal_q auto const ...Is),
					//\
					_std::bind_front(defunctor<Xs...>(Is...), &self())
					[this, Is...] (auto &&...xs) XTAL_0FN_((self().*defunctor<Xs...>(Is...)) (XTAL_REF_(xs)...))
				)

			protected:
				template <class ...Xs>
				XTAL_DEF_(return,inline)
				XTAL_REF defunctor(nominal_q auto const &...Is)
				XTAL_0FX
				{
					return defunctor(figure<Xs...>::template type<Is...>::value);
				}
				template <class A>
				XTAL_DEF_(return,inline)
				XTAL_REF defunctor(_std::array<A, T::size()> const &value)
				XTAL_0FX
				{
					static_assert(1 == bond::operating::bit_count_f(T::size()));
					size_t i = head(); i &= (T::size() - 1);
					return R_::defunctor(value[i]);
				}

				template <class ...Xs>
				struct figure
				{
					template <auto ...Is>
					class type
					{
						template <size_t ...I>
						XTAL_DEF_(static)
						XTAL_LET enumerate_f(bond::seek_t<I...>)
						XTAL_0EX
						{
							using context = typename R_::template figure<Xs...>;
							return _std::array {(context::template type<Is..., I>::value)...};
						}
					
					public:
						XTAL_DEF_(static)
						XTAL_LET value      = enumerate_f(bond::seek_s<T::size()> {});
						XTAL_USE value_type = decltype(value);
					
					};
				};

			};
		};
		///\
		Assigns `T`, allowing update via `influx` and aggregated inspection via `efflux`. \
		
		template <int N_mask=-1>
		struct expect
		{
			using subkind = attach<N_mask>;
			
			template <_retail::any_q R>
			class subtype : public bond::compose_s<R, subkind>
			{
				using R_ = bond::compose_s<R, subkind>;
			
			public:
				using R_::R_;
				
				XTAL_TNX effuse(auto &&o)
				XTAL_0EX
				{
					if constexpr (is_q<T, decltype(o)>) {
						return R_::heading(XTAL_REF_(o));
					}
					else {
						return R_::effuse(XTAL_REF_(o));
					}
				}

			};
		};
		///\
		Assigns `T`, allowing update via `efflux` aggregated inspection via `influx`. \

		template <int N_mask=-1>
		struct inspect
		{
			using subkind = attach<N_mask>;
			
			template <_retail::any_q R>
			class subtype : public bond::compose_s<R, subkind>
			{
				using R_ = bond::compose_s<R, subkind>;
			
			public:
				using R_::R_;

				XTAL_TNX infuse(auto &&o)
				XTAL_0EX
				{
					if constexpr (is_q<T, decltype(o)>) {
						return R_::heading(XTAL_REF_(o));
					}
					else {
						return R_::infuse(XTAL_REF_(o));
					}
				}

			};
		};
		///\
		Uses the current `T` as the return value of `functor`. \
		
		template <int N_mask=-1>
		struct poll
		{
			using subkind = attach<N_mask>;
			
			template <_retail::any_q R>
			class subtype : public bond::compose_s<R, subkind>
			{
				using R_ = bond::compose_s<R, subkind>;
			
			public:
				using R_::R_;
				using R_::head;

				XTAL_DEF_(return,inline)
				XTAL_LET functor()
				XTAL_0FX
				{
					return head();
				}

			};
		};

	};
};
template <class T>
struct refine
:	_retail::refine<T>
{
};


////////////////////////////////////////////////////////////////////////////////

template <class U>
struct defer
:	_retail::defer<U>
{
};
template <class U>
struct refer
:	_retail::refer<U>
{
};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
