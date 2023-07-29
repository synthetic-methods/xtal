#pragma once
#include "./any.hpp"
#include "./sluice.hpp"





XTAL_ENV_(push)
namespace xtal::compound::fluid
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <class ..._s> XTAL_NYM siphon;
template <class ..._s> XTAL_USE siphon_t = typename siphon<_s...>::type;
template <class ...Ts> XTAL_ASK siphon_q = tag_p<siphon, Ts...>;


////////////////////////////////////////////////////////////////////////////////
///\

template <class A>
struct siphon<A>
{
	template <class T>
	using demitype = iterate_t<T>;

	template <class T>
	using hemitype = compose_s<demitype<T>, tag<siphon>>;

	template <class T>
	class homotype: public hemitype<T>
	{
		using S_ = hemitype<T>;

		using store_t = sluice_t<A>;
		using valve_t = typename store_t::iterator;
		using value_t = typename store_t::value_type;
		using count_t = typename store_t::difference_type;

		store_t store_m{};
		count_t begin_n = 0;
		count_t   end_n = 0;

	public:
		using S_::S_;
		
		///\note\
		The `size()` of the `std::initializer_list` determines the extent of lookup/lookahead. \

		XTAL_CON homotype(bracket_t<value_t> w)
		:	end_n {_std::distance(w.begin(), w.end())}
		,	store_m(w)
		{}

		XTAL_TO2_(XTAL_FN2     begin(count_t n=0), _std::next(store_m.begin(), begin_n + n))
		XTAL_TO2_(XTAL_FN2       end(count_t n=0), _std::prev(store_m.  end(),   end_n + n))
		XTAL_FN2_(value_t &)    peek(count_t n=0) XTAL_0EX {              return *begin(n);}
		XTAL_FN1_(value_t &) advance(count_t n=1) XTAL_0EX {begin_n += n; return *begin(0);}
		XTAL_FN1_(value_t &) abandon(bool    n=1)
		XTAL_0EX
		{
			if (n) {
				begin_n = 0;
				clear();
			}
			return *begin();
		}
		XTAL_FN0 clear()
		XTAL_0EX
		{
			store_m.erase(store_m.begin(), end());
		}

		///\note\
		Cost can be amortized by invoking `advance` and `abandon` separately, \
		allowing for branchless `advance`ment. \

		XTAL_FN0 pop(valve_t i)
		XTAL_0EX
		{
			assert(i < end());
			begin_n -= i < begin();
			store_m.erase(i);
			abandon(begin() == end());
		}
		XTAL_FN0 pop()
		XTAL_0EX
		{
			advance();
			abandon(begin() == end());
		}
		XTAL_FN2_(valve_t) scan(XTAL_DEF w)
		XTAL_0EX
		{
			return _std::lower_bound(store_m.begin(), store_m.end()
			,	XTAL_REF_(w)
			);
		}
		XTAL_FN2_(valve_t) scan(XTAL_DEF w, XTAL_DEF f)
		XTAL_0EX
		{
			return _std::lower_bound(store_m.begin(), store_m.end()
			,	XTAL_REF_(w)
			,	[f = XTAL_REF_(f)] (XTAL_DEF x, XTAL_DEF y) XTAL_0FN_(f(x) < f(y))
			);
		}
		///\note\
		Conflicting entries w.r.t. `==` are overwritten. \

		XTAL_FN1_(valve_t) push(value_t v)
		XTAL_0EX
		{
			valve_t v_ = scan(v);
			if (*v_ == v) {
				_std::swap(*v_, v); return v_;
			}
			else {
				return poke(v_, XTAL_MOV_(v));
			}
		}
		template <is_q<value_t> W>
		XTAL_FN1_(valve_t) poke(valve_t v_, W &&w)
		XTAL_0EX
		{
			return store_m.insert(v_, XTAL_REF_(w));
		}
		XTAL_FN1_(valve_t) poke(valve_t v_, XTAL_DEF ...ws)
		XTAL_0EX
		{
			return store_m.insert(v_, value_t(XTAL_REF_(ws)...));
		}
		XTAL_FN1_(valve_t) poke(valve_t v_, XTAL_DEF ...ws)
		XTAL_0EX
		XTAL_REQ_(store_m.inplace(v_, XTAL_REF_(ws)...))
		{
			return store_m.inplace(v_, XTAL_REF_(ws)...);
		}

	};
	using type = _detail::isotype<homotype>;

};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
