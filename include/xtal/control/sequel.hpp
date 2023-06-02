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
Temporal cursors that govern block-based `processor`s, \
defined by the `size`, `step`, and position of the current block. \
They are designed to prestore contiguity by maintaining sequential ordering on `efflux`. \
\
The arithmetic operators are used to jump and/or resize to adjacent blocks, \
while the logic operators facilitate contiguous comparison. \
\
The range-based `sequel<counted_q>` uses `iota_view` to represent the sample-window corresponding to a block, \
and may be used to parameterize `view`s of unbounded streams. \
\
The integer-based `sequel<countee_q>` provides a lossy counterpart that mitigates the potential for overflow, \
preserving only the `step` order and `size` of the object to which it's attached. \
(A sample-accurate counter running at 96 kilohertz would otherwise overflow within 12 hours.) \
While the exact time-position is unknown, contiguity is guaranteed (by `assert`ion on `efflux`), \
and the value may be reset on `influx` (ignoring any misalignment issues that may occur). \

template <typename, typename ...>
struct sequel;

template <typename W=counted_t<>, typename ...As>
using sequel_t = typename confined<sequel<W, As...>>::template subtype<any_of_t<sequel>>;

template <typename... Ts>
concept sequel_q = any_of_q<sequel, Ts...>;

template <typename ...As>
XTAL_FZ2 sequel_f(XTAL_DEF w)
{
	return sequel_t<decltype(w), As...>(XTAL_REF_(w));
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
	class subtype: public common::compose_s<S>
	{
		using co = common::compose_s<S>;
	protected:
		using typename co::self_t;
	public:
		using co::co;
		using co::self;
		using co::twin;

		XTAL_FN2 skip(iota_q auto n)
		XTAL_0FX
		{
			auto t = self(); t.step(t.step() + n);
			return t;
		}

		///\
		\returns the block at distance `n` steps with the same `size`. \

		XTAL_OP2_(self_t) * (iota_q auto n)
		XTAL_0FX
		{
			return twin().operator*=(n);
		}
		///\
		Advance `1` step while retaining `size`. \

		XTAL_OP1_(self_t &) ++()
		XTAL_0EX
		{
			return self().operator+=(self().size());
		}
		XTAL_OP1_(self_t) ++(int)
		XTAL_0EX
		{
			auto t = self(); operator++(); return t;
		}
		///\
		\returns the adjacent block with the same `size`. \

		XTAL_FN2_(self_t) next(iota_q auto n)
		XTAL_0FX
		{
			return self().operator*(n);
		}
		XTAL_FN2_(self_t) next()
		XTAL_0FX
		{
			return twin().operator++();
		}
		///\
		\returns the adjacent block of size `n`. \

		XTAL_OP2_(self_t) + (iota_q auto n)
		XTAL_0FX
		{
			return twin().operator+=(n);
		}
		///\
		\returns the adjacent block of size `0`. \

		XTAL_FN2_(self_t) null()
		XTAL_0FX
		{
			return twin().operator+=(0);
		}
		XTAL_FN2_(self_t) null(iota_q auto n)
		XTAL_0FX
		{
			auto s = null(); s.step(n); return s;
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
		
		XTAL_FN2_(sign_t) infuse(XTAL_DEF o)
		XTAL_0EX
		{
			return co::infuse(XTAL_REF_(o));
		}
		XTAL_FN2_(sign_t) infuse(self_t t)
		XTAL_0EX
		{
			auto &s = self();
			return s == t? (0): ((s = t), 1);
		}
		/*/
		XTAL_FN2_(sign_t) infuse(XTAL_DEF_(sequel_q) t)
		XTAL_0EX
		{
			auto &s = self();
			return s == t? (0): ((s = s.null(t.step())), 1);
		}
		/***/

		///\
		Enforces ordering on the incoming sequels by `assert`ion. \

		///\
		\note Unrecognized `sequel_q` are incrementally incorporated, \
		updating the size and step only if they align. \

		XTAL_FN2_(sign_t) effuse(XTAL_DEF o)
		XTAL_0EX
		{
			return co::effuse(XTAL_REF_(o));
		}
		XTAL_FN2_(sign_t) effuse(XTAL_DEF_(sequel_q) t)
		XTAL_0EX
		{
			auto &s = self();
		//	assert(s.next(s != t).step() == t.step());// FIXME: Check `interrupt` using `countee`.
			return s == t? (0): ((s += t.size()), 1);
		}

	};
};


////////////////////////////////////////////////////////////////////////////////

template <countee_q V>
struct sequel<V>
{
	using subkind = common::compose<defer<unit_t>, sequel<void>, resize<V>, restep<V>>;

	template <any_q S>
	class subtype: public common::compose_s<S, subkind>
	{
		using co = common::compose_s<S, subkind>;
	protected:
		using typename co::self_t;
	public:
	//	using co::co;
		using co::self;
		using co::twin;

		XTAL_CO4_(subtype);
		XTAL_CO2_(subtype);

		XTAL_NEW_(explicit) subtype(XTAL_DEF ...oo)
		XTAL_0EX
		:	co(unit_t(), XTAL_REF_(oo)...)
		{
		}
		XTAL_NEW_(explicit) subtype(XTAL_DEF_(iterated_q) o, XTAL_DEF ...oo)
		XTAL_0EX
		:	co(unit_t(), XTAL_REF_(o).size(), XTAL_REF_(oo)...)
		{
		}

		XTAL_FN2 slice(V i, V j)
		XTAL_0FX
		{
			auto t = self(); t.size(j - i);
			return t;
		}

		///\
		Advance `i` steps while retaining `size`. \

		XTAL_OP1 *=(V i)
		XTAL_0EX
		{
			co::step() += i;
			return self();
		}
		///\
		Advance `1` step of size `n`. \

		XTAL_OP1_(self_t &) +=(V n)
		XTAL_0EX
		{
			co::step() += co::size() != 0;
			co::size(n);
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
	using subkind = common::compose<sequel<void>, refer<U>, rescan<U>, restep<V>>;

	template <any_q S>
	class subtype: public common::compose_s<S, subkind>
	{
		using co = common::compose_s<S, subkind>;
	protected:
		using typename co::self_t;
	public:
		using co::co;
		using co::self;
		using co::twin;
		
		XTAL_NEW_(explicit) subtype(U u, V v)
		XTAL_0EX
		:	co(u, v)
		{
		}
		template <to_q<V> N>
		XTAL_NEW_(explicit) subtype(N n)
		XTAL_0EX
		:	subtype(U(0, n), 0)
		{
		}
		XTAL_NEW subtype()
		XTAL_0EX
		:	subtype(U(0, 0), 0)
		{
		}

		XTAL_FN2 slice(V i, V j)
		XTAL_0FX
		{
			V const &front_n = *co::begin();
			return self_t(U(front_n + i, front_n + j), co::step());
		}

		///\
		Advance `n` steps while retaining `size`. \

		XTAL_OP1 *=(V n)
		XTAL_0EX
		{
			auto const i0 = co::begin(), iM = co::end();
			auto const nm = n*_std::distance(i0, iM);
			co::scan(*_std::next(i0, nm), *_std::next(iM, nm));
			co::step() += n;
			return self();
		}
		///\
		Advance `1` step of size `n`. \

		XTAL_OP1 +=(V n)
		XTAL_0EX
		{
			auto &s = self();
			auto const i0 = co::begin(), iM = co::end();
			auto const j0 = iM, jN = _std::next(j0, n);
			co::step() += i0 != iM;
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
