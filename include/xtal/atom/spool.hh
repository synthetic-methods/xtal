#pragma once
#include "./any.hh"
#include "./buffer.hh"






XTAL_ENV_(push)
namespace xtal::atom
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <class ..._s> struct   spool;
template <class ..._s> using    spool_t = typename spool<_s...>::type;
template <class ...Ts> concept  spool_q = bond::tag_p<spool_t, Ts...>;


////////////////////////////////////////////////////////////////////////////////
///\
A priority-queue based on `buffer_t<A>`. \
Currently used for both event spools (\see `occur/schedule.ii`) \
and to implement polymorphism (\see `processor/polymer.ii`). \

template <class A>
struct spool<A>
{
	template <class T>
	using endotype = arranged_t<T>;

	template <class T>
	using holotype = bond::compose_s<endotype<T>, bond::tag<spool_t>>;

	template <class T>
	class homotype : public holotype<T>
	{
		using S_ = holotype<T>;

		using U_buffer = buffer_t<A>;
		using U_point  = typename U_buffer::iterator;
		using U_value  = typename U_buffer::value_type;
		using U_count  = typename U_buffer::difference_type;
		
		U_buffer u_buffer;
		U_count u_begin = 0;
		U_count u_end   = 0;

	public:
		using value_type = A;

	public:
		using S_::S_;
		
//		XTAL_NEW_(delete) (homotype, noexcept = default)
//		XTAL_NEW_(create) (homotype, noexcept = default)
//		XTAL_NEW_(move)   (homotype, noexcept = default)
//		XTAL_NEW_(copy)   (homotype, noexcept = default)
//		XTAL_NEW_(cast)   (homotype, noexcept)
		
		///\note\
		The `size()` of the `std::initializer_list` determines the extent of lookup/lookahead. \

		XTAL_NEW_(explicit)
		homotype(          bond::seek_t<>, auto &&...oo)
		noexcept(false)
		:	u_buffer{                       U_value{XTAL_REF_(oo)}...}
		,	u_begin(0), u_end(sizeof...(oo))
		{}
		XTAL_NEW_(explicit)
		homotype(auto &&o, bond::seek_t<>, auto &&...oo)
		noexcept(false)
		:	u_buffer{U_value{XTAL_REF_(o)}, U_value{XTAL_REF_(oo)}...}
		,	u_begin(1), u_end(sizeof...(oo))
		{}

		XTAL_FX2_(to) (XTAL_DEF_(return,inline,get)   end(U_count n=0), _std::prev(u_buffer.end  (), n + u_end  ))
		XTAL_FX2_(to) (XTAL_DEF_(return,inline,get) begin(U_count n=0), _std::next(u_buffer.begin(), n + u_begin))
		XTAL_FX2_(to) (XTAL_DEF_(return,inline,get)  peek(U_count n=0), *begin(n))
		XTAL_FX2_(to) (XTAL_DEF_(return,inline,get)  span(U_count n, U_count m), _std::span(begin(n), end(m)))
		XTAL_FX2_(to) (XTAL_DEF_(return,inline,get)  span(U_count n), span(n, n))
		XTAL_FX2_(to) (XTAL_DEF_(return,inline,get)  span(         ), span(0, 0))

		XTAL_DEF_(mutate,inline,let)
		advance(U_count n=1)
		noexcept -> U_point
		{
			u_begin += n;
			return begin();
		}
		XTAL_DEF_(mutate,inline,let)
		abandon(U_count n=1)
		noexcept -> U_point
		{
			if (n) {
				u_begin = 0;
				free();
			}
			return begin();
		}
		XTAL_DEF_(mutate,inline,let)
		free()
		noexcept -> void
		{
			u_buffer.erase(u_buffer.begin(), end());
		}

		XTAL_DEF_(mutate,inline,let)
		free(auto &&f)
		noexcept -> void
		{
			u_buffer.erase(_std::remove_if(begin(), end(), XTAL_REF_(f)), end());
		}
		template <auto  f>
		XTAL_DEF_(mutate,inline,let)
		free()
		noexcept -> void
		{
			u_buffer.erase(_std::remove_if(begin(), end(),           f ), end());
		}
		template <class F>
		XTAL_DEF_(mutate,inline,let)
		free()
		noexcept -> void
		{
			return free<bond::operate<F>{}>();
		}

		///\note\
		Cost can be amortized by invoking `advance` and `abandon` separately, \
		allowing for branchless `advance`ment. \

		XTAL_DEF_(let)
		pop(U_point i)
		noexcept -> void
		{
			assert(i < end());
			u_begin -= i < begin();
			u_buffer.erase(i);
			abandon(begin() == end());
		}
		XTAL_DEF_(let)
		pop()
		noexcept -> void
		{
			advance();
			abandon(begin() == end());
		}
		XTAL_DEF_(return,inline,let)
		scan(auto &&w)
		noexcept -> U_point
		{
			return _std::lower_bound(begin(), u_buffer.end(), XTAL_REF_(w));
		}
		XTAL_DEF_(return,inline,let)
		scan(auto &&w, auto &&f)
		noexcept -> U_point
		{
			return _std::lower_bound(begin(), u_buffer.end(), XTAL_REF_(w)
			,	[f=XTAL_REF_(f)] (auto &&x, auto &&y) XTAL_0FN_(to) (f(x) < f(y))
			);
		}
		///\note\
		Conflicting entries w.r.t. `==` are overwritten. \

		XTAL_DEF_(mutate,inline,let)
		push(same_q<U_value> auto &&u)
		noexcept -> U_point
		{
			U_point v_ = scan(u);
			if (u_buffer.size() and u == *v_) {
				v_->~U_value(); return new (v_) U_value(XTAL_REF_(u));
			}
			else {
				return poke(v_, XTAL_REF_(u));
			}
		}
		XTAL_DEF_(mutate,inline,let)
		push(auto &&..._s)
		noexcept -> U_point
		{
			return push(U_value(XTAL_REF_(_s)...));
		}

		XTAL_DEF_(mutate,inline,let)
		poke(U_point v_, same_q<U_value> auto &&u)
		noexcept -> U_point
		{
			return u_buffer.insert(v_, XTAL_REF_(u));
		}
		XTAL_DEF_(mutate,inline,let)
		poke(U_point v_, auto &&..._s)
		noexcept -> U_point
		{
			return u_buffer.emplace(v_, XTAL_REF_(_s)...);
		}

	};
	using type = derive_t<homotype>;

};


////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
