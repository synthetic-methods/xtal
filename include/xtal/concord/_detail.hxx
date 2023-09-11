#include "../concord/_kernel.hxx"








namespace _detail
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

using namespace _retail::_detail;


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

struct refine_head
{
	template <any_q S>
	class subtype: public S
	{
	public:
		using S::S;

	};
	template <any_q S> requires (1 == S::arity::value)
	class subtype<S>: public S
	{
		using T_ = typename S::self_t;
		using U_ = typename S::head_t;

	public:
		using S::S;
		using S::head;

		///\
		Implicit conversion to the singleton kernel-type. \

		XTAL_DO4_(XTAL_OP0_(implicit) U_(), {return head();})
		
		///\returns the `sentinel` boundary in the direction of `N_polarity`. \

		template <int N_polarity=0>
		XTAL_FN2 sentry(XTAL_DEF... oo)
		XTAL_0EX
		XTAL_REQ algebraic_field_q<U_> and equality_q<U_> and sign_p<N_polarity>
		{
			using L = _std::numeric_limits<U_>;
			if constexpr (N_polarity == +1) return T_(L::max(), XTAL_REF_(oo)...);
			if constexpr (N_polarity ==  0) return T_(0,        XTAL_REF_(oo)...);
			if constexpr (N_polarity == -1) return T_(L::min(), XTAL_REF_(oo)...);
		}

	};
};
struct refine_tuple
{
	template <any_q S>
	class subtype: public S
	{
	public:
		using S::S;
		using S::tuple;

		using tuple_type = XTAL_TYP_(XTAL_VAL_(S).tuple());

		XTAL_DO4_(XTAL_OP0_(implicit) tuple_type(), {return tuple();})
		
	};
};


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

template <class U>
struct refer_iterators
:	common::compose<>
{};
template <class U> requires begin_q<U>
struct refer_iterators<U>
{
	template <any_q S>
	class subtype: public S
	{
	public:
		using S::S;
		XTAL_TN2 begin() XTAL_0EX {return S::head().begin();}
		XTAL_TN2   end() XTAL_0EX {return S::head().  end();}
		
	};
	template <any_q S> requires begin_q<U const &>
	class subtype<S>: public S
	{
	public:
		using S::S;
		XTAL_TN2 begin() XTAL_0EX {return S::head().begin();}
		XTAL_TN2   end() XTAL_0EX {return S::head().  end();}
		XTAL_TN2 begin() XTAL_0FX {return S::head().begin();}
		XTAL_TN2   end() XTAL_0FX {return S::head().  end();}

	};
};


///////////////////////////////////////////////////////////////////////////////

template <class U>
struct refer_equality
:	common::compose<>
{};
template <class U> requires equality_p<U>
struct refer_equality<U>
{
	template <any_q S>
	class subtype: public S
	{
	public:
		using S::S;
		XTAL_OP2_(bool) == (subtype const &t) XTAL_0FX {return S::head() == t.head();}
		XTAL_OP2_(bool) != (subtype const &t) XTAL_0FX {return S::head() != t.head();}

	};
};


template <class U>
struct refer_inequality
:	common::compose<>
{};
template <class U> requires inequality_p<U>
struct refer_inequality<U>
{
	template <any_q S>
	class subtype: public S
	{
	public:
		using S::S;
		XTAL_OP2 <=> (subtype const &t)
		XTAL_0FX
		{
			return S::head() <=> t.head();
		}

	};
};


template <class U>
struct refer_qualities
:	common::compose<void
	,	refer_equality<U>
	,	refer_inequality<U>
	>
{};


////////////////////////////////////////////////////////////////////////////////

template <class U, size_t N=0>
struct refer_binary_logic
:	common::compose<>
{};
template <class U>
struct refer_binary_logic<U, 0>
:	common::compose<void
	,	refer_binary_logic<U, 1>
	,	refer_binary_logic<U, 2>
	>
{};
template <class U> requires binary_logic_p<U, 1> and remember_q<U>
struct refer_binary_logic<U, 1>
{
	template <any_q S>
	class subtype: public S
	{
	public:
		using S::S;
		XTAL_OP1 ^=(XTAL_DEF_(to_q<U>) w) XTAL_0EX {return S::head() ^=(U) XTAL_REF_(w), S::self();}
		XTAL_OP1 |=(XTAL_DEF_(to_q<U>) w) XTAL_0EX {return S::head() |=(U) XTAL_REF_(w), S::self();}
		XTAL_OP1 &=(XTAL_DEF_(to_q<U>) w) XTAL_0EX {return S::head() &=(U) XTAL_REF_(w), S::self();}

	};
};
template <class U> requires binary_logic_p<U, 2>
struct refer_binary_logic<U, 2>
{
	template <any_q S>
	class subtype: public S
	{
		using T_ = typename S::self_t;
	
	public:
		using S::S;
		XTAL_OP2 ^ (XTAL_DEF_(to_q<U>) w) XTAL_0FX {return T_(S::head() ^ (U) XTAL_REF_(w));}
		XTAL_OP2 | (XTAL_DEF_(to_q<U>) w) XTAL_0FX {return T_(S::head() | (U) XTAL_REF_(w));}
		XTAL_OP2 & (XTAL_DEF_(to_q<U>) w) XTAL_0FX {return T_(S::head() & (U) XTAL_REF_(w));}

	};
};


template <class U, size_t N=0>
struct refer_logics
:	common::compose<void
	,	refer_binary_logic<U, N>
	>
{};


////////////////////////////////////////////////////////////////////////////////

template <class U, size_t N=0>
struct refer_multiplicative_group
:	common::compose<>
{};
template <class U>
struct refer_multiplicative_group<U, 0>
:	common::compose<void
	,	refer_multiplicative_group<U, 1>
	,	refer_multiplicative_group<U, 2>
	>
{};
template <class U> requires multiplicative_group_p<U, 1> and remember_q<U>
struct refer_multiplicative_group<U, 1>
{
	template <any_q S>
	class subtype: public S
	{
	public:
		using S::S;
		XTAL_OP1 *=(XTAL_DEF_(to_q<U>) w) XTAL_0EX {return S::head() *=(U) XTAL_REF_(w), S::self();}
		XTAL_OP1 /=(XTAL_DEF_(to_q<U>) w) XTAL_0EX {return S::head() /=(U) XTAL_REF_(w), S::self();}

	};
};
template <class U> requires multiplicative_group_p<U, 2>
struct refer_multiplicative_group<U, 2>
{
	template <any_q S>
	class subtype: public S
	{
		using T_ = typename S::self_t;
	
	public:
		using S::S;
		XTAL_OP2 * (XTAL_DEF_(to_q<U>) w) XTAL_0FX {return T_(S::head() * (U) XTAL_REF_(w));}
		XTAL_OP2 / (XTAL_DEF_(to_q<U>) w) XTAL_0FX {return T_(S::head() / (U) XTAL_REF_(w));}

	};
};


template <class U, size_t N=0>
struct refer_additive_group
:	common::compose<>
{};
template <class U>
struct refer_additive_group<U, 0>
:	common::compose<void
	,	refer_additive_group<U, 1>
	,	refer_additive_group<U, 2>
	>
{};
template <class U> requires additive_group_p<U, 1> and remember_q<U>
struct refer_additive_group<U, 1>
{
	template <any_q S>
	class subtype: public S
	{
	public:
		using S::S;
		XTAL_OP1 +=(XTAL_DEF_(to_q<U>) w) XTAL_0EX {return S::head() +=(U) XTAL_REF_(w), S::self();}
		XTAL_OP1 -=(XTAL_DEF_(to_q<U>) w) XTAL_0EX {return S::head() -=(U) XTAL_REF_(w), S::self();}

	};
};
template <class U> requires additive_group_p<U, 2>
struct refer_additive_group<U, 2>
{
	template <any_q S>
	class subtype: public S
	{
		using T_ = typename S::self_t;
	
	public:
		using S::S;
		XTAL_OP2 + (XTAL_DEF_(to_q<U>) w) XTAL_0FX {return T_(S::head() + (U) XTAL_REF_(w));}
		XTAL_OP2 - (XTAL_DEF_(to_q<U>) w) XTAL_0FX {return T_(S::head() - (U) XTAL_REF_(w));}
		XTAL_OP1 - () XTAL_0FX {return T_(-S::head());}

	};
};


template <class U, size_t N=0>
struct refer_discrete_group
:	common::compose<>
{};
template <class U>
struct refer_discrete_group<U, 0>
:	common::compose<void
	,	refer_discrete_group<U, 1>
	,	refer_discrete_group<U, 2>
	>
{};
template <class U> requires discrete_group_p<U, 1> and remember_q<U>
struct refer_discrete_group<U, 1>
{
	template <any_q S>
	class subtype: public S
	{
	public:
		using S::S;
		XTAL_OP1 ++(int) XTAL_0EX {auto  t = S::self(); ++S::head(); return t;}
		XTAL_OP1 --(int) XTAL_0EX {auto  t = S::self(); --S::head(); return t;}
		XTAL_OP1 ++()    XTAL_0EX {auto &s = S::self(); ++S::head(); return s;}
		XTAL_OP1 --()    XTAL_0EX {auto &s = S::self(); --S::head(); return s;}

	};
};


template <class U, size_t N=0>
struct refer_groups
:	common::compose<void
	,	refer_multiplicative_group<U, N>
	,	refer_additive_group<U, N>
	,	refer_discrete_group<U, N>
	>
{};


}//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
