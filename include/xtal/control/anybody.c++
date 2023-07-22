#pragma once
#include "./any.c++"
#include "./anybody.hpp"// testing...

#include "../control/all.hpp"
#include "../process/all.hpp"
#include "../processor/all.hpp"

XTAL_ENV_(push)
namespace xtal::context::__test
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

using namespace xtal::__test;

////////////////////////////////////////////////////////////////////////////////
/*/
struct __dispatch_partial__mix
{
	template <process::any_q S>
	class subtype: public S
	{
		using S_ = S;
		
	public:
		using S_::S_;

		template <auto onset, auto level>
		XTAL_FN2 method(XTAL_DEF ...xs)
		XTAL_0FX
		{
			return (XTAL_REF_(xs) +...+ onset)*level;
		}

	};
	using type = subtype<process::any_t<>>;
	
};
using __dispatch_partial__mix_t = process::confined_t<level_t::template dispatch<(1<<7)>, __dispatch_partial__mix>;


TEST_CASE("xtal/control/anybody.hpp: dispatch partial")
{
	__dispatch_partial__mix_t mix_o; mix_o << level_t(5);
	REQUIRE(mix_o.template method<3>(2, 1) == 30);
	REQUIRE(true);
	
}
/***/
////////////////////////////////////////////////////////////////////////////////
/**/
TEST_CASE("xtal/control/anybody.hpp: hold process")
{
	size_t constexpr N_size = 1<<3;

	using sequel_u = control::sequel_t<>;
	using gate_t   = control::label_t<typename realized::alpha_t, struct T_gate>;
	using gated_t  = process::confined_t<typename gate_t::template hold<(1<<7)>>;

	gated_t gated_o;
	
	using point_t = context::point_s<>;
	gated_o << bundle_f((point_t) 0, (gate_t)  7);
	gated_o << bundle_f((point_t) 1, (gate_t)  1);
	gated_o << bundle_f((point_t) 3, (gate_t) -1);
	gated_o << bundle_f((point_t) 4, (gate_t)  1);
	gated_o << bundle_f((point_t) 5, (gate_t) -1);
	gated_o << bundle_f((point_t) 7, (gate_t)  7);
	gated_o << bundle_f((point_t) 7, (gate_t) 77);
	
	REQUIRE(gated_o() ==  7);
	REQUIRE(gated_o() ==  1);
	REQUIRE(gated_o() ==  1);
	REQUIRE(gated_o() == -1);
	REQUIRE(gated_o() ==  1);
	REQUIRE(gated_o() == -1);
	REQUIRE(gated_o() == -1);
	REQUIRE(gated_o() == 77);
	REQUIRE(gated_o() == 77);
	REQUIRE(gated_o() == 77);
//	...
	gated_o >> sequel_u(N_size);
	gated_o << bundle_f((point_t) 4, (gate_t)  11);
	REQUIRE(gated_o() == 77);
	REQUIRE(gated_o() == 77);
	REQUIRE(gated_o() == 77);
	REQUIRE(gated_o() == 77);
	REQUIRE(gated_o() == 11);
	REQUIRE(gated_o() == 11);
	REQUIRE(gated_o() == 11);
	REQUIRE(gated_o() == 11);

}
/***/
////////////////////////////////////////////////////////////////////////////////
/**/
template <typename ...As>
void test__hold_processor()
{
	size_t constexpr N_size = 1<<3;

	using gate_t = control::label_t<typename realized::alpha_t, struct T_gate>;

	using gated_t = process::confined_t<typename gate_t::template hold<(1<<7)>>;
	using array_t = _std::array<typename realized::alpha_t, N_size>;
	using point_t = context::point_s<>;

	using resize_u = control::resize_t<>;
	using sequel_u = control::sequel_t<>;

	auto gated_o = processor::monomer_t<gated_t, As...>::bond_f();
	auto array_o = array_t();
	
	gated_o << resize_u(N_size);
	gated_o << bundle_f((point_t) 0, (gate_t)  7);
	gated_o << bundle_f((point_t) 1, (gate_t)  1);
	gated_o << bundle_f((point_t) 3, (gate_t) -1);
	gated_o << bundle_f((point_t) 4, (gate_t)  1);
	gated_o << bundle_f((point_t) 5, (gate_t) -1);
	gated_o << bundle_f((point_t) 7, (gate_t)  7);
	gated_o << bundle_f((point_t) 7, (gate_t) 77);

	gated_o >> sequel_u(N_size)*0; _v3::ranges::copy(gated_o, array_o.begin());
	REQUIRE(array_o == array_t {  7,  1,  1, -1,  1, -1, -1, 77});

	gated_o << bundle_f((point_t) 4, (gate_t)  11);
	gated_o >> sequel_u(N_size)*1; _v3::ranges::copy(gated_o, array_o.begin());
	REQUIRE(array_o == array_t { 77, 77, 77, 77, 11, 11, 11, 11});

}
TEST_CASE("xtal/control/anybody.hpp: hold processor")
{
	test__hold_processor<collect<-1>>();
//	test__hold_processor();
}
/***/
////////////////////////////////////////////////////////////////////////////////
/**/
template <class mix_t>
void test__respan_internal_intermit()
{
	using alpha_t = typename realized::alpha_t;

	using    mix_z = processor::monomer_t<mix_t, collect<-1>, typename onset_t::template intermit<(1<<4)>>;
	using resize_u = control::resize_t<>;
	using sequel_n = control::sequel_t<>;

	auto _01 = _v3::views::iota(0, 10)|_v3::views::transform(to_f<alpha_t>);
	auto _10 = _01|_v3::views::transform([] (alpha_t n) {return n*10;});
	auto _11 = _01|_v3::views::transform([] (alpha_t n) {return n*11;});

	auto lhs = processor::let_f(_01); REQUIRE(identical_f(lhs.head(), processor::let_f(lhs).head()));
	auto rhs = processor::let_f(_10); REQUIRE(identical_f(rhs.head(), processor::let_f(rhs).head()));
	
	auto xhs = mix_z::bond_f(lhs, rhs);
	auto seq = sequel_n(4);

	xhs << resize_u(4);
	REQUIRE(0 == xhs.size());//NOTE: Only changes after `sequel`.

	xhs << context::point_s<onset_t>(0, (alpha_t) 100);
	xhs << context::point_s<onset_t>(1, (alpha_t) 200);
	xhs << context::point_s<onset_t>(2, (alpha_t) 300);
	xhs >> seq++;
	REQUIRE(4 == xhs.size());
	REQUIRE(_v3::ranges::equal(xhs, _std::vector{100, 211, 322, 333}));

	xhs << context::point_s<onset_t>(2, (alpha_t) 400);// relative timing!
	xhs >> seq++;
	REQUIRE(4 == xhs.size());
	REQUIRE(_v3::ranges::equal(xhs, _std::vector{344, 355, 466, 477}));

}
TEST_CASE("xtal/control/anybody.hpp: respan internal intermit")
{
	test__respan_internal_intermit<dynamic_onset_mix_t>();
//	test__respan_internal_intermit<static_onset_mix_t>();
}
/***/
///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
