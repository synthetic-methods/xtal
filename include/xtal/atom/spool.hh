#pragma once
#include "./any.hh"
#include "./store.hh"






XTAL_ENV_(push)
namespace xtal::atom
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <class ..._s> XTAL_TYP spool;
template <class ..._s> XTAL_USE spool_t = typename spool<_s...>::type;
template <class ...Ts> XTAL_REQ spool_q = bond::any_tag_p<spool_t, Ts...>;


////////////////////////////////////////////////////////////////////////////////
///\
A fluid-sized fixed-capacity priority-queue based on `store_t<A>`. \
Currently used for both event queues (\see `occur/schedule.ii`) \
and to implement polymorphism (\see `processor/polymer.ii`). \

template <class A>
struct spool<A>
{
	template <class T>
	using allotype = initerated_t<T>;

	template <class T>
	using holotype = bond::compose_s<allotype<T>, bond::tag<spool_t>>;

	template <class T>
	class homotype : public holotype<T>
	{
		using T_ = holotype<T>;

		using U_store = store_t<A>;
		using U_point = typename U_store::iterator;
		using U_value = typename U_store::value_type;
		using U_count = typename U_store::difference_type;

		U_store u_store;
		U_count u_begin = 0;
		U_count u_end   = 0;

	public:
		using value_type = A;

	public:
	//	using T_::T_;
		
		XTAL_CO0_(homotype)
		XTAL_CO1_(homotype)
		XTAL_CO4_(homotype)

		///\note\
		The `size()` of the `std::initializer_list` determines the extent of lookup/lookahead. \

		XTAL_CON_(implicit) homotype(embrace_t<U_value> w)
		:	u_end(count_f(w))
		,	u_store(w.begin(), w.end())
		{}

		XTAL_TO2_(XTAL_DEF_(return,inline) XTAL_LET   end(U_count n=0), _std::prev(u_store.end  (), n + u_end  ))
		XTAL_TO2_(XTAL_DEF_(return,inline) XTAL_LET begin(U_count n=0), _std::next(u_store.begin(), n + u_begin))
		XTAL_TO2_(XTAL_DEF_(return,inline) XTAL_LET  peek(U_count n=0), *begin(n))
		XTAL_TO2_(XTAL_DEF_(return,inline) XTAL_RET  span(U_count n, U_count m), _std::span(begin(n), end(m)))
		XTAL_TO2_(XTAL_DEF_(return,inline) XTAL_RET  span(U_count n), span(n, n))
		XTAL_TO2_(XTAL_DEF_(return,inline) XTAL_RET  span(         ), span(0, 0))

		XTAL_DEF_(inline)
		XTAL_LET advance(U_count n=1)
		XTAL_0EX -> U_point
		{
			u_begin += n;
			return begin();
		}
		XTAL_DEF_(inline)
		XTAL_LET abandon(U_count n=1)
		XTAL_0EX -> U_point
		{
			if (n) {
				u_begin = 0;
				cull();
			}
			return begin();
		}
		XTAL_DEF_(inline)
		XTAL_LET cull()
		XTAL_0EX -> void
		{
			u_store.erase(u_store.begin(), end());
		}
		XTAL_DEF_(inline)
		XTAL_LET cull(auto &&f)
		XTAL_0EX -> void
		{
			u_store.erase(_std::remove_if(begin(), end(), f), end());
		}

		///\note\
		Cost can be amortized by invoking `advance` and `abandon` separately, \
		allowing for branchless `advance`ment. \

	//	XTAL_DEF_(inline)
		XTAL_LET pop(U_point i)
		XTAL_0EX -> void
		{
			assert(i < end());
			u_begin -= i < begin();
			u_store.erase(i);
			abandon(begin() == end());
		}
	//	XTAL_DEF_(inline)
		XTAL_LET pop()
		XTAL_0EX -> void
		{
			advance();
			abandon(begin() == end());
		}
		XTAL_DEF_(return,inline)
		XTAL_LET scan(auto &&w)
		XTAL_0EX -> U_point
		{
			return _std::lower_bound(u_store.begin(), u_store.end(), XTAL_REF_(w));
		}
		XTAL_DEF_(return,inline)
		XTAL_LET scan(auto &&w, auto &&f)
		XTAL_0EX -> U_point
		{
			return _std::lower_bound(u_store.begin(), u_store.end(), XTAL_REF_(w)
			,	[f = XTAL_REF_(f)] (auto &&x, auto &&y) XTAL_0FN_(f(x) < f(y))
			);
		}
		///\note\
		Conflicting entries w.r.t. `==` are overwritten. \

	//	XTAL_DEF_(inline)
		XTAL_LET push(U_value u)
		XTAL_0EX -> U_point
		{
			if (u_store.empty()) {
				u_store.push_back(XTAL_MOV_(u));
				return begin();
			}
			U_point _v = scan(u);
			U_value &v = *_v;
			if (v == u) {
				v.~ U_value();
				v = XTAL_MOV_(u);
				return _v;
			}
			else {
				return poke(_v, XTAL_MOV_(u));
			}
		}
		XTAL_DEF_(inline)
		XTAL_LET push(auto ..._s)
		XTAL_0EX -> U_point
		{
			return push(U_value(XTAL_MOV_(_s)...));
		}

		XTAL_DEF_(inline)
		XTAL_LET poke(U_point _v, U_value u)
		XTAL_0EX -> U_point
		{
			return u_store.insert(_v, XTAL_MOV_(u));
		}
		XTAL_DEF_(inline)
		XTAL_LET poke(U_point _v, auto..._s)
		XTAL_0EX -> U_point
		{
			return u_store.emplace(_v, XTAL_MOV_(_s)...);
		}

	};
	using type = bond::isotype<homotype>;

};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
