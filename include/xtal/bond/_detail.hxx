








namespace _detail
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

template <class U_tail, class U_self, class U_head=void>
struct query
{
	class type
	{
	public:
		template <class _,               class ...Is> struct duper:  U_tail::template super<_,                       Is...> {};
		template <class _,               class ...Is> struct super                  : duper<_,                       Is...> {};
		template <class _,  liminal_q I, class ...Is> struct super<_, I,      Is...>: duper<null_t, subliminal_s<I>, Is...> {};
		template <class _, terminal_q I, class ...Is> struct super<_, I,      Is...>: super<U_self,                  Is...> {};
		template <class _,               class ...Is> struct super<_, U_head, Is...>: super<U_self,                  Is...> {};
		template <class _,               class ...Is> struct super<_, U_self, Is...>: super<U_self,                  Is...> {};

	};
	template <class S>
	class subtype: public S
	{
		using S_ = S;
		friend S_;
		friend U_tail;
		friend U_self;

	public://protected:
		using typename S_::T_self;
	//	using typename S_::U_head;

	public:
		template <class _, class ...Is>
		using super = typename type::template super<_, Is...>;

	public:
		using S_::S_;

		template <class ...Is> using self_s = typename super<T_self, Is...>::type;
		template <class ...Is> using head_s = typename super<U_self, Is...>::type;
		template <class ...Is> using head_t = typename head_s<Is...>::U_head;

		using S_::self;
		using S_::head;
		
		XTAL_TO4_(template <class  ...Is> requires some_q<Is...>
		XTAL_TN2 self(auto &&...oo), S_::template self<self_s<Is...>>(XTAL_FWD_(oo)...)
		)
		XTAL_TO4_(template <class  ...Is> requires some_q<Is...>
		XTAL_TN2 head(auto &&...oo), S_::template self<head_s<Is...>>().head(XTAL_FWD_(oo)...)
		)
		XTAL_TO4_(template <size_t ...Is> requires some_n<Is...>
		XTAL_TN2 self(auto &&...oo), self<cardinal_t<Is>...>(XTAL_FWD_(oo)...)
		)
		XTAL_TO4_(template <size_t ...Is> requires some_n<Is...>
		XTAL_TN2 head(auto &&...oo), head<cardinal_t<Is>...>(XTAL_FWD_(oo)...)
		)

	};
};


////////////////////////////////////////////////////////////////////////////////

template <int N_width>
struct assay
{
	template <class S>
	class subtype: public S
	{
		using S_ = S;
	
	public:
		using S_::S_;

		XTAL_FN2 size()
		XTAL_0EX
		{
			return N_width;
		};

	};
};
template <class T>
concept assay_q = requires {{T::size()} -> integral_p;};


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
