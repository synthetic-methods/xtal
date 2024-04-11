#pragma once
#include "./any.hh"
#include "./buffer.hh"






XTAL_ENV_(push)
namespace xtal::atom
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <class ..._s> struct  spool;
template <class ..._s> using   spool_t = typename spool<_s...>::type;
template <class ...Ts> concept spool_q = bond::tag_p<spool, Ts...>;


////////////////////////////////////////////////////////////////////////////////
///\
A fluid-sized fixed-capacity priority-queue based on `buffer_t<A>`. \
Currently used for both event queues (\see `occur/schedule.ii`) \
and to implement polymorphism (\see `processor/polymer.ii`). \

template <class A>
struct spool<A>
{
	template <class T>
	using demitype = initerated_t<T>;

	template <class T>
	using hemitype = bond::compose_s<demitype<T>, bond::tag<spool>>;

	template <class T>
	class homotype : public hemitype<T>
	{
		using T_ = hemitype<T>;

		using U_buffer = buffer_t<A>;
		using U_point = typename U_buffer::iterator;
		using U_value = typename U_buffer::value_type;
		using U_count = typename U_buffer::difference_type;

		U_buffer u_buffer;
		U_count u_begin = 0;
		U_count u_end   = 0;

	public:
	//	using T_::T_;
		
		XTAL_CO0_(homotype)
		XTAL_CO1_(homotype)
		XTAL_CO4_(homotype)

		///\note\
		The `size()` of the `std::initializer_list` determines the extent of lookup/lookahead. \

		XTAL_CON homotype(braces_t<U_value> w)
		:	u_end{_std::distance(w.begin(), w.end())}
		,	u_buffer(w.begin(), w.end())
		{}

		XTAL_TO2_(XTAL_TN2   begin(U_count n=0), _std::next(u_buffer.begin(), n + u_begin))
		XTAL_TO2_(XTAL_TN2     end(U_count n=0), _std::prev(u_buffer.end  (), n + u_end  ))
		XTAL_TN1_(U_point) advance(U_count n=1) XTAL_0EX {u_begin += n; return  begin(0);}
		XTAL_TN1_(U_point) abandon(U_count n=1)
		XTAL_0EX
		{
			if (n) {u_begin = 0; cull();}
			return begin();
		}
		XTAL_TN0 cull()
		XTAL_0EX
		{
			u_buffer.erase(u_buffer.begin(), end());
		}
		XTAL_TN0 cull(auto &&f)
		XTAL_0EX
		{
			u_buffer.erase(_std::remove_if(begin(), end(), f), end());
		}

		///\note\
		Cost can be amortized by invoking `advance` and `abandon` separately, \
		allowing for branchless `advance`ment. \

		XTAL_TN0 pop(U_point i)
		XTAL_0EX
		{
			assert(i < end());
			u_begin -= i < begin();
			u_buffer.erase(i);
			abandon(begin() == end());
		}
		XTAL_TN0 pop()
		XTAL_0EX
		{
			advance();
			abandon(begin() == end());
		}
		XTAL_TN2_(U_point) scan(auto &&w)
		XTAL_0EX
		{
			return _std::lower_bound(u_buffer.begin(), u_buffer.end(), XTAL_REF_(w));
		}
		XTAL_TN2_(U_point) scan(auto &&w, auto &&f)
		XTAL_0EX
		{
			return _std::lower_bound(u_buffer.begin(), u_buffer.end(), XTAL_REF_(w)
			,	[f = XTAL_REF_(f)] (auto &&x, auto &&y) XTAL_0FN_(f(x) < f(y))
			);
		}
		///\note\
		Conflicting entries w.r.t. `==` are overwritten. \

		XTAL_TN1_(U_point) push(U_value v)
		XTAL_0EX
		{
			U_point v_ = scan(v);
			if (*v_ == v) {
				_std::swap(v, *v_); return v_;
			}
			else {
				return poke(v_, XTAL_MOV_(v));
			}
		}
		template <is_q<U_value> W>
		XTAL_TN1_(U_point) poke(U_point v_, W &&w)
		XTAL_0EX
		{
			return u_buffer.insert(v_, XTAL_REF_(w));
		}
		XTAL_TN1_(U_point) poke(U_point v_, auto &&...ws)
		XTAL_0EX
		{
			return u_buffer.insert(v_, U_value(XTAL_REF_(ws)...));
		}
		XTAL_TN1_(U_point) poke(U_point v_, auto &&...ws)
		XTAL_0EX
		XTAL_REQ_(u_buffer.inplace(v_, XTAL_REF_(ws)...))
		{
			return u_buffer.inplace(v_, XTAL_REF_(ws)...);
		}

	};
	using type = bond::isotype<homotype>;

};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
