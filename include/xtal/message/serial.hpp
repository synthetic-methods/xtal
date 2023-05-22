#pragma once
#include "./any.hpp"






XTAL_ENV_(push)
namespace xtal::message
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
///\
The `serial` cursors represent the temporal state of block-based `processor`s by \
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

template <countee_q V>
struct serial<V>
{

	template <typename T>
	using subkind = compose<resize<>, restep<>, define<T>>;

	template <any_q S>
	class subtype: public compose_s<S, subkind<subtype<S>>>
	{
		using co = compose_s<S, subkind<subtype<S>>>; using T = typename co::self_t;
	public:
		using co::co;
		using co::self;
		
		///\
		\returns the empty block at this position. \

		XTAL_FN2 null()
		XTAL_0FX
		{
			return subtype(0, co::step());
		}

		///\
		\returns the following contiguous block. \

		XTAL_FN2 next()
		XTAL_0FX
		{
			auto r = self(); ++r; return r;
		}

		///\
		Moves to the following contiguous block. \

		XTAL_OP1 ++(int)
		XTAL_0EX
		{
			auto r = self(); ++co::step(); return r;
		}
		XTAL_OP1 ++()
		XTAL_0EX
		{
			auto&s = self(); ++co::step(); return s;
		}

		///\
		Moves to the following contiguous block with the given size. \

		XTAL_OP1 +=(XTAL_DEF_(as_q<iota_t>) n)
		XTAL_0EX
		{
			co::size() = iota_t(XTAL_REF_(n));
			return operator++();
		}

		///\
		\returns the following contiguous block with the given size. \

		XTAL_OP2 + (XTAL_DEF_(as_q<iota_t>) n)
		XTAL_0FX
		{
			auto const s = next();
			return subtype(XTAL_REF_(n), s.step());
		}

		///\
		\returns `true` iff the left-hand argument immediately precedes the right. \

		XTAL_OP2_(bool) < (T const &t)
		XTAL_0FX
		{
			auto const s = next();
			return s.step() == t.step() - 1;
		}
		XTAL_OP2_(bool) <=(T const &t)
		XTAL_0FX
		{
			auto const &s =   self();
			auto const &m = s.size();
			auto const &n = t.size();
			auto const &i = s.step();
			auto const &j = t.step();
			return (1 + i == j) or (i == j) and (0 == m or m == n or n == 0);
		//	return operator<(t) or (i == j) and (0 == m or m == n or n == 0);
		}

		///\
		\returns `true` iff the left-hand argument immediately follows the right. \

		XTAL_OP2_(bool) >(T const &t)
		XTAL_0FX
		{
			return operator< (t, self());
		}
		XTAL_OP2_(bool) >=(T const &t)
		XTAL_0FX
		{
			return operator<=(t, self());
		}

		struct attach
		{
			using subkind = typename co::attach;

			template <context::any_q _S>
			class subtype: public compose_s<_S, subkind>
			{
				using co = compose_s<_S, subkind>;

				using serial_n = T;
			//	using serial_u = compose_s<S, serial<counted_t<V>>>;

			public:
				using co::co;

			//	XTAL_RE4_(XTAL_FN2 serial(), co::head())

				///\
				NOTE: Influxing `serial_u = serial<counter_u>` move to the position specified, \
				while setting `size = 0` to allow future `efflux`. \

				XTAL_FN2_(iota_t) influx(XTAL_DEF ...oo)
				XTAL_0EX
				{
					return co::influx(XTAL_REF_(oo)...);
				}
				XTAL_FN2_(iota_t) influx(serial_n w, XTAL_DEF ...oo)
				XTAL_0EX
				{
					auto i = w.step();
					return co::influx(serial_n(0, i), XTAL_REF_(oo)...);
				}

				XTAL_FN2_(iota_t) efflux(XTAL_DEF ...oo)
				XTAL_0EX
				{
					return co::efflux(XTAL_REF_(oo)...);
				}
				XTAL_FN2_(iota_t) efflux(serial_n serial_w, XTAL_DEF ...oo)
				XTAL_0EX
				{
					auto const &m = co::head();
					assert(m <= serial_w);
					return co::efflux(serial_w, XTAL_REF_(oo)...);
				}

			};
		};

	};
};
template <counted_q U>
struct serial<U>
{
	template <typename T>
	using subkind = typename contrive<U>::template subkind<T>;

	template <any_q S>
	class subtype: public compose_s<S, subkind<subtype<S>>>
	{
		using co = compose_s<S, subkind<subtype<S>>>; using T = typename co::self_t;
	public:
		using co::co;
		using co::self;
		
		XTAL_NEW subtype()
		XTAL_0EX
		:	subtype(0)
		{
		}

		XTAL_NEW_(explicit) subtype(XTAL_DEF_(as_q<iota_t>) n)
		XTAL_0EX
		:	co(U(0, n))
		{
		}
		XTAL_NEW_(explicit) subtype(XTAL_DEF_(as_q<iota_t>) n, XTAL_DEF_(countee_q) i)
		XTAL_0EX
		:	co(U(i, i + XTAL_REF_(n)))
		{
		}
		XTAL_NEW_(explicit) subtype(XTAL_DEF_(as_q<iota_t>) n, XTAL_DEF_(countor_q) i)
		XTAL_0EX
		:	co(U(*(i), *(i + XTAL_REF_(n))))
		{
		}

		///\
		\returns the empty block at this position. \

		XTAL_FN2 null()
		XTAL_0FX
		{
			return subtype(0, co::begin());
		}

		///\
		\returns the following contiguous block. \

		XTAL_FN2 next()
		XTAL_0FX
		{
			auto r = self(); ++r; return r;
		}

		///\
		Moves to the following contiguous block with the same size. \

		XTAL_OP1 ++(int)
		XTAL_0EX
		{
			auto r = self(); operator+=(r.size()); return r;
		}
		XTAL_OP1 ++()
		XTAL_0EX
		{
			auto&s = self(); operator+=(s.size()); return s;
		}

		///\
		Moves to the following contiguous block with the given size. \

		XTAL_OP1 +=(XTAL_DEF_(as_q<iota_t>) n)
		XTAL_0EX
		{
			auto&s = self(); return s = s + XTAL_REF_(n);
		}

		///\
		\returns the following contiguous block with the given size. \

		XTAL_OP2 + (XTAL_DEF_(as_q<iota_t>) n)
		XTAL_0FX
		{
			return subtype(XTAL_REF_(n), co::end());
		}

		///\
		\returns `true` iff the left-hand argument immediately precedes the right. \

		XTAL_OP2_(bool) < (T const &t)
		XTAL_0FX
		{
			return co::end() == t.begin();
		}
		XTAL_OP2_(bool) <=(T const &t)
		XTAL_0FX
		{
			return operator<(t) or co::operator==(t);
		}

		///\
		\returns `true` iff the left-hand argument immediately follows the right. \

		XTAL_OP2_(bool) >(T const &t)
		XTAL_0FX
		{
			return operator< (t, self());
		}
		XTAL_OP2_(bool) >=(T const &t)
		XTAL_0FX
		{
			return operator<=(t, self());
		}

		struct attach
		{
			using subkind = typename co::attach;

			template <context::any_q _S>
			class subtype: public compose_s<_S, subkind>
			{
				using co = compose_s<_S, subkind>;

				using serial_n = compose_s<S, serial<countee_t<U>>>;
				using serial_u = T;

			public:
				using co::co;

			//	XTAL_RE4_(XTAL_FN2 serial(), co::head())

				///\
				NOTE: Influxing `serial_u = serial<counter_u>` move to the position specified, \
				while setting `size = 0` to allow future `efflux`. \

				XTAL_FN2_(iota_t) influx(auto ...ws)
				XTAL_0EX
				{
					return co::influx(ws...);
				}
				XTAL_FN2_(iota_t) influx(serial_u w, auto ...ws)
				XTAL_0EX
				{
					return co::influx(w.null(), ws...);
				}
				XTAL_FN2_(iota_t) influx(serial_n w, auto ...ws)
				XTAL_0EX
				{
					auto i = w.step();
					assert(i == 0);
					return co::influx(w.null(), ws...);
				}

				///\
				NOTE: Effluxing `serial_n = serial<countee_t<>>` will always update the current state, \
				so consistency must be guaranteed downstream. \

				XTAL_FN2_(iota_t) efflux(auto ...ws)
				XTAL_0EX
				{
					return co::efflux(ws...);
				}
				///\
				NOTE: Effluxing `serial_u = serial<counter_u>` will `assert` that the `serial`s are received in sequence. \

				XTAL_FN2_(iota_t) efflux(serial_u w, auto ...ws)
				XTAL_0EX
				{
					auto &m = co::head();
					assert(m <= w);
					return co::efflux(w, ws...);
				}
				///\
				NOTE: Effluxing `serial_n = serial<countee_t<>>` will update without sequence-checking, \
				so consistency must be guaranteed elsewhere by `serial_n::efflux`. \

				XTAL_FN2_(iota_t) efflux(serial_n w, auto ...ws)
				XTAL_0EX
				{
					auto &m = co::head();
					m += w.size();
					return co::efflux(w, ws...);
				}

			};
		};

	};
};
template <typename W=countee_t<>>
using serial_t = compose_s<any_t<>, serial<W>>;

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
