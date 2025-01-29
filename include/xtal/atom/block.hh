#pragma once
#include "./any.hh"






XTAL_ENV_(push)
namespace xtal::atom
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
///\
Defines a fixed-width `type` that supports homogeneous/heterogeneous construction, \
as well as expression-templates. \

template <class ..._s> struct   block;
template <class ..._s> using    block_t = typename block<_s...>::type;
template <class ..._s> concept  block_q = bond::tag_p<block_t, _s...>;

template <class U, auto  N, auto  ..._s> struct   block<U   [N][_s]...> : block<block_t<U[_s]...>   [N]> {};
template <class U, auto  N, auto  ..._s> struct   block<U(&)[N][_s]...> : block<block_t<U[_s]...>(&)[N]> {};


namespace _detail
{///////////////////////////////////////////////////////////////////////////////

template <class ..._s> struct   superblock;
template <class ..._s> using    superblock_t = typename superblock<_s...>::type;

template <class U, auto N, auto  ...Ns> struct superblock<U   [N][Ns]...> : superblock<superblock_t<U[Ns]...>   [N]> {};
template <class U, auto N, auto  ...Ns> struct superblock<U(&)[N][Ns]...> : superblock<superblock_t<U[Ns]...>(&)[N]> {};

template <scalar_q ...Us> requires      same_q<Us...>
struct superblock<Us ...>
:	superblock<common_t<Us...>[sizeof...(Us)]>
{
};
template <scalar_q ...Us> requires different_q<Us...>
struct superblock<Us...>
{
	using endotype = bond::pack_t<Us...>;
	
	template <class T>
	using holotype = bond::compose_s<endotype, bond::define<T>>;

	template <class T>
	class homotype: public holotype<T>
	{
		using S_ = holotype<T>;

	protected:
		static auto constexpr N_data = sizeof...(Us);
		using T_data =  common_t<objective_t<Us>...>;
		using U_data =  common_t<Us...>;
		using V_data = absolve_u<Us...>;

	public:// TYPE
		using archetype        =  endotype;
		using initializer_list = _std::initializer_list<T_data>;

	public:// OPERATE
		static constant_t<sizeof(archetype)> constexpr size_bytes{};
		
	public:// CONSTRUCT
		using S_::S_;

		using        size_type = _std::   size_t;
		using  difference_type = _std::ptrdiff_t;

	};	
	using type = derive_t<homotype>;

};
template <scalar_q U, auto N>
struct superblock<U(&)[N]>
{
	//\
	using endotype = reiterated_t<_std::array<U, N>>;//NOTE: Doesn't truncate properly?
	using endotype = _std::span<U, N>;
	
	template <class T>
	using holotype = bond::compose_s<endotype, bond::define<T>>;

	template <class T>
	class homotype: public holotype<T>
	{
		using S_ = holotype<T>;

	protected:
		static auto constexpr N_data = N ;
		using T_data =                 U ;
		using U_data =                 U ;
		using V_data =       absolve_u<U>;

	public:// TYPE
		using archetype        =  endotype;
		using initializer_list = _std::initializer_list<T_data>;

		using        size_type = _std::   size_t;
		using  difference_type = _std::ptrdiff_t;
		
	public:// CONSTRUCT
		using S_::S_;

	};	
	using type = derive_t<homotype>;

};
template <scalar_q U, auto N>
struct superblock<U   [N]>
{
	using endotype = _std::array<U, N>;
	
	template <class T>
	using holotype = bond::compose_s<endotype, bond::define<T>>;

	template <class T>
	class homotype: public holotype<T>
	{
		using S_ = holotype<T>;

	protected:
		static auto constexpr N_data = N ;
		using T_data =                 U ;
		using U_data =                 U ;
		using V_data =       absolve_u<U>;

	public:// TYPE
		using archetype        =  endotype;
		using initializer_list = _std::initializer_list<T_data>;

	public:// OPERATE
		static constant_t<sizeof(archetype)> constexpr size_bytes{};
		
	public:// CONSTRUCT
		using S_::S_;
	~	homotype()                 noexcept=default;
	//	homotype()                 noexcept=default;
		XTAL_NEW_(copy) (homotype, noexcept=default)
		XTAL_NEW_(move) (homotype, noexcept=default)
		
		XTAL_NEW_(explicit) homotype()
		noexcept
		:	homotype(size_type{})
		{}
		XTAL_NEW_(explicit) homotype(same_q<size_type> auto const n)
		noexcept
		{
			assert(n <= N_data);
			if (_std::is_constant_evaluated() or n < N_data) {
				S_::fill(U_data{});
			}
		}
	//	TODO: Should check `coindexed_q`? Or how to determine if `ordinate` has been replaced?

		XTAL_NEW_(implicit) homotype(initializer_list a)
		noexcept
		:	homotype(count_f(a))
		{
			XTAL_IF0
			XTAL_0IF (covalued_q<T>) {_detail::move_to<[] XTAL_0FN_(alias) (T::ordinate)>(S_::begin(), a);}
			XTAL_0IF_(else)          {_detail::move_to                                   (S_::begin(), a);}
		}
		XTAL_NEW_(explicit) homotype(iterable_q auto       &&a)
		noexcept
		:	homotype(count_f(a))
		{
			XTAL_IF0
			XTAL_0IF (covalued_q<T>) {_detail::move_to<[] XTAL_0FN_(alias) (T::ordinate)>(S_::begin(), a);}
			XTAL_0IF_(else)          {_detail::move_to                                   (S_::begin(), a);}
		}
		XTAL_NEW_(explicit) homotype(iterable_q auto const  &a)
		noexcept
		:	homotype(count_f(a))
		{
			XTAL_IF0
			XTAL_0IF (covalued_q<T>) {_detail::copy_to<[] XTAL_0FN_(alias) (T::ordinate)>(S_::begin(), a);}
			XTAL_0IF_(else)          {_detail::copy_to                                   (S_::begin(), a);}
		}

	};
	using type = derive_t<homotype>;

};


}///////////////////////////////////////////////////////////////////////////////

template <class ..._s>
struct block
{
	template <class T>
	using endotype = typename _detail::superblock<_s...>::template homotype<T>;

	template <class T>
	using holotype = bond::compose_s<endotype<T>, bond::tag<block_t>>;

	template <class T>
	class homotype : public holotype<T>
	{
		using S_ = holotype<T>;

	public:// CONSTRUCT
		using S_::S_;

	protected:
		using          S_::N_data;///< The           number of elements. 
		using typename S_::T_data;///< The constrained-type of elements.
		using typename S_::U_data;///< The      common-type of elements. 
		using typename S_::V_data;///< The  arithmetic-type of elements.

	public:// TYPE
		using typename S_::archetype;

		template <size_type N>
		using tuple_element = _std::tuple_element<N, archetype>;
		//\
		using tuple_size    = _std::tuple_size   <   archetype>;
		using tuple_size    = constant_t<N_data>;

		///\
		Reinvokes the current `template` (uniquely determined by the `bond::tag`s). \
 		
		template <class _, class ...As> struct  reforge           {using type = typename T::taboo::template hypertype<As...>;};
		template <class _             > struct  reforge<_, _s...> {using type = T;};
		template <         class ...As> using   reforge_t = typename reforge<void, As...>::type;

		///\returns a reconstruction of `this` using the supplied `template`-arguments. \
		
		XTAL_FX2_(do) (template <class ...As>
		XTAL_DEF_(return,inline,let)
		reform(),
		noexcept -> decltype(auto)
		{
			XTAL_IF0
			XTAL_0IF (0 == sizeof...(As)) {return reforge_t<_s...>(self());}
			XTAL_0IF (1 <= sizeof...(As)) {return reforge_t<As...>(self());}
		})

		///\returns the internal representation of the given `co`ordinate. \

		XTAL_DEF_(return,inline,set)
		ordinate(auto &&co)
		noexcept -> decltype(auto)
		{
			return XTAL_REF_(co);
		}
		///\returns the external representation of the given `o`rdinate. \

		XTAL_DEF_(return,inline,set)
		coordinate(auto &&o)
		noexcept -> decltype(auto)
		{
			return XTAL_REF_(o);
		}

	public:// ACCESS
		using S_::self;

		///\returns the first `i` elements of `this` as a truncated view over `U`. \

		XTAL_FX4_(do) (template <scalar_q U=U_data>
		XTAL_DEF_(return,inline,let)
		self(constant_q auto i),
		noexcept -> decltype(auto)
		{
			return reform<U(&)[i()]>();
		})

		///\returns the first `i` elements of `this` as a truncated copy over `U`. \

		XTAL_FX4_(do) (template <scalar_q U=U_data>
		XTAL_DEF_(return,inline,let)
		twin(constant_q auto i),
		noexcept -> decltype(auto)
		{
			return reform<U   [i()]>();
		})
		XTAL_FX4_(do) (template <scalar_q U=U_data>
		XTAL_DEF_(return,inline,let)
		twin(),
		noexcept -> decltype(auto)
		{
			return twin(constant_n<N_data>);
		})

		///\returns the size of this type or value. \

		static constant_t<N_data> constexpr size{};

		template <size_type I>
		XTAL_DEF_(return,inline,let)
		operator() () const
		noexcept -> decltype(auto)
		{
			return self().coordinate(element<I>());
		}
		XTAL_DEF_(return,inline,let)
		operator() (auto i) const
		noexcept -> decltype(auto)
		requires vector_q<_s...>
		{
			return self().coordinate(element(i));
		}
		
		XTAL_FX4_(do) (template <size_type I>
		XTAL_DEF_(return,inline,let)
		element(),
		noexcept -> decltype(auto)
		{
			auto &s = S_::template self<archetype>();
			XTAL_IF0
			XTAL_0IF_(return) (*get<I>(s))
			XTAL_0IF_(return) ( get<I>(s))
			XTAL_0IF_(return) (element(constant_n<I>))//NOTE: Required for `span` but not `subrange`...
		})
		XTAL_FX4_(do) (template <auto I=0>
		XTAL_DEF_(return,inline,let)
		element(auto i),
		noexcept -> decltype(auto)
		requires vector_q<_s...>
		{
			assert(i + I < N_data);
			return self().operator[](i + I);
		})

	public:// OPERATE

		XTAL_DEF_(return,inline,friend,let)
		operator==(homotype const &s, homotype const &t)
		noexcept -> bool
		{
			XTAL_IF0
			XTAL_0IF XTAL_TRY_(return)
				(static_cast<archetype const &>(s) == static_cast<archetype const &>(t))

			XTAL_0IF (vector_q<_s...> and _std::is_standard_layout_v<U_data>) {
				return 0 == _std::memcmp(s.data(), t.data(), S_::size_bytes());//FIXME: Not working for complex values?
			}
			XTAL_0IF_(else) {
				return [&]<auto ...I>(bond::seek_t<I...>)
					XTAL_0FN_(return) (...and (get<I>(s) == get<I>(t)))
				(bond::seek_s<N_data> {});
			}
		}

		///\returns `true` if the underlying `data` is zero, `false` otherwise. \

		template <auto N_value=0>
		XTAL_DEF_(return,inline,let)
		blanked() const
		noexcept -> auto
		{
			reforge_t<based_t<_s>...> constexpr blank{N_value};
			return blank == self();
		}
		///\returns the result of `blanked()` before refilling with `N_value=0`. \

		template <auto N_value=0>
		XTAL_DEF_(inline,let)
		blanket()
		noexcept -> bool
		requires vector_q<_s...>
		{
			using U_value = absolve_u<U_data>;
			using V_value = typename bond::fixture<U_value>::sigma_type;

			auto constexpr u  =    static_cast<U_value>(N_value);
			auto constexpr v  = _xtd::bit_cast<V_value>(u);
			bool const     z  = blanked();
			auto const     zu = u* static_cast<U_value>(z);
			auto const    _zv = v&-z;
#if XTAL_ENV_(LLVM)
			if constexpr (false) {
			}
#else
			if constexpr (anyplex_q<U_data>) {
				auto &s = dissolve_f(*this);
				bond::seek_forward_f<N_data>([&] (auto I) XTAL_0FN {
					XTAL_IF0
					XTAL_0IF (simplex_q<U_data>) {return reinterpret_cast<V_value &>(s[I]   ) |= _zv;}
					XTAL_0IF (complex_q<U_data>) {return reinterpret_cast<V_value &>(s[I][0]) |= _zv;}
				});
			}
#endif
			else {
				auto const n = static_cast<U_value>(z)*u;
				auto      &s = *this;
				bond::seek_forward_f<N_data>([&] (auto I) XTAL_0FN {
					get<I>(s) += n;
				});
			}
			return z;
		}

	};
	using type = derive_t<homotype>;

};
template <size_type I> XTAL_DEF_(return,inline,let) get(block_q auto const &&o) noexcept -> decltype(auto) {return XTAL_MOV_(o).template element<I>();}
template <size_type I> XTAL_DEF_(return,inline,let) get(block_q auto       &&o) noexcept -> decltype(auto) {return XTAL_MOV_(o).template element<I>();}
template <size_type I> XTAL_DEF_(return,inline,let) get(block_q auto const  &o) noexcept -> decltype(auto) {return XTAL_REF_(o).template element<I>();}
template <size_type I> XTAL_DEF_(return,inline,let) get(block_q auto        &o) noexcept -> decltype(auto) {return XTAL_REF_(o).template element<I>();}


////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
/**/
namespace std
{///////////////////////////////////////////////////////////////////////////////

template <xtal::atom::block_q T>
struct tuple_size<T> : T::tuple_size {};

template <size_t N, xtal::atom::block_q T>
struct tuple_element<N, T> : T::template tuple_element<N> {};


}/////////////////////////////////////////////////////////////////////////////
/***/
XTAL_ENV_(pop)
