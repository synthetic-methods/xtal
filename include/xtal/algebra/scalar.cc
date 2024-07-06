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

		  TRUE_(U4{2, 12, 6, 2}.cofactored() == U2{2, 12});
		  TRUE_(U4{2, 12, 6, 2}.cofactorable());
		UNTRUE_(U4{2, 12, 6, 3}.cofactorable());
		UNTRUE_(U4{2, 12, 6, 4}.cofactorable());


		U4 const xs_expected { 1,  2,  1,  2};
		U4 const xs_provided { 2, 12,  6,  2};
		
		auto const xs_extents = xs_provided/xs_expected;
		auto const ys_extent  = xs_extents.cofactorable()? 
			xs_extents.template cofactored<1>():
			xs_extents.template  colimited<1>();
		
		U3 const ys_expected { 2,  1,  2};
		U3 const ys_provided = ys_expected*ys_extent;

		TRUE_(xs_extents == U4{2, 6, 6, 1});
		TRUE_(ys_extent   == 6);
		
		TRUE_(xs_provided.sum() == 22);
		TRUE_(ys_provided.sum() == 30);

		/*/
		echo("\ninputs:");
		for (size_type i = 0; i < ys_extent; ++i) {
			auto input_tables = [&]<auto ...I> (bond::seek_t<I...>)
				//\
				XTAL_0FN_(bond::pack_rowwise_f<xs_expected[I]>(inputs.count(), inputs.samples(...)))
				XTAL_0FN_(echo('\t'
				,	((i*xs_expected[I])%xs_provided[I] + xs_provided++[I])...
				))
				(bond::seek_s<bond::pack_size_n<U4>>{});
		}
		echo("\noutputs:");
		for (size_type i = 0; i < ys_extent; ++i) {
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
	TRY_("referencing")
	{
		XTAL_LET N = (size_type) 4;
		float foo[2][N] {{1, 2, 3, 4}, {5, 6, 7, 8}};

		using simplex_val = scalar_t<float   [N]>;
		using simplex_ref = scalar_t<float(&)[N]>;
		
		using complex_val = _std::complex<simplex_val>;
		using complex_ref = _std::complex<simplex_ref>;
		
		simplex_ref bar_re{_std::span(foo[0], 4)};
		simplex_ref bar_im{_std::span(foo[1], 4)};
		complex_ref bar{bar_re, bar_im};
	//	complex_ref bar{_std::span(foo[0], 4), _std::span(foo[1], 4)};// NOPE!

		simplex_val &baz_re = reinterpret_cast<simplex_val &>(foo[0]);
		simplex_val &baz_im = reinterpret_cast<simplex_val &>(foo[1]);
		complex_val &baz    = reinterpret_cast<complex_val &>(foo   );

	//	auto bar_bar = bar*bar;
	//	auto baz_baz = baz*baz;
	//	auto baz_baz = _op::square_f(baz);

	//	echo(baz.real());

	}
}


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
