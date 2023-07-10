#pragma once
#include "./any.hpp"
#include "./rescan.hpp"
#include "./resize.hpp"
#include "./restep.hpp"



XTAL_ENV_(push)
namespace xtal::control
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
///\
Tracks the progress of block-based `processor`s, \
defined by the `step`, `size`, and position of the current block. \
They are designed to prestore contiguity by maintaining monotonic ordering on `efflux`. \
\
The arithmetic operators are used to jump and/or resize to adjacent blocks, \
while the logic operators facilitate contiguous comparison. \
\
The range-based `sequel<counted_q>` uses `iota_view` to represent the sample-window corresponding to a block, \
and may be used to parameterize `view`s of unbounded streams. \
\
The integer-based `sequel<counter_q>` provides a lossy counterpart that mitigates the potential for overflow, \
preserving only the `step` order and `size` of the object to which it's attached. \
(A sample-accurate counter running at 96 kilohertz would otherwise overflow within 12 hours.) \
While the exact time-position is unknown, contiguity is guaranteed (by `assert`ion on `efflux`), \
and the value may be reset on `influx` (ignoring any misalignment issues that may occur). \

template <typename ...>
struct sequel;

template <typename... Ts>
XTAL_ASK sequel_q = tag_q<sequel, Ts...>;

template <typename W=counter_t<>, typename ...As>
XTAL_USE sequel_t = confined_t<sequel<W>, As...>;

template <typename ...As>
XTAL_CN2 sequel_f(XTAL_DEF w) {return sequel_t<counter_t<>, As...>(XTAL_REF_(w));}


////////////////////////////////////////////////////////////////////////////////

XTAL_OP2_(bool) == (sequel_q auto const &s, sequel_q auto const &t)
XTAL_0EX
{
	return s.step() == t.step() and s.size() == t.size();
}


namespace _detail
{///////////////////////////////////////////////////////////////////////////////

struct prequel
{
	template <any_p S>
	class subtype: public S
	{
		using T_ = typename S::self_t;
		using U_ = typename S::head_t;
		using V_ = counter_t<U_>;
	
	public:
		using S::S;
		using S::self;
		using S::twin;
		using value_type = V_;

		XTAL_FN2 skip(V_ v)
		XTAL_0FX
		{
			auto t = self(); (void) t.step(t.step() + v);
			return t;
		}

		///\returns the block at distance `v` steps with the same `size`. \

		XTAL_OP2_(T_) * (V_ v)
		XTAL_0FX
		{
			return twin().operator*=(v);
		}
		XTAL_OP2_(T_) / (V_ v)
		XTAL_0FX
		{
			return twin().operator/=(v);
		}
		///\
		Advance `1` step while retaining `size`. \

		XTAL_OP1_(T_ &) ++()
		XTAL_0EX
		{
			return self().operator+=(count_f(self()));
		}
		XTAL_OP1_(T_) ++(int)
		XTAL_0EX
		{
			auto t = self(); operator++(); return t;
		}
		///\returns the adjacent block with the same `size`. \

		XTAL_FN2_(T_) next(V_ v)
		XTAL_0FX
		{
			return self().operator*(v);
		}
		XTAL_FN2_(T_) next()
		XTAL_0FX
		{
			return twin().operator++();
		}
		///\returns the adjacent block of size `v`. \

		XTAL_OP2_(T_) + (V_ v)
		XTAL_0FX
		{
			return twin().operator+=(v);
		}
		XTAL_OP2_(T_) - (V_ v)
		XTAL_0FX
		{
			return twin().operator-=(v);
		}
		///\returns the adjacent block of size `0`. \

		XTAL_FN2_(T_) null()
		XTAL_0FX
		{
			return twin().operator+=(0);
		}
		XTAL_FN2_(T_) null(V_ v)
		XTAL_0FX
		{
			auto s = null(); s.step(v); return s;
		}

		///\returns `true` iff the left-hand argument immediately follows the right. \

		XTAL_OP2_(bool) >=(subtype const &t)
		XTAL_0FX
		{
			return S::operator>(t) or S::operator==(t);
		}

		XTAL_OP2_(bool) <=(subtype const &t)
		XTAL_0FX
		{
			return S::operator<(t) or S::operator==(t);
		}

		///\
		Updates to the incoming position, \
		while setting `size = 0` for future `efflux`. \
		
		XTAL_FNX infuse(T_ t)
		XTAL_0EX
		{
			auto &s = self();
			return s == t or ((s = t), 0);
		}
		/**/
		XTAL_FNX infuse(XTAL_DEF_(sequel_q) t)
		XTAL_0EX
		{
			auto &s = self();
			if (s == t) {
				return 1;
			}
			else {
				s.operator+=(0);
				s.operator-=(count_f(t));
				(void) s.step(t.step());
				return 0;
			}
		}
		/***/
		XTAL_FNX infuse(XTAL_DEF o)
		XTAL_0EX
		{
			return S::infuse(XTAL_REF_(o));
		}

		///\
		Enforces ordering on the incoming sequels by `assert`ion. \

		///\note\
		Unrecognized `sequel_q` are incrementally incorporated, \
		updating the size and step only if they align. \

		XTAL_FNX effuse(XTAL_DEF o)
		XTAL_0EX
		{
			return S::effuse(XTAL_REF_(o));
		}
		XTAL_FNX effuse(XTAL_DEF_(sequel_q) t)
		XTAL_0EX
		{
			auto &s = self();
			if (s == t) {
				return 1;
			}
			else {
				s.operator+=(count_f(t));
				assert(s.step() == t.step());
				return 0;
			}
		}

	};
};


}///////////////////////////////////////////////////////////////////////////////

template <counter_q V>
struct sequel<V>
{
	using subkind = compose<_detail::prequel, resize<V>, restep<V>, tag<sequel>>;

	template <any_p S>
	class subtype: public compose_s<S, subkind>
	{
		using S_ = compose_s<S, subkind>;
		using T_ = typename S_::self_t;

	public:
	//	using S_::S_;
		using S_::self;
		using S_::twin;

		~subtype() = default;
	//	XTAL_CO0_(subtype);
		XTAL_CO4_(subtype);

		XTAL_CON subtype()
		XTAL_0EX
		:	S_(0, 0)
		{}
		XTAL_CXN subtype(XTAL_DEF ...oo)
		XTAL_0EX
		:	S_(XTAL_REF_(oo)...)
		{}
		XTAL_CXN subtype(XTAL_DEF_(iterated_q) o, XTAL_DEF ...oo)
		XTAL_0EX
		:	S_(count_f(XTAL_REF_(o)), XTAL_REF_(oo)...)
		{}

		XTAL_FN2 slice(XTAL_DEF_(counted_q) w)
		XTAL_0FX
		{
			auto t = twin(); (void) t.size(count_f(w)); return t;
		}

		///\
		Advance `i` steps while retaining `size`. \

		XTAL_OP1 *=(V v)
		XTAL_0EX
		{
			S_::step() += v;
			return self();
		}
		XTAL_OP1 /=(V v)
		XTAL_0EX
		{
			S_::step() -= v;
			return self();
		}
		///\
		Advance `1` step of size `v`. \

		XTAL_OP1_(T_ &) +=(V v)
		XTAL_0EX
		{
			S_::step() += S_::size() != 0; (void) S_::size(v);
			return self();
		}
		XTAL_OP1_(T_ &) -=(V v)
		XTAL_0EX
		{
			S_::step() -= v != 0; (void) S_::size(v);
			return self();
		}

		///\returns `true` iff the left-hand argument immediately precedes the right. \

		XTAL_OP2_(bool) < (subtype const &t)
		XTAL_0FX
		{
			return S_::next().step() == t.step();
		}
		XTAL_OP2_(bool) > (subtype const &t)
		XTAL_0FX
		{
			return S_::step() == t.next().step();
		}

	};
};


////////////////////////////////////////////////////////////////////////////////

template <counted_q U>
struct sequel<U>
{
private:
	using V = iteratee_t<U>;

public:
	using subkind = compose<_detail::prequel, refer<U>, rescan<U>, restep<V>, tag<sequel>>;

	template <any_p S>
	class subtype: public compose_s<S, subkind>
	{
		using S_ = compose_s<S, subkind>;
		using T_ = typename S_::self_t;

	public:
		using S_::S_;
		using S_::self;
		using S_::twin;
		
		XTAL_CXN subtype(U u, V v)
		XTAL_0EX
		:	S_(u, v)
		{}
		template <to_q<V> W>
		XTAL_CXN subtype(W w)
		XTAL_0EX
		:	subtype(U(0, w), 0)
		{}
		XTAL_CON subtype()
		XTAL_0EX
		:	subtype(U(0, 0), 0)
		{}

		XTAL_FN2 slice(XTAL_DEF_(counted_q) w)
		XTAL_0FX
		{
			V const &front_n = *S_::begin();
			auto i = front_n + w.front();
			auto j = front_n + w.back() + 1;
			return T_(U(i, j), S_::step());
		}

		///\
		Advance `v` steps while retaining `size`. \

		XTAL_OP1 *=(V v)
		XTAL_0EX
		{
			using namespace _v3::ranges;
			auto const i0 = S_::begin(), iM = S_::end();
			auto const nm = v*distance(i0, iM);
			(void) S_::scan(*next(i0, nm), *next(iM, nm));
			S_::step() += v;
			return self();
		}
		XTAL_OP1 /=(V v)
		XTAL_0EX
		{
			using namespace _v3::ranges;
			auto const i0 = S_::begin(), iM = S_::end();
			auto const nm = v*distance(i0, iM);
			(void) S_::scan(*prev(i0, nm), *prev(iM, nm));
			S_::step() -= v;
			return self();
		}
		///\
		Advance `1` step of size `v`. \

		XTAL_OP1 +=(V v)
		XTAL_0EX
		{
			using namespace _v3::ranges;
			auto &s = self();
			auto const i0 = S_::begin(), iM = S_::end();
			auto const j0 = iM, jN = next(j0, v);
			S_::step() += i0 != iM;
			(void) S_::scan(*j0, *jN);
			return self();
		}
		XTAL_OP1 -=(V v)
		XTAL_0EX
		{
			using namespace _v3::ranges;
			auto &s = self();
			auto const i0 = S_::begin(), iM = S_::end();
			auto const jN = i0, j0 = prev(jN, v);
			S_::step() -= v != 0;
			(void) S_::scan(*j0, *jN);
			return self();
		}

		///\returns `true` iff the left-hand argument immediately precedes the right. \

		XTAL_OP2_(bool) < (subtype const &t)
		XTAL_0FX
		{
			return S_::end() == t.begin();
		}
		XTAL_OP2_(bool) > (subtype const &t)
		XTAL_0FX
		{
			return S_::begin() == t.end();
		}

	};
};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
