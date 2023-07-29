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
		using U = typename S::head_t;

	public:
		using S::S;
		using S::head;

		///\
		Implicit conversion to the singleton kernel-type. \

		XTAL_DO4_(XTAL_OP0_(implicit) U(), {return head();})
		
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
:	compose<>
{};
template <class U> requires begin_q<U>
struct refer_iterators<U>
{
	template <any_q S>
	class subtype: public S
	{
	public:
		using S::S;
		XTAL_FN2 begin() XTAL_0EX {return S::head().begin();}
		XTAL_FN2   end() XTAL_0EX {return S::head().  end();}
		
	};
	template <any_q S> requires begin_q<U const &>
	class subtype<S>: public S
	{
	public:
		using S::S;
		XTAL_FN2 begin() XTAL_0EX {return S::head().begin();}
		XTAL_FN2   end() XTAL_0EX {return S::head().  end();}
		XTAL_FN2 begin() XTAL_0FX {return S::head().begin();}
		XTAL_FN2   end() XTAL_0FX {return S::head().  end();}

	};
};


///////////////////////////////////////////////////////////////////////////////

template <class U>
struct refer_equality
:	compose<>
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
:	compose<>
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
struct refer_quality
:	compose<void
	,	refer_equality<U>
	,	refer_inequality<U>
	>
{};


////////////////////////////////////////////////////////////////////////////////

template <class U, size_t N=0>
struct refer_binary_logic
:	compose<>
{};
template <class U>
struct refer_binary_logic<U, 0>
:	compose<void
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
		XTAL_OP1 ^=(XTAL_DEF_(to_q<U>) w) XTAL_0EX {return S::body_m ^=(U) XTAL_REF_(w), S::self();}
		XTAL_OP1 |=(XTAL_DEF_(to_q<U>) w) XTAL_0EX {return S::body_m |=(U) XTAL_REF_(w), S::self();}
		XTAL_OP1 &=(XTAL_DEF_(to_q<U>) w) XTAL_0EX {return S::body_m &=(U) XTAL_REF_(w), S::self();}

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


////////////////////////////////////////////////////////////////////////////////

template <class U, size_t N=0>
struct refer_multiplicative_group
:	compose<>
{};
template <class U>
struct refer_multiplicative_group<U, 0>
:	compose<void
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
		XTAL_OP1 *=(XTAL_DEF_(to_q<U>) w) XTAL_0EX {return S::body_m *=(U) XTAL_REF_(w), S::self();}
		XTAL_OP1 /=(XTAL_DEF_(to_q<U>) w) XTAL_0EX {return S::body_m /=(U) XTAL_REF_(w), S::self();}

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
:	compose<>
{};
template <class U>
struct refer_additive_group<U, 0>
:	compose<void
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
		XTAL_OP1 +=(XTAL_DEF_(to_q<U>) w) XTAL_0EX {return S::body_m +=(U) XTAL_REF_(w), S::self();}
		XTAL_OP1 -=(XTAL_DEF_(to_q<U>) w) XTAL_0EX {return S::body_m -=(U) XTAL_REF_(w), S::self();}

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
:	compose<>
{};
template <class U>
struct refer_discrete_group<U, 0>
:	compose<void
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
		XTAL_OP1 ++(int) XTAL_0EX {auto  t = S::self(); ++S::body_m; return t;}
		XTAL_OP1 --(int) XTAL_0EX {auto  t = S::self(); --S::body_m; return t;}
		XTAL_OP1 ++()    XTAL_0EX {auto &s = S::self(); ++S::body_m; return s;}
		XTAL_OP1 --()    XTAL_0EX {auto &s = S::self(); --S::body_m; return s;}

	};
};


template <class U, size_t N=0>
struct refer_groups
:	compose<void
	,	refer_multiplicative_group<U, N>
	,	refer_additive_group<U, N>
	,	refer_discrete_group<U, N>
	>
{};


}//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
