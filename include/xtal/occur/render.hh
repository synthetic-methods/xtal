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
(A counter running at 96 kilohertz would otherwise overflow within 12 hours.) \
While the exact time-position is unknown, contiguity is guaranteed (by `assert`ion on `efflux`), \
and the value may be reset on `influx` (ignoring any misalignment issues that may occur). \

template <class ..._s> struct   render;
template <class ..._s> using    render_t =  confined_t<render< _s...>>;
template <class ..._s> concept  render_q = bond::tag_p<render, _s...> ;

XTAL_DEF_(return,inline,let)   render_f(auto &&w)
noexcept -> decltype(auto) {return render_t<>(XTAL_REF_(w));}


////////////////////////////////////////////////////////////////////////////////

template <render_q X, render_q Y> requires different_q<X, Y>
XTAL_DEF_(return,inline,let)
operator == (X const &x, Y const &y)
noexcept -> bool
{
	auto const &s = x.self();
	auto const &t = y.self();
	return s.step() == t.step() and s.size() == t.size();
}


namespace _detail
{///////////////////////////////////////////////////////////////////////////////

struct surrender
{
	template <class S>
	class subtype : public S
	{
		static_assert(any_q<S>);
		using S_ = S;
		using T_ = typename S_::self_type;
		using U_ = typename S_::head_type;
		using V_ = counter_t<U_>;
	
	public:
		using S_::S_;
		using S_::self;
		using S_::twin;
		
		using value_type = V_;

		XTAL_DEF_(return,inline,let)
		skip(V_ v) const
		noexcept -> T_
		{
			auto t = self(); (void) t.step(t.step() + v);
			return t;
		}

		///\returns the block at distance `v` steps with the same `size`. \

		XTAL_DEF_(inline,let)
		operator * (V_ v) const
		noexcept -> T_
		{
			return twin().operator*=(v);
		}
		XTAL_DEF_(inline,let)
		operator / (V_ v) const
		noexcept -> T_
		{
			return twin().operator/=(v);
		}
		///\
		Advance `1` step while retaining `size`. \

		XTAL_DEF_(inline,let)
		operator ++()
		noexcept -> T_ &
		{
			return self().operator+=(count_f(self()));
		}
		XTAL_DEF_(inline,let)
		operator ++(int)
		noexcept -> T_
		{
			auto t = self(); operator++(); return t;
		}
		///\
		Retreat `1` step while retaining `size`. \

		XTAL_DEF_(inline,let)
		operator --()
		noexcept -> T_ &
		{
			return self().operator-=(count_f(self()));
		}
		XTAL_DEF_(inline,let)
		operator --(int)
		noexcept -> T_
		{
			auto t = self(); operator--(); return t;
		}
		///\returns the adjacent block with the same `size`. \

		XTAL_DEF_(return,inline,let)
		next(V_ v) const
		noexcept -> T_
		{
			return self().operator*(v);
		}
		XTAL_DEF_(return,inline,let)
		next() const
		noexcept -> T_
		{
			return twin().operator++();
		}
		///\returns the adjacent block of size `v`. \

		XTAL_DEF_(return,inline,let)
		operator + (V_ v) const
		noexcept -> T_
		{
			return twin().operator+=(v);
		}
		XTAL_DEF_(return,inline,let)
		operator - (V_ v) const
		noexcept -> T_
		{
			return twin().operator-=(v);
		}
		///\returns the adjacent block of size `0`. \

		XTAL_DEF_(return,inline,let)
		null() const
		noexcept -> T_
		{
			return twin().operator+=(0);
		}
		XTAL_DEF_(return,inline,let)
		null(V_ v) const
		noexcept -> T_
		{
			auto s = null(); s.step(v); return s;
		}

		///\returns `true` iff the left-hand argument immediately follows the right. \

		XTAL_DEF_(return,inline,let)
		operator >=(subtype const &t) const
		noexcept -> bool
		{
			return S_::operator>(t) or S_::operator==(t);
		}

		XTAL_DEF_(return,inline,let)
		operator <=(subtype const &t) const
		noexcept -> bool
		{
			return S_::operator<(t) or S_::operator==(t);
		}


		template <signed N_ion>
		XTAL_DEF_(return,inline,let)
		fuse(auto &&o)
		noexcept -> signed
		{
			return S_::template fuse<N_ion>(XTAL_REF_(o));
		}

		///\
		Updates to the incoming position, \
		while setting `size = 0` for future `efflux`. \
		
		///\
		Enforces ordering on the incoming renders by `assert`ion. \

		///\note\
		Unrecognized `render_q` are incrementally incorporated, \
		updating the size and step only if they align. \

		template <signed N_ion> requires in_n<N_ion, -1>
		XTAL_DEF_(return,inline,let)
		fuse(render_q auto &&t)
		noexcept -> signed
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
		/**/
		template <signed N_ion> requires in_n<N_ion, +1>
		XTAL_DEF_(return,let)
		fuse(render_q auto &&t)
		noexcept -> signed
		{
			auto &s = self();
			if (s == t) {
				return 1;
			}
			else {
				if constexpr (same_q<T_, decltype(t)>) {
					s = t;
				}
				else {
					s.operator+=(0);
					s.operator-=(count_f(t));
					(void) s.step(t.step());
				}
				return 0;
			}
		}
		/***/

	};
};


}///////////////////////////////////////////////////////////////////////////////

template <counter_q V>
struct render<V>
{
	using superkind = bond::compose<_detail::surrender, resize<V>, restep<V>, bond::tag<render>>;

	template <class S>
	class subtype : public bond::compose_s<S, superkind>
	{
		static_assert(any_q<S>);
		using S_ = bond::compose_s<S, superkind>;
		using T_ = typename S_::self_type;

	public:
	//	using S_::S_;
		using S_::self;
		using S_::twin;

	~	subtype()                 noexcept=default;
	//	subtype()                 noexcept=default;
		XTAL_NEW_(copy) (subtype, noexcept=default)
		XTAL_NEW_(move) (subtype, noexcept=default)
		XTAL_NEW_(auto) (subtype, noexcept)

		XTAL_NEW_(implicit) subtype()
		noexcept
		:	S_(0, 0)
		{}
		XTAL_NEW_(explicit) subtype(auto &&...oo)
		noexcept
		:	S_(XTAL_REF_(oo)...)
		{}
		XTAL_NEW_(explicit) subtype(iterated_q auto &&o, auto &&...oo)
		noexcept
		:	S_(count_f(XTAL_REF_(o)), XTAL_REF_(oo)...)
		{}

		XTAL_DEF_(return,inline,let)
		subview(auto &&w) const
		noexcept -> T_
		{
			auto t = twin(); (void) t.size(count_f(w)); return t;
		}

		///\
		Advance `i` steps while retaining `size`. \

		XTAL_DEF_(inline,let)
		operator *=(V v)
		noexcept -> T_ &
		{
			S_::step() += v;
			return self();
		}
		XTAL_DEF_(inline,let)
		operator /=(V v)
		noexcept -> T_ &
		{
			S_::step() -= v;
			return self();
		}
		///\
		Advance `1` step of size `v`. \

		XTAL_DEF_(inline,let)
		operator +=(V v)
		noexcept -> T_ &
		{
			S_::step() += S_::size() != 0; (void) S_::size(v);
			return self();
		}
		XTAL_DEF_(inline,let)
		operator -=(V v)
		noexcept -> T_ &
		{
			S_::step() -= v != 0; (void) S_::size(v);
			return self();
		}

		///\returns `true` iff the left-hand argument immediately precedes the right. \

		XTAL_DEF_(return,inline,let)
		operator < (subtype const &t) const
		noexcept -> bool
		{
			return S_::next().step() == t.step();
		}
		XTAL_DEF_(return,inline,let)
		operator > (subtype const &t) const
		noexcept -> bool
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
	using V = iterated_u<U>;

public:
	using superkind = bond::compose<_detail::surrender, review<U>, restep<V>, bond::tag<render>>;

	template <class S>
	class subtype : public bond::compose_s<S, superkind>
	{
		static_assert(any_q<S>);
		using S_ = bond::compose_s<S, superkind>;
		using T_ = typename S_::self_type;

	public:
		using S_::S_;//NOTE: Inherited and respecialized!
		using S_::self;
		using S_::twin;
		
		XTAL_NEW_(explicit) subtype(U u, V v)
		noexcept
		:	S_(u, v)
		{}
		template <make_q<V> W>
		XTAL_NEW_(explicit) subtype(W w)
		noexcept
		:	subtype(U(0, w), 0)
		{}
		XTAL_NEW_(implicit) subtype()
		noexcept
		:	subtype(U(0, 0), 0)
		{}

		XTAL_DEF_(return,inline,let)
		subview(auto &&w) const
		noexcept -> T_
		{
			return T_(S_::subhead(XTAL_REF_(w)), S_::step());
		}

		///\
		Advance `v` steps while retaining `size`. \

		XTAL_DEF_(inline,let)
		operator *=(V v)
		noexcept -> T_ &
		{
			using _xtd::ranges::distance;
			using _xtd::ranges::next;
			auto const i0 = S_::begin(), iM = S_::end();
			auto const nm = v*distance(i0, iM);
			(void) S_::view(*next(i0, nm), *next(iM, nm));
			S_::step() += v;
			return self();
		}
		XTAL_DEF_(inline,let)
		operator /=(V v)
		noexcept -> T_ &
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

		XTAL_DEF_(inline,let)
		operator +=(V v)
		noexcept -> T_ &
		{
			using _xtd::ranges::next;
		//	auto &s = self();
			auto const i0 = S_::begin(), iM = S_::end();
			auto const j0 = iM, jN = next(j0, v);
			S_::step() += i0 != iM;
			(void) S_::view(*j0, *jN);
			return self();
		}
		XTAL_DEF_(inline,let)
		operator -=(V v)
		noexcept -> T_ &
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

		XTAL_DEF_(return,inline,let)
		operator < (subtype const &t) const
		noexcept -> bool
		{
			return S_::end() == t.begin();
		}
		XTAL_DEF_(return,inline,let)
		operator > (subtype const &t) const
		noexcept -> bool
		{
			return S_::begin() == t.end();
		}

	};
};


////////////////////////////////////////////////////////////////////////////////

template <> struct render<void> : render<counter_t<>> {};
template <> struct render<    > : render<counter_t<>> {};


////////////////////////////////////////////////////////////////////////////////

static_assert(render_q<render_t<counter_t<>>>);
static_assert(render_q<render_t<counted_t<>>>);


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
