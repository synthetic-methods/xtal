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

	template <class S>
	class subtype : public bond::compose_s<S, superkind>
	{
		static_assert(any_q<S>);
		using S_ = bond::compose_s<S, superkind>;
	
	public:
		using S_::S_;

		XTAL_NEW_(explicit) subtype(size_type u)
		noexcept
		{
			assert(0 == u);
		};
		template <constant_q U>
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
		struct clutch
		{
			using U_choke = conferred_t<bool, bond::tab<clutch<N_mask>>>;

			using superkind = bond::compose<void
			,	typename U_choke::template dispatch<N_mask>
			,	attach<N_mask>
			>;
			template <flux::any_q R>
			class subtype : public bond::compose_s<R, superkind>
			{
				using R_ = bond::compose_s<R, superkind>;

			public:// CONSTRUCT
				using R_::R_;
			
			public:// *FLUX

				XTAL_DEF_(short)
				XTAL_LET influx(auto &&...oo)
				noexcept -> signed
				{
					return R_::influx(XTAL_REF_(oo)...);
				}
				XTAL_DEF_(short)
				XTAL_LET influx(XTAL_SYN_(T) auto &&t, auto &&...oo)
				noexcept -> signed
				{
					(void) R_::influx(U_choke(0 < t));
					return R_::influx(XTAL_REF_(t), XTAL_REF_(oo)...);
				}
			
			};
		};
		///\
		Attaches `T` as a member of `this`, appending it to the arguments used to `deify` `method<auto ...>`. \

		template <int N_mask=-1>
		struct dispatch
		{
			static_assert(integral_q<typename T::head_type>);

			using superkind = attach<N_mask>;
			
			template <flux::any_q R>
			class subtype : public bond::compose_s<R, superkind>
			{
				using R_ = bond::compose_s<R, superkind>;

				XTAL_SET A_size = T::cardinality() - size_0;
				XTAL_SET A_mask = T::cardinality() - size_1;

			public:// CONSTRUCT
				using R_::R_;
			
			public:// OPERATE
				using R_::self;
				using R_::head;

				XTAL_DO2_(template <auto ...Is>
				XTAL_DEF_(short)
				XTAL_LET operator() (auto &&...xs),
				noexcept -> decltype(auto)
				{
					return (self().*deify<decltype(xs)...>(constant_t<Is>{}...)) (XTAL_REF_(xs)...);
				})

			protected:// DEIFY

				template <class A>
				XTAL_DEF_(short)
				XTAL_LET deify(_std::array<A, A_size> const &point) const
				noexcept -> decltype(auto)
				{
					auto const &h = head();
					//\
					auto        i = static_cast<size_type>(h);// TODO: Should be handled by conversion?
					auto        i = static_cast<size_type>(h.body_part);
					auto const _i = A_mask - i;
					i += bond::operating::bit_sign_f(_i)&_i;
					return R_::deify(point[i]);
				}
				template <class ...Xs>
				XTAL_DEF_(short)
				XTAL_LET deify(constant_q auto ...Is) const
				noexcept -> decltype(auto)
				{
					return deify(digest<Xs...>::template index<Is...>::point);
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
						using    point_type = decltype(point);
					
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
				
				XTAL_DEF_(short)
				XTAL_LET effuse(auto &&o)
				noexcept -> signed
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

				XTAL_DEF_(short)
				XTAL_LET infuse(auto &&o)
				noexcept -> signed
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
				XTAL_DEF_(short)
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
