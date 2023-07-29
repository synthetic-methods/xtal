#pragma once
#include "./anybody.hpp"






XTAL_ENV_(push)
namespace xtal::process
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <           typename ..._s> XTAL_NYM star;
template <           typename ..._s> XTAL_ASK star_q = tag_p<star, _s...>;
template <array_q W, typename ...As> XTAL_USE star_t = confined_t<star<W, As...>>;


////////////////////////////////////////////////////////////////////////////////
///\

template <array_q W, typename ...As>
struct star<W, As...>
{
	XTAL_LET N_ = _std::       extent_v<W>;
	XTAL_USE U_ = _std::remove_extent_t<W>;
	
	using array_u = solid::serial_t<W>;
	using shard_u = typename context::shard_s<array_u>;
	using subkind = compose<tag<star>
	,	_detail::refer_iterators<array_u>
	,	typename shard_u::refract
	,	As...
	>;
	
	template <class S>
	class subtype: public compose_s<S, subkind>
	{
		using S_ = compose_s<S, subkind>;

	public:
		using S_::S_;
		using S_::self;
		using S_::head;
		
		///\
		Access by dynamic index. \
		
		XTAL_TO4_(XTAL_FN2 d(size_t i), head().d(i))

		XTAL_DO2_(template <auto ...Ks>
		XTAL_FN2 method(),
		{
			return ++head();
		})
		XTAL_DO2_(template <auto ...Ks>
		XTAL_FN2 method(XTAL_DEF_(array_q<N_>) a),
		{
			S_::influx(XTAL_REF_(a));
			return method();
		})
		XTAL_DO2_(template <auto ...Ks>
		XTAL_FN2 method(XTAL_DEF_(subarray_q<(int) N_ - 1>) a),
		{
			using A = XTAL_TYP_(a);
			using U = typename context::shard_s<A, N_ - arity_v<A>>;
			S_::influx(U(XTAL_REF_(a)));
			return method();
		})
		
	//	using S_::infuse;
		///\todo\
		Prevent same-cycle duplicates for non-idempotent handlers... \
		The `control` itself could handle this with a `bool` modified by `&= 1` on successful update, \
		and propagating the result upstream (instead of just forwarding the original message). \
		(Potentially need a `context::sequel` to express this cleanly?) \
		
		/**/
		XTAL_FNX infuse(XTAL_DEF_(array_q<(int) N_ - 1>) a)
		XTAL_0EX
		{
			head() += a;
			return 0;
		}
		XTAL_FNX infuse(XTAL_DEF o)
		XTAL_0EX
		{
			return S_::infuse(XTAL_REF_(o));
		}
		/***/

		///\todo\
		Introduce `control::per` etc to manage downsampling \
		(by scalar/integer multiplication followed by normalization). \

	};
};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)