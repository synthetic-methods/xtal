#pragma once
#include "./any.hh"






XTAL_ENV_(push)
namespace xtal::atom
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
/*!
\brief
Defines member-`type` as an extensible analogue of `std::array`.

When supplied with an array-signature, e.g. `U_data[N_data]` or `U_data(&)[N_data]`,
the associated `value_type` and `size` are used to configure the underlying container.
The presence of a reference determines whether `std::array` or `std::span` is used in this instance.

Supports homogeneous/heterogeneous definition depending on the commonality of components `Us...`.
Supports expression-templates by way of `operator() (unsigned)`.
*/
template <class ...Us>	struct  block;
template <class ...Us>	using   block_t = typename block<Us...>::type;

template <class ...Ts>	concept block_q               = bond::tag_in_p<block_t, Ts...>;
template <class ...Ts>	concept block_revalued_q   = (...and different_q<decltype(Ts::revalue_f), _std::identity>);
#ifndef XTAL_DOC
template <class U, auto  N, auto ...Ns> struct   block<U   [N][Ns]...> : block<block_t<U[Ns]...>   [N]> {};
template <class U, auto  N, auto ...Ns> struct   block<U(&)[N][Ns]...> : block<block_t<U[Ns]...>(&)[N]> {};
#endif

namespace _detail
{///////////////////////////////////////////////////////////////////////////////

template <class ...Us> struct   superblock;
template <class ...Us> using    superblock_t = typename superblock<Us...>::type;

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
		using        archetype = endotype;
		using        size_type = _std::size_t;
		using  difference_type = _std::make_signed_t<size_type>;

		using       index_type = difference_type;
		using       value_type = common_t<objective_t<Us>...>;
		using       scale_type = unstruct_t<value_type>;

	//	using       bytes_size = cardinal_constant_t<sizeof(archetype)>;
		using       tuple_size = cardinal_constant_t<sizeof...(Us)>;
	//	static      bytes_size   constexpr size_bytes{};
		static      tuple_size   constexpr size      {};
		template <size_type I>
		using       tuple_element = _std::tuple_element<I, archetype>;

	public:// CONSTRUCT
		using S_::S_;

		XTAL_DEF_(return,inline,get) front_f(auto &&o) noexcept {return get<       0>(qualify_f<T>(XTAL_REF_(o)));}
		XTAL_DEF_(return,inline,get)  back_f(auto &&o) noexcept {return get<size - 1>(qualify_f<T>(XTAL_REF_(o)));}

		XTAL_FN1_(go) (XTAL_DEF_(return,inline,get)   front,   front_f)
		XTAL_FN1_(go) (XTAL_DEF_(return,inline,get)    back,    back_f)

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
		using        archetype = endotype;
		using        size_type = decltype(N);
		using  difference_type = _std::make_signed_t<size_type>;

		using       index_type = difference_type;
		using       value_type = U;
		using       scale_type = unstruct_t<value_type>;
		
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
		using        archetype = endotype;
		using        size_type = typename S_::      size_type;
		using  difference_type = typename S_::difference_type;

		using       index_type = difference_type;
		using       value_type = U;
		using       scale_type = unstruct_t<value_type>;

		using       bytes_size = cardinal_constant_t<sizeof(archetype)>;
		using       tuple_size = cardinal_constant_t<N>;
		static      bytes_size   constexpr size_bytes{};
		static      tuple_size   constexpr size      {};
		template <size_type I>
		struct      tuple_element {using type = U;};

		static_assert(_std::same_as<U, typename S_::value_type>);

	public:// CONSTRUCT
	//	using S_::S_;
		XTAL_NEW_(delete) (homotype, noexcept=default)
	//	XTAL_NEW_(create) (homotype, noexcept=default)
		XTAL_NEW_(move)   (homotype, noexcept=default)
		XTAL_NEW_(copy)   (homotype, noexcept=default)
		XTAL_NEW_(then)   (homotype, noexcept:homotype)
	//	XTAL_NEW_(else)   (homotype, noexcept:S_)


		XTAL_NEW_(explicit)
		homotype(variable<size_type> const n)
		noexcept
		{
			if (n < size or _std::is_constant_evaluated()) {
				S_::fill(value_type{});
			}
		}
		/*!
		\note   	Defining `{}` allows `constexpr` evaluation,
		but invalidates `std::trivially_default_constructible`.
		*/
		XTAL_NEW_(implicit)
		homotype()
		noexcept
		:	homotype(variable{size_type{}})
		{
		}
		XTAL_NEW_(explicit)
		homotype(iterable_q auto &&xs)
		noexcept
		requires epimorphic_q<homotype, decltype(xs)>
		:	homotype(variable{count_f(xs)})
		{
			auto const n = bond::fit<size_type>::minimum_f(size(), count_f(xs));
			_detail::copy_to<T::devalue_f>(S_::begin(), point_f(XTAL_REF_(xs)), n);
		}
		XTAL_NEW_(implicit)
		homotype(_std::initializer_list<value_type> xs)
		noexcept
		:	homotype(variable{count_f(xs)})
		{
			auto const n = bond::fit<size_type>::minimum_f(size(), count_f(xs));
			_detail::move_to<T::devalue_f>(S_::begin(), point_f(xs), n);
		}

		XTAL_NEW_(explicit)
		homotype(make_q<typename T::devalue_type> auto &&...xs)
		noexcept
		requires requires {archetype{XTAL_REF_(xs)...};}
		:	S_([&]<auto ...I> (bond::seek_t<I...>)
				XTAL_0FN_(to) (static_cast<S_ &&>(archetype{XTAL_REF_(xs)...,
					_std::tuple_element_t<I + sizeof...(xs), archetype>{}...}))
				(bond::seek_s<size - sizeof...(xs)>{})
			)
		{
		}
		XTAL_NEW_(explicit)
		homotype(make_q<typename T::revalue_type> auto &&...xs)
		noexcept
		requires different_q<decltype(T::devalue_f), decltype(T::revalue_f)>
		:	homotype{T::devalue_f(XTAL_REF_(xs))...}
		{
		}

	};
	using type = bond::derive_t<homotype>;

};


}///////////////////////////////////////////////////////////////////////////////

template <scalar_q ...Us> requires same_q<Us...>
struct block<Us ...>
:	block<common_t<Us...>[sizeof...(Us)]>
{
};
/*!
\brief Defines a fixed-width `std::array`- or `std::tuple`-like container.

If `same_q<Us...`, the member-`type` is `std::derived_from<std::tuple<Us...>>`.
Otherwise, the member-`type` derives from `std::span` or `std::array`,
depending respectively on whether the supplied signature is referenced or unreferenced.
*/
template <class ...Us>
struct block
{
	template <class T>
	using endotype = typename _detail::superblock<Us...>::template homotype<T>;

	template <class T>
	using holotype = bond::compose_s<endotype<T>, bond::tag<block_t>>;

	template <class T>
	class homotype : public holotype<T>
	{
		using S_ = holotype<T>;

		template <class _, class ...As> struct form_           {using type = bond::compose_s<T, bond::tagged<As...>>;};
		template <class _             > struct form_<_, Us...> {using type = T;};
		template <class _             > struct form_<_       > {using type = T;};
		
		template <class _, scalar_q ...As> requires same_q<As...>
		struct form_<_, As...> : form_<_, common_t<As...>[sizeof...(As)]> {};

	public:// OPERATE
		using S_::size;

	public:// CONSTRUCT
		using S_::S_;

		using typename S_:: archetype;
		using typename S_::value_type;
		using typename S_::scale_type;
		using typename S_::index_type;

		using devalue_type = value_type;
		using revalue_type = value_type;

		/*!
		\brief  	Reinvokes the current `template` (uniquely determined by the `bond::tag`s).
		*/
		template <class ...Xs> using form_t = typename form_<void, Xs...>::type;
		
		/*!
		\returns	A specialized instance of the underlying template using the argument types `Xs...`.
		*/
		template <class ...Xs>
		XTAL_DEF_(return,inline,set)
		form(Xs &&...xs)
		noexcept -> auto
		{
			return form_t<_xtd::decay_value_reference_t<Xs>...>{XTAL_REF_(xs)...};
		}

		/*!
		\returns	A specialized instance of `this` using the underlying template.
		*/
		XTAL_FN2_(to) (template <class ...Xs>
		XTAL_DEF_(return,inline,let)
		reform(),
			form_t<Xs...>(S_::self()))

	public:
		using S_::self;

		/*!
		\returns	The first `count` elements of `this` as a truncated view of `U`.
		*/
		XTAL_FN2_(do) (template <scalar_q V=value_type>
		XTAL_DEF_(return,inline,let)
		self(constant_q auto count),
		{
			auto constexpr N = count();
			auto constexpr M = N < 0? size + N: N;
			static_assert(M <= size());
			XTAL_IF0
			XTAL_0IF (M == size()) {
				return self();
			}
			XTAL_0IF (same_q<Us...>) {
				return reform<V(&)[M]>();
			}
			else {
				static_assert(same_q<V, value_type>);// Default...
				return [&]<auto ...I> (bond::seek_t<I...>)
					XTAL_0FN_(to) (reform(get<I>(self())...))
				(bond::seek_s<M>{});
			}
		})

	public:
	//	using S_::twin;

		/*!
		\returns	A copy of `this`.
		*/
		XTAL_DEF_(return,inline,let)
		twin() const
		noexcept -> auto
		{
			return reform<_std::remove_cvref_t<Us>...>();
		}

		/*!
		\returns	A copy of `this` truncated to the first `count` elements.
		*/
		template <scalar_q V=value_type>
		XTAL_DEF_(return,inline,let)
		twin(constant_q auto count) const
		noexcept -> auto
		{
			auto constexpr N = count();
			auto constexpr M = N < 0? size + N: N;
			static_assert(M <= size());
			XTAL_IF0
			XTAL_0IF (M == size()) {
				return twin();
			}
			XTAL_0IF (same_q<Us...>) {
				return reform<V[M]>();
			}
			else {
				static_assert(same_q<V, value_type>);// Default...
				return [&]<auto ...I> (bond::seek_t<I...>)
					XTAL_0FN_(to) (reform(got<I>(self())...))
				(bond::seek_s<M>{});
			}
		}

	public:// ACCESS
		/*!
		\returns	The internal/external representation of the given co/devalue_f.
		*/
		static auto constexpr devalue_f = _std::identity{};
		static auto constexpr revalue_f = _std::identity{};

		template <index_type N_ind=0>
		XTAL_DEF_(return,inline,set)
		element_f(auto &&o)
		noexcept -> decltype(auto)
		{
			XTAL_IF0
			XTAL_0IF_(to) (*get<N_ind>(qualify_f<archetype>(XTAL_REF_(o))))// Required for `subrange`!
			XTAL_0IF_(to) ( get<N_ind>(qualify_f<archetype>(XTAL_REF_(o))))
			XTAL_0IF_(to) (element_f(XTAL_REF_(o), constant_t<N_ind>{}))// Required for `span`!
		}
		template <index_type N_ind=0>
		XTAL_DEF_(return,inline,set)
		element_f(auto &&o, auto const n_ind)
		noexcept -> decltype(auto)
		requires same_q<Us...>
		{
			auto const i = N_ind + n_ind;
			assert(0 <= i and i < size);
			return qualify_f<T>(XTAL_REF_(o)).operator[](i);
		}

		template <index_type I=0>
		XTAL_DEF_(return,inline,set)
		coelement_f(auto &&o)
		noexcept -> decltype(auto)
		{
			return T::revalue_f(element_f<I>(XTAL_REF_(o)));
		}
		XTAL_DEF_(return,inline,set)
		coelement_f(auto &&o, integral_q auto i)
		noexcept -> decltype(auto)
		{
			return T::revalue_f(element_f   (XTAL_REF_(o), i));
		}

		XTAL_FN1_(go) (template <auto ...Ns> XTAL_DEF_(return,inline,get)   element,   element_f<Ns...>)
		XTAL_FN1_(go) (template <auto ...Ns> XTAL_DEF_(return,inline,get) coelement, coelement_f<Ns...>)

		XTAL_FN2_(to) (template <index_type I  > XTAL_DEF_(return,inline,let) operator() (   ), coelement<I>())
		XTAL_FN2_(to) (template <integral_q I  > XTAL_DEF_(return,inline,let) operator() (I i), coelement(i)  )

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
#ifndef XTAL_DOC
namespace std
{///////////////////////////////////////////////////////////////////////////////

template <xtal::atom::block_q T>
struct tuple_size<T> : T::tuple_size {};

template <size_t N, xtal::atom::block_q T>
struct tuple_element<N, T> : T::template tuple_element<N> {};


}/////////////////////////////////////////////////////////////////////////////
#endif
/***/
XTAL_ENV_(pop)
