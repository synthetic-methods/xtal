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

				XTAL_SET A_size = T::size() - 0; static_assert(0 <= A_size);
				XTAL_SET A_mask = T::size() - 1; static_assert(1 == bond::operating::bit_count_f(A_size));

			public:// CONSTRUCT
				using R_::R_;
			
			public:// OPERATE
				using R_::self;
				using R_::head;

				XTAL_DO2_(template <auto ...Is>
				XTAL_DEF_(return,inline)
				XTAL_LET operator() (auto &&...xs), -> decltype(auto)
				{
					return (self().*deify<decltype(xs)...>(Is...)) (XTAL_REF_(xs)...);
				})

			protected:// DEIFY

				XTAL_DEF_(return,inline)
				XTAL_LET deify(array_q<A_size> auto &&point)
				XTAL_0FX -> decltype(auto)
				{
					size_type const i = head();
					return R_::deify(XTAL_REF_(point)[A_mask&i]);
				}
				template <class ...Xs>
				XTAL_DEF_(return,inline)
				XTAL_LET deify(integral_q auto &&...Is)
				XTAL_0FX -> decltype(auto)
				{
					return deify(codex<Xs...>::template index<Is...>::point);
				}
				
				template <class ...Xs>
				struct codex
				{
					using supercodex = typename R_::template codex<Xs...>;

					template <size_type ...Is>
					class index
					{
						template <size_type    J > XTAL_SET extend_v = supercodex::template index<Is..., J>::point;
						template <size_type    J > XTAL_USE extend_t = decltype(extend_v<J>);
						template <size_type ...Js>
						XTAL_SET expand_f(bond::seek_t<Js...>)
						XTAL_0EX {
							return _std::array{extend_v<Js>...};
						}
					
					public:
						XTAL_SET point      = expand_f(bond::seek_s<A_size> {});
						XTAL_USE point_type = decltype(point);
					
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

				template <auto ...>
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
