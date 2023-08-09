#pragma once
#include "./any.cc"
#include "./sequel.ii"// testing...





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

	auto n_seq = X(4);
	auto u_seq = Y(4), w_seq = Y(4*i);

	w_seq >>= n_seq++; TRUE_(w_seq == Y(U(0, 4), 0));
	
	w_seq >>= n_seq.skip(0).slice(U(0, 2)); TRUE_(w_seq == Y(U(4, 6), 1));
	w_seq >>= n_seq.skip(1).slice(U(2, 4)); TRUE_(w_seq == Y(U(6, 8), 2));
	w_seq <<= n_seq++;                      TRUE_(w_seq == Y(U(4, 8), 1));
	
	w_seq >>= n_seq.skip(0).slice(U(0, 2)); TRUE_(w_seq == Y(U( 8, 10), 2));
	w_seq >>= n_seq.skip(1).slice(U(2, 4)); TRUE_(w_seq == Y(U(10, 12), 3));
	w_seq <<= n_seq++;                      TRUE_(w_seq == Y(U( 8, 12), 2));

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

		auto n_seq = sequel_n(3);
		auto u_seq = sequel_u(3);

		++n_seq; u_seq += n_seq.size(); TRUE_(3 == u_seq.front()); TRUE_(3 + (3 - 1) == u_seq.back());
		++n_seq; u_seq += n_seq.size(); TRUE_(6 == u_seq.front()); TRUE_(6 + (3 - 1) == u_seq.back());
		++n_seq; u_seq += n_seq.size(); TRUE_(9 == u_seq.front()); TRUE_(9 + (3 - 1) == u_seq.back());

		n_seq += 4; u_seq += n_seq.size(); TRUE_(12 == u_seq.front()); TRUE_(12 + (4 - 1) == u_seq.back());
		n_seq += 5; u_seq += n_seq.size(); TRUE_(16 == u_seq.front()); TRUE_(16 + (5 - 1) == u_seq.back());
		n_seq += 6; u_seq += n_seq.size(); TRUE_(21 == u_seq.front()); TRUE_(21 + (6 - 1) == u_seq.back());

		TRUE_((int) n_seq.size() == (int) u_seq.size());
	}
	TRY_("synchronization")
	{
		using V = counter_t<>;
		using U = counted_t<>;

		using sequel_n = sequel_t<V>; auto n_seq = sequel_n(3);
		using sequel_u = sequel_t<U>; auto u_seq = sequel_u(3);

		TRUE_(u_seq.size() == n_seq.size());
		TRUE_(u_seq.step() == n_seq.step());
		TRUE_(u_seq == sequel_u(U(0, 3), 0));
		
		TRUE_((n_seq.step() == 0 and u_seq.front() == 0 and u_seq.back() == 2));

		++n_seq;
		++u_seq;
		TRUE_(u_seq.size() == n_seq.size());
		TRUE_(u_seq.step() == n_seq.step());
		TRUE_(u_seq == sequel_u(U(3, 6), 1));

		n_seq++;
		u_seq++;
		TRUE_(u_seq.size() == n_seq.size());
		TRUE_(u_seq.step() == n_seq.step());
		TRUE_(u_seq == sequel_u(U(6, 9), 2));

		n_seq += 5;
		u_seq += 5;
		TRUE_(u_seq.size() == n_seq.size());
		TRUE_(u_seq.step() == n_seq.step());
		TRUE_(u_seq == sequel_u(U(9, 14), 3));
		TRUE_(u_seq.null() == sequel_u(U(14, 14), 4));
		TRUE_(u_seq.next() == sequel_u(U(14, 19), 4));
		
		u_seq = sequel_u(11) *= (7);
		TRUE_(u_seq == sequel_u(U(77, 88), 7));

		n_seq = sequel_n(11) *= (7);
		TRUE_(n_seq == sequel_n(11, 7));

		TRUE_(n_seq.skip(0).slice(U(0, 11)) == sequel_n(11, 7));
		TRUE_(n_seq.skip(0).slice(U(0, 01)) == sequel_n(01, 7));
		TRUE_(n_seq.skip(1).slice(U(1, 11)) == sequel_n(10, 8));

		TRUE_(u_seq.skip(0).slice(U(0, 11)) == sequel_u(U(77, 88), 7));
		TRUE_(u_seq.skip(0).slice(U(0, 01)) == sequel_u(U(77, 78), 7));
		TRUE_(u_seq.skip(1).slice(U(1, 11)) == sequel_u(U(78, 88), 8));

		n_seq = sequel_n(4, 1);
		n_seq = n_seq.null(); TRUE_(n_seq == sequel_n(0, 2));

	}
	TRY_("intrepidation with unit-offset")
	{
		using V = counter_t<>;
		using U = counted_t<>;
		using sequel_n = sequel_t<V>; auto n_seq = sequel_n(3);
		using sequel_u = sequel_t<U>; auto u_seq = sequel_u(3), w_seq = u_seq;

		TRUE_(w_seq.efflux(u_seq) == 1); TRUE_(w_seq == sequel_u(U(0, 3), 0));
		w_seq >>= ++u_seq;                 TRUE_(w_seq == sequel_u(U(3, 6), 1));
		w_seq >>= ++u_seq;                 TRUE_(w_seq == sequel_u(U(6, 9), 2));

	}
	TRY_("intrepidation with null-offset")
	{
		using V = counter_t<>;
		using U = counted_t<>;
		using sequel_n = sequel_t<V>; auto n_seq = sequel_n(3);
		using sequel_u = sequel_t<U>; auto u_seq = sequel_u(3), w_seq = sequel_u(0);

		TRUE_(w_seq.efflux(u_seq) == 0); TRUE_(w_seq == sequel_u(U(0, 3), 0));
		w_seq >>= ++u_seq;                 TRUE_(w_seq == sequel_u(U(3, 6), 1));
		w_seq >>= ++u_seq;                 TRUE_(w_seq == sequel_u(U(6, 9), 2));

	}
	TRY_("cycle")
	{
		using V = counter_t<size_t>; using sequel_n = sequel_t<V>;
		using U = counted_t<size_t>; using sequel_u = sequel_t<U>;
		size_t constexpr N = 5;

		sequel_n n_seq(N); n_seq *= N;
		sequel_n m_seq = n_seq;

		m_seq += N;
		m_seq -= N;
		TRUE_(m_seq == n_seq);

		m_seq += 0;
		m_seq -= N;
		TRUE_(m_seq == n_seq);

		m_seq -= 0;
		m_seq += N;
		TRUE_(m_seq == n_seq);

		m_seq += 0;
		m_seq -= 0;
		TRUE_(m_seq == n_seq.null());

	}
}


///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
