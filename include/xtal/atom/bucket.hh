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

template <scalar_array_q ...Us> requires same_q<Us...>
struct superbucket<Us ...>
:	superbucket<common_t<Us...>[sizeof...(Us)]>
{
};
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

		template <fixed_valued_q<archetype> X_> requires (N <= fixed<X_>::extent())
		XTAL_VAL_(new,explicit)
		homotype(X_ &&x_)
		noexcept
		:	S_(point_f<0>(x_), point_f<N>(x_))
		{
		}

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

	protected:
		template <size_type I>
		using       tuple_element_t = typename tuple_element<I>::type;

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
		homotype(std::variant<size_type> const n)
		noexcept
		{
			if constexpr (un_v<0, size>) {
				if (get<size_type>(n) < size or std::is_constant_evaluated()) {
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
		:	homotype(std::variant<size_type>{size_type{}})
		{
		}
		XTAL_VAL_(new,implicit)
		homotype(std::initializer_list<value_type> xs)
		noexcept
		:	homotype(std::variant<size_type>{count_f(xs)})
		{
			auto const n = bond::fit<size_type>::minimum_f(size(), count_f(xs));
			_detail::copy_to<T::devalue_f>(S_::begin(), point_f(          xs ), n);
		}
		XTAL_VAL_(new,explicit)
		homotype(iterable_q auto &&xs)
		noexcept
		requires infungible_q<homotype, decltype(xs)> and epimorphic_q<homotype, decltype(xs)>
		:	homotype(std::variant<size_type>{count_f(xs)})
		{
			auto const n = bond::fit<size_type>::minimum_f(size(), count_f(xs));
			_detail::copy_to<T::devalue_f>(S_::begin(), point_f(XTAL_REF_(xs)), n);
		}

		XTAL_VAL_(new,explicit)
		homotype(make_q<typename T::devalue_type> auto &&...xs)
		noexcept
		requires in_v<same_q<decltype(T::devalue_f), decltype(T::revalue_f)>>
		and      requires {archetype{XTAL_REF_(xs)...};}
		:	S_([&]<auto ...I> (bond::seek_in_t<I...>)
				XTAL_0FN_(to) (static_cast<S_ &&>(archetype{XTAL_REF_(xs)...,
				    tuple_element_t<I + sizeof...(xs)>{}...}))
				(bond::seek_to_t<size - sizeof...(xs)>{})
			)
		{
		}
		XTAL_VAL_(new,explicit)
		homotype(make_q<typename T::revalue_type> auto &&...xs)
		noexcept
		requires un_v<same_q<decltype(T::devalue_f), decltype(T::revalue_f)>>
		:	homotype(T::devalue_f(XTAL_REF_(xs))...)
		{
		}

	};
	using type = bond::derive_t<homotype>;

};


}///////////////////////////////////////////////////////////////////////////////
/*!
\brief Defines a fixed-width `std::array`- or `std::tuple`-like container.

If `different_q<Us...`, the member-`type` is `std::derived_from<std::tuple<Us...>>`.
Otherwise, the member-`type` derives from `std::span` or `std::array`,
depending respectively on whether the supplied signature is referenced or unreferenced.
*/
template <scalar_array_q ...Us> requires same_q<Us...>
struct bucket<Us ...> : bucket<common_t<Us...>[sizeof...(Us)]>
{};
template <class ...Us>
struct bucket
{
	template <class T>
	using endotype = typename bond::devoid_s<_detail::superbucket, Us...>::template homotype<T>;

	template <class T>
	using holotype = bond::compose_s<endotype<T>, bond::tag<bucket_t>>;

	template <class T>
	class homotype : public holotype<T>
	{
		using S_ = holotype<T>;

		template <class T_, class ...As> struct form_            {using type = bond::compose_s<T_, bond::tagged<As...>>;};
		template <class T_             > struct form_<T_, Us...> {using type = T_;};
		template <class T_             > struct form_<T_       > {using type = T_;};
		
		template <class T_, scalar_array_q ...As> requires same_q<As...>
		struct form_<T_, As...>
		:	    form_<T_, common_t<As...>[sizeof...(As)]>
		{};

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
		template <class ...Xs>
		XTAL_TYP_(set)
		form_t = typename form_<T, Xs...>::type;
		
		/*!
		\returns	A specialized instance of the underlying template using the argument types `Xs...`.
		*/
		template <class ...Xs>
		XTAL_VAL_(return,inline,set)
		reform(Xs &&...xs)
		noexcept -> auto
		{
			return form_t<xtd::decay_xvalue_t<Xs>...>{XTAL_REF_(xs)...};
		}

		/*!
		\returns	A specialized instance of `this` using the underlying template.
		*/
		XTAL_FN2_(to) (template <class ...Xs>
		XTAL_VAL_(return,inline,let)
		deform(), form_t<Xs...>(self()))

	public:// OPERATE
		using S_::self;
		using S_::size;
	//	static cardinal_constant_t<std::rank_v<common_t<Us...>>> constexpr rank{};

		XTAL_VAL_(set) mask = size_constant_t<size - 1>{};

		/*!
		\returns	`true` if component-wise equal, `false` otherwise.
		*/
		XTAL_VAL_(return,inline,friend,let)
		operator==(homotype const &s, homotype const &t)
		noexcept -> bool
		{
			XTAL_IF0
		//	XTAL_0IF (fixed_valued_q<archetype> and atomic_q<value_type>) {
		//		return 0 == std::memcmp(s.data(), t.data(), S_::size_bytes());//TODO: Not working for complex values?
		//	}
			XTAL_0IF XTAL_TRY_(to) (
				static_cast<S_ const &>(s) == static_cast<S_ const &>(t)
			)
			XTAL_0IF_(else) {
				return [&]<auto ...I>(bond::seek_in_t<I...>)
					XTAL_0FN_(to) (...and (get<I>(s) == get<I>(t)))
				(bond::seek_to_t<size>{});
			}
		}

		/*!
		\returns	The first `resize` elements of `this` as a truncated view of `U`.
		*/
		XTAL_FN2_(do) (template <scalar_array_q U_form=value_type>
		XTAL_VAL_(return,inline,let)
		self(cardinal_constant_q auto N_form),
		{
			bool constexpr K_default = same_q<U_form, value_type>;
			bool constexpr K_uniform = fixed_valued_q<archetype>;
			XTAL_IF0
			XTAL_0IF (K_default and N_form == size()) {
				return self();
			}
			XTAL_0IF (K_uniform and N_form <= size()) {
				return form_t<U_form(&)[N_form]>(self());
			}
			XTAL_0IF_(else) {
				static_assert(K_default);
				return [&]<auto ...I> (bond::seek_in_t<I...>)
					XTAL_0FN_(to) (deform(get<I>(self())...))
				(bond::seek_to_t<N_form>{});
			}
			static_assert(N_form <= size());
		})
		XTAL_FN2_(do) (template <scalar_array_q U_form=value_type>
		XTAL_VAL_(return,inline,let)
		self( ordinal_constant_q auto desize),
		{
			return self<U_form>(cardinal_constant_t<desize + size()>{});
		})

		/*!
		\returns	A copy of `this`.
		*/
		XTAL_VAL_(return,inline,let)
		twin() const
		noexcept -> auto
		{
			return deform<std::remove_cvref_t<Us>...>();
		}
		/*!
		\returns	A copy of `this` truncated to the first `resize` elements.
		*/
		template <scalar_array_q U_form=value_type>
		XTAL_VAL_(return,inline,let)
		twin(cardinal_constant_q auto N_form) const
		noexcept -> auto
		{
			bool constexpr K_default = same_q<U_form, value_type>;
			bool constexpr K_uniform = fixed_valued_q<archetype>;
			XTAL_IF0
			XTAL_0IF (K_default and N_form == size()) {
				return twin();
			}
			XTAL_0IF (K_uniform and N_form == size()) {
				return deform<U_form  [N_form]>();
			}
			XTAL_0IF_(else) {
			//	static_assert(K_default);// Not necessary?
				return [&]<auto ...I> (bond::seek_in_t<I...>)
					XTAL_0FN_(to) (reform(got<I>(self())...))
				(bond::seek_to_t<N_form>{});
			}
		}
		template <scalar_array_q U_form=value_type>
		XTAL_VAL_(return,inline,let)
		twin( ordinal_constant_q auto desize) const
		noexcept -> auto
		{
			return twin<U_form>(cardinal_constant_t<desize + size()>{});
		}

	public:// ACCESS
		XTAL_VAL_(set) devalue_f = std::identity{};///<\returns The internal value.
		XTAL_VAL_(set) revalue_f = std::identity{};///<\returns The external value.
		XTAL_VAL_(set) deindex_f = std::identity{};///<\returns The internal index.
		XTAL_VAL_(set) reindex_f = std::identity{};///<\returns The external index.

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
			static_assert(fixed_valued_q<archetype>);
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

	public:// APPLY
		/*!
		\returns	A `revalue_f`d instance of `this`.
		*/
		XTAL_FN2_(to) (XTAL_VAL_(return,inline,let) deform(), apply())

		/*!
		\returns	A `revalue_f`d instance of `this`.
		*/
		XTAL_VAL_(return,inline,let)
		apply() const
		noexcept -> decltype(auto)
		{
			using F = decltype(T::revalue_f);
			if constexpr (fixed_valued_q<archetype>) {
				return apply<typename S_::template form_t<return_t<F, value_type>[size]>>();
			}
			else {
				return apply<return_t<F, Us>...>();
			}
		}

		/*!
		\returns	An invocation of `F` applied to the `revalue_f`s of `this`.
		*/
		template <complete_q F>
		XTAL_VAL_(return,inline,explicit)
		operator F() const
		noexcept
		{
			return apply<F>();
		}

		/*!
		\returns	An invocation of `F` applied to the `revalue_f`s of `this`.
		*/
		template <class F>
		XTAL_VAL_(return,inline,let)
		apply() const
		noexcept -> decltype(auto)
		{
			return apply<bond::operate<F>{}>();
		}
		/*!
		\returns	The result of applying `f` to the `revalue_f`s of `this`.
		*/
		template <auto  f>
		XTAL_VAL_(return,inline,let)
		apply() const
		noexcept -> decltype(auto)
		{
			return apply(f);
		}
		/*!
		\returns	The result of applying `f` to the `revalue_f`s of `this`.
		*/
		XTAL_VAL_(return,inline,let)
		apply(auto &&f) const
		noexcept -> decltype(auto)
		{
			return [this, f=XTAL_REF_(f)]<auto ...I> (bond::seek_in_t<I...>)
				XTAL_0FN_(to) (f(self().template coelement<I>()...))
			(bond::seek_to_t<size>{});
		}

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
