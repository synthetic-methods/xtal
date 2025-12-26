#pragma once
#include "../bond.hh"
#include "../flow/any.hh"// `_retail`
#include "../flow/tag.hh"
#include "../flow/mask.hh"
#include "../flow/assess.hh"



XTAL_ENV_(push)
namespace xtal::occur
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

namespace _retail = xtal::flow;
#include "./_entail.ii"
#include "./_detail.ii"


////////////////////////////////////////////////////////////////////////////////

/*!
\brief   Extends `flow::define` with message-attachment subdecorators.
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
	
	public:
		using S_::S_;//NOTE: Inherited and respecialized!

		template <constant_q        U> XTAL_NEW_(explicit) subtype(U u) noexcept {assert(0 == u);};
	//	template <same_q<size_type> U> XTAL_NEW_(explicit) subtype(U u) noexcept {assert(0 == u);};

		/*!
		\brief  	Attaches `T` as a member of `this`.
		*/
		template <extent_type N_mask=1>
		struct attach
		{
			using superkind = bond::compose<flow::mask<N_mask>, defer<T>>;

			template <class R>
			class subtype : public bond::compose_s<R, superkind>
			{
				static_assert(cell::any_q<R>);
				using R_ = bond::compose_s<R, superkind>;
				
			public:// CONSTRUCT
			//	using R_::R_;

				XTAL_NEW_(delete) (subtype, noexcept=default)
				XTAL_NEW_(create) (subtype, noexcept=default)
				XTAL_NEW_(move)   (subtype, noexcept=default)
				XTAL_NEW_(copy)   (subtype, noexcept=default)
				XTAL_NEW_(then)   (subtype, noexcept:subtype)
			//	XTAL_NEW_(else)   (subtype, noexcept:S_)

				/*!
				\brief  	Constructs the `attach`ed message using its default,
				before `forward`ing the arguments to `this`.
				*/
				XTAL_NEW_(explicit)
				subtype(auto &&...oo)
				noexcept
				:	R_{T{}, XTAL_REF_(oo)...}
				{}

			public:// ACCESS

				XTAL_FX4_(to) (XTAL_DEF_(return,inline,implicit)
				operator T(), R_::head())

			public:// FLOW

				template <signed N_ion>
				XTAL_DEF_(return,inline,let)
				fuse(auto &&o)
				noexcept -> signed
				{
					return R_::template fuse<N_ion>(XTAL_REF_(o));
				}
				template <signed N_ion>
				XTAL_DEF_(return,inline,let)
				fuse(same_q<flow::assess_s<T>> auto &&o)
				noexcept -> signed
				{
					return R_::heading(XTAL_REF_(o).tail());
				}

			};
		};
		/*!
		\brief  	Attaches `T`, and appends to the arguments of `method` and `method_f`.
		*/
		template <extent_type N_mask=1>
		struct attend
		{
			using superkind = typename T::template attach<N_mask>;

			template <class R>
			class subtype : public bond::compose_s<R, superkind>
			{
				using R_ = bond::compose_s<R, superkind>;

			public:// CONSTRUCT
				using R_::R_;

			public:// OPERATE

				template <auto ...Ns>
				XTAL_DEF_(return,inline,let)
				method(auto &&...oo)
				noexcept -> decltype(auto)
				requires requires (R_       &r_) {
					r_ .template method<Ns...>(XTAL_REF_(oo)..., XTAL_ANY_(T).head());
				}
				{
					return R_::template method<Ns...>(XTAL_REF_(oo)..., R_::template head<T>().head());
				}
				template <auto ...Ns>
				XTAL_DEF_(return,inline,let)
				method(auto &&...oo) const
				noexcept -> decltype(auto)
				requires requires (R_ const &r_) {
					r_ .template method<Ns...>(XTAL_REF_(oo)..., XTAL_ANY_(T).head());
				}
				{
					return R_::template method<Ns...>(XTAL_REF_(oo)..., R_::template head<T>().head());
				}

			};
		};
		/*!
		\brief  	Attaches `T` as a member of `this`,
		`dispatch`ing a conditional indicating positivity.
		*/
		/*!
		\note   	Automatic attachment is currently disabled!
		*/
		template <extent_type N_mask=1>
		struct clutch
		{
			using U_choke = inferred_t<bond::tab<clutch<N_mask>>, bond::seek_t<0, 1>>;

			using superkind = bond::compose<void
			,	typename U_choke::template dispatch<N_mask>
		//	,	attach<N_mask>
			>;
			template <flow::any_q R>
			class subtype : public bond::compose_s<R, superkind>
			{
				using R_ = bond::compose_s<R, superkind>;

			public:// CONSTRUCT
				using R_::R_;
			
			public:// FLOW
				template <signed N_ion>
				XTAL_DEF_(return,inline,let)
				flux(auto &&...oo)
				noexcept -> signed
				{
					return R_::template flux<N_ion>(XTAL_REF_(oo)...);
				}
				template <signed N_ion> requires in_v<N_ion, +1>
				XTAL_DEF_(return,let)
				flux(same_q<T> auto &&t, auto &&...oo)
				noexcept -> signed
				{
					(void) R_::template flux<N_ion>(U_choke(0 != t.head()));
					return R_::template flux<N_ion>(XTAL_REF_(t), XTAL_REF_(oo)...);
				}
			
			};
		};
		/*!
		\brief  	Attaches `T` as a member of `this`, appending it to the arguments used to `deify` `method<auto ...>`.
		*/
		template <extent_type N_mask=1>
		struct dispatch
		{
			static_assert(integral_q<typename T::head_type>);

			using superkind = typename T::template attach<N_mask>;
			
			template <flow::any_q R>
			class subtype : public bond::compose_s<R, superkind>
			{
				using R_ = bond::compose_s<R, superkind>;

				static size_type constexpr A_size = T::cardinality();
				static size_type constexpr A_mask = A_size - one;

			public:// CONSTRUCT
				using R_::R_;
			
			public:// OPERATE
				using R_::self;
				using R_::head;

			protected:// DEIFY
			public:

				template <class ...Xs>
				XTAL_DEF_(return,inline,let)
				deify(constant_q auto ...Is) const
				noexcept -> decltype(auto)
				{
					return deify(digest<Xs...>::template index<Is...>::point);
				}
				template <class A>
				XTAL_DEF_(return,inline,let)
				deify(_std::array<A, A_size> const &point) const
				noexcept -> decltype(auto)
				{
					//\
					auto i = static_cast<size_type>(head());
					auto i = static_cast<size_type>(R_::body_part);
					XTAL_IF0
					XTAL_0IF (1 == _std::popcount(A_size)) {
						i &= A_mask;
					}
					XTAL_0IF (1 != _std::popcount(A_size)) {
						i %= A_size;
						i += A_size;
						i %= A_size;
					}
					XTAL_IF1_(assume) (0 <= i and i < A_size);
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
						static auto constexpr intend_v = same_q<typename T::body_type, size_type>?
							(XTAL_ALL_(J)) T{static_cast<size_type>(J)}: J;
						
						template <auto J>
						static auto constexpr extend_v = digested::template index<Is..., intend_v<J>>::point;
						
						template <auto ...Js>
						static auto constexpr expand_f(bond::seek_t<Js...>)
						noexcept -> auto
						{
							return _std::array{extend_v<Js>...};
						}
					
					public:
						static auto constexpr point = expand_f(bond::seek_s<A_size> {});
						using point_type = decltype(point);
					
					};
				};

			};
		};
		/*!
		\brief  	Assigns `T`, allowing update via `influx`, and aggregated expectation via `efflux`.
		*/
		template <extent_type N_mask=1>
		struct expect
		{
			using superkind = typename T::template attach<N_mask>;
			
			template <flow::any_q R>
			class subtype : public bond::compose_s<R, superkind>
			{
				using R_ = bond::compose_s<R, superkind>;
			
			public:
				using R_::R_;
				
				template <signed N_ion>
				XTAL_DEF_(return,inline,let)
				fuse(auto &&o)
				noexcept -> signed
				{
					return R_::template fuse<N_ion>(XTAL_REF_(o));
				}
				template <signed N_ion> requires in_v<N_ion, -1>
				XTAL_DEF_(return,inline,let)
				fuse(same_q<T> auto &&o)
				noexcept -> signed
				{
					return R_::heading(o);
				}

			};
		};
		/*!
		\brief  	Assigns `T`, allowing update via `efflux` and aggregated inspection via `influx`.
		*/
		template <extent_type N_mask=1>
		struct inspect
		{
			using superkind = typename T::template attach<N_mask>;
			
			template <flow::any_q R>
			class subtype : public bond::compose_s<R, superkind>
			{
				using R_ = bond::compose_s<R, superkind>;
			
			public:
				using R_::R_;

				template <signed N_ion>
				XTAL_DEF_(return,inline,let)
				fuse(auto &&o)
				noexcept -> signed
				{
					return R_::template fuse<N_ion>(XTAL_REF_(o));
				}
				template <signed N_ion> requires in_v<N_ion, +1>
				XTAL_DEF_(return,inline,let)
				fuse(same_q<T> auto &&o)
				noexcept -> signed
				{
					return R_::heading(o);
				}

			};
		};
		/*!
		\brief  	Uses the current `T` as the return value of `method`.
		*/
		template <extent_type N_mask=1>
		struct poll
		{
			using superkind = typename T::template attach<N_mask>;
			
			template <flow::any_q R>
			class subtype : public bond::compose_s<R, superkind>
			{
				using R_ = bond::compose_s<R, superkind>;
			
			public:
				using R_::R_;
				using R_::head;

				template <auto ...>
				XTAL_DEF_(return,inline,let)
				method() const
				{
					return head();
				}

			};
		};

	};
};
/*!
\brief   Aliases `flow::refine`.
*/
template <class T>
struct refine
:	_retail::refine<T>
{
};


////////////////////////////////////////////////////////////////////////////////

/*!
\brief   Aliases `flow::defer`.
*/
template <class U>
struct defer
:	_retail::defer<U>
{
};
/*!
\brief   Aliases `flow::refer`.
*/
template <class U>
struct refer
:	_retail::refer<U>
{
};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
