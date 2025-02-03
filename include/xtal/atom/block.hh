#pragma once
#include "./any.hh"






XTAL_ENV_(push)
namespace xtal::atom
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
///\
Defines a statically-bounded `type` that supports homogeneous/heterogeneous construction, \
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

	public:// ACCESS
		using        size_type = _std::size_t;
		using  difference_type = _std::make_signed_t<size_type>;

		using        archetype = endotype;
		using       value_type = common_t<objective_t<Us>...>;
		using       scale_type = absolve_u<value_type>;

	//	using       bytes_size = constant_t<sizeof(archetype)>;
	//	static      bytes_size   constexpr size_bytes{};
		using       tuple_size = constant_t<sizeof...(Us)>;
		static      tuple_size   constexpr size      {};
		template <size_type I>
		using       tuple_element = _std::tuple_element<I, archetype>;

	public:// CONSTRUCT
		using S_::S_;

		XTAL_FX4_(alias) (template <class ...Xs> XTAL_DEF_(return,inline,let) front(), get<       0>(S_::self()))
		XTAL_FX4_(alias) (template <class ...Xs> XTAL_DEF_(return,inline,let) back (), get<size - 1>(S_::self()))

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

	public:// ACCESS
		using        size_type = decltype(N);
		using  difference_type = _std::make_signed_t<size_type>;

		using        archetype =  endotype;
		using       value_type =  U;
		using       scale_type =  absolve_u<value_type>;
		
	//	using       bytes_size = constant_t<sizeof(archetype)>;
	//	static      bytes_size   constexpr size_bytes{};
		using       tuple_size = constant_t<N>;
		static      tuple_size   constexpr size      {};
		template <size_type I>
		struct      tuple_element {using type = U;};

		static_assert(_std::same_as<U, typename S_::value_type>);

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

	public:// ACCESS
		using        archetype =  endotype;		
		using       value_type =  U;
		using       scale_type =  absolve_u<value_type>;

		using       bytes_size = constant_t<sizeof(archetype)>;
		static      bytes_size   constexpr size_bytes{};
		using       tuple_size = constant_t<N>;
		static      tuple_size   constexpr size      {};
		template <size_type I>
		struct      tuple_element {using type = U;};

		static_assert(_std::same_as<U, typename S_::value_type>);

	public:// CONSTRUCT
	//	using S_::S_;

	~	homotype()                 noexcept=default;
	//	homotype()                 noexcept=default;
		XTAL_NEW_(copy) (homotype, noexcept=default)
		XTAL_NEW_(move) (homotype, noexcept=default)
		
		XTAL_NEW_(implicit) homotype()
		noexcept
		:	homotype(size_type{})
		{}
		XTAL_NEW_(explicit) homotype(same_q<size_type> auto const n)
		noexcept
		{
			assert(n <= size);
			if (_std::is_constant_evaluated() or n < size) {
				S_::fill(value_type{});
			}
		}
		XTAL_NEW_(implicit) homotype(_std::initializer_list<value_type> xs)
		noexcept
		:	homotype(count_f(xs))
		{
			_detail::move_to<T::ordinate>(S_::begin(), xs.begin(), count_f(xs));
		}
		XTAL_NEW_(explicit) homotype(iterable_q auto &&xs)
		noexcept
		requires epimorphic_q<homotype, decltype(xs)>
		:	homotype(count_f(xs))
		{
			_detail::transfer_to<T::ordinate>(S_::begin(), XTAL_REF_(xs), count_f(xs));
		}

	};
	using type = derive_t<homotype>;

};


}///////////////////////////////////////////////////////////////////////////////

template <scalar_q ..._s> requires same_q<_s...>
struct block<_s ...>
:	block<common_t<_s...>[sizeof...(_s)]>
{
};
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

		template <class _, class ...As> struct form_           {using type = bond::compose_s<T, bond::hypertag<As...>>;};
		template <class _             > struct form_<_       > {using type = T;};
		template <class _             > struct form_<_, _s...> {using type = T;};

	public:// OPERATE
		using S_::size;

	public:// CONSTRUCT
		using S_::S_;

		using typename S_:: archetype;
		using typename S_::value_type;
		using typename S_::scale_type;

		///\
		Reinvokes the current `template` (uniquely determined by the `bond::tag`s). \
 		
		template <class ...As> using form_t = typename form_<void, As...>::type;
		
		///\returns a specialized instance of the underlying template using the argument types `Xs...`. \

		XTAL_FX0_(alias) (template <class ...Xs>
		XTAL_DEF_(return,inline,set)
		form(Xs &&...xs),
			form_t<Xs...>{XTAL_REF_(xs)...})

		///\returns a specialized instance of `this` using the underlying template. \

		XTAL_FX2_(alias) (template <class ...Xs>
		XTAL_DEF_(return,inline,let)
		reform(),
			form_t<Xs...>(S_::self()))

	public:
		using S_::self;

		///\returns the first `count` elements of `this` as a truncated view of `U`. \
		
		///\todo\
		Allow truncation/projection of heterogeneous `block`s.

		XTAL_FX4_(do) (template <scalar_q V=value_type>
		XTAL_DEF_(return,inline,let)
		self(constant_q auto count),
		{
			if constexpr (same_q<_s...>) {
				static_assert(count() <= size());
				return reform<V(&)[count]>();
			}
			else {
				static_assert(count() == size());
				static_assert(same_q<V, value_type>);
				return reform<_std::add_lvalue_reference_t<_s>...>();
			}
		})

	public:
	//	using S_::twin;

		///\see [`bond::any`](../bond/any.hh). \

		XTAL_DEF_(return,inline,let)
		twin() const
		noexcept -> auto
		{
			return reform<_std::remove_cvref_t<_s>...>();
		}

		///\returns the first `count` elements of `this` as a truncated copy of `U`. \
		
		///\todo\
		Allow truncation/copying of heterogeneous `block`s. \

		XTAL_FX4_(do) (template <scalar_q V=value_type>
		XTAL_DEF_(return,inline,let)
		twin(constant_q auto count),
		{
			if constexpr (same_q<_s...>) {
				static_assert(count() <= size());
				return reform<V[count]>();
			}
			else {
				static_assert(count() == size());
				static_assert(same_q<V, value_type>);
				return reform<_std::remove_cvref_t<_s>...>();
			}
		})

	public:// ACCESS
		///\returns the internal/external representation of the given co/ordinate. \

		static auto constexpr   ordinate = _std::identity{};
		static auto constexpr coordinate = _std::identity{};

		XTAL_FX4_(do) (template <size_type I>
		XTAL_DEF_(return,inline,let)
		element(),
		noexcept -> decltype(auto)
		{
			auto &s = S_::template self<archetype>();
			XTAL_IF0
			XTAL_0IF_(return) (*get<I>(s))              // Required for `subrange`!
			XTAL_0IF_(return) ( get<I>(s))
			XTAL_0IF_(return) (element(constant_t<I>{}))// Required for `span`!
		})
		XTAL_FX4_(do) (template <auto I=0>
		XTAL_DEF_(return,inline,let)
		element(auto i),
		noexcept -> decltype(auto)
		requires same_q<_s...>
		{
			if constexpr (I) {i += I;} assert(i < size);
			return self().operator[](i);
		})

		XTAL_FX1_(alias) (template <extent_type I> XTAL_DEF_(return,inline,let) coelement  (   ), self().coordinate(element<I>()))
		XTAL_FX1_(alias) (template <integral_q  I> XTAL_DEF_(return,inline,let) coelement  (I i), self().coordinate(element(i)  ))

		XTAL_FX1_(alias) (template <extent_type I> XTAL_DEF_(return,inline,let) operator() (   ), coelement<I>())
		XTAL_FX1_(alias) (template <integral_q  I> XTAL_DEF_(return,inline,let) operator() (I i), coelement(i)  )

	};
	using type = derive_t<homotype>;

};
template <size_type I> XTAL_DEF_(return,inline,let) get(block_q auto const &&o) noexcept -> decltype(auto) {return XTAL_MOV_(o).template   element<I>();}
template <size_type I> XTAL_DEF_(return,inline,let) get(block_q auto       &&o) noexcept -> decltype(auto) {return XTAL_MOV_(o).template   element<I>();}
template <size_type I> XTAL_DEF_(return,inline,let) get(block_q auto const  &o) noexcept -> decltype(auto) {return XTAL_REF_(o).template   element<I>();}
template <size_type I> XTAL_DEF_(return,inline,let) get(block_q auto        &o) noexcept -> decltype(auto) {return XTAL_REF_(o).template   element<I>();}

template <size_type I> XTAL_DEF_(return,inline,let) got(block_q auto const &&o) noexcept -> decltype(auto) {return XTAL_MOV_(o).template coelement<I>();}
template <size_type I> XTAL_DEF_(return,inline,let) got(block_q auto       &&o) noexcept -> decltype(auto) {return XTAL_MOV_(o).template coelement<I>();}
template <size_type I> XTAL_DEF_(return,inline,let) got(block_q auto const  &o) noexcept -> decltype(auto) {return XTAL_REF_(o).template coelement<I>();}
template <size_type I> XTAL_DEF_(return,inline,let) got(block_q auto        &o) noexcept -> decltype(auto) {return XTAL_REF_(o).template coelement<I>();}


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
