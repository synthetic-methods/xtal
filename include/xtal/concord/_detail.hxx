#include "../common/_kernel.hxx"

namespace _detail
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

using namespace _retail::_detail;


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

		XTAL_DO4_(XTAL_OP0 U(), {return head();})
		
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

		XTAL_DO4_(XTAL_OP0 tuple_type(), {return tuple();})
		
	};
};


///////////////////////////////////////////////////////////////////////////////

template <class U, int N=0>
struct refer_iterators
:	compose<>
{
};
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


template <class U, int N=0> struct refer_inequality_comparators: compose<> {};
template <class U, int N=0> struct   refer_equality_comparators: compose<> {};
template <class U, int N=0> struct            refer_comparators: compose<void
,	refer_equality_comparators<U, N>
,	refer_inequality_comparators<U, N>
>
{
};
template <class U> requires equality_comparators_p<U>
struct refer_equality_comparators<U>
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
template <class U> requires inequality_comparators_p<U>
struct refer_inequality_comparators<U>
{
	template <any_q S>
	class subtype: public S
	{
	public:
		using S::S;
		XTAL_OP2 <=> (subtype const &t)
		XTAL_0FX
		{
			auto const &u = S::head(), v = t.head();
			if constexpr (requires {u.operator<=>(v);}) {
				return u.operator<=>(v);
			}
			else {
				return u <=> v;
			}
		}

	};
};


template <class U, int N=0> struct refer_bitwise_operators: compose<> {};
template <class U, int N=0> struct   refer_group_operators: compose<> {};
template <class U, int N=0> struct   refer_field_operators: compose<> {};
template <class U, int N=0> struct         refer_operators: compose<void
,	refer_field_operators <U, N>
,	refer_group_operators <U, N>
,	refer_bitwise_operators<U, N>
>
{
};
template <class U> struct refer_bitwise_operators<U, 0> : compose< refer_bitwise_operators<U, 1>, refer_bitwise_operators<U, 2>> {};
template <class U> struct   refer_group_operators<U, 0> : compose<   refer_group_operators<U, 1>,   refer_group_operators<U, 2>> {};
template <class U> struct   refer_field_operators<U, 0> : compose<   refer_field_operators<U, 1>,   refer_field_operators<U, 2>> {};
template <class U> struct         refer_operators<U, 0> : compose<         refer_operators<U, 1>,         refer_operators<U, 2>> {};

template <class U> requires bitwise_operators_p<U, 1> and remember_q<U>
struct refer_bitwise_operators<U, 1>
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
template <class U> requires bitwise_operators_p<U, 2>
struct refer_bitwise_operators<U, 2>
{
	template <any_q S>
	class subtype: public S
	{
		using T_ = typename S::self_t;

	public:
		using S::S;
		XTAL_OP2 ^ (XTAL_DEF_(to_q<U>) w) XTAL_0FX {return T_(S::head()  ^ (U) XTAL_REF_(w));}
		XTAL_OP2 | (XTAL_DEF_(to_q<U>) w) XTAL_0FX {return T_(S::head()  | (U) XTAL_REF_(w));}
		XTAL_OP2 & (XTAL_DEF_(to_q<U>) w) XTAL_0FX {return T_(S::head()  & (U) XTAL_REF_(w));}
		XTAL_OP2 ~ () XTAL_0FX {return T_(~S::head());}

	};
};

template <class U> requires group_operators_p<U, 1> and remember_q<U>
struct refer_group_operators<U, 1>
{
	template <any_q S>
	class subtype: public S
	{
	public:
		using S::S;
		XTAL_OP1 %=(XTAL_DEF_(to_q<U>) w) XTAL_0EX {return S::body_m %=(U) XTAL_REF_(w), S::self();}
		XTAL_OP1 +=(XTAL_DEF_(to_q<U>) w) XTAL_0EX {return S::body_m +=(U) XTAL_REF_(w), S::self();}
		XTAL_OP1 -=(XTAL_DEF_(to_q<U>) w) XTAL_0EX {return S::body_m -=(U) XTAL_REF_(w), S::self();}
		XTAL_OP1 ++(int) XTAL_0EX {auto  t = S::self(); ++S::body_m; return t;}
		XTAL_OP1 --(int) XTAL_0EX {auto  t = S::self(); --S::body_m; return t;}
		XTAL_OP1 ++()    XTAL_0EX {auto &s = S::self(); ++S::body_m; return s;}
		XTAL_OP1 --()    XTAL_0EX {auto &s = S::self(); --S::body_m; return s;}

	};
};
template <class U> requires group_operators_p<U, 2>
struct refer_group_operators<U, 2>
{
	template <any_q S>
	class subtype: public S
	{
		using T_ = typename S::self_t;

	public:
		using S::S;
		XTAL_OP2 % (XTAL_DEF_(to_q<U>) w) XTAL_0FX {return T_(S::head()  % (U) XTAL_REF_(w));}
		XTAL_OP2 + (XTAL_DEF_(to_q<U>) w) XTAL_0FX {return T_(S::head()  + (U) XTAL_REF_(w));}
		XTAL_OP2 - (XTAL_DEF_(to_q<U>) w) XTAL_0FX {return T_(S::head()  - (U) XTAL_REF_(w));}
		XTAL_OP2 - () XTAL_0FX {return T_(-S::head());}

	};
};

template <class U> requires field_operators_p<U, 1> and remember_q<U>
struct refer_field_operators<U, 1>
{
	template <any_q S>
	class subtype: public S
	{
	public:
		using S::S;
		XTAL_OP1 *=(XTAL_DEF_(to_q<U>) w) XTAL_0EX {return S::body_m *=(U) XTAL_REF_(w), S::self();}
		XTAL_OP1 /=(XTAL_DEF_(to_q<U>) w) XTAL_0EX {return S::body_m /=(U) XTAL_REF_(w), S::self();}
		XTAL_OP1 +=(XTAL_DEF_(to_q<U>) w) XTAL_0EX {return S::body_m +=(U) XTAL_REF_(w), S::self();}
		XTAL_OP1 -=(XTAL_DEF_(to_q<U>) w) XTAL_0EX {return S::body_m -=(U) XTAL_REF_(w), S::self();}

	};
};
template <class U> requires field_operators_p<U, 2>
struct refer_field_operators<U, 2>
{
	template <any_q S>
	class subtype: public S
	{
		using T_ = typename S::self_t;
	
	public:
		using S::S;
		XTAL_OP2 * (XTAL_DEF_(to_q<U>) w) XTAL_0FX {return T_(S::head() * (U) XTAL_REF_(w));}
		XTAL_OP2 / (XTAL_DEF_(to_q<U>) w) XTAL_0FX {return T_(S::head() / (U) XTAL_REF_(w));}
		XTAL_OP2 + (XTAL_DEF_(to_q<U>) w) XTAL_0FX {return T_(S::head() + (U) XTAL_REF_(w));}
		XTAL_OP2 - (XTAL_DEF_(to_q<U>) w) XTAL_0FX {return T_(S::head() - (U) XTAL_REF_(w));}
		XTAL_OP1 - () XTAL_0FX {return T_(-S::head());}

	};
};


}//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
