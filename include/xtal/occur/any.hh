#pragma once
#include "../flux/all.hh"// `_retail`

#include "../flux/mask.hh"




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

	template <any_q S>
	class subtype : public bond::compose_s<S, subkind>
	{
		friend T;
		using S_ = bond::compose_s<S, subkind>;
	
	public:
		using S_::S_;

		XTAL_CON_(explicit) subtype(size_type u)
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
		Attaches `T` as a member of `this`. \

		template <int N_mask=-1>
		struct attach
		:	bond::compose<flux::mask<N_mask>, typename S_::template afflux<>>
		{
		};
		template <int N_mask=-1>
		using  attach_t = confined_t<attach<N_mask>>;

		///\
		Attaches `T` as a member of `this`, appending it to the arguments used to `deify` `method<auto ...>`. \

		template <int N_mask=-1>
		struct dispatch
		{
			using subkind = attach<N_mask>;
			
			template <flux::any_q R>
			class subtype : public bond::compose_s<R, subkind>
			{
				using R_ = bond::compose_s<R, subkind>;
				
				XTAL_SET N_ = T::size() - 0;
				XTAL_SET M_ = T::size() - 1;

				static_assert(0 <= N_);
				static_assert(1 == bond::operating::bit_count_f(N_));

			public:
				using R_::R_;
				using R_::self;
				using R_::head;

				XTAL_DO2_(template <auto ...Is>
				XTAL_DEF_(return,inline)
				XTAL_LET operator() (auto &&...xs), -> decltype(auto)
				{
					return (self().*deify<decltype(xs)...>(Is...)) (XTAL_REF_(xs)...);
				})

				XTAL_DO4_(template <class ...Xs>
				XTAL_DEF_(return,inline)
				XTAL_LET reify(nominal_q auto const ...Is), -> decltype(auto)
				{
					//\
					return _std::bind_front(deify<Xs...>(Is...), &self());
					return [this, Is...] XTAL_1FN_((self().*deify<Xs...>(Is...)));
				})

			protected:
				template <class ...Xs>
				XTAL_DEF_(return,inline)
				XTAL_LET deify(nominal_q auto const &...Is)
				XTAL_0FX -> decltype(auto)
				{
					return deify(figure<Xs...>::template type<Is...>::value);
				}
				template <class A>
				XTAL_DEF_(return,inline)
				XTAL_LET deify(_std::array<A, N_> const &value)
				XTAL_0FX -> decltype(auto)
				{
					size_type i = head(); i &= M_;
					return R_::deify(value[i]);
				}

				template <class ...Xs>
				struct figure
				{
					template <auto ...Is>
					class type
					{
						template <size_type ...I>
						XTAL_DEF_(static)
						XTAL_LET enumerate_f(bond::seek_t<I...>)
						XTAL_0EX
						{
							using context = typename R_::template figure<Xs...>;
							return _std::array{(context::template type<Is..., I>::value)...};
						}
					
					public:
						XTAL_DEF_(static)
						XTAL_LET value      = enumerate_f(bond::seek_s<N_> {});
						XTAL_USE value_type = decltype(value);
					
					};
				};

			};
		};
		template <int N_mask=-1>
		using  dispatch_t = confined_t<dispatch<N_mask>>;

		///\
		Assigns `T`, allowing update via `influx` and aggregated inspection via `efflux`. \
		
		template <int N_mask=-1>
		struct expect
		{
			using subkind = attach<N_mask>;
			
			template <flux::any_q R>
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
		template <int N_mask=-1>
		using  expect_t = confined_t<expect<N_mask>>;

		///\
		Assigns `T`, allowing update via `efflux` aggregated inspection via `influx`. \

		template <int N_mask=-1>
		struct inspect
		{
			using subkind = attach<N_mask>;
			
			template <flux::any_q R>
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
		template <int N_mask=-1>
		using  inspect_t = confined_t<inspect<N_mask>>;

		///\
		Uses the current `T` as the return value of `method`. \
		
		template <int N_mask=-1>
		struct poll
		{
			using subkind = attach<N_mask>;
			
			template <flux::any_q R>
			class subtype : public bond::compose_s<R, subkind>
			{
				using R_ = bond::compose_s<R, subkind>;
			
			public:
				using R_::R_;
				using R_::head;

				XTAL_DEF_(return,inline)
				XTAL_LET method()
				XTAL_0FX
				{
					return head();
				}

			};
		};
		template <int N_mask=-1>
		using  poll_t = confined_t<poll<N_mask>>;

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
