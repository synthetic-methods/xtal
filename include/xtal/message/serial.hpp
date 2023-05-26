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
The `serial` objects are temporal cursors that govern block-based `processor`s, \
defining the `size` and position of the current block. \
They are designed to preserve contiguity by maintaining sequential ordering on `efflux`. \
\
The arithmetic operators are used to jump and/or resize to adjacent blocks, \
while the logic operators facilitate contiguous comparison. \
\
The range-based `serial<counted_q>` uses `iota_view` to represent the sample-window corresponding to a block, \
and may be used to parameterize `view`s of unbounded streams. \
\
The integer-based `serial<countee_q>` provides a lossy counterpart that mitigates the potential for overflow, \
preserving only the `step` order and `size` of the object to which it's attached. \
(A sample-accurate counter running at 96 kilohertz would otherwise overflow within 12 hours.) \
While the exact time-position is unknown, contiguity is guaranteed (by `assert`ion on `efflux`), \
and the value may be reset on `influx` (ignoring any misalignment issues that may occur). \

template <typename>
struct serial;

template <typename W=counted_t<>>
using serial_t = compose_s<any_t<tag_t<serial>>, confined<serial<W>>>;

template <typename T>
concept serial_q = of_q<T, any_t<tag_t<serial>>>;


////////////////////////////////////////////////////////////////////////////////

template <countee_q V>
struct serial<V>
{
	using subkind = compose<defer<construct_t<>>, resize<iota_t>, restep<iota_t>>;

	template <any_q S>
	class subtype: public compose_s<S, subkind>
	{
		using co = compose_s<S, subkind>; using T = typename co::self_t;

	public:
	//	using co::co;
		using co::self;
		using co::twin;

		XTAL_CO4_(subtype);
		XTAL_CO2_(subtype);

		XTAL_NEW_(explicit) subtype(XTAL_DEF ...ws)
		XTAL_0EX
		:	co(construct_t<>(), XTAL_REF_(ws)...)
		{
		}

		///\
		Advance `i` steps while retaining `size`. \

		XTAL_OP1 *=(iota_t i)
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

		XTAL_OP1_(T &) +=(iota_t n)
		XTAL_0EX
		{
			co::step() += co::size() != 0;
			co::size(n);
			return self();
		}

		///\
		\returns the block at distance `n` steps with the same `size`. \

		XTAL_OP2_(T) * (iota_t n)
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

		XTAL_OP2_(T) + (iota_t n)
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

		struct attach
		{
			using subkind = typename co::attach;

			template <context::any_q R>
			class subtype: public compose_s<R, subkind>
			{
				using co = compose_s<R, subkind>;

			public:
				using co::co;

				using co::influx;
				///\
				Intercepts `T` and moves to the position specified, \
				setting the `size = 0` to finesse future `efflux`. \

				XTAL_FN2_(flux_t) influx(T t, XTAL_DEF ...oo)
				XTAL_0EX
				{
					return co::influx(t.null(), XTAL_REF_(oo)...);
				}

				using co::efflux;
				///\
				Asserts that the incoming serials arrive in order. \

				XTAL_FN2_(flux_t) efflux(T t, XTAL_DEF ...oo)
				XTAL_0EX
				{
					auto const &m = co::head();
					assert(m <= t);
					return co::efflux(t, XTAL_REF_(oo)...);
				}

			};
		};

	};
};


////////////////////////////////////////////////////////////////////////////////

template <counted_q U>
struct serial<U>
{
private:
	using iteratee_u = iteratee_t<U>;
	using iterator_u = iterator_t<U>;
	using distance_u = typename iterator_ts<iterator_u>::difference_type;
public:

	using subkind = compose<refer<U>, rescan<U>, restep<iteratee_u>>;

	template <any_q S>
	class subtype: public compose_s<S, subkind>
	{
		using co = compose_s<S, subkind>; using T = typename co::self_t;
	public:
		using co::co;
		using co::self;
		using co::twin;
		
		XTAL_NEW subtype()
		XTAL_0EX
		:	co(U(0, 0), 0)
		{
		}
		template <to_q<distance_u> N>
		XTAL_NEW_(explicit) subtype(N n)
		XTAL_0EX
		:	co(U(0, n), 0)
		{
		}

		///\
		Advance `n` steps while retaining `size`. \

		XTAL_OP1 *=(iota_t n)
		XTAL_0EX
		{
			auto const i0 = co::begin(), iM = co::end();
			auto const nm = n*_v3::ranges::distance(i0, iM);
			co::scan(*(nm + i0), *(nm + iM));
			co::step() += n;
			return self();
		}
		///\
		Advance `1` step while retaining `size`. \

		XTAL_OP1 ++()
		XTAL_0EX
		{
			return operator+=(_v3::ranges::distance(co::begin(), co::end()));
		}
		XTAL_OP1_(T) ++(int)
		XTAL_0EX
		{
			auto copy = self(); operator++(); return copy;
		}
		///\
		Advance `1` step of size `n`. \

		XTAL_OP1 +=(iota_t n)
		XTAL_0EX
		{
			auto &s = self();
			auto const i0 = co::begin(), iM = co::end();
			auto const j0 = iM, jN = _v3::ranges::next(j0, n);
			co::step() += i0 != iM;
			co::scan(*j0, *jN);
			return self();
		}


		///\
		\returns the block at distance `n` steps with the same `size`. \

		XTAL_OP2_(T) * (iota_t n)
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

		XTAL_OP2_(T) + (iota_t n)
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
			class subtype: public compose_s<R, subkind>
			{
				using co = compose_s<R, subkind>;

			public:
				using co::co;

				using co::influx;
				///\
				Updates to the incoming position, \
				while setting `size = 0` to finesse future `efflux`. \

				XTAL_FN2_(flux_t) influx(T t, XTAL_DEF ...oo)
				XTAL_0EX
				{
					return co::influx(t.null(), XTAL_REF_(oo)...);
				}
				///\
				\note Unrecognized `serial_q` are enforced by `assert`ion to `influx` at the initial `step == 0`. \

				XTAL_FN2_(flux_t) influx(XTAL_DEF_(serial_q) t, XTAL_DEF ...oo)
				XTAL_0EX
				{
					auto &s = co::head();
					assert(0 == t.step());
					return co::influx(s.null(), XTAL_REF_(oo)...);
				}

				using co::efflux;
				///\
				Enforces ordering on the incoming serials by `assert`ion. \

				XTAL_FN2_(flux_t) efflux(T t, XTAL_DEF ...oo)
				XTAL_0EX
				{
					auto &s = co::head();
					assert(s <= t);
					return co::efflux(t, XTAL_REF_(oo)...);
				}
				///\
				\note Unrecognized `serial_q` are incrementally incorporated, \
				updating the size and step only if they align. \

				XTAL_FN2_(flux_t) efflux(XTAL_DEF_(serial_q) t, XTAL_DEF ...oo)
				XTAL_0EX
				{
					auto &s = co::head();
					s += t.size()*(t.step() == s.next().step());
					return co::efflux(t, XTAL_REF_(oo)...);
				}

			};
		};

	};
};

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
