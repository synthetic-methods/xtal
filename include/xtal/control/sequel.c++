#pragma once
#include "./any.c++"
#include "./sequel.ipp"// testing...





XTAL_ENV_(push)
namespace xtal::control::__test
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

template <class Y, class X>
void serial__initialization(auto n)
{
	X x; Y y;
	x = X(n); y = Y(0); TRUE_(y.efflux(x) == 0); TRUE_(y.step() == 0); TRUE_(y.size() == n);
	x = X(n); y = Y(n); TRUE_(y.efflux(x) == 1); TRUE_(y.step() == 0); TRUE_(y.size() == n);

}
template <class Y, class X>
void serial__finalization(auto n)
{
	X x; Y y;
	x = X(n); y = Y(n)       ; TRUE_(y.influx(x) == 0); TRUE_(y.step() == 1); TRUE_(y.size() == 0);
//	x = X(n); y = Y(n).null(); TRUE_(y.influx(x) == 1); TRUE_(y.step() == 2); TRUE_(y.size() == 0);

}
template <class Y, class X>
void serial__interference(auto i)
{
	using V = counter_t<>;
	using U = counted_t<>;

	auto seq_n = X(4);
	auto seq_u = Y(4), seq_w = Y(4*i);

	seq_w >> seq_n++; TRUE_(seq_w == Y(U(0, 4), 0));
	
	seq_w >> seq_n.skip(0).slice(U(0, 2)); TRUE_(seq_w == Y(U(4, 6), 1));
	seq_w >> seq_n.skip(1).slice(U(2, 4)); TRUE_(seq_w == Y(U(6, 8), 2));
	seq_w << seq_n++;                      TRUE_(seq_w == Y(U(4, 8), 1));
	
	seq_w >> seq_n.skip(0).slice(U(0, 2)); TRUE_(seq_w == Y(U( 8, 10), 2));
	seq_w >> seq_n.skip(1).slice(U(2, 4)); TRUE_(seq_w == Y(U(10, 12), 3));
	seq_w << seq_n++;                      TRUE_(seq_w == Y(U( 8, 12), 2));

}
TAG_("serial")
{
	TRY_("initialization")
	{
		using sequel_n = sequel_t<counter_t<>>;
		using sequel_u = sequel_t<counted_t<>>;
		using I = typename sequel_u::step_t;

		serial__initialization<sequel_u, sequel_u>((I) 3);
		serial__initialization<sequel_u, sequel_n>((I) 3);
		serial__initialization<sequel_n, sequel_u>((I) 3);
		serial__initialization<sequel_n, sequel_n>((I) 3);

	}
	TRY_("finalization")
	{
		using sequel_n = sequel_t<counter_t<>>;
		using sequel_u = sequel_t<counted_t<>>;
		using I = typename sequel_u::step_t;
		
		serial__initialization<sequel_u, sequel_u>((I) 3);
		serial__initialization<sequel_u, sequel_n>((I) 3);
		serial__initialization<sequel_n, sequel_u>((I) 3);
		serial__initialization<sequel_n, sequel_n>((I) 3);

	}
	TRY_("interference")
	{
		using V = counter_t<>; using sequel_n = sequel_t<V>;
		using U = counted_t<>; using sequel_u = sequel_t<U>;
		using I = typename sequel_u::step_t;

		for (I i = 0; i <= 1; ++i)
		{
			serial__interference<sequel_u, sequel_u>(i);
			serial__interference<sequel_u, sequel_n>(i);
			serial__interference<sequel_n, sequel_u>(i);
			serial__interference<sequel_n, sequel_n>(i);
		}

	}
	TRY_("interconversion")
	{
		using sequel_n = sequel_t<counter_t<>>;
		using sequel_u = sequel_t<counted_t<>>;

		auto seq_n = sequel_n(3);
		auto seq_u = sequel_u(3);

		++seq_n; seq_u += seq_n.size(); TRUE_(3 == seq_u.front()); TRUE_(3 + (3 - 1) == seq_u.back());
		++seq_n; seq_u += seq_n.size(); TRUE_(6 == seq_u.front()); TRUE_(6 + (3 - 1) == seq_u.back());
		++seq_n; seq_u += seq_n.size(); TRUE_(9 == seq_u.front()); TRUE_(9 + (3 - 1) == seq_u.back());

		seq_n += 4; seq_u += seq_n.size(); TRUE_(12 == seq_u.front()); TRUE_(12 + (4 - 1) == seq_u.back());
		seq_n += 5; seq_u += seq_n.size(); TRUE_(16 == seq_u.front()); TRUE_(16 + (5 - 1) == seq_u.back());
		seq_n += 6; seq_u += seq_n.size(); TRUE_(21 == seq_u.front()); TRUE_(21 + (6 - 1) == seq_u.back());

		TRUE_((int) seq_n.size() == (int) seq_u.size());
	}
	TRY_("synchronization")
	{
		using V = counter_t<>;
		using U = counted_t<>;

		using sequel_n = sequel_t<V>; auto seq_n = sequel_n(3);
		using sequel_u = sequel_t<U>; auto seq_u = sequel_u(3);

		TRUE_(seq_u.size() == seq_n.size());
		TRUE_(seq_u.step() == seq_n.step());
		TRUE_(seq_u == sequel_u(U(0, 3), 0));
		
		TRUE_((seq_n.step() == 0 and seq_u.front() == 0 and seq_u.back() == 2));

		++seq_n;
		++seq_u;
		TRUE_(seq_u.size() == seq_n.size());
		TRUE_(seq_u.step() == seq_n.step());
		TRUE_(seq_u == sequel_u(U(3, 6), 1));

		seq_n++;
		seq_u++;
		TRUE_(seq_u.size() == seq_n.size());
		TRUE_(seq_u.step() == seq_n.step());
		TRUE_(seq_u == sequel_u(U(6, 9), 2));

		seq_n += 5;
		seq_u += 5;
		TRUE_(seq_u.size() == seq_n.size());
		TRUE_(seq_u.step() == seq_n.step());
		TRUE_(seq_u == sequel_u(U(9, 14), 3));
		TRUE_(seq_u.null() == sequel_u(U(14, 14), 4));
		TRUE_(seq_u.next() == sequel_u(U(14, 19), 4));
		
		seq_u = sequel_u(11) *= (7);
		TRUE_(seq_u == sequel_u(U(77, 88), 7));

		seq_n = sequel_n(11) *= (7);
		TRUE_(seq_n == sequel_n(11, 7));

		TRUE_(seq_n.skip(0).slice(U(0, 11)) == sequel_n(11, 7));
		TRUE_(seq_n.skip(0).slice(U(0, 01)) == sequel_n(01, 7));
		TRUE_(seq_n.skip(1).slice(U(1, 11)) == sequel_n(10, 8));

		TRUE_(seq_u.skip(0).slice(U(0, 11)) == sequel_u(U(77, 88), 7));
		TRUE_(seq_u.skip(0).slice(U(0, 01)) == sequel_u(U(77, 78), 7));
		TRUE_(seq_u.skip(1).slice(U(1, 11)) == sequel_u(U(78, 88), 8));

		seq_n = sequel_n(4, 1);
		seq_n = seq_n.null(); TRUE_(seq_n == sequel_n(0, 2));

	}
	TRY_("intrepidation with unit-offset")
	{
		using V = counter_t<>;
		using U = counted_t<>;
		using sequel_n = sequel_t<V>; auto seq_n = sequel_n(3);
		using sequel_u = sequel_t<U>; auto seq_u = sequel_u(3), seq_w = seq_u;

		TRUE_(seq_w.efflux(seq_u) == 1); TRUE_(seq_w == sequel_u(U(0, 3), 0));
		seq_w >> ++seq_u;                 TRUE_(seq_w == sequel_u(U(3, 6), 1));
		seq_w >> ++seq_u;                 TRUE_(seq_w == sequel_u(U(6, 9), 2));

	}
	TRY_("intrepidation with null-offset")
	{
		using V = counter_t<>;
		using U = counted_t<>;
		using sequel_n = sequel_t<V>; auto seq_n = sequel_n(3);
		using sequel_u = sequel_t<U>; auto seq_u = sequel_u(3), seq_w = sequel_u(0);

		TRUE_(seq_w.efflux(seq_u) == 0); TRUE_(seq_w == sequel_u(U(0, 3), 0));
		seq_w >> ++seq_u;                 TRUE_(seq_w == sequel_u(U(3, 6), 1));
		seq_w >> ++seq_u;                 TRUE_(seq_w == sequel_u(U(6, 9), 2));

	}
	TRY_("cycle")
	{
		using V = counter_t<size_t>; using sequel_n = sequel_t<V>;
		using U = counted_t<size_t>; using sequel_u = sequel_t<U>;
		size_t constexpr N = 5;

		sequel_n seq_n(N); seq_n *= N;
		sequel_n seq_m = seq_n;

		seq_m += N;
		seq_m -= N;
		TRUE_(seq_m == seq_n);

		seq_m += 0;
		seq_m -= N;
		TRUE_(seq_m == seq_n);

		seq_m -= 0;
		seq_m += N;
		TRUE_(seq_m == seq_n);

		seq_m += 0;
		seq_m -= 0;
		TRUE_(seq_m == seq_n.null());

	}
}


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
