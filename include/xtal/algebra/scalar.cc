#pragma once
#include "./any.cc"
#include "./scalar.hh"// testing...





XTAL_ENV_(push)
namespace xtal::algebra::_test
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

TAG_("scalar")
{
	using _op = bond::operating;
	using T_delta = typename _op::delta_type;
	using T_sigma = typename _op::sigma_type;
	using T_alpha = typename _op::alpha_type;
	using T_aphex = typename _op::aphex_type;

	TRY_("construction")
	{
		auto constexpr N_size = 2;
		using W = scalar_t<T_alpha[N_size]>;

		auto foo = W{2.0, 0.5};
		auto bar = _op::template roots_f<2>((T_alpha) 2);
		auto baz = bar*bar;
	//	bar.transact([] XTAL_1FN_(_op::square_f), bond::computrim_f<1>);
		TRUE_(get<0>(foo) == bond::computrim_f<19>(get<0>(baz)));
		TRUE_(get<1>(foo) == bond::computrim_f<19>(get<1>(baz)));

		foo *= {(T_alpha) 0.0, (T_alpha) 0.0};

	}
	TRY_("summation")
	{
		auto constexpr N_size = 3;
		using W = scalar_t<T_alpha[N_size]>;
		auto  w = W{2.0, 1.0, 0.5};

		TRUE_(3.5 == w.sum());
		TRUE_(1.5 == w.template sum<-1>());

	}
	TRY_("reflection")
	{
		auto constexpr N_size = 2;
		using W = scalar_t<T_alpha[N_size]>;

		auto bar = W{2.0, 0.5};
		auto foo = bar.template reflected<-1>();
		auto baz = foo.template reflected<+1>();
		
		TRUE_(bond::computrim_f<19>(foo[0]) == 1.25);
		TRUE_(bond::computrim_f<19>(foo[1]) == 0.75);
		TRUE_(bond::computrim_f<19>(baz[0]) == bar[0]);
		TRUE_(bond::computrim_f<19>(baz[1]) == bar[1]);

	}
	TRY_("refactoring")
	{
		using U0 = T_sigma;
		using U1 = scalar_t<U0[1]>;
		using U2 = scalar_t<U0[2]>;
		using U3 = scalar_t<U0[3]>;
		using U4 = scalar_t<U0[4]>;

		TRUE_(U2{2, 12} == U4{2, 12, 6, 2}.cofactored());
		TRUE_(U2{0,  0} == U4{2, 12, 6, 3}.cofactored());
		TRUE_(U2{0,  0} == U4{2, 12, 6, 4}.cofactored());

		U4   const xs_provided { 2, 12,  6,  2};
		U4   const xs_expected { 1,  2,  1,  2};
		
		U4   const xs_ignored  = xs_provided%xs_expected;
		U4   const xs_counted  = xs_provided/xs_expected;
		U0   const ys_arity    = xs_counted.cofactored(1);
		
		U3   const ys_expected { 2,  1,  2};
		U3   const ys_provided  = ys_expected*ys_arity;

		TRUE_(xs_ignored == U4{0, 0, 0, 0});
		TRUE_(xs_counted == U4{2, 6, 6, 1});
		TRUE_(ys_arity   == 6);
		
		TRUE_(xs_provided.sum() == 22);
		TRUE_(ys_provided.sum() == 30);

		/*/
		echo("\ninputs:");
		for (size_type i = 0; i < ys_arity; ++i) {
			auto input_tables = [&]<auto ...I> (bond::seek_t<I...>)
				//\
				XTAL_0FN_(bond::pack_rowwise_f<xs_expected[I]>(inputs.count(), inputs.samples(...)))
				XTAL_0FN_(echo('\t'
				,	((i*xs_expected[I])%xs_provided[I] + xs_provided++[I])...
				))
				(bond::seek_s<bond::pack_size_n<U4>>{});
		}
		echo("\noutputs:");
		for (size_type i = 0; i < ys_arity; ++i) {
			auto output_table = [&]<auto ...I> (bond::seek_t<I...>)
				//\
				XTAL_0FN_(bond::pack_f(bond::pack_rowwise_f<ys_expected[I]>(outputs.count(), output.samples(...)))
				XTAL_0FN_(echo('\t'
				,	((i*ys_expected[I])                + ys_provided++[I])...
				))
				(bond::seek_s<bond::pack_size_n<U3>>{});
		}
		/***/

	}
}


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
