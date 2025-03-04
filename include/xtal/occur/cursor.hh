#pragma once
#include "./any.hh"
#include "./review.hh"
#include "./resize.hh"
#include "./restep.hh"



XTAL_ENV_(push)
namespace xtal::occur
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
/*!
\brief
Tracks the logical progression of contiguous block-based `processor`s.

\details   
Characterized by the integral-valued `step` and `size`,
with arithmetic operations for adjacent movement and comparison.

The arithmetic operators are used to jump and/or resize to adjacent blocks,
while the logic operators facilitate contiguous comparison.

The range-based `cursor<counted_q>` additionall records sample position,
making it possible to obtain `subview`s of infinite/generated streams.
Usage is subject to overflow when the underlying type is insufficient,
e.g. a `cursor<counted_t<int>>` running at 192 kHz would overflow in `2^31/192000/60/60 < 4` hours.

The integer-based `cursor<counter_q>` provides a lossy counterpart,
mitigating potential overflow with `step` increasing once per block.

\note
Preserves contiguity on `efflux` by constraining step-order by `assert`ion.
May be resynchronized by `influx` unchecked.
*/
template <class=counter_t<>>
struct  cursor;

template <class ...Ts>
concept cursor_q = bond::tag_in_p<cursor, Ts...> ;


////////////////////////////////////////////////////////////////////////////////
/*!
\brief  	Tracks the logical progression of contiguous block-based `processor`s.
*/
template <incomplete_q T>
struct cursor<T>
{
	using superkind = bond::tag<cursor>;

	template <class S>
	class subtype : public bond::compose_s<S, superkind>
	{
		static_assert(any_q<S>);
		using S_ = bond::compose_s<S, superkind>;
		using U_ = typename S_::head_type;
		using V_ = counter_t<U_>;
		using V_step = V_;
		using V_size = V_;
	
	public:
		using S_::S_;
		using S_::self;
		using S_::twin;
		
		using value_type = V_;

	public:// OPERATE
		XTAL_DEF_(return,inline,let)        skip(V_step i) const noexcept -> auto   {auto o = twin(); (void) o.step(i + self().step()); return o;} ///<\returns `twin` with `step` adjusted by `i`.
		XTAL_DEF_(return,inline,let)        null(V_step i) const noexcept -> auto   {auto o = null(); (void) o.step(i                ); return o;} ///<\returns the adjacent block of `size=0` with `step=i`.
		XTAL_DEF_(return,inline,let)        null(        ) const noexcept -> auto   {return twin().operator+=(0);}                                 ///<\returns the adjacent block of `size=0`.

		XTAL_DEF_(return,inline,let)        next(V_step i) const noexcept -> auto   {return self().operator* (i);}                ///<\returns the following `i`th block with the same `size`.
		XTAL_DEF_(return,inline,let)        next(        ) const noexcept -> auto   {return twin().operator++( );}                ///<\returns the following       block with the same `size`.

		XTAL_DEF_(return,inline,let) operator + (V_size n) const noexcept -> auto   {return twin().operator+=(n);}                ///<\returns the following adjacent block of size `n`.
		XTAL_DEF_(return,inline,let) operator - (V_size n) const noexcept -> auto   {return twin().operator-=(n);}                ///<\returns the preceding adjacent block of size `n`.

		XTAL_DEF_(return,inline,let) operator * (V_step i) const noexcept -> auto   {return twin().operator*=(i);}                ///<\returns the following `i`th block with the same `size`.
		XTAL_DEF_(return,inline,let) operator / (V_step i) const noexcept -> auto   {return twin().operator/=(i);}                ///<\returns the preceding `i`th block with the same `size`.

		XTAL_DEF_(mutate,inline,let) operator ++(   )        noexcept -> auto & {return self().operator+=(count_f(self()));}      ///<\returns `self()` after   advancing one step while retaining `size`.
		XTAL_DEF_(mutate,inline,let) operator --(   )        noexcept -> auto & {return self().operator-=(count_f(self()));}      ///<\returns `self()` after  retreating one step while retaining `size`.
		
		XTAL_DEF_(mutate,inline,let) operator ++(int)        noexcept -> auto   {return _detail::thunk_f(twin()) (operator++());} ///<\returns `twin()` before  advancing one step while retaining `size`.
		XTAL_DEF_(mutate,inline,let) operator --(int)        noexcept -> auto   {return _detail::thunk_f(twin()) (operator--());} ///<\returns `twin()` before retreating one step while retaining `size`.

		XTAL_DEF_(return,inline,let) operator >=(subtype const &t) const noexcept -> bool {return self().operator>(t.self()) or self().operator==(t.self());} ///<\returns `true` if the LHS immediately follows  the RHS.
		XTAL_DEF_(return,inline,let) operator <=(subtype const &t) const noexcept -> bool {return self().operator<(t.self()) or self().operator==(t.self());} ///<\returns `true` if the LHS immediately precedes the RHS.

	public:// FLOW
		template <signed N_ion>
		XTAL_DEF_(return,inline,let)
		fuse(auto &&o)
		noexcept -> signed
		{
			return S_::template fuse<N_ion>(XTAL_REF_(o));
		}

		/*!
		\brief  	Updates the incoming position, enforcing `step`-ordering on `efflux` by `assert`ion.
		\brief  	Unrecognized `cursor_q` are incorporated by arithmetic assigment.
		*/
		template <signed N_ion> requires in_n<N_ion, -1>
		XTAL_DEF_(return,inline,let)
		fuse(cursor_q auto &&t)
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
		template <signed N_ion> requires in_n<N_ion, +1>
		XTAL_DEF_(return,let)
		fuse(cursor_q auto &&t)
		noexcept -> signed
		{
			auto &s = self();
			if (s == t) {
				return 1;
			}
			else if constexpr (fungible_q<T, decltype(t)>) {
				s = t;
				return 0;
			}
			else {
				s.operator+=(0);
				s.operator-=(count_f(t));
				(void) s.step(t.step());
				return 0;
			}
		}

	};
};


////////////////////////////////////////////////////////////////////////////////

template <counter_q V>
struct cursor<V>
{
	template <class T>
	using holokind = bond::compose<cursor<T>, resize<V>, restep<V>>;

	template <class S>
	class subtype : public bond::compose_s<S, holokind<subtype<S>>>
	{
		static_assert(any_q<S>);
		using S_ = bond::compose_s<S, holokind<subtype<S>>>;
		using V_step = V;
		using V_size = V;

	public:// CONSTRUCT
	//	using S_::S_;
		XTAL_NEW_(delete) (subtype, noexcept = default)
	//	XTAL_NEW_(create) (subtype, noexcept = default)
		XTAL_NEW_(move)   (subtype, noexcept = default)
		XTAL_NEW_(copy)   (subtype, noexcept = default)
		XTAL_NEW_(cast)   (subtype, noexcept :        )
		XTAL_NEW_(then)   (subtype, noexcept : S_     )

		XTAL_NEW_(implicit) subtype()
		noexcept
		:	S_(0, 0)
		{}
		XTAL_NEW_(explicit) subtype(iterated_q auto &&o, auto &&...oo)
		noexcept
		:	S_(count_f(XTAL_REF_(o)), XTAL_REF_(oo)...)
		{}

		XTAL_DEF_(return,inline,let)
		subview(auto &&w) const
		noexcept -> auto
		{
			auto t = twin(); (void) t.size(count_f(w)); return t;
		}

	public:// OPERATE
		using S_::self;
		using S_::twin;

		XTAL_DEF_(inline,let) operator *=(V_step i) noexcept -> auto & {S_::step() += i; return self();}                                   ///<\returns `self()` after  advancing `i` steps of the current `size`.
		XTAL_DEF_(inline,let) operator /=(V_step i) noexcept -> auto & {S_::step() -= i; return self();}                                   ///<\returns `self()` after retreating `i` steps of the current `size`.

		XTAL_DEF_(inline,let) operator +=(V_size n) noexcept -> auto & {S_::step() += S_::size() != 0; (void) S_::size(n); return self();} ///<\returns `self()` after  advancing one step of size `n`.
		XTAL_DEF_(inline,let) operator -=(V_size n) noexcept -> auto & {S_::step() -=          n != 0; (void) S_::size(n); return self();} ///<\returns `self()` after retreating one step of size `n`.

		XTAL_DEF_(return,inline,let) operator < (subtype const &t) const noexcept -> bool {return S_::next().step() == t.step();}          ///<\returns `true` iff the LHS strictly precedes the RHS.
		XTAL_DEF_(return,inline,let) operator > (subtype const &t) const noexcept -> bool {return S_::step() == t.next().step();}          ///<\returns `true` iff the LHS strictly follows  the RHS.

	};
};


////////////////////////////////////////////////////////////////////////////////

template <counted_q U>
struct cursor<U>
{
private:
	using V = based_t<iteratee_t<U>>;

public:
	template <class T>
	using holokind = bond::compose<cursor<T>, review<U>, restep<V>>;

	template <class S>
	class subtype : public bond::compose_s<S, holokind<subtype<S>>>
	{
		static_assert(any_q<S>);
		using S_ = bond::compose_s<S, holokind<subtype<S>>>;
		using V_step = V;
		using V_size = V;

	public:// CONSTRUCT
		using S_::S_;
		
		XTAL_NEW_(implicit) subtype(U u, V v)
		noexcept
		:	S_(u, v)
		{}
		template <make_q<V> W>
		XTAL_NEW_(implicit) subtype(W w)
		noexcept
		:	subtype(U(0, w), 0)
		{}
		XTAL_NEW_(implicit) subtype()
		noexcept
		:	subtype(U(0, 0), 0)
		{}

		XTAL_DEF_(return,inline,let)
		subview(auto &&w) const
		noexcept -> typename S_::self_type
		{
			return {S_::subhead(XTAL_REF_(w)), S_::step()};
		}

	public:// OPERATE
		using S_::self;
		using S_::twin;

		XTAL_DEF_(inline,let)
		operator *=(V_step i)
		noexcept -> auto &
		{
			using _xtd::ranges::distance;
			using _xtd::ranges::next;
			auto const i0 = S_::begin(), iM = S_::end();
			auto const nm = i*distance(i0, iM);
			(void) S_::view(*next(i0, nm), *next(iM, nm));
			S_::step() += i;
			return self();
		}
		///<\brief Advances `i` steps while retaining `size`.

		XTAL_DEF_(inline,let)
		operator /=(V_step i)
		noexcept -> auto &
		{
			using _xtd::ranges::distance;
			using _xtd::ranges::prev;
			auto const i0 = S_::begin(), iM = S_::end();
			auto const nm = i*distance(i0, iM);
			(void) S_::view(*prev(i0, nm), *prev(iM, nm));
			S_::step() -= i;
			return self();
		}
		///<\brief Retreats `i` steps while retaining `size`.

		XTAL_DEF_(inline,let)
		operator +=(V_size n)
		noexcept -> auto &
		{
			using _xtd::ranges::next;
			auto const i0 = S_::begin(), iM = S_::end();
			auto const j0 = iM, jN = next(j0, n);
			S_::step() += i0 != iM;
			(void) S_::view(*j0, *jN);
			return self();
		}
		///<\brief Advances `1` step of size `n`.

		XTAL_DEF_(inline,let)
		operator -=(V_size n)
		noexcept -> auto &
		{
			using _xtd::ranges::prev;
			auto const i0 = S_::begin(), iM = S_::end();
			auto const jN = i0, j0 = prev(jN, n);
			S_::step() -= n != 0;
			(void) S_::view(*j0, *jN);
			return self();
		}
		///<\brief Retreats `1` step of size `n`.

		XTAL_DEF_(return,inline,let) operator > (subtype const &t) const noexcept -> bool {return S_::begin() == t.  end();}///<\returns `true` iff the LHS strictly precedes the RHS.
		XTAL_DEF_(return,inline,let) operator < (subtype const &t) const noexcept -> bool {return S_::  end() == t.begin();}///<\returns `true` iff the LHS strictly follows  the RHS.

	};
};


////////////////////////////////////////////////////////////////////////////////

template <cursor_q X, cursor_q Y> requires different_q<X, Y>
XTAL_DEF_(return,inline,let)
operator == (X const &x, Y const &y)
noexcept -> bool
{
	auto const &s = x.self();
	auto const &t = y.self();
	return s.step() == t.step() and s.size() == t.size();
}


////////////////////////////////////////////////////////////////////////////////

template <class W=counter_t<>>
using cursor_t = confined_t<cursor<W>>;

XTAL_DEF_(let) cursor_f = [] XTAL_1FN_(call) (cursor_t<>);

static_assert(cursor_q<cursor_t<counter_t<>>>);
static_assert(cursor_q<cursor_t<counted_t<>>>);


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
