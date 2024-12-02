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
	using superkind = _retail::define<T>;

	template <any_q S>
	class subtype : public bond::compose_s<S, superkind>
	{
		friend T;
		using S_ = bond::compose_s<S, superkind>;
	
	public:
		using S_::S_;

		XTAL_NEW_(explicit) subtype(size_type u)
		noexcept
		{
			assert(0 == u);
		};
		template <nominal_q U>
		XTAL_NEW_(explicit) subtype(U &&u)
		noexcept
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
		///\
		Attaches `T` as a member of `this`, \
		`dispatch`ing a conditional indicating positivity. \

		template <int N_mask=-1>
			requires anisotropic_q<bool, typename T::head_type>// Avoids self-referencing `T`...
		struct clutch
		{
			using U_switch = conferred_t<bool, bond::tab<clutch<N_mask>>>;

			using superkind = bond::compose<void
			,	typename U_switch::template dispatch<N_mask>
			,	attach<N_mask>
			>;
			template <flux::any_q R>
			class subtype : public bond::compose_s<R, superkind>
			{
				using R_ = bond::compose_s<R, superkind>;

			public:// CONSTRUCT
				using R_::R_;
			
			public:// *FLUX

				XTAL_DEF_(return,inline)
				XTAL_LET influx(auto &&...oo)
				noexcept -> sign_type
				{
					return R_::influx(XTAL_REF_(oo)...);
				}
				XTAL_DEF_(return,inline)
				XTAL_LET influx(XTAL_ARG_(T) &&t, auto &&...oo)
				noexcept -> sign_type
				{
					(void) R_::influx(U_switch(0 < t));
					return R_::influx(XTAL_REF_(t), XTAL_REF_(oo)...);
				}
			
			};
		};
		///\
		Attaches `T` as a member of `this`, appending it to the arguments used to `deify` `method<auto ...>`. \

		template <int N_mask=-1>
		struct dispatch
		{
			using superkind = attach<N_mask>;
			
			template <flux::any_q R>
			class subtype : public bond::compose_s<R, superkind>
			{
				using R_ = bond::compose_s<R, superkind>;

				XTAL_SET A_size = T::cardinality() - size_0; static_assert(size_0 <= A_size);
				XTAL_SET A_mask = T::cardinality() - size_1; static_assert(size_1 == bond::operating::bit_count_f(A_size));

			public:// CONSTRUCT
				using R_::R_;
			
			public:// OPERATE
				using R_::self;
				using R_::head;

				XTAL_DO2_(template <auto ...Is>
				XTAL_DEF_(return,inline)
				XTAL_LET operator() (auto &&...xs), -> decltype(auto)
				{
					return (self().*deify<decltype(xs)...>(nominal_t<Is>{}...)) (XTAL_REF_(xs)...);
				})

			protected:// DEIFY

				template <class A>
				XTAL_DEF_(return,inline)
				XTAL_LET deify(_std::array<A, A_size> const &point) const
				noexcept -> decltype(auto)
				{
					auto const i = static_cast<size_type>(head());
					return R_::deify(point[A_mask&i]);
				}
				template <class ...Xs>
				XTAL_DEF_(return,inline)
				XTAL_LET deify(nominal_q auto ...Is) const
				noexcept -> decltype(auto)
				{
					return deify(digest<Xs...>::template index<XTAL_VAL_(Is)...>::point);
				}
				
				template <class ...Xs>
				struct digest
				{
					using digested = typename R_::template digest<Xs...>;

					template <auto ...Is>
					class index
					{
						template <auto _I>
						XTAL_SET intend_v = is_q<typename T::body_type, size_type>?
							(decltype(_I)) T(static_cast<size_type>(_I)): _I;
						
						template <auto _I>
						XTAL_SET extend_v = digested::template index<Is..., intend_v<_I>>::point;
						
						template <auto ..._Is>
						XTAL_SET expand_f(bond::seek_t<_Is...>)
						noexcept -> auto
						{
							return _std::array{extend_v<_Is>...};
						}
					
					public:
						XTAL_SET point      = expand_f(bond::seek_s<A_size> {});
						XTAL_USE point_type = decltype(point);
					
					};
				};

			};
		};

		///\
		Assigns `T`, allowing update via `influx` and aggregated inspection via `efflux`. \
		
		template <int N_mask=-1>
		struct expect
		{
			using superkind = attach<N_mask>;
			
			template <flux::any_q R>
			class subtype : public bond::compose_s<R, superkind>
			{
				using R_ = bond::compose_s<R, superkind>;
			
			public:
				using R_::R_;
				
				XTAL_DEF_(return,inline)
				XTAL_LET effuse(auto &&o)
				noexcept -> sign_type
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
			using superkind = attach<N_mask>;
			
			template <flux::any_q R>
			class subtype : public bond::compose_s<R, superkind>
			{
				using R_ = bond::compose_s<R, superkind>;
			
			public:
				using R_::R_;

				XTAL_DEF_(return,inline)
				XTAL_LET infuse(auto &&o)
				noexcept -> sign_type
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
		Uses the current `T` as the return value of `method`. \
		
		template <int N_mask=-1>
		struct poll
		{
			using superkind = attach<N_mask>;
			
			template <flux::any_q R>
			class subtype : public bond::compose_s<R, superkind>
			{
				using R_ = bond::compose_s<R, superkind>;
			
			public:
				using R_::R_;
				using R_::head;

				template <auto ...>
				XTAL_DEF_(return,inline)
				XTAL_LET method() const
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
