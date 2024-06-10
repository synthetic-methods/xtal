#pragma once
#include "./any.hh"
#include "./review.hh"
#include "./resize.hh"
#include "./restep.hh"



XTAL_ENV_(push)
namespace xtal::occur
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
///\
Tracks the progress of block-based `processor`s, \
defined by the `step`, `size`, and position of the current block. \
Preserves contiguity by maintaining monotonic ordering on `efflux`. \
\
The arithmetic operators are used to jump and/or resize to adjacent blocks, \
while the logic operators facilitate contiguous comparison. \
\
The range-based `render<counted_q>` uses `iota_view` to represent the sample-window corresponding to a block, \
and may be used to parameterize `view`s of unbounded streams. \
\
The integer-based `render<counter_q>` provides a lossy counterpart that mitigates the potential for overflow, \
preserving only the `step` order and `size` of the object to which it's attached. \
(A sample-accurate counter running at 96 kilohertz would otherwise overflow within 12 hours.) \
While the exact time-position is unknown, contiguity is guaranteed (by `assert`ion on `efflux`), \
and the value may be reset on `influx` (ignoring any misalignment issues that may occur). \

template <                     typename ..._s> XTAL_TYP render;
template <class W=counter_t<>, typename ..._s> XTAL_USE render_t = confined_t<render<W>, _s...>;
template <                     typename ..._s> XTAL_ASK render_q = bond::head_tag_p<render, _s...>;
template <                     typename ..._s>
XTAL_DEF_(return,inline)
XTAL_LET     render_f(auto &&w)
XTAL_0EX_TO_(render_t<counter_t<>, _s...>(XTAL_REF_(w)))


template <class ...Ts>
concept efflux_render_q = (...or (render_q<Ts>));

template <class ...Ts>
concept influx_render_q = false;


////////////////////////////////////////////////////////////////////////////////

template <render_q X, render_q Y> requires (not is_q<X, Y>)
XTAL_DEF_(inline)
XTAL_LET operator == (X const &x, Y const &y)
XTAL_0EX -> bool
{
	auto &s = x.self();
	auto &t = y.self();
	return s.step() == t.step() and s.size() == t.size();
}


namespace _detail
{///////////////////////////////////////////////////////////////////////////////

struct surrender
{
	template <any_q S>
	class subtype : public S
	{
		using S_ = S;

	protected:
		using typename S_::T_self; friend T_self;
		using typename S_::U_head;

	private:
		using V_ = counter_t<U_head>;
	
	public:
		using S_::S_;
		using S_::self;
		using S_::twin;
		using value_type = V_;

		using ring = int;

		XTAL_DEF_(return,inline)
		XTAL_LET skip(V_ v)
		XTAL_0FX -> T_self
		{
			auto t = self(); (void) t.step(t.step() + v);
			return t;
		}

		///\returns the block at distance `v` steps with the same `size`. \

		XTAL_DEF_(inline)
		XTAL_LET operator * (V_ v)
		XTAL_0FX -> T_self
		{
			return twin().operator*=(v);
		}
		XTAL_DEF_(inline)
		XTAL_LET operator / (V_ v)
		XTAL_0FX -> T_self
		{
			return twin().operator/=(v);
		}
		///\
		Advance `1` step while retaining `size`. \

		XTAL_DEF_(inline)
		XTAL_LET operator ++()
		XTAL_0EX -> T_self &
		{
			return self().operator+=(count_f(self()));
		}
		XTAL_DEF_(inline)
		XTAL_LET operator ++(int)
		XTAL_0EX -> T_self
		{
			auto t = self(); operator++(); return t;
		}
		///\
		Retreat `1` step while retaining `size`. \

		XTAL_DEF_(inline)
		XTAL_LET operator --()
		XTAL_0EX -> T_self &
		{
			return self().operator-=(count_f(self()));
		}
		XTAL_DEF_(inline)
		XTAL_LET operator --(int)
		XTAL_0EX -> T_self
		{
			auto t = self(); operator--(); return t;
		}
		///\returns the adjacent block with the same `size`. \

		XTAL_DEF_(return,inline)
		XTAL_LET next(V_ v)
		XTAL_0FX -> T_self
		{
			return self().operator*(v);
		}
		XTAL_DEF_(return,inline)
		XTAL_LET next()
		XTAL_0FX -> T_self
		{
			return twin().operator++();
		}
		///\returns the adjacent block of size `v`. \

		XTAL_DEF_(return,inline)
		XTAL_LET operator + (V_ v)
		XTAL_0FX -> T_self
		{
			return twin().operator+=(v);
		}
		XTAL_DEF_(return,inline)
		XTAL_LET operator - (V_ v)
		XTAL_0FX -> T_self
		{
			return twin().operator-=(v);
		}
		///\returns the adjacent block of size `0`. \

		XTAL_DEF_(return,inline)
		XTAL_LET null()
		XTAL_0FX -> T_self
		{
			return twin().operator+=(0);
		}
		XTAL_DEF_(return,inline)
		XTAL_LET null(V_ v)
		XTAL_0FX -> T_self
		{
			auto s = null(); s.step(v); return s;
		}

		///\returns `true` iff the left-hand argument immediately follows the right. \

		XTAL_DEF_(return,inline)
		XTAL_LET operator >=(subtype const &t)
		XTAL_0FX -> bool
		{
			return S_::operator>(t) or S_::operator==(t);
		}

		XTAL_DEF_(return,inline)
		XTAL_LET operator <=(subtype const &t)
		XTAL_0FX -> bool
		{
			return S_::operator<(t) or S_::operator==(t);
		}

		///\
		Updates to the incoming position, \
		while setting `size = 0` for future `efflux`. \
		
		XTAL_TNX infuse(T_self t)
		XTAL_0EX
		{
			auto &s = self();
			return s == t || ((s = t), 0);
		}
		/**/
		XTAL_TNX infuse(render_q auto &&t)
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
		XTAL_TNX infuse(auto &&o)
		XTAL_0EX
		{
			return S_::infuse(XTAL_REF_(o));
		}

		///\
		Enforces ordering on the incoming renders by `assert`ion. \

		///\note\
		Unrecognized `render_q` are incrementally incorporated, \
		updating the size and step only if they align. \

		XTAL_TNX effuse(auto &&o)
		XTAL_0EX
		{
			return S_::effuse(XTAL_REF_(o));
		}
		XTAL_TNX effuse(render_q auto &&t)
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
struct render<V>
{
	using subkind = bond::compose<_detail::surrender, resize<V>, restep<V>, bond::tag<render>>;

	template <any_q S>
	class subtype : public bond::compose_s<S, subkind>
	{
		using S_ = bond::compose_s<S, subkind>;

	protected:
		using typename S_::T_self; friend T_self;

	public:
	//	using S_::S_;
		using S_::self;
		using S_::twin;

		XTAL_CO0_(subtype)
	//	XTAL_CO1_(subtype)
		XTAL_CO4_(subtype)

		XTAL_CON_(implicit) subtype()
		XTAL_0EX
		:	S_(0, 0)
		{}
		XTAL_CON_(explicit) subtype(auto &&...oo)
		XTAL_0EX
		:	S_(XTAL_REF_(oo)...)
		{}
		XTAL_CON_(explicit) subtype(iterated_q auto &&o, auto &&...oo)
		XTAL_0EX
		:	S_(count_f(XTAL_REF_(o)), XTAL_REF_(oo)...)
		{}

		XTAL_DEF_(return,inline)
		XTAL_LET subview(counted_q auto &&w)
		XTAL_0FX -> T_self
		{
			auto t = twin(); (void) t.size(count_f(w)); return t;
		}

		///\
		Advance `i` steps while retaining `size`. \

		XTAL_DEF_(inline)
		XTAL_LET operator *=(V v)
		XTAL_0EX -> T_self &
		{
			S_::step() += v;
			return self();
		}
		XTAL_DEF_(inline)
		XTAL_LET operator /=(V v)
		XTAL_0EX -> T_self &
		{
			S_::step() -= v;
			return self();
		}
		///\
		Advance `1` step of size `v`. \

		XTAL_DEF_(inline)
		XTAL_LET operator +=(V v)
		XTAL_0EX -> T_self &
		{
			S_::step() += S_::size() != 0; (void) S_::size(v);
			return self();
		}
		XTAL_DEF_(inline)
		XTAL_LET operator -=(V v)
		XTAL_0EX -> T_self &
		{
			S_::step() -= v != 0; (void) S_::size(v);
			return self();
		}

		///\returns `true` iff the left-hand argument immediately precedes the right. \

		XTAL_DEF_(return,inline)
		XTAL_LET operator < (subtype const &t)
		XTAL_0FX -> bool
		{
			return S_::next().step() == t.step();
		}
		XTAL_DEF_(return,inline)
		XTAL_LET operator > (subtype const &t)
		XTAL_0FX -> bool
		{
			return S_::step() == t.next().step();
		}

	};
};


////////////////////////////////////////////////////////////////////////////////

template <counted_q U>
struct render<U>
{
private:
	using V = iteratee_t<U>;

public:
	using subkind = bond::compose<_detail::surrender, review<U>, restep<V>, bond::tag<render>>;

	template <any_q S>
	class subtype : public bond::compose_s<S, subkind>
	{
		using S_ = bond::compose_s<S, subkind>;

	protected:
		using typename S_::T_self; friend T_self;

	public:
		using S_::S_;
		using S_::self;
		using S_::twin;
		
		XTAL_CON_(explicit) subtype(U u, V v)
		XTAL_0EX
		:	S_(u, v)
		{}
		template <as_q<V> W>
		XTAL_CON_(explicit) subtype(W w)
		XTAL_0EX
		:	subtype(U(0, w), 0)
		{}
		XTAL_CON_(implicit) subtype()
		XTAL_0EX
		:	subtype(U(0, 0), 0)
		{}

		XTAL_DEF_(return,inline)
		XTAL_LET subview(counted_q auto &&w)
		XTAL_0FX -> T_self
		{
			return T_self(S_::subhead(XTAL_REF_(w)), S_::step());
		}

		///\
		Advance `v` steps while retaining `size`. \

		XTAL_DEF_(inline)
		XTAL_LET operator *=(V v)
		XTAL_0EX -> T_self &
		{
			using _xtd::ranges::distance;
			using _xtd::ranges::next;
			auto const i0 = S_::begin(), iM = S_::end();
			auto const nm = v*distance(i0, iM);
			(void) S_::view(*next(i0, nm), *next(iM, nm));
			S_::step() += v;
			return self();
		}
		XTAL_DEF_(inline)
		XTAL_LET operator /=(V v)
		XTAL_0EX -> T_self &
		{
			using _xtd::ranges::distance;
			using _xtd::ranges::prev;
			auto const i0 = S_::begin(), iM = S_::end();
			auto const nm = v*distance(i0, iM);
			(void) S_::view(*prev(i0, nm), *prev(iM, nm));
			S_::step() -= v;
			return self();
		}
		///\
		Advance `1` step of size `v`. \

		XTAL_DEF_(inline)
		XTAL_LET operator +=(V v)
		XTAL_0EX -> T_self &
		{
			using _xtd::ranges::next;
		//	auto &s = self();
			auto const i0 = S_::begin(), iM = S_::end();
			auto const j0 = iM, jN = next(j0, v);
			S_::step() += i0 != iM;
			(void) S_::view(*j0, *jN);
			return self();
		}
		XTAL_DEF_(inline)
		XTAL_LET operator -=(V v)
		XTAL_0EX -> T_self &
		{
			using _xtd::ranges::prev;
		//	auto &s = self();
			auto const i0 = S_::begin(), iM = S_::end();
			auto const jN = i0, j0 = prev(jN, v);
			S_::step() -= v != 0;
			(void) S_::view(*j0, *jN);
			return self();
		}

		///\returns `true` iff the left-hand argument immediately precedes the right. \

		XTAL_DEF_(return,inline)
		XTAL_LET operator < (subtype const &t)
		XTAL_0FX -> bool
		{
			return S_::end() == t.begin();
		}
		XTAL_DEF_(return,inline)
		XTAL_LET operator > (subtype const &t)
		XTAL_0FX -> bool
		{
			return S_::begin() == t.end();
		}

	};
};

static_assert(render_q<render_t<counter_t<>>>);
static_assert(render_q<render_t<counted_t<>>>);

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
