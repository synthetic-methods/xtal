








namespace _detail
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

template <int N_width>
struct wield
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
concept wield_p = requires {{T::size()} -> integral_p;};

template <class T>
concept wield_q = wield_p<T> and some_q<typename T::W_field>;


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
