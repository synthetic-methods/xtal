#include "../cell/_kernel.hxx"








namespace _detail
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

using namespace _retail::_detail;


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

template <class T>
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
	protected:
		using typename S::T_self;
		using typename S::U_head;

	public:
		using S::S;
		using S::twin;
		using S::self;
		using S::head;

		///\
		Implicit conversion to the singleton kernel-type. \

		XTAL_DO4_(XTAL_OP0_(implicit) U_head(), {return head();})
		
//		///\
//		\returns a copy of `this` with `head<Is...>(oo...)` applied. \
//
//		template <class  ...Is>
//		XTAL_TN1 alter(auto &&...oo)
//		XTAL_0FX
//		{
//			auto t = twin();
//			(void) t.template head<Is...>(XTAL_FWD_(oo)...);
//			return t;
//		}

		///\
		\returns the `sentinel` boundary in the direction of `N_polarity`, \
		provided `std::numeric_limits<...>` exists. \

		template <int N_polarity=0> requires sign_p<N_polarity, 0> and extremum_q<U_head>
		XTAL_FN2 sentry(auto &&...oo)
		XTAL_0EX 
	//	XTAL_REQ algebraic_field_q<U_head> and equality_q<U_head> and sign_p<N_polarity, 0>
		{
			return T_self(extremum_f<U_head>(N_polarity), XTAL_FWD_(oo)...);
		}

	};
};

template <class T>
struct refine_tuple
{
	template <any_q S>
	class subtype: public S
	{
	public:
		using S::S;
		using S::apple;

		using apple_type = XTAL_TYP_(XTAL_VAL_(S).apple());

		XTAL_DO4_(XTAL_OP0_(implicit) apple_type(), {return apple();})
		
	};
};


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

template <class U>
struct defer_field
{
	using T_head = U;
	using T_body = debased_t<U>;

	template <any_q S>
	class subtype: public bond::compose_s<S>
	{
		using S_ = bond::compose_s<S>;

	protected:
		using U_head = T_head;
		using U_body = T_body;

	public:
		//\
		Public visibility allows `auto` parameterization in templates.

		U_body u_body;

	public:
	//	using S_::S_;
		
	//	XTAL_CO0_(subtype);
		XTAL_CO4_(subtype);
		
		///\
		Constructs `this` using the default value. \

		XTAL_CON subtype()
		XTAL_0EX
		:	subtype(U_body {})
		{}
		/**/
		XTAL_CON subtype(braced_t<U_body> a)
		XTAL_0EX
		XTAL_REQ braced_q<U_body> and rebased_q<U>
		:	u_body(a)
		{}
		/*/
		XTAL_CON subtype(bracket_t<value_t<U_body>> a)
		XTAL_0EX
		XTAL_REQ array_q<U_body> and id_q<U_body, U_head>
		:	u_body(a)
		{}
		/***/
		///\
		Constructs `this` using the first argument, forwarding the rest to the parent. \

		template <infungible_q<subtype> A>
		XTAL_CXN subtype(A &&a, auto &&...oo)
		XTAL_0EX
		:	S_(XTAL_FWD_(oo)...)
		,	u_body(member_f<U_head>(XTAL_FWD_(a)))
		{}

		///\returns the kernel-body (prior to reconstruction using the given arguments, if provided). \

		XTAL_TN2 head() XTAL_0FX_( &) {return remember_f(u_body);}
		XTAL_TN2 head() XTAL_0EX_( &) {return remember_f(u_body);}
		XTAL_TN2 head() XTAL_0FX_(&&) {return remember_f(XTAL_MOV_(u_body));}
		XTAL_TN2 head() XTAL_0EX_(&&) {return remember_f(XTAL_MOV_(u_body));}
		
		XTAL_TN1 head(auto &&...oo)
		XTAL_0EX
		XTAL_REQ rebased_q<U_head> and (0 < sizeof...(oo))
		{
			return dismember_f(u_body, XTAL_FWD_(oo)...);
		}

	};
};
template <integral_q U>
struct defer_field<U>
{
	using T_head = U;
	using T_body = debased_t<U>;

	template <any_q S>
	class subtype: public bond::compose_s<S>
	{
		using S_ = bond::compose_s<S>;

	protected:
		using U_head = T_head;
		using U_body = T_body;

	public:
		using S_::S_;
		using S_::self;
		U_body u_body {};

		template <integral_q A>
		XTAL_CXN subtype(A &&a, auto &&...oo)
		XTAL_0EX
		:	S_(XTAL_FWD_(oo)...)
		{
			static_assert(A::value == U::value);
		}

		///\returns the kernel-body (prior to reconstruction using the given arguments, if provided). \

		XTAL_TN2 head() XTAL_0FX {return U_head(u_body);}
		XTAL_TN2 head() XTAL_0EX {return U_head(u_body);}
		
	};
};
template <size_t N_width>
struct defer_field<unit_t[N_width]>
{
	XTAL_LET N_depth = bond::realized::bit_ceiling_f(N_width);
	static_assert(N_width == size_1 << N_depth);

	using T_head = size_t;
	using T_body = unsigned;

	using subkind = bond::assay<N_width>;

	template <any_q S>
	class subtype: public bond::compose_s<S, subkind>
	{
		using S_ = bond::compose_s<S, subkind>;

	protected:
		using U_head = T_head;
		using U_body = T_body;

	public:
		U_body u_body:N_depth;

	public:
	//	using S_::S_;
		using S_::self;

		XTAL_CO0_(subtype);
		XTAL_CO4_(subtype);
		
		///\
		Constructs `this` using the first argument, forwarding the rest to the parent. \

		template <infungible_q<subtype> A>
		XTAL_CXN subtype(A &&a, auto &&...oo)
		XTAL_0EX
		:	S_(XTAL_FWD_(oo)...)
		,	u_body(member_f<U_head>(XTAL_FWD_(a)))
		{
		}
		template <integral_p A>
		XTAL_CON subtype(A &&a)
		XTAL_0EX
		:	S_(U_head(XTAL_FWD_(a)) >> N_depth)
		,	u_body(U_head(a)&(N_width - 1))
		{
		}

		///\returns the kernel-body (prior to reconstruction using the given arguments, if provided). \

		XTAL_TN2 head() XTAL_0FX {return U_head(u_body);}
		XTAL_TN2 head() XTAL_0EX {return U_head(u_body);}
		
	};
};
template <size_t N_depth>
struct defer_field<null_t[N_depth]>
:	defer_field<unit_t[(size_1 << N_depth)]>
{
};


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

template <class U>
struct refer_iterators
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

template <class U>
struct infer_iterators: bond::compose<> {};

template <class U> requires begin_q<U>
struct infer_iterators<U>: refer_iterators<U> {};


///////////////////////////////////////////////////////////////////////////////

template <class U>
struct refer_equality
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
struct infer_equality: bond::compose<> {};

template <class U> requires equality_q<U>
struct infer_equality<U>: refer_equality<U> {};


template <class U>
struct refer_inequality
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
struct infer_inequality: bond::compose<> {};

template <class U> requires inequality_q<U>
struct infer_inequality<U>: refer_inequality<U> {};


template <class U>
struct refer_qualities
:	bond::compose<void
	,	refer_equality<U>
	,	refer_inequality<U>
	>
{};
template <class U>
struct infer_qualities
:	bond::compose<void
	,	infer_equality<U>
	,	infer_inequality<U>
	>
{};


////////////////////////////////////////////////////////////////////////////////

template <class U, size_t N=0>
struct refer_binary_logic
:	bond::compose<void
	,	refer_binary_logic<U, 1>
	,	refer_binary_logic<U, 2>
	>
{};
template <class U>
struct refer_binary_logic<U, 1>
{
	template <any_q S>
	class subtype: public S
	{
	public:
		using S::S;
		XTAL_OP1 ^=(auto &&o) XTAL_0EX {S::head() ^= XTAL_FWD_(o); return S::self();}
		XTAL_OP1 |=(auto &&o) XTAL_0EX {S::head() |= XTAL_FWD_(o); return S::self();}
		XTAL_OP1 &=(auto &&o) XTAL_0EX {S::head() &= XTAL_FWD_(o); return S::self();}

	};
};
template <class U>
struct refer_binary_logic<U, 2>
{
	template <any_q S>
	class subtype: public S
	{
	protected:
		using typename S::T_self;
	
	public:
		using S::S;
		XTAL_OP2 ^ (auto &&o) XTAL_0FX {return T_self(S::head() ^ XTAL_FWD_(o));}
		XTAL_OP2 | (auto &&o) XTAL_0FX {return T_self(S::head() | XTAL_FWD_(o));}
		XTAL_OP2 & (auto &&o) XTAL_0FX {return T_self(S::head() & XTAL_FWD_(o));}

	};
};

template <class U, size_t N=0>
struct infer_binary_logic: bond::compose<> {};

template <class U, size_t N> requires binary_logic_p<U, N>
struct infer_binary_logic<U, N>: refer_binary_logic<U, N> {};



template <class U, size_t N=0>
struct refer_logics
:	bond::compose<void
	,	refer_binary_logic<U, N>
	>
{};
template <class U, size_t N=0>
struct infer_logics
:	bond::compose<void
	,	infer_binary_logic<U, N>
	>
{};


////////////////////////////////////////////////////////////////////////////////

template <class U, size_t N=0>
struct refer_multiplicative_group
:	bond::compose<void
	,	refer_multiplicative_group<U, 1>
	,	refer_multiplicative_group<U, 2>
	>
{};
template <class U>
struct refer_multiplicative_group<U, 1>
{
	template <any_q S>
	class subtype: public S
	{
	public:
		using S::S;
		XTAL_OP1 *=(auto &&o) XTAL_0EX {S::head() *= XTAL_FWD_(o); return S::self();}
		XTAL_OP1 /=(auto &&o) XTAL_0EX {S::head() /= XTAL_FWD_(o); return S::self();}

	};
};
template <class U>
struct refer_multiplicative_group<U, 2>
{
	template <any_q S>
	class subtype: public S
	{
	protected:
		using typename S::T_self;
	
	public:
		using S::S;
		XTAL_OP2 * (auto &&o) XTAL_0FX {return T_self(S::head() * XTAL_FWD_(o));}
		XTAL_OP2 / (auto &&o) XTAL_0FX {return T_self(S::head() / XTAL_FWD_(o));}

	};
};

template <class U, size_t N=0>
struct infer_multiplicative_group: bond::compose<> {};

template <class U, size_t N> requires multiplicative_group_p<U, N>
struct infer_multiplicative_group<U, N>: refer_multiplicative_group<U, N> {};



template <class U, size_t N=0>
struct refer_additive_group
:	bond::compose<void
	,	refer_additive_group<U, 1>
	,	refer_additive_group<U, 2>
	>
{};
template <class U>
struct refer_additive_group<U, 1>
{
	template <any_q S>
	class subtype: public S
	{
	public:
		using S::S;
		XTAL_OP1 +=(auto &&o) XTAL_0EX {S::head() += XTAL_FWD_(o); return S::self();}
		XTAL_OP1 -=(auto &&o) XTAL_0EX {S::head() -= XTAL_FWD_(o); return S::self();}

	};
};
template <class U>
struct refer_additive_group<U, 2>
{
	template <any_q S>
	class subtype: public S
	{
	protected:
		using typename S::T_self;
	
	public:
		using S::S;
		XTAL_OP2 + (auto &&o) XTAL_0FX {return T_self(S::head() + XTAL_FWD_(o));}
		XTAL_OP2 - (auto &&o) XTAL_0FX {return T_self(S::head() - XTAL_FWD_(o));}
		XTAL_OP1 - () XTAL_0FX {return T_self(-S::head());}

	};
};

template <class U, size_t N=0>
struct infer_additive_group: bond::compose<> {};

template <class U, size_t N> requires additive_group_p<U, N>
struct infer_additive_group<U, N>: refer_additive_group<U, N> {};



template <class U, size_t N=0>
struct refer_discrete_group
:	bond::compose<void
	,	refer_discrete_group<U, 1>
	,	refer_discrete_group<U, 2>
	>
{};
template <class U>
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
template <class U>
struct refer_discrete_group<U, 2>
{
	template <any_q S>
	using subtype = S;

};

template <class U, size_t N=0>
struct infer_discrete_group: bond::compose<> {};

template <class U, size_t N> requires discrete_group_p<U, N>
struct infer_discrete_group<U, N>: refer_discrete_group<U, N> {};



template <class U, size_t N=0>
struct refer_groups
:	bond::compose<void
	,	refer_multiplicative_group<U, N>
	,	refer_additive_group<U, N>
	,	refer_discrete_group<U, N>
	>
{};
template <class U, size_t N=0>
struct infer_groups
:	bond::compose<void
	,	infer_multiplicative_group<U, N>
	,	infer_additive_group<U, N>
	,	infer_discrete_group<U, N>
	>
{};


}//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
