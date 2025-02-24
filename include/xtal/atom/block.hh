#pragma once
#include "./any.hh"






XTAL_ENV_(push)
namespace xtal::atom
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
///\
Defines a statically-bounded `type` that supports homogeneous/heterogeneous construction, \
as well as expression-templates. \

template <class ...As>	struct  block;
template <class ...As>	using   block_t = typename block<As...>::type;
template <class ...As>	concept block_q = bond::     tag_p<block_t, As...>;

template <class U, auto  N, auto ...Ns> struct   block<U   [N][Ns]...> : block<block_t<U[Ns]...>   [N]> {};
template <class U, auto  N, auto ...Ns> struct   block<U(&)[N][Ns]...> : block<block_t<U[Ns]...>(&)[N]> {};


namespace _detail
{///////////////////////////////////////////////////////////////////////////////

template <class ...As> struct   superblock;
template <class ...As> using    superblock_t = typename superblock<As...>::type;

template <class U, auto N, auto ...Ns> struct superblock<U   [N][Ns]...> : superblock<superblock_t<U[Ns]...>   [N]> {};
template <class U, auto N, auto ...Ns> struct superblock<U(&)[N][Ns]...> : superblock<superblock_t<U[Ns]...>(&)[N]> {};

template <scalar_q ...Us> requires different_q<Us...>
struct superblock<Us...>
{
	using endotype = bond::pack_t<_xtd::decay_trivial_value_reference_t<Us>...>;
	
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
		using       scale_type = unstruct_u<value_type>;

	//	using       bytes_size = cardinal_constant_t<sizeof(archetype)>;
		using       tuple_size = cardinal_constant_t<sizeof...(Us)>;
	//	static      bytes_size   constexpr size_bytes{};
		static      tuple_size   constexpr size      {};
		template <size_type I>
		using       tuple_element = _std::tuple_element<I, archetype>;

	public:// CONSTRUCT
		using S_::S_;

		XTAL_FX4_(to) (template <class ...Xs> XTAL_DEF_(return,inline,let) front(), get<       0>(S_::self()))
		XTAL_FX4_(to) (template <class ...Xs> XTAL_DEF_(return,inline,let) back (), get<size - 1>(S_::self()))

	};
	using type = bond::derive_t<homotype>;

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
		using       scale_type =  unstruct_u<value_type>;
		
	//	using       bytes_size = cardinal_constant_t<sizeof(archetype)>;
		using       tuple_size = cardinal_constant_t<N>;
	//	static      bytes_size   constexpr size_bytes{};
		static      tuple_size   constexpr size      {};
		template <size_type I>
		struct      tuple_element {using type = U;};

		static_assert(_std::same_as<U, typename S_::value_type>);

	public:// CONSTRUCT
		using S_::S_;

	};
	using type = bond::derive_t<homotype>;

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
		using       scale_type =  unstruct_u<value_type>;

		using       bytes_size = cardinal_constant_t<sizeof(archetype)>;
		using       tuple_size = cardinal_constant_t<N>;
		static      bytes_size   constexpr size_bytes{};
		static      tuple_size   constexpr size      {};
		template <size_type I>
		struct      tuple_element {using type = U;};

		static_assert(_std::same_as<U, typename S_::value_type>);

	public:// CONSTRUCT
	//	using S_::S_;

		XTAL_NEW_(delete) (homotype, noexcept = default)
	//	XTAL_NEW_(create) (homotype, noexcept = default)
		XTAL_NEW_(move)   (homotype, noexcept = default)
		XTAL_NEW_(copy)   (homotype, noexcept = default)
		XTAL_NEW_(cast)   (homotype, noexcept)

		///\note\
		Defining `{}` allows `constexpr` evaluation, \
		but invalidates `std::trivially_default_constructible`. \
		
		XTAL_NEW_(implicit)
		homotype()
		noexcept
		:	homotype(size_type{})
		{}
		XTAL_NEW_(explicit)
		homotype(same_q<size_type> auto const n)
		noexcept
		{
			assert(n <= size);
			if (_std::is_constant_evaluated() or n < size) {
				S_::fill(value_type{});
			}
		}
		XTAL_NEW_(implicit)
		homotype(_std::initializer_list<value_type> xs)
		noexcept
		:	homotype(count_f(xs))
		{
			_detail::move_to<T::ordinate>(S_::begin(), point_f(xs), count_f(xs));
		}
		XTAL_NEW_(explicit)
		homotype(iterable_q auto &&xs)
		noexcept
		requires epimorphic_q<homotype, decltype(xs)>
		:	homotype(count_f(xs))
		{
			_detail::copy_to<T::ordinate>(S_::begin(), XTAL_REF_(xs));
		}

	};
	using type = bond::derive_t<homotype>;

};


}///////////////////////////////////////////////////////////////////////////////

template <scalar_q ...As> requires same_q<As...>
struct block<As ...>
:	block<common_t<As...>[sizeof...(As)]>
{
};
template <class ...As>
struct block
{
	template <class T>
	using endotype = typename _detail::superblock<As...>::template homotype<T>;

	template <class T>
	using holotype = bond::compose_s<endotype<T>, bond::tag<block_t>>;

	template <class T>
	class homotype : public holotype<T>
	{
		using S_ = holotype<T>;

		template <class _, class ..._As> struct form_           {using type = bond::compose_s<T, bond::hypertag<_As...>>;};
		template <class _              > struct form_<_       > {using type = T;};
		template <class _              > struct form_<_, As...> {using type = T;};

	public:// OPERATE
		using S_::size;

	public:// CONSTRUCT
		using S_::S_;

		using typename S_:: archetype;
		using typename S_::value_type;
		using typename S_::scale_type;

		///\
		Reinvokes the current `template` (uniquely determined by the `bond::tag`s). \
 		
		template <class ..._As> using form_t = typename form_<void, _As...>::type;
		
		///\returns a specialized instance of the underlying template using the argument types `Xs...`. \

		XTAL_FX0_(to) (template <class ...Xs>
		XTAL_DEF_(return,inline,set)
		form(Xs &&...xs),
			form_t<Xs...>{XTAL_REF_(xs)...})

		///\returns a specialized instance of `this` using the underlying template. \

		XTAL_FX2_(to) (template <class ...Xs>
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
			auto constexpr N = count();
			if constexpr (same_q<As...>) {
				static_assert(N <= size());
				return reform<V(&)[N]>();
			}
			else {
				static_assert(N == size());
				static_assert(same_q<V, value_type>);
				return reform<_std::add_lvalue_reference_t<As>...>();
			}
		})

	public:
	//	using S_::twin;

		///\see [`bond::any`](../bond/any.hh). \

		XTAL_DEF_(return,inline,let)
		twin() const
		noexcept -> auto
		{
			return reform<_std::remove_cvref_t<As>...>();
		}

		///\returns the first `count` elements of `this` as a truncated copy of `U`. \
		
		///\todo\
		Allow truncation/copying of heterogeneous `block`s. \

		XTAL_FX4_(do) (template <scalar_q V=value_type>
		XTAL_DEF_(return,inline,let)
		twin(constant_q auto count),
		{
			if constexpr (same_q<As...>) {
				static_assert(count() <= size());
				return reform<V[count]>();
			}
			else {
				static_assert(count() == size());
				static_assert(same_q<V, value_type>);
				return reform<_std::remove_cvref_t<As>...>();
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
			XTAL_0IF_(to) (*get<I>(s))              // Required for `subrange`!
			XTAL_0IF_(to) ( get<I>(s))
			XTAL_0IF_(to) (element(constant_t<I>{}))// Required for `span`!
		})
		XTAL_FX4_(do) (template <auto I=0>
		XTAL_DEF_(return,inline,let)
		element(auto i),
		noexcept -> decltype(auto)
		requires same_q<As...>
		{
			if constexpr (I) {i += I;} assert(i < size);
			return self().operator[](i);
		})

		XTAL_FX1_(to) (template <extent_type I> XTAL_DEF_(return,inline,let) coelement  (   ), self().coordinate(element<I>()))
		XTAL_FX1_(to) (template <integral_q  I> XTAL_DEF_(return,inline,let) coelement  (I i), self().coordinate(element(i)  ))

		XTAL_FX1_(to) (template <extent_type I> XTAL_DEF_(return,inline,let) operator() (   ), coelement<I>())
		XTAL_FX1_(to) (template <integral_q  I> XTAL_DEF_(return,inline,let) operator() (I i), coelement(i)  )

	};
	using type = bond::derive_t<homotype>;

};
template <size_type I> XTAL_DEF_(inline,let) get(block_q auto const &&o) noexcept -> decltype(auto) {return XTAL_MOV_(o).template   element<I>();}
template <size_type I> XTAL_DEF_(inline,let) get(block_q auto       &&o) noexcept -> decltype(auto) {return XTAL_MOV_(o).template   element<I>();}
template <size_type I> XTAL_DEF_(inline,let) get(block_q auto const  &o) noexcept -> decltype(auto) {return XTAL_REF_(o).template   element<I>();}
template <size_type I> XTAL_DEF_(inline,let) get(block_q auto        &o) noexcept -> decltype(auto) {return XTAL_REF_(o).template   element<I>();}

template <size_type I> XTAL_DEF_(inline,let) got(block_q auto const &&o) noexcept -> decltype(auto) {return XTAL_MOV_(o).template coelement<I>();}
template <size_type I> XTAL_DEF_(inline,let) got(block_q auto       &&o) noexcept -> decltype(auto) {return XTAL_MOV_(o).template coelement<I>();}
template <size_type I> XTAL_DEF_(inline,let) got(block_q auto const  &o) noexcept -> decltype(auto) {return XTAL_REF_(o).template coelement<I>();}
template <size_type I> XTAL_DEF_(inline,let) got(block_q auto        &o) noexcept -> decltype(auto) {return XTAL_REF_(o).template coelement<I>();}


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
