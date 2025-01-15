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

		template <constant_q U>
		XTAL_NEW_(explicit) subtype(U       &&u) noexcept {assert(0 == u);};
		XTAL_NEW_(explicit) subtype(size_type u) noexcept {assert(0 == u);};

		///\
		Attaches `T` as a member of `this`. \

		template <extent_type N_mask=-1>
		struct attach
		:	bond::compose<flux::mask<N_mask>, typename S_::template afflux<>>
		{
		};
		///\
		Attaches `T` as a member of `this`, \
		`dispatch`ing a conditional indicating positivity. \

		template <extent_type N_mask=-1>
		struct clutch
		{
			using U_choke = inferred_t<bond::tab<clutch<N_mask>>, bond::seek_t<0, 1,-1>>;

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
					auto const h = t.head();
					auto const h_up = 0 < h;
					auto const h_dn = h < 0;
					(void) R_::influx(U_choke(h_up - h_dn));
					return R_::influx(XTAL_REF_(t), XTAL_REF_(oo)...);
				}
			
			};
		};
		///\
		Attaches `T` as a member of `this`, appending it to the arguments used to `deify` `method<auto ...>`. \

		template <extent_type N_mask=-1>
		struct dispatch
		{
			static_assert(integral_q<typename T::head_type>);

			using superkind = attach<N_mask>;
			
			template <flux::any_q R>
			class subtype : public bond::compose_s<R, superkind>
			{
				using R_ = bond::compose_s<R, superkind>;

				XTAL_SET A_size = T::cardinality();
				XTAL_SET A_mask = A_size - one;

			public:// CONSTRUCT
				using R_::R_;
			
			public:// OPERATE
				using R_::self;
				using R_::head;

			protected:// DEIFY
			public:

				template <class ...Xs>
				XTAL_DEF_(short)
				XTAL_LET deify(constant_q auto ...Is) const
				noexcept -> decltype(auto)
				{
					return deify(digest<Xs...>::template index<Is...>::point);
				}
				template <class A>
				XTAL_DEF_(short)
				XTAL_LET deify(_std::array<A, A_size> const &point) const
				noexcept -> decltype(auto)
				{
					auto const &h = head();
					//\
					auto i  = static_cast<  size_type>(h);// TODO: Should be handled by conversion?
					auto i  = static_cast<  size_type>(h.body_part);
					auto i_ = static_cast<extent_type>(A_mask -  i);
					i_     &= static_cast<extent_type>(bond::bit_sign_f(i_));
					i      += i_;
					return R_::deify(point[i]);
				}
				
				template <class ...Xs>
				struct digest
				{
					using digested = typename R_::template digest<Xs...>;

					template <auto ...Is>
					class index
					{
						template <auto J>
						XTAL_SET intend_v = same_q<typename T::body_type, size_type>?
							(XTAL_ALL_(J)) T(static_cast<size_type>(J)): J;
						
						template <auto J>
						XTAL_SET extend_v = digested::template index<Is..., intend_v<J>>::point;
						
						template <auto ...Js>
						XTAL_SET expand_f(bond::seek_t<Js...>)
						noexcept -> auto
						{
							return _std::array{extend_v<Js>...};
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
		
		template <extent_type N_mask=-1>
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
					if constexpr (same_q<T, decltype(o)>) {
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

		template <extent_type N_mask=-1>
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
					if constexpr (same_q<T, decltype(o)>) {
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
		
		template <extent_type N_mask=-1>
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
