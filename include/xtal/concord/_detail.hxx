#include "../common/_kernel.hxx"

namespace _detail
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

using namespace _retail::_detail;


////////////////////////////////////////////////////////////////////////////////

struct refine_head
{
	template <any_p S>
	class subtype: public S
	{
	public:
		using S::S;

	};
	template <any_p S> requires (1 == S::tuple_size::value)
	class subtype<S>: public S
	{
		using U = typename S::head_t;

	public:
		using S::S;
		using S::head;

		///\
		Implicit conversion to the singleton kernel-type. \

		XTAL_TO4_(XTAL_OP0 U(), head())
		
	};
};
struct refine_tuple
{
	template <any_p S>
	class subtype: public S
	{
	public:
		using S::S;

		using tuple_type = XTAL_TYP_(XTAL_VAL_(S).tuple());

	};
};


///////////////////////////////////////////////////////////////////////////////

template <typename U, int N=0>
struct refer_iterators
:	compose<>
{};
template <typename U> requires begin_q<U>
struct refer_iterators<U>
{
	template <any_p S>
	class subtype: public S
	{
	public:
		using S::S;
		XTAL_FN2 begin() XTAL_0EX {return S::head().begin();}
		XTAL_FN2   end() XTAL_0EX {return S::head().  end();}
		
	};
	template <any_p S> requires begin_q<U const &>
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


template <typename U, int N=0> struct refer_inequality_comparators: compose<> {};
template <typename U, int N=0> struct   refer_equality_comparators: compose<> {};
template <typename U, int N=0> struct            refer_comparators: compose<void
,	refer_equality_comparators<U, N>
,	refer_inequality_comparators<U, N>
>
{};
template <typename U> requires equality_comparators_p<U>
struct refer_equality_comparators<U>
{
	template <any_p S>
	class subtype: public S
	{
	public:
		using S::S;
		XTAL_OP2_(bool) == (subtype const &t) XTAL_0FX {return S::head() == t.head();}
		XTAL_OP2_(bool) != (subtype const &t) XTAL_0FX {return S::head() != t.head();}

	};
};
template <typename U> requires inequality_comparators_p<U>
struct refer_inequality_comparators<U>
{
	template <any_p S>
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


template <typename U, int N=0> struct refer_bitwise_operators: compose<> {};
template <typename U, int N=0> struct   refer_group_operators: compose<> {};
template <typename U, int N=0> struct   refer_field_operators: compose<> {};
template <typename U, int N=0> struct         refer_operators: compose<void
,	refer_field_operators <U, N>
,	refer_group_operators <U, N>
,	refer_bitwise_operators<U, N>
>
{};
template <typename U> struct refer_bitwise_operators<U, 0> : compose< refer_bitwise_operators<U, 1>, refer_bitwise_operators<U, 2>> {};
template <typename U> struct   refer_group_operators<U, 0> : compose<   refer_group_operators<U, 1>,   refer_group_operators<U, 2>> {};
template <typename U> struct   refer_field_operators<U, 0> : compose<   refer_field_operators<U, 1>,   refer_field_operators<U, 2>> {};
template <typename U> struct         refer_operators<U, 0> : compose<         refer_operators<U, 1>,         refer_operators<U, 2>> {};

template <typename U> requires bitwise_operators_p<U, 1> and remember_q<U>
struct refer_bitwise_operators<U, 1>
{
	template <any_p S>
	class subtype: public S
	{
	public:
		using S::S;
		XTAL_OP1 ^=(XTAL_DEF_(to_q<U>) w) XTAL_0EX {return S::body_m ^=(U) XTAL_REF_(w), S::self();}
		XTAL_OP1 |=(XTAL_DEF_(to_q<U>) w) XTAL_0EX {return S::body_m |=(U) XTAL_REF_(w), S::self();}
		XTAL_OP1 &=(XTAL_DEF_(to_q<U>) w) XTAL_0EX {return S::body_m &=(U) XTAL_REF_(w), S::self();}

	};
};
template <typename U> requires bitwise_operators_p<U, 2>
struct refer_bitwise_operators<U, 2>
{
	template <any_p S>
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

template <typename U> requires group_operators_p<U, 1> and remember_q<U>
struct refer_group_operators<U, 1>
{
	template <any_p S>
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
template <typename U> requires group_operators_p<U, 2>
struct refer_group_operators<U, 2>
{
	template <any_p S>
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

template <typename U> requires field_operators_p<U, 1> and remember_q<U>
struct refer_field_operators<U, 1>
{
	template <any_p S>
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
template <typename U> requires field_operators_p<U, 2>
struct refer_field_operators<U, 2>
{
	template <any_p S>
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
