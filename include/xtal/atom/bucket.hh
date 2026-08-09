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
template <class ...Us>	struct  bucket;
template <class ...Us>	using   bucket_t = typename bucket<Us...>::type;

template <class ...Ts>	concept bucket_q               = bond::tag_inner_p<bucket_t, Ts...>;
template <class ...Ts>	concept bucket_revalued_q   = (...and different_q<decltype(Ts::revalue_f), std::identity>);
#ifndef XTAL_DOC
template <class U, auto  N, auto ...Ns> struct   bucket<U   [N][Ns]...> : bucket<bucket_t<U[Ns]...>   [N]> {};
template <class U, auto  N, auto ...Ns> struct   bucket<U(&)[N][Ns]...> : bucket<bucket_t<U[Ns]...>(&)[N]> {};
#endif

namespace _detail
{///////////////////////////////////////////////////////////////////////////////

template <class ...Us> struct   superbucket;
template <class ...Us> using    superbucket_t = typename superbucket<Us...>::type;

template <class U, auto N, auto ...Ns> struct superbucket<U   [N][Ns]...> : superbucket<superbucket_t<U[Ns]...>   [N]> {};
template <class U, auto N, auto ...Ns> struct superbucket<U(&)[N][Ns]...> : superbucket<superbucket_t<U[Ns]...>(&)[N]> {};

template <scalar_array_q ...Us> requires different_q<Us...>
struct superbucket<Us...>
{
	using endotype = bond::pack_t<xtd::decay_trivial_xvalue_t<Us>...>;
	
	template <class T>
	using holotype = bond::compose_s<endotype, bond::define<T>>;

	template <class T>
	class homotype: public holotype<T>
	{
		using S_ = holotype<T>;

	public:// ACCESS
		using        archetype = endotype;
		using        size_type = std::size_t;
		using  difference_type = std::make_signed_t<size_type>;

		using       index_type = std::remove_cvref_t<difference_type>;
		using       value_type = common_t<objective_t<Us>...>;
		using       scale_type = unstruct_t<value_type>;

	//	using       bytes_size = cardinal_constant_t<sizeof(archetype)>;
		using       tuple_size = cardinal_constant_t<sizeof...(Us)>;
	//	static      bytes_size   constexpr size_bytes{};
		static      tuple_size   constexpr size      {};
		template <size_type I>
		using       tuple_element = std::tuple_element<I, archetype>;

	public:// OPERATE
		XTAL_FN0_(go) (XTAL_VAL_(return,inline,let)
		objectify, [] (auto &&o) XTAL_0FN -> decltype(auto) {
			if constexpr ((...or xtd::mutable_reference<Us>)) {
				return qualify_f<T>(XTAL_REF_(o)).twin();
			}
			else {
				return qualify_f<T>(XTAL_REF_(o)).self();
			}
		})

	public:// CONSTRUCT
		using S_::S_;

		XTAL_VAL_(return,inline,get) front_f(auto &&o) noexcept {return get<       0>(qualify_f<T>(XTAL_REF_(o)));}
		XTAL_VAL_(return,inline,get)  back_f(auto &&o) noexcept {return get<size - 1>(qualify_f<T>(XTAL_REF_(o)));}

		XTAL_FN1_(go) (XTAL_VAL_(return,inline,get)   front,   front_f)
		XTAL_FN1_(go) (XTAL_VAL_(return,inline,get)    back,    back_f)

	};
	using type = bond::derive_t<homotype>;

};
template <vector_array_q A> requires in_v<xtd::reference<A>>
struct superbucket<A>
{
	XTAL_TYP_(set) U = xtd::dereference_t<xtd::remove_extent_t<A>>;
	XTAL_VAL_(set) N = xtd::extent_v<A>;
	//\
	using endotype = reiterated_t<std::array<U, N>>;//NOTE: Doesn't truncate properly?
	using endotype = std::span<U, N>;
	
	template <class T>
	using holotype = bond::compose_s<endotype, bond::define<T>>;

	template <class T>
	class homotype: public holotype<T>
	{
		using S_ = holotype<T>;

	public:// ACCESS
		using        archetype = endotype;
		using        size_type = decltype(N);
		using  difference_type = std::make_signed_t<size_type>;

		using       index_type = std::remove_cvref_t<difference_type>;
		using       value_type = U;
		using       scale_type = unstruct_t<value_type>;
		
	//	using       bytes_size = cardinal_constant_t<sizeof(archetype)>;
		using       tuple_size = cardinal_constant_t<N>;
	//	static      bytes_size   constexpr size_bytes{};
		static      tuple_size   constexpr size      {};
		template <size_type I>
		struct      tuple_element {using type = U;};

		static_assert(std::same_as<U, typename S_::value_type>);

	public:// OPERATE
		XTAL_FN0_(go) (XTAL_VAL_(return,inline,let)
		objectify, [] (auto &&o) XTAL_0FN_(to) (qualify_f<T>(XTAL_REF_(o)).twin()))

	public:// CONSTRUCT
		using S_::S_;

	};
	using type = bond::derive_t<homotype>;

};
template <vector_array_q A> requires un_v<xtd::reference<A>>
struct superbucket<A>
{
	XTAL_TYP_(set) U = xtd::dereference_t<xtd::remove_extent_t<A>>;
	XTAL_VAL_(set) N = xtd::extent_v<A>;
	using endotype = std::array<U, N>;
	
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

		using       index_type = std::remove_cvref_t<difference_type>;
		using       value_type = U;
		using       scale_type = unstruct_t<value_type>;

		using       bytes_size = cardinal_constant_t<sizeof(archetype)>;
		using       tuple_size = cardinal_constant_t<N>;
		static      bytes_size   constexpr size_bytes{};
		static      tuple_size   constexpr size      {};
		template <size_type I>
		struct      tuple_element {using type = U;};

		static_assert(std::same_as<U, typename S_::value_type>);

	public:// OPERATE
		XTAL_FN0_(go) (XTAL_VAL_(return,inline,let)
		objectify, [] (auto &&o) XTAL_0FN_(to) (qualify_f<T>(XTAL_REF_(o))))

	public:// CONSTRUCT
	//	using S_::S_;
		XTAL_VAL_(delete) (homotype, noexcept=default)
	//	XTAL_VAL_(create) (homotype, noexcept=default)
		XTAL_VAL_(move)   (homotype, noexcept=default)
		XTAL_VAL_(copy)   (homotype, noexcept=default)
		XTAL_VAL_(induce) (homotype, noexcept:homotype)
	//	XTAL_VAL_(reduce) (homotype, noexcept:S_)

		XTAL_VAL_(new,explicit)
		homotype(variable<size_type> const n)
		noexcept
		{
			if constexpr (un_v<0, size>) {
				if (n < size or std::is_constant_evaluated()) {
					S_::fill(value_type{});
				}
			}
		}
		/*!
		\note   	Defining `{}` allows `constexpr` evaluation,
		but invalidates `std::trivially_default_constructible`.
		*/
		XTAL_VAL_(new,implicit)
		homotype()
		noexcept
		:	homotype(variable{size_type{}})
		{
		}
		XTAL_VAL_(new,explicit)
		homotype(iterable_q auto &&xs)
		noexcept
		requires epimorphic_q<homotype, decltype(xs)>
		:	homotype(variable{count_f(xs)})
		{
			auto const n = bond::fit<size_type>::minimum_f(size(), count_f(xs));
			_detail::copy_to<T::devalue_f>(S_::begin(), point_f(XTAL_REF_(xs)), n);
		}
		XTAL_VAL_(new,implicit)
		homotype(std::initializer_list<value_type> xs)
		noexcept
		:	homotype(variable{count_f(xs)})
		{
			auto const n = bond::fit<size_type>::minimum_f(size(), count_f(xs));
			_detail::move_to<T::devalue_f>(S_::begin(), point_f(xs), n);
		}

		XTAL_VAL_(new,explicit)
		homotype(make_q<typename T::devalue_type> auto &&...xs)
		noexcept
		requires requires {archetype{XTAL_REF_(xs)...};}
		:	S_([&]<auto ...I> (bond::seek_in_t<I...>)
				XTAL_0FN_(to) (static_cast<S_ &&>(archetype{XTAL_REF_(xs)...,
					std::tuple_element_t<I + sizeof...(xs), archetype>{}...}))
				(bond::seek_to_t<size - sizeof...(xs)>{})
			)
		{
		}
		XTAL_VAL_(new,explicit)
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

template <scalar_array_q ...Us> requires same_q<Us...>
struct bucket<Us ...>
:	bucket<common_t<Us...>[sizeof...(Us)]>
{
};
/*!
\brief Defines a fixed-width `std::array`- or `std::tuple`-like container.

If `same_q<Us...`, the member-`type` is `std::derived_from<std::tuple<Us...>>`.
Otherwise, the member-`type` derives from `std::span` or `std::array`,
depending respectively on whether the supplied signature is referenced or unreferenced.
*/
template <class ...Us>
struct bucket
{
	template <class T>
	using endotype = typename _detail::superbucket<Us...>::template homotype<T>;

	template <class T>
	using holotype = bond::compose_s<endotype<T>, bond::tag<bucket_t>>;

	template <class T>
	class homotype : public holotype<T>
	{
		using S_ = holotype<T>;

		template <class _, class ...As> struct form_           {using type = bond::compose_s<T, bond::tagged<As...>>;};
		template <class _             > struct form_<_, Us...> {using type = T;};
		template <class _             > struct form_<_       > {using type = T;};
		
		template <class _, scalar_array_q ...As> requires same_q<As...>
		struct form_<_, As...> : form_<_, common_t<As...>[sizeof...(As)]> {};

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
		XTAL_VAL_(return,inline,set)
		form(Xs &&...xs)
		noexcept -> auto
		{
			return form_t<xtd::decay_xvalue_t<Xs>...>{XTAL_REF_(xs)...};
		}

		/*!
		\returns	A specialized instance of `this` using the underlying template.
		*/
		XTAL_FN2_(to) (template <class ...Xs>
		XTAL_VAL_(return,inline,let)
		reform(),
			form_t<Xs...>(S_::self()))

	public:// OPERATE
		using S_::self;
		using S_::size;
		static cardinal_constant_t<std::rank_v<common_t<Us...>>> constexpr rank{};

		XTAL_VAL_(set) mask = size_constant_t<size - 1>{};

		/*!
		\returns	The first `resize` elements of `this` as a truncated view of `U`.
		*/
		XTAL_FN2_(do) (template <scalar_array_q U_val=value_type>
		XTAL_VAL_(return,inline,let)
		self(cardinal_constant_q auto resize),
		{
			bool constexpr K_default = same_q<U_val, value_type>;
			bool constexpr K_uniform = same_q<Us...>;
			XTAL_IF0
			XTAL_0IF (K_default and resize == size()) {
				return self();
			}
			XTAL_0IF (K_uniform and resize <= size()) {
				return reform<U_val(&)[resize]>();
			}
			XTAL_0IF_(else) {
				static_assert(K_default);
				return [&]<auto ...I> (bond::seek_in_t<I...>)
					XTAL_0FN_(to) (reform(get<I>(self())...))
				(bond::seek_to_t<resize>{});
			}
			static_assert(resize <= size());
		})
		XTAL_FN2_(do) (template <scalar_array_q U_val=value_type>
		XTAL_VAL_(return,inline,let)
		self( ordinal_constant_q auto desize),
		{
			return self<U_val>(cardinal_constant_t<desize + size()>{});
		})

	public:
	//	using S_::twin;

		/*!
		\returns	A copy of `this`.
		*/
		XTAL_VAL_(return,inline,let)
		twin() const
		noexcept -> auto
		{
			return reform<std::remove_cvref_t<Us>...>();
		}
		/*!
		\returns	A copy of `this` truncated to the first `resize` elements.
		*/
		template <scalar_array_q U_val=value_type>
		XTAL_VAL_(return,inline,let)
		twin(cardinal_constant_q auto resize) const
		noexcept -> auto
		{
			bool constexpr K_default = same_q<U_val, value_type>;
			bool constexpr K_uniform = same_q<Us...>;
			XTAL_IF0
			XTAL_0IF (K_default and resize == size()) {
				return twin();
			}
			XTAL_0IF (K_uniform and resize == size()) {
				return reform<U_val  [resize]>();
			}
			XTAL_0IF_(else) {
			//	static_assert(K_default);// Not necessary?
				return [&]<auto ...I> (bond::seek_in_t<I...>)
					XTAL_0FN_(to) (form(got<I>(self())...))
				(bond::seek_to_t<resize>{});
			}
		}
		template <scalar_array_q U_val=value_type>
		XTAL_VAL_(return,inline,let)
		twin( ordinal_constant_q auto desize) const
		noexcept -> auto
		{
			return twin<U_val>(cardinal_constant_t<desize + size()>{});
		}

	public:// ACCESS
		static auto constexpr devalue_f = std::identity{};///<\returns The internal value.
		static auto constexpr revalue_f = std::identity{};///<\returns The external value.
		static auto constexpr deindex_f = std::identity{};///<\returns The internal index.
		static auto constexpr reindex_f = std::identity{};///<\returns The external index.

		template <index_type N_ind>
		XTAL_VAL_(return,inline,set)
		elementary_f(auto &&o)
		noexcept -> decltype(auto)
		requires requires {std::get<N_ind>(XTAL_ANY_(archetype));}
		{
			XTAL_IF0
			XTAL_0IF (reiterated_q<archetype>) {return *get<N_ind>(elementary_f(XTAL_REF_(o)));}
			XTAL_0IF_(else)                    {return  get<N_ind>(elementary_f(XTAL_REF_(o)));}
		}
		XTAL_VAL_(return,inline,set)
		elementary_f(auto &&o)
		noexcept -> decltype(auto)
		{
			return qualify_f<archetype>(XTAL_REF_(o));
		}

		template <index_type N_ind=0>
		XTAL_VAL_(return,inline,set)
		element_f(auto &&o)
		noexcept -> decltype(auto)
		{
			auto constexpr K_ind = T::deindex_f(N_ind);
			XTAL_IF0
			XTAL_0IF (K_ind < zero and zero < size()) {return XTAL_ALL_(get<zero>(o)){};} // Negative underflow!
			XTAL_0IF (mask < K_ind and zero < size()) {return XTAL_ALL_(get<mask>(o)){};} // Positive  overflow!
			XTAL_0IF_(to) (elementary_f<K_ind>(XTAL_REF_(o)))
			XTAL_0IF_(to) (elementary_f       (XTAL_REF_(o)).operator[](K_ind))           // Required for `span`!
		}
		template <index_type N_ind=0>
		XTAL_VAL_(return,inline,set)
		element_f(auto &&o, constant_q auto i)
		noexcept -> decltype(auto)
		{
			return element_f<XTAL_ALL_(i){}>(XTAL_REF_(o));
		}
		template <index_type N_ind=0>
		XTAL_VAL_(return,inline,set)
		element_f(auto &&o, index_type i)
		noexcept -> decltype(auto)
		{
			static_assert(same_q<Us...>);
			auto const K_ind = T::deindex_f(N_ind + i);
			return qualify_f<archetype>(XTAL_REF_(o)).operator[](K_ind);
		}

		template <index_type N_ind=0>
		XTAL_VAL_(return,inline,set)
		coelement_f(auto &&o, auto &&...oo)
		noexcept -> auto
		{
			return T::revalue_f(T::template element_f<N_ind>(XTAL_REF_(o), XTAL_REF_(oo)...));
		}

		XTAL_FN1_(go) (template <auto ...Ns> XTAL_VAL_(return,inline,get)    element, T::template   element_f<Ns...>)
		XTAL_FN1_(go) (template <auto ...Ns> XTAL_VAL_(return,inline,let)  coelement, T::template coelement_f<Ns...>)
		XTAL_FN1_(go) (template <auto ...Ns> XTAL_VAL_(return,inline,get) operator[], T::template   element_f<Ns...>)
		XTAL_FN1_(go) (template <auto ...Ns> XTAL_VAL_(return,inline,let) operator(), T::template coelement_f<Ns...>)
	//	XTAL_FN2_(to) (template <index_type N_ind > XTAL_VAL_(return,inline,let) operator() (       ), coelement<N_ind>())
	//	XTAL_FN2_(to) (template <integral_q N_ind > XTAL_VAL_(return,inline,let) operator() (N_ind i), coelement(i))

	};
	using type = bond::derive_t<homotype>;

};
template <size_type N_ind> XTAL_VAL_(inline,let) get(bucket_q auto const &&o) noexcept -> decltype(auto) {return XTAL_MOV_(o).template   element<N_ind>();}
template <size_type N_ind> XTAL_VAL_(inline,let) get(bucket_q auto       &&o) noexcept -> decltype(auto) {return XTAL_MOV_(o).template   element<N_ind>();}
template <size_type N_ind> XTAL_VAL_(inline,let) get(bucket_q auto const  &o) noexcept -> decltype(auto) {return XTAL_REF_(o).template   element<N_ind>();}
template <size_type N_ind> XTAL_VAL_(inline,let) get(bucket_q auto        &o) noexcept -> decltype(auto) {return XTAL_REF_(o).template   element<N_ind>();}

template <size_type N_ind> XTAL_VAL_(inline,let) got(bucket_q auto const &&o) noexcept -> decltype(auto) {return XTAL_MOV_(o).template coelement<N_ind>();}
template <size_type N_ind> XTAL_VAL_(inline,let) got(bucket_q auto       &&o) noexcept -> decltype(auto) {return XTAL_MOV_(o).template coelement<N_ind>();}
template <size_type N_ind> XTAL_VAL_(inline,let) got(bucket_q auto const  &o) noexcept -> decltype(auto) {return XTAL_REF_(o).template coelement<N_ind>();}
template <size_type N_ind> XTAL_VAL_(inline,let) got(bucket_q auto        &o) noexcept -> decltype(auto) {return XTAL_REF_(o).template coelement<N_ind>();}


////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
/**/
#ifndef XTAL_DOC
namespace std
{///////////////////////////////////////////////////////////////////////////////

template <xtal::atom::bucket_q T>
struct tuple_size<T> : T::tuple_size {};

template <size_t N, xtal::atom::bucket_q T>
struct tuple_element<N, T> : T::template tuple_element<N> {};


}/////////////////////////////////////////////////////////////////////////////
#endif
/***/
XTAL_ENV_(pop)
