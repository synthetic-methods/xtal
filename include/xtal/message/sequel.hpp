#pragma once
#include "./any.hpp"
#include "./rescan.hpp"
#include "./resize.hpp"
#include "./restep.hpp"



XTAL_ENV_(push)
namespace xtal::message
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

template <typename, typename ...>
struct sequel;

template <typename W=counter_t<>, typename ...As>
using sequel_t = typename confined<sequel<W, As...>>::template subtype<any_of_t<sequel>>;

template <typename... Ts>
concept sequel_q = any_of_q<sequel, Ts...>;

template <typename ...As>
XTAL_FZ2 sequel_f(XTAL_DEF w)
{
	using _realized = realize<XTAL_TYP_(w)>;
	return sequel_t<counter_t<>, As...>(XTAL_REF_(w));
}


////////////////////////////////////////////////////////////////////////////////

XTAL_OP2_(bool) == (sequel_q auto const &s, sequel_q auto const &t)
XTAL_0EX
{
	return s.step() == t.step() and s.size() == t.size();
}

template <>
struct sequel<void>
{
	template <any_q S>
	class subtype: public compose_s<S>
	{
		using co = compose_s<S>;
		using T = typename co::self_t;
		using U = typename co::head_t;
		using V = counter_t<U>;
	
	public:
		using co::co;
		using co::self;
		using co::twin;
		using value_type = V;

		XTAL_FN2 skip(V v)
		XTAL_0FX
		{
			auto t = self(); t.step(t.step() + v);
			return t;
		}

		///\
		\returns the block at distance `v` steps with the same `size`. \

		XTAL_OP2_(T) * (V v)
		XTAL_0FX
		{
			return twin().operator*=(v);
		}
		XTAL_OP2_(T) / (V v)
		XTAL_0FX
		{
			return twin().operator/=(v);
		}
		///\
		Advance `1` step while retaining `size`. \

		XTAL_OP1_(T &) ++()
		XTAL_0EX
		{
			return self().operator+=(self().count());
		}
		XTAL_OP1_(T) ++(int)
		XTAL_0EX
		{
			auto t = self(); operator++(); return t;
		}
		///\
		\returns the adjacent block with the same `size`. \

		XTAL_FN2_(T) next(V v)
		XTAL_0FX
		{
			return self().operator*(v);
		}
		XTAL_FN2_(T) next()
		XTAL_0FX
		{
			return twin().operator++();
		}
		///\
		\returns the adjacent block of size `v`. \

		XTAL_OP2_(T) + (V v)
		XTAL_0FX
		{
			return twin().operator+=(v);
		}
		XTAL_OP2_(T) - (V v)
		XTAL_0FX
		{
			return twin().operator-=(v);
		}
		///\
		\returns the adjacent block of size `0`. \

		XTAL_FN2_(T) null()
		XTAL_0FX
		{
			return twin().operator+=(0);
		}
		XTAL_FN2_(T) null(V v)
		XTAL_0FX
		{
			auto s = null(); s.step(v); return s;
		}

		///\
		\returns `true` iff the left-hand argument immediately follows the right. \

		XTAL_OP2_(bool) >=(subtype const &t)
		XTAL_0FX
		{
			return co::operator>(t) or co::operator==(t);
		}

		XTAL_OP2_(bool) <=(subtype const &t)
		XTAL_0FX
		{
			return co::operator<(t) or co::operator==(t);
		}

		///\
		Updates to the incoming position, \
		while setting `size = 0` for future `efflux`. \
		
		XTAL_FNX infuse(XTAL_DEF o)
		XTAL_0EX
		{
			return co::infuse(XTAL_REF_(o));
		}
		XTAL_FNX infuse(T t)
		XTAL_0EX
		{
			auto &s = self();
			return s == t? 0: true_f(s = t);
		}
		/**/
		XTAL_FNX infuse(XTAL_DEF_(sequel_q) t)
		XTAL_0EX
		{
			auto &s = self();
			if (s == t)
			{	return 0;
			}
			else
			{	s.operator+=(0);
				s.operator-=(t.count()); s.step(t.step());
				return 1;
			}
		}
		/***/

		///\
		Enforces ordering on the incoming sequels by `assert`ion. \

		///\
		\note Unrecognized `sequel_q` are incrementally incorporated, \
		updating the size and step only if they align. \

		XTAL_FNX effuse(XTAL_DEF o)
		XTAL_0EX
		{
			return co::effuse(XTAL_REF_(o));
		}
		XTAL_FNX effuse(XTAL_DEF_(sequel_q) t)
		XTAL_0EX
		{
			auto &s = self();
			if (s == t)
			{	return 0;
			}
			else
			{	s.operator+=(t.count());
				assert(s.step() == t.step());
				return 1;
			}
		}

	};
};


////////////////////////////////////////////////////////////////////////////////

template <counter_q V>
struct sequel<V>
{
	using subkind = compose<sequel<void>, resize<V>, restep<V>>;

	template <any_q S>
	class subtype: public compose_s<S, subkind>
	{
		using co = compose_s<S, subkind>; using T = typename co::self_t;

	public:
	//	using co::co;
		using co::self;
		using co::twin;

		XTAL_CN4_(subtype);
	//	XTAL_CN2_(subtype);

		XTAL_NEW subtype()
		XTAL_0EX
		:	co(0, 0)
		{
		}
		XTAL_NEW_(explicit) subtype(XTAL_DEF ...oo)
		XTAL_0EX
		:	co(XTAL_REF_(oo)...)
		{
		}
		XTAL_NEW_(explicit) subtype(XTAL_DEF_(iterated_q) o, XTAL_DEF ...oo)
		XTAL_0EX
		:	co(count_f(XTAL_REF_(o)), XTAL_REF_(oo)...)
		{
		}

		XTAL_RN2_(XTAL_FN2 count(), co::size())

		XTAL_FN2 slice(V i, V j)
		XTAL_0FX
		{
			auto t = self(); t.size(j - i);
			return t;
		}

		///\
		Advance `i` steps while retaining `size`. \

		XTAL_OP1 *=(V v)
		XTAL_0EX
		{
			co::step() += v;
			return self();
		}
		XTAL_OP1 /=(V v)
		XTAL_0EX
		{
			co::step() -= v;
			return self();
		}
		///\
		Advance `1` step of size `v`. \

		XTAL_OP1_(T &) +=(V v)
		XTAL_0EX
		{
			co::step() += co::size() != 0;
			co::size(v);
			return self();
		}
		XTAL_OP1_(T &) -=(V v)
		XTAL_0EX
		{
			co::step() -= v != 0;
			co::size(v);
			return self();
		}

		///\
		\returns `true` iff the left-hand argument immediately precedes the right. \

		XTAL_OP2_(bool) < (subtype const &t)
		XTAL_0FX
		{
			return co::next().step() == t.step();
		}
		XTAL_OP2_(bool) > (subtype const &t)
		XTAL_0FX
		{
			return co::step() == t.next().step();
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
	using subkind = compose<sequel<void>, refer<U>, rescan<U>, restep<V>>;

	template <any_q S>
	class subtype: public compose_s<S, subkind>
	{
		using co = compose_s<S, subkind>; using T = typename co::self_t;

	public:
		using co::co;
		using co::self;
		using co::twin;
		
		XTAL_NEW_(explicit) subtype(U u, V v)
		XTAL_0EX
		:	co(u, v)
		{
		}
		template <to_q<V> W>
		XTAL_NEW_(explicit) subtype(W w)
		XTAL_0EX
		:	subtype(U(0, w), 0)
		{
		}
		XTAL_NEW subtype()
		XTAL_0EX
		:	subtype(U(0, 0), 0)
		{
		}

		XTAL_RN2_(XTAL_FN2 count(), count_f(co::scan()))

		XTAL_FN2 slice(V i, V j)
		XTAL_0FX
		{
			V const &front_n = *co::begin();
			return T(U(front_n + i, front_n + j), co::step());
		}

		///\
		Advance `v` steps while retaining `size`. \

		XTAL_OP1 *=(V v)
		XTAL_0EX
		{
			auto const i0 = co::begin(), iM = co::end();
			auto const nm = v*_std::distance(i0, iM);
			co::scan(*(i0 + nm), *(iM + nm));
			co::step() += v;
			return self();
		}
		XTAL_OP1 /=(V v)
		XTAL_0EX
		{
			auto const i0 = co::begin(), iM = co::end();
			auto const nm = v*_std::distance(i0, iM);
			co::scan(*(i0 - nm), *(iM - nm));
			co::step() -= v;
			return self();
		}
		///\
		Advance `1` step of size `v`. \

		XTAL_OP1 +=(V v)
		XTAL_0EX
		{
			auto &s = self();
			auto const i0 = co::begin(), iM = co::end();
			auto const j0 = iM, jN = (j0 + v);
			co::step() += i0 != iM;
			co::scan(*j0, *jN);
			return self();
		}
		XTAL_OP1 -=(V v)
		XTAL_0EX
		{
			auto &s = self();
			auto const i0 = co::begin(), iM = co::end();
			auto const jN = i0, j0 = (jN - v);
			co::step() -= v != 0;
			co::scan(*j0, *jN);
			return self();
		}

		///\
		\returns `true` iff the left-hand argument immediately precedes the right. \

		XTAL_OP2_(bool) < (subtype const &t)
		XTAL_0FX
		{
			return co::end() == t.begin();
		}
		XTAL_OP2_(bool) > (subtype const &t)
		XTAL_0FX
		{
			return co::begin() == t.end();
		}

	};
};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
