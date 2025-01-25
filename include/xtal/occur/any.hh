#pragma once
#include "../flow/all.hh"// `_retail`

#include "../flow/mask.hh"




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
		{
			using superkind = bond::compose<void
			,	flow::mask<N_mask>
			,	typename S_::template afflux<>
			>;
			template <class R>
			using subtype = bond::compose_s<R, superkind>;

		};
		///\
		Attaches `T`, and appends to the arguments of `method` and `function`. \

		template <extent_type N_mask=-1>
		struct attend
		{
			using superkind = attach<N_mask>;

			template <class R>
			class subtype : public bond::compose_s<R, superkind>
			{
				using R_ = bond::compose_s<R, superkind>;

			public:// CONSTRUCT
				using R_::R_;

			public:// OPERATE

				template <auto ...Ns>
				XTAL_DEF_(short)
				XTAL_LET method(auto &&...oo)
				noexcept -> decltype(auto)
				requires requires (R_       &r_) {
					r_ .template method<Ns...>(XTAL_REF_(oo)..., XTAL_ANY_(T).head());
				}
				{
					return R_::template method<Ns...>(XTAL_REF_(oo)..., R_::template head<T>().head());
				}
				template <auto ...Ns>
				XTAL_DEF_(short)
				XTAL_LET method(auto &&...oo) const
				noexcept -> decltype(auto)
				requires requires (R_ const &r_) {
					r_ .template method<Ns...>(XTAL_REF_(oo)..., XTAL_ANY_(T).head());
				}
				{
					return R_::template method<Ns...>(XTAL_REF_(oo)..., R_::template head<T>().head());
				}

			};
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
			template <flow::any_q R>
			class subtype : public bond::compose_s<R, superkind>
			{
				using R_ = bond::compose_s<R, superkind>;

			public:// CONSTRUCT
				using R_::R_;
			
			public:// FLOW
				template <signed N_ion>
				XTAL_DEF_(short)
				XTAL_LET flux(auto &&...oo)
				noexcept -> signed
				{
					return R_::template flux<N_ion>(XTAL_REF_(oo)...);
				}
				template <signed N_ion> requires in_n<N_ion, +1>
				XTAL_DEF_(short)
				XTAL_LET flux(same_q<T> auto &&t, auto &&...oo)
				noexcept -> signed
				{
					auto const h = t.head();
					auto const h_up = 0 < h;
					auto const h_dn = h < 0;
					(void) R_::template flux<N_ion>(U_choke(h_up - h_dn));
					return R_::template flux<N_ion>(XTAL_REF_(t), XTAL_REF_(oo)...);
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
			
			template <flow::any_q R>
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
					auto i = static_cast<size_type>(h);
					auto i = static_cast<size_type>(h.body_part);
					if constexpr (1 == _std::popcount(A_size)) {
						i &= A_mask;
					}
					else {
						i %= A_size;
					}
					assert(0 <= i and i < A_size);
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
			
			template <flow::any_q R>
			class subtype : public bond::compose_s<R, superkind>
			{
				using R_ = bond::compose_s<R, superkind>;
			
			public:
				using R_::R_;
				
				template <signed N_ion>
				XTAL_DEF_(short)
				XTAL_LET fuse(auto &&o)
				noexcept -> signed
				{
					return R_::template fuse<N_ion>(XTAL_REF_(o));
				}
				template <signed N_ion> requires in_n<N_ion, -1>
				XTAL_DEF_(short)
				XTAL_LET fuse(same_q<T> auto &&o)
				noexcept -> signed
				{
					return R_::heading(XTAL_REF_(o));
				}

			};
		};

		///\
		Assigns `T`, allowing update via `efflux` aggregated inspection via `influx`. \

		template <extent_type N_mask=-1>
		struct inspect
		{
			using superkind = attach<N_mask>;
			
			template <flow::any_q R>
			class subtype : public bond::compose_s<R, superkind>
			{
				using R_ = bond::compose_s<R, superkind>;
			
			public:
				using R_::R_;

				template <signed N_ion>
				XTAL_DEF_(short)
				XTAL_LET fuse(auto &&o)
				noexcept -> signed
				{
					return R_::template fuse<N_ion>(XTAL_REF_(o));
				}
				template <signed N_ion> requires in_n<N_ion, +1>
				XTAL_DEF_(short)
				XTAL_LET fuse(same_q<T> auto &&o)
				noexcept -> signed
				{
					return R_::heading(XTAL_REF_(o));
				}

			};
		};

		///\
		Uses the current `T` as the return value of `method`. \
		
		template <extent_type N_mask=-1>
		struct poll
		{
			using superkind = attach<N_mask>;
			
			template <flow::any_q R>
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
