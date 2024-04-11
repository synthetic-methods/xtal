#pragma once
#include "./any.hh"






XTAL_ENV_(push)
namespace xtal::atom
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

template <class ..._s> struct  block;
template <class ..._s> using   block_t = typename block<_s...>::type;
template <class ..._s> concept block_q = bond::tag_p<block, _s...>;


////////////////////////////////////////////////////////////////////////////////
///\
Defines a fixed-width `type` that supports arithmetic operators. \
Only scalar multiplication is defined by default. \

///\todo\
Specialize for SIMDe types. \

///\todo\
Adapt `_detail::apply_to` etc to execute in parallel using SIMDE? \


template <class U_type, size_t N, int Ns>
struct block<U_type[N][Ns]> : block<block_t<U_type[N]>[Ns]>
{};
template <class U_type, size_t N_size>
struct block<U_type[N_size]>
{
	using re = bond::realize<U_type>;
	
	template <class T>
	using demitype = bond::compose_s<_std::array<U_type, N_size>, bond::define<T>>;

	template <class T>
	using hemitype = bond::compose_s<demitype<T>, bond::tag<block>>;

	template <class T>
	class homotype : public hemitype<T>
	{
		friend T;
		using  T_ = hemitype<T>;
		using  I_ = typename T_::difference_type;

	public:// ACCESS
		using T_::self;
		using T_::twin;
		XTAL_FN2_(typename re::sigma_t) size()
		XTAL_0EX {return N_size;}

		XTAL_TN2 get(I_ i) XTAL_0FX_(&&) {return XTAL_MOV_(T_::operator[](i));}
		XTAL_TN2 get(I_ i) XTAL_0FX_(&)  {return          (T_::operator[](i));}

		XTAL_TN2 let(I_ i) XTAL_0EX_(&&) {return XTAL_MOV_(T_::operator[](i));}
		XTAL_TN2 let(I_ i) XTAL_0EX_(&)  {return          (T_::operator[](i));}

	public:// CONVERSION
		///\
		Elementwise immutative transformer. \

		XTAL_TO4_(template <array_q W> XTAL_TN1 transmorph(), transmorph<W>(make_f<devalue_t<W>>))
		template <array_q W> XTAL_TN1 transmorph(_std::invocable<U_type> auto &&f) XTAL_0EX_(&&) {return transmove<W>(XTAL_REF_(f));}
		template <array_q W> XTAL_TN1 transmorph(_std::invocable<U_type> auto &&f) XTAL_0FX_(&&) {return transmove<W>(XTAL_REF_(f));}
		template <array_q W> XTAL_TN1 transmorph(_std::invocable<U_type> auto &&f) XTAL_0EX_( &) {return transcopy<W>(XTAL_REF_(f));}
		template <array_q W> XTAL_TN1 transmorph(_std::invocable<U_type> auto &&f) XTAL_0FX_( &) {return transcopy<W>(XTAL_REF_(f));}
		template <array_q W> XTAL_TN1 transmove (_std::invocable<U_type> auto &&f) XTAL_0EX {based_t<W> w; _detail::move_to(w.begin(), self(), XTAL_REF_(f)); return w;}
		template <array_q W> XTAL_TN1 transcopy (_std::invocable<U_type> auto &&f) XTAL_0FX {based_t<W> w; _detail::copy_to(w.begin(), self(), XTAL_REF_(f)); return w;}

		///\
		Elementwise mutative transformer. \

		XTAL_TN1 transmorph(_std::invocable<U_type> auto &&...fs)
		XTAL_0EX
		{
			return (transmorph(XTAL_REF_(fs)), ...);
		}
		XTAL_TN1 transmorph(_std::invocable<U_type> auto &&f)
		XTAL_0EX
		{
			_detail::apply_to(self(), XTAL_REF_(f));
			return self();
		}
		
	public:// CONSTRUCTION
	//	using T_::T_;

		~homotype() noexcept = default;
		XTAL_CO4_(homotype)
		
		XTAL_CON homotype()
		XTAL_0EX
		:	homotype((size_t) 0)
		{}
		XTAL_CXN homotype(size_t n)
		XTAL_0EX
		{
			assert(n <= N_size);
			_std::uninitialized_value_construct_n(_std::next(T_::data(), n), T_::size() - n);
		}
		XTAL_CON homotype(braces_t<U_type> a)
		XTAL_0EX
		:	homotype(a.size())
		{
			_detail::copy_to(T_::begin(), a.begin(), a.end());
		}
		template <bounded_q A>
		XTAL_CXN homotype(A const &a)
		:	homotype(a.size())
		{
			_detail::copy_to(T_::begin(), a);
		}
		template <bounded_q A>
		XTAL_CXN homotype(A &&a)
		:	homotype(a.size())
		{
			_detail::move_to(T_::begin(), a);
		}
		
	};
	using type = bond::isotype<homotype>;

};

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
/**/
namespace std
{///////////////////////////////////////////////////////////////////////////////

template <xtal::atom::block_q T>
struct tuple_size<T> : xtal::cardinal_t<T::size()> {};

template <size_t N_size, xtal::atom::block_q T>
struct tuple_element<N_size, T> {using type = xtal::unvalue_t<T>;};


}/////////////////////////////////////////////////////////////////////////////
/***/
XTAL_ENV_(pop)
