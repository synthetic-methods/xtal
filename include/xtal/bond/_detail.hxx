#include "../bond/_kernel.hxx"








namespace _detail
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

using namespace _retail::_detail;


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

template <class T>
struct define_field
{
	template <any_q S>
	class subtype: public S
	{
	public:
		using S::S;

		using word_depth = cardinal_t<0>;
		using word_width = cardinal_t<1>;

		XTAL_FN2_(size_t) enumerate()
		XTAL_0EX
		{
			return T::word_width::value;
		}

	};
};


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
	public://protected:
		using typename S::T_self;
		using typename S::U_head;

	public:
		using S::S;
		using S::self;
		using S::head;

		///\
		Implicit conversion to the singleton kernel-type. \

		XTAL_DO4_(XTAL_OP0_(implicit) U_head(), {return head();})
		
		///\
		\returns `true` if the supplied body matches `head`, `false` otherwise. \

		template <class  ...Is>
		XTAL_TN1 with(XTAL_DEF ...oo) XTAL_0FX {(void) head(XTAL_REF_(oo)...); return self();}

		template <size_t ...Is>
		XTAL_TN1 with(XTAL_DEF ...oo) XTAL_0FX {(void) head(XTAL_REF_(oo)...); return self();}

		///\
		\returns the `sentinel` boundary in the direction of `N_polarity`. \

		template <int N_polarity=0>
		XTAL_FN2 sentry(XTAL_DEF... oo)
		XTAL_0EX
		XTAL_REQ algebraic_field_q<U_head> and equality_q<U_head> and sign_p<N_polarity, 0>
		{
			using L = _std::numeric_limits<U_head>;
			if constexpr (N_polarity == +1) return T_self(L::max(), XTAL_REF_(oo)...);
			if constexpr (N_polarity ==  0) return T_self(0,        XTAL_REF_(oo)...);
			if constexpr (N_polarity == -1) return T_self(L::min(), XTAL_REF_(oo)...);
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
	template <any_q S>
	class subtype: public atom::compose_s<S>
	{
		using S_ = atom::compose_s<S>;

	public://protected:
		using U_head = U;
		using U_body = debased_t<U>;

	public:
	//	using S_::S_;
		using S_::self;
		U_body body_m;

	//	XTAL_CO0_(subtype);
		XTAL_CO4_(subtype);
		
		///\
		Constructs `this` using the default value. \

		XTAL_CON subtype()
		XTAL_0EX
		:	subtype(U_body{})
		{}
		XTAL_CON subtype(bracket_t<revalued_t<U_head>> a)
		XTAL_REQ array_q<U_head> and rebased_q<U_head>
		:	body_m(a)
		{}
		///\
		Constructs `this` using the first argument, forwarding the rest to the parent. \

		template <infungible_q<subtype> A>
		XTAL_CXN subtype(A &&a, XTAL_DEF ...oo)
		XTAL_0EX
		:	S_(XTAL_REF_(oo)...)
		,	body_m(member_f<U_head>(XTAL_REF_(a)))
		{}

		///\returns the kernel-body (prior to reconstruction using the given arguments, if provided). \

		XTAL_TN2 head() XTAL_0FX_( &) {return remember_f(body_m);}
		XTAL_TN2 head() XTAL_0EX_( &) {return remember_f(body_m);}
		XTAL_TN2 head() XTAL_0FX_(&&) {return remember_f(XTAL_MOV_(body_m));}
		XTAL_TN2 head() XTAL_0EX_(&&) {return remember_f(XTAL_MOV_(body_m));}
		
		XTAL_TN1 head(XTAL_DEF... oo)
		XTAL_0EX
		XTAL_REQ rebased_q<U_head> and (0 < sizeof...(oo))
		{
			return dismember_f(body_m, XTAL_REF_(oo)...);
		}

		using word_width = cardinal_t<0>;
		static_assert(terminal_q<typename S_::word_depth>);// for now...

	};
};
template <integral_q U>
struct defer_field<U>
{
	template <any_q S>
	class subtype: public atom::compose_s<S>
	{
		using S_ = atom::compose_s<S>;

	public://protected:
		using U_head = U;
		using U_body = debased_t<U>;

	public:
		using S_::S_;
		using S_::self;
		U_body body_m {};

		template <integral_q A>
		XTAL_CXN subtype(A &&a, XTAL_DEF ...oo)
		XTAL_0EX
		:	S_(XTAL_REF_(oo)...)
		{
			static_assert(A::value == U::value);
		}

		///\returns the kernel-body (prior to reconstruction using the given arguments, if provided). \

		XTAL_TN2 head() XTAL_0FX {return U_head(body_m);}
		XTAL_TN2 head() XTAL_0EX {return U_head(body_m);}
		
	};
};
template <size_t N_width>
struct defer_field<unit_t[N_width]>
{
	XTAL_LET N_mask = N_width - 1;
	XTAL_LET N_depth = atom::computer::bit_ceiling_f(N_width);
	static_assert(N_width == size_1 << N_depth);

	template <any_q S>
	class subtype: public atom::compose_s<S>
	{
		using S_ = atom::compose_s<S>;

	public://protected:
		using U_head = size_t;
		using U_body = unsigned;

	public:
	//	using S_::S_;
		using S_::self;

		U_body body_m:N_depth;

		XTAL_CO0_(subtype);
		XTAL_CO4_(subtype);
		
		///\
		Constructs `this` using the first argument, forwarding the rest to the parent. \

		template <infungible_q<subtype> A>
		XTAL_CXN subtype(A &&a, XTAL_DEF ...oo)
		XTAL_0EX
		:	S_(XTAL_REF_(oo)...)
		,	body_m(member_f<U_head>(XTAL_REF_(a)))
		{}
		template <integral_p A> requires  liminal_q<typename S_::word_depth>
		XTAL_CON subtype(A &&a)
		XTAL_0EX
		:	S_(U_head(XTAL_REF_(a)) >> N_depth)
		,	body_m(U_head(a)&N_mask)
		{};
		template <integral_p A> requires terminal_q<typename S_::word_depth>
		XTAL_CON subtype(A &&a)
		XTAL_0EX
		:	body_m(U_head(a)&N_mask)
		{
			assert(0 == a >> N_depth);
		};

		///\returns the kernel-body (prior to reconstruction using the given arguments, if provided). \

		XTAL_TN2 head() XTAL_0FX {return U_head(body_m);}
		XTAL_TN2 head() XTAL_0EX {return U_head(body_m);}
		
		using word_depth = cardinal_t<N_depth + S_::word_depth::value>;// specified with `null_t[N_depth]`
		using word_width = cardinal_t<N_width * S_::word_width::value>;// specified with `unit_t[N_width]`
		static_assert(size_1 << word_depth::value == word_width::value);// for now...

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
:	atom::compose<>
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
:	atom::compose<>
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
:	atom::compose<>
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
:	atom::compose<void
	,	refer_equality<U>
	,	refer_inequality<U>
	>
{};


////////////////////////////////////////////////////////////////////////////////

template <class U, size_t N=0>
struct refer_binary_logic
:	atom::compose<>
{};
template <class U>
struct refer_binary_logic<U, 0>
:	atom::compose<void
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
	public://protected:
		using typename S::T_self;
	
	public:
		using S::S;
		XTAL_OP2 ^ (XTAL_DEF_(to_q<U>) w) XTAL_0FX {return T_self(S::head() ^ (U) XTAL_REF_(w));}
		XTAL_OP2 | (XTAL_DEF_(to_q<U>) w) XTAL_0FX {return T_self(S::head() | (U) XTAL_REF_(w));}
		XTAL_OP2 & (XTAL_DEF_(to_q<U>) w) XTAL_0FX {return T_self(S::head() & (U) XTAL_REF_(w));}

	};
};


template <class U, size_t N=0>
struct refer_logics
:	atom::compose<void
	,	refer_binary_logic<U, N>
	>
{};


////////////////////////////////////////////////////////////////////////////////

template <class U, size_t N=0>
struct refer_multiplicative_group
:	atom::compose<>
{};
template <class U>
struct refer_multiplicative_group<U, 0>
:	atom::compose<void
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
	public://protected:
		using typename S::T_self;
	
	public:
		using S::S;
		XTAL_OP2 * (XTAL_DEF_(to_q<U>) w) XTAL_0FX {return T_self(S::head() * (U) XTAL_REF_(w));}
		XTAL_OP2 / (XTAL_DEF_(to_q<U>) w) XTAL_0FX {return T_self(S::head() / (U) XTAL_REF_(w));}

	};
};


template <class U, size_t N=0>
struct refer_additive_group
:	atom::compose<>
{};
template <class U>
struct refer_additive_group<U, 0>
:	atom::compose<void
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
	public://protected:
		using typename S::T_self;
	
	public:
		using S::S;
		XTAL_OP2 + (XTAL_DEF_(to_q<U>) w) XTAL_0FX {return T_self(S::head() + (U) XTAL_REF_(w));}
		XTAL_OP2 - (XTAL_DEF_(to_q<U>) w) XTAL_0FX {return T_self(S::head() - (U) XTAL_REF_(w));}
		XTAL_OP1 - () XTAL_0FX {return T_self(-S::head());}

	};
};


template <class U, size_t N=0>
struct refer_discrete_group
:	atom::compose<>
{};
template <class U>
struct refer_discrete_group<U, 0>
:	atom::compose<void
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
:	atom::compose<void
	,	refer_multiplicative_group<U, N>
	,	refer_additive_group<U, N>
	,	refer_discrete_group<U, N>
	>
{};


}//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
