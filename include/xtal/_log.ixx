//////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

#if not XTAL_LOG
class
{
public:
	XTAL_OP1() (XTAL_DEF ...xs)
	{
		if constexpr (0 < sizeof...(xs)) {
			return (XTAL_REF_(xs), ...);
		}
	}

} echo;
#else
class
{
	XTAL_TN0 print_list(XTAL_DEF x)
	{
		for (XTAL_DEF w: XTAL_REF_(x)) ::std::cout << XTAL_REF_(w) << '\t';
	}
	XTAL_TN0 print_item(XTAL_DEF x)
	{
		using W = XTAL_TYP_(x);
		if constexpr (::std::is_floating_point_v<W>) {
			::std::cout.precision(17);
		}
		if constexpr (::std::is_arithmetic_v<W>) {
			if (::std::copysign(1.0, x) == 1.0) {
				 ::std::cout << ' ';
			}
		}
		::std::cout << XTAL_REF_(x) << '\t';
	}
	XTAL_TN1 put(XTAL_DEF x)
	{
		using W = XTAL_TYP_(x);
		if constexpr (_v3::ranges::range<W> and requires {::std::is_arithmetic_v<typename W::value_type>;}) {
			print_list(XTAL_REF_(x));
		}
		else {
			print_item(XTAL_REF_(x));
		}
		return XTAL_REF_(x);
	}

public:
	XTAL_OP1() (XTAL_DEF ...xs)
	{
		if constexpr (0 < sizeof...(xs)) {
			::std::cout << '\t'; auto const x = (put(XTAL_REF_(xs)), ...);
			::std::cout << '\n';
			return x;
		}
		else {
			::std::cout << '\n';
		}
	}

} echo;
#endif


///////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
