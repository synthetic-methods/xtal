#include "../compound/_kernel.hxx"








namespace _detail
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

using namespace _retail::_detail;


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

struct define_member
{
	template <any_q S>
	class subtype: public S
	{
	public:
		using S::S;

		using bit_field = cardinal_t<0>;

	};
};


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
		using _T = typename S::self_u;
		using _U = typename S::head_u;

	public:
		using S::S;
		using S::head;

		///\
		Implicit conversion to the singleton kernel-type. \

		XTAL_DO4_(XTAL_OP0_(implicit) _U(), {return head();})
		
		///\returns the `sentinel` boundary in the direction of `N_polarity`. \

		template <int N_polarity=0>
		XTAL_FN2 sentry(XTAL_DEF... oo)
		XTAL_0EX
		XTAL_REQ algebraic_field_q<_U> and equality_q<_U> and sign_q<N_polarity>
		{
			using L = _std::numeric_limits<_U>;
			if constexpr (N_polarity == +1) return _T(L::max(), XTAL_REF_(oo)...);
			if constexpr (N_polarity ==  0) return _T(0,        XTAL_REF_(oo)...);
			if constexpr (N_polarity == -1) return _T(L::min(), XTAL_REF_(oo)...);
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
		using S::apple;

		using tuple_type = XTAL_TYP_(XTAL_VAL_(S).apple());

		XTAL_DO4_(XTAL_OP0_(implicit) tuple_type(), {return apple();})
		
	};
};


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

template <class U>
struct defer_member
{
	template <any_q S>
	class subtype: public common::compose_s<S>
	{
		using _S = common::compose_s<S>;

	public:
	//	using _S::_S;
		using _S::self;
		using head_u = U;
		using body_t = debased_t<U>;
		body_t body_m;

	//	XTAL_CO0_(subtype);
		XTAL_CO4_(subtype);
		
		///\
		Constructs `this` using the default value. \

		XTAL_CON subtype()
		XTAL_0EX
		:	subtype(body_t{})
		{}
		XTAL_CON subtype(bracket_t<devalued_t<head_u>> a)
		XTAL_REQ array_q<head_u> and rebased_q<head_u>
		:	body_m(a)
		{}
		///\
		Constructs `this` using the first argument, forwarding the rest to the parent. \

		template <infungible_q<subtype> A>
		XTAL_CXN subtype(A &&a, XTAL_DEF ...oo)
		XTAL_0EX
		:	_S(XTAL_REF_(oo)...)
		,	body_m(member_f<head_u>(XTAL_REF_(a)))
		{}

		///\returns the kernel-body (prior to reconstruction using the given arguments, if provided). \

		XTAL_TN2 head() XTAL_0FX_( &) {return remember_f(body_m);}
		XTAL_TN2 head() XTAL_0EX_( &) {return remember_f(body_m);}
		XTAL_TN2 head() XTAL_0FX_(&&) {return remember_f(XTAL_MOV_(body_m));}
		XTAL_TN2 head() XTAL_0EX_(&&) {return remember_f(XTAL_MOV_(body_m));}
		
		XTAL_TN1 head(XTAL_DEF... oo)
		XTAL_0EX
		XTAL_REQ rebased_q<head_u> and (0 < sizeof...(oo))
		{
			return dismember_f(body_m, XTAL_REF_(oo)...);
		}

	};
};
template <size_t N_depth>
struct defer_member<unit_t[N_depth]>
{
	XTAL_LET N_width = size_1 << N_depth;
	XTAL_LET N_mask  = N_width -  size_1;

	template <any_q S>
	class subtype: public common::compose_s<S>
	{
		using _S = common::compose_s<S>;

	public:
	//	using _S::_S;
		using _S::self;

		using head_u = size_t;
		using body_t = unsigned;
		body_t body_m:N_depth;

		XTAL_CO0_(subtype);
		XTAL_CO4_(subtype);
		
		using bit_field = cardinal_t<N_depth + _S::bit_field::value>;

		///\
		Constructs `this` using the first argument, forwarding the rest to the parent. \

		template <infungible_q<subtype> A>
		XTAL_CXN subtype(A &&a, XTAL_DEF ...oo)
		XTAL_0EX
		:	_S(XTAL_REF_(oo)...)
		,	body_m(member_f<head_u>(XTAL_REF_(a)))
		{}
		template <_std::integral A> requires  liminal_q<typename _S::bit_field>
		XTAL_CON subtype(A &&a)
		XTAL_0EX
		:	_S(head_u(XTAL_REF_(a)) >> N_depth)
		,	body_m(head_u(a)&N_mask)
		{};
		template <_std::integral A> requires terminal_q<typename _S::bit_field>
		XTAL_CON subtype(A &&a)
		XTAL_0EX
		:	body_m(head_u(a)&N_mask)
		{
			assert(0 == a >> N_depth);
		};

		///\returns the kernel-body (prior to reconstruction using the given arguments, if provided). \

		XTAL_TN2 head() XTAL_0FX {return head_u(body_m);}
		XTAL_TN2 head() XTAL_0EX {return head_u(body_m);}
		
	};
};
template <constant_q U>
struct defer_member<U>
{
	template <any_q S>
	class subtype: public common::compose_s<S>
	{
		using _S = common::compose_s<S>;

	public:
		using _S::_S;
		using _S::self;
		using head_u = U;
		using body_t = debased_t<U>;
		body_t body_m {};

		template <is_q<head_u> A>
		XTAL_CXN subtype(A &&a, XTAL_DEF ...oo)
		XTAL_0EX
		:	_S(XTAL_REF_(oo)...)
		{}

		///\returns the kernel-body (prior to reconstruction using the given arguments, if provided). \

		XTAL_TN2 head() XTAL_0FX {return remember_f(body_m);}
		XTAL_TN2 head() XTAL_0EX {return remember_f(body_m);}
		
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
template <class U> requires binary_logic_p<U, 1> and rebased_q<U>
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
		using _T = typename S::self_u;
	
	public:
		using S::S;
		XTAL_OP2 ^ (XTAL_DEF_(to_q<U>) w) XTAL_0FX {return _T(S::head() ^ (U) XTAL_REF_(w));}
		XTAL_OP2 | (XTAL_DEF_(to_q<U>) w) XTAL_0FX {return _T(S::head() | (U) XTAL_REF_(w));}
		XTAL_OP2 & (XTAL_DEF_(to_q<U>) w) XTAL_0FX {return _T(S::head() & (U) XTAL_REF_(w));}

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
template <class U> requires multiplicative_group_p<U, 1> and rebased_q<U>
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
		using _T = typename S::self_u;
	
	public:
		using S::S;
		XTAL_OP2 * (XTAL_DEF_(to_q<U>) w) XTAL_0FX {return _T(S::head() * (U) XTAL_REF_(w));}
		XTAL_OP2 / (XTAL_DEF_(to_q<U>) w) XTAL_0FX {return _T(S::head() / (U) XTAL_REF_(w));}

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
template <class U> requires additive_group_p<U, 1> and rebased_q<U>
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
		using _T = typename S::self_u;
	
	public:
		using S::S;
		XTAL_OP2 + (XTAL_DEF_(to_q<U>) w) XTAL_0FX {return _T(S::head() + (U) XTAL_REF_(w));}
		XTAL_OP2 - (XTAL_DEF_(to_q<U>) w) XTAL_0FX {return _T(S::head() - (U) XTAL_REF_(w));}
		XTAL_OP1 - () XTAL_0FX {return _T(-S::head());}

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
template <class U> requires discrete_group_p<U, 1> and rebased_q<U>
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
