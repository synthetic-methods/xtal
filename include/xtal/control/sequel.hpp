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

XTAL_OP2_(bool) == (sequel_q auto const &s, sequel_q auto const &t)
XTAL_0EX
{
	return s.step() == t.step() and s.size() == t.size();
}

////////////////////////////////////////////////////////////////////////////////

template <countee_q V>
struct sequel<V>
{
	using subkind = common::compose<defer<unit_t>, resize<V>, restep<V>>;

	template <any_q S>
	class subtype: public common::compose_s<S, subkind>
	{
		using co = common::compose_s<S, subkind>; using T = typename co::self_t;

	public:
	//	using co::co;
		using co::self;
		using co::twin;

		using value_type = V;

		XTAL_CO4_(subtype);
		XTAL_CO2_(subtype);

		XTAL_NEW_(explicit) subtype(XTAL_DEF ...ws)
		XTAL_0EX
		:	co(unit_t(), XTAL_REF_(ws)...)
		{
		}

		XTAL_FN2 trip(V step_n)
		XTAL_0FX
		{
			return T(co::size(), co::step() + step_n);
		}
		XTAL_FN2 trip(V step_n, V i, V j)
		XTAL_0FX
		{
			V const &step_m = co::step();
			V const  size_n = j - i;
			return T(size_n, step_n + step_m);
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
		Advance `1` step while retaining `size`. \

		XTAL_OP1_(T &) ++()
		XTAL_0EX
		{
			return operator+=(co::size());
		}
		XTAL_OP1_(T) ++(int)
		XTAL_0EX
		{
			auto copy = self(); operator++(); return copy;
		}
		///\
		Advance `1` step of size `n`. \

		XTAL_OP1_(T &) +=(V n)
		XTAL_0EX
		{
			co::step() += co::size() != 0;
			co::size(n);
			return self();
		}

		///\
		\returns the block at distance `n` steps with the same `size`. \

		XTAL_OP2_(T) * (V n)
		XTAL_0FX
		{
			return twin().operator*=(n);
		}
		///\
		\returns the adjacent block with the same `size`. \

		XTAL_FN2_(T) next()
		XTAL_0FX
		{
			return twin().operator++();
		}
		///\
		\returns the adjacent block of size `n`. \

		XTAL_OP2_(T) + (V n)
		XTAL_0FX
		{
			return twin().operator+=(n);
		}
		///\
		\returns the adjacent block of size `0`. \

		XTAL_FN2_(T) null()
		XTAL_0FX
		{
			return twin().operator+=(0);
		}


		///\
		\returns `true` iff the left-hand argument immediately precedes the right. \

		XTAL_OP2_(bool) < (subtype const &t)
		XTAL_0FX
		{
			auto const s = next();
			return s.step() == t.step() - 1;
		}
		XTAL_OP2_(bool) <=(subtype const &t)
		XTAL_0FX
		{
			auto const &s =   self();
			auto const &m = s.size();
			auto const &n = t.size();
			auto const &i = s.step();
			auto const &j = t.step();
			return (1 + i == j) or (i == j) and (0 == m or m == n or n == 0);
		}

		///\
		\returns `true` iff the left-hand argument immediately follows the right. \

		XTAL_OP2_(bool) > (subtype const &t)
		XTAL_0FX
		{
			return t.operator< (self());
		}
		XTAL_OP2_(bool) >=(subtype const &t)
		XTAL_0FX
		{
			return t.operator<=(self());
		}


		XTAL_OP2_(bool) ==(subtype const &t)
		XTAL_0FX
		{
			auto const &s =   self();
			auto const &m = s.size();
			auto const &n = t.size();
			auto const &i = s.step();
			auto const &j = t.step();
			return (i == j) and (m == n);
		}

		struct attach
		{
			using subkind = typename co::attach;

			template <context::any_q R>
			class subtype: public common::compose_s<R, subkind>
			{
				using co = common::compose_s<R, subkind>;

			public:
				using co::co;

				using co::influx;
				///\
				Intercepts `T` and moves to the position specified, \
				setting the `size = 0` for future `efflux`. \

				XTAL_FN2_(sign_t) influx(T t, XTAL_DEF ...oo)
				XTAL_0EX
				{
					return co::influx(t.null(), XTAL_REF_(oo)...);
				}

				using co::efflux;
				///\
				Asserts that the incoming sequels arrive in order. \

				XTAL_FN2_(sign_t) efflux(T t, XTAL_DEF ...oo)
				XTAL_0EX
				{
					auto const &m = co::head();
					assert(m <= t);// FIXME
					return co::efflux(t, XTAL_REF_(oo)...);
				}
				XTAL_FN2_(sign_t) efflux(sequel_q auto t, XTAL_DEF ...oo)
				XTAL_0EX
				{
					auto &s = co::head();
					if (s == t)
					{	return 0;
					}
					else
					{	s += t.size(); assert(s.step() == t.step());
						(void) co::efflux(XTAL_REF_(oo)...);
						return 1;
					}
				}

			};
		};

	};
};


////////////////////////////////////////////////////////////////////////////////

template <counted_q U>
struct sequel<U>
{
private:
	using V = iteratee_t<U>;

public:
	using subkind = common::compose<refer<U>, rescan<U>, restep<V>>;

	template <any_q S>
	class subtype: public common::compose_s<S, subkind>
	{
		using co = common::compose_s<S, subkind>; using T = typename co::self_t;
	public:
		using co::co;
		using co::self;
		using co::twin;
		
		using value_type = U;

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

		XTAL_FN2 trip(V step_n)
		XTAL_0FX
		{
			return T(co::scan(), co::step() + step_n);
		}
		XTAL_FN2 trip(V step_n, V i, V j)
		XTAL_0FX
		{
			V const &front_n = *co::begin();
			V const   size_n = j - i;
			V const   size_m = co::end() - co::begin();
			return size_n == size_m? self(): T(U(front_n + i, front_n + j), co::step() + step_n);
		}

		///\
		Advance `n` steps while retaining `size`. \

		XTAL_OP1 *=(V n)
		XTAL_0EX
		{
			auto const i0 = co::begin(), iM = co::end();
			auto const nm = n*(iM - i0);
			co::scan(*(nm + i0), *(nm + iM));
			co::step() += n;
			return self();
		}
		///\
		Advance `1` step while retaining `size`. \

		XTAL_OP1 ++()
		XTAL_0EX
		{
			return operator+=(co::end() - co::begin());
		}
		XTAL_OP1_(T) ++(int)
		XTAL_0EX
		{
			auto copy = self(); operator++(); return copy;
		}
		///\
		Advance `1` step of size `n`. \

		XTAL_OP1 +=(V n)
		XTAL_0EX
		{
			auto &s = self();
			auto const i0 = co::begin(), iM = co::end();
			auto const j0 = iM, jN =j0 + n;
			co::step() += i0 != iM;
			co::scan(*j0, *jN);
			return self();
		}


		///\
		\returns the block at distance `n` steps with the same `size`. \

		XTAL_OP2_(T) * (V n)
		XTAL_0FX
		{
			return twin().operator*=(n);
		}
		///\
		\returns the adjacent block with the same `size`. \

		XTAL_FN2_(T) next()
		XTAL_0FX
		{
			return twin().operator++();
		}
		///\
		\returns the adjacent block of size `n`. \

		XTAL_OP2_(T) + (V n)
		XTAL_0FX
		{
			return twin().operator+=(n);
		}
		///\
		\returns the adjacent block of size `0`. \

		XTAL_FN2_(T) null()
		XTAL_0FX
		{
			return twin().operator+=(0);
		}


		///\
		\returns `true` iff the left-hand argument immediately precedes the right. \

		XTAL_OP2_(bool) < (subtype const &t)
		XTAL_0FX
		{
			auto const &s = self();
			return s.end() == t.begin();
		}
		XTAL_OP2_(bool) <=(subtype const &t)
		XTAL_0FX
		{
			return operator<(t) or co::operator==(t);
		}

		///\
		\returns `true` iff the left-hand argument immediately follows the right. \

		XTAL_OP2_(bool) > (subtype const &t)
		XTAL_0FX
		{
			auto const &s = self();
			return t.operator< (s);
		}
		XTAL_OP2_(bool) >=(subtype const &t)
		XTAL_0FX
		{
			auto const &s = self();
			return t.operator<=(s);
		}


		struct attach
		{
			using subkind = typename co::attach;

			template <context::any_q R>
			class subtype: public common::compose_s<R, subkind>
			{
				using co = common::compose_s<R, subkind>;

			public:
				using co::co;

				using co::influx;
				///\
				Updates to the incoming position, \
				while setting `size = 0` for future `efflux`. \

				XTAL_FN2_(sign_t) influx(T t, XTAL_DEF ...oo)
				XTAL_0EX
				{
					return co::influx(t.null(), XTAL_REF_(oo)...);
				}
				///\
				\note Unrecognized `sequel_q` are enforced by `assert`ion to `influx` at the initial `step == 0`. \

				XTAL_FN2_(sign_t) influx(sequel_q auto t, XTAL_DEF ...oo)
				XTAL_0EX
				{
					/*/
					auto o = co::head(); o.step(t.step());// or something...
					return co::influx(o.null(), XTAL_REF_(oo)...);
					/*/
					auto o = co::head().null(); o.step(t.step());// or something...
					return co::influx(o, XTAL_REF_(oo)...);
					/***/
				}

				using co::efflux;
				///\
				Enforces ordering on the incoming sequels by `assert`ion. \

				XTAL_FN2_(sign_t) efflux(T t, XTAL_DEF ...oo)
				XTAL_0EX
				{
					auto &s = co::head();
					assert(s <= t);
					return co::efflux(t, XTAL_REF_(oo)...);
				}
				///\
				\note Unrecognized `sequel_q` are incrementally incorporated, \
				updating the size and step only if they align. \

				XTAL_FN2_(sign_t) efflux(sequel_q auto t, XTAL_DEF ...oo)
				XTAL_0EX
				{
					auto &s = co::head();
					if (s == t)
					{	return 0;
					}
					else
					{	s += t.size(); assert(s.step() == t.step());
						(void) co::efflux(XTAL_REF_(oo)...);
						return 1;
					}
				}

			};
		};

	};
};

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
