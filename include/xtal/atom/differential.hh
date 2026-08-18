#pragma once
#include "./any.hh"
#include "./qualify.hh"
#include "./quantity.hh"




XTAL_ENV_(push)
namespace xtal::atom
{/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
/*!
\brief
Extends `quantity` with component-wise addition and differential succession.
*/
template <class ...Us>	struct  differential;
template <class ...Us>	using   differential_t = typename differential<Us...>::type;
template <class ...Us>	concept differential_q = bond::tag_inner_fixed_p<differential_t, Us...>;

XTAL_VAL_(let) differential_f = [] XTAL_1FN_(call) (_detail::factory<differential_t>::make);


////////////////////////////////////////////////////////////////////////////////

template <scalar_array_q ...Us> requires same_q<Us...>
struct differential<Us ...> : differential<common_t<Us...>[sizeof...(Us)]>
{};
template <class ...Us>
struct differential
{
	template <class T>
	//\
	using endotype = typename quantity<qualify_s<Us, std::plus>...>::template homotype<T>;
	using endotype = typename quantity<Us...>::template homotype<T>;

	template <class T>
	using holotype = bond::compose_s<endotype<T>, bond::tag<differential_t>>;

	template <class T>
	class homotype : public holotype<T>
	{
		using S_ = holotype<T>;
		using A_ = typename S_:: archetype;

	public:// CONSTRUCT
		using S_::S_;

		using typename S_::value_type;
		using typename S_::scale_type;

		template <intercedent_q K, quantity_multiplies_q U>
		XTAL_VAL_(new,explicit)
		homotype(U &&u, K)
 		noexcept
		:	S_{XTAL_REF_(u), [=]<auto ...I> (bond::seek_in_t<I...>)
				XTAL_0FN_(to) ((I, u) *...* (u)) (bond::seek_to_t<K::value - 1>{})}
 		{}
		template <intercedent_q K, class                  U>
		XTAL_VAL_(new,explicit)
		homotype(U &&u, K)
 		noexcept
		:	S_{XTAL_REF_(u), [=]<auto ...I> (bond::seek_in_t<I...>)
				XTAL_0FN_(to) ((I, u) +...+ (u)) (bond::seek_to_t<K::value - 1>{})}
 		{}

	public:// ACCESS
		using S_::element;
		using S_::size;
		using S_::self;
		using S_::twin;
	
	public:// OPERATE
		
		XTAL_VAL_(inline,let) operator++(int)
		noexcept -> auto {auto t = twin(); operator++(); return t;}
		
		XTAL_VAL_(inline,let) operator--(int)
		noexcept -> auto {auto t = twin(); operator--(); return t;}

		/*!
		\brief  	Produces the successor by pairwise addition from `begin()` to `end()`,
		assuming the entries of `this` are finite differences/derivatives.
		*/
		XTAL_VAL_(inline,let)
		operator ++ ()
		noexcept -> T &
		{
			bond::seek_to_e<(int) size - 1>([this]<constant_q I> (I)
			XTAL_0FN -> void {
				auto           &s = S_::self();
				auto constexpr I0 = 0 + I{};
				auto constexpr I1 = 1 + I{};
				using          U0 = XTAL_ALL_(get<I0>(s));
				using          U1 = XTAL_ALL_(get<I1>(s));
				if constexpr (quantity_multiplies_q<U0, U1>) {get<I0>(s) *= get<I1>(s);}
				else                                         {get<I0>(s) += get<I1>(s);}
			});
			return self();
		}
		/*!
		\brief  	Produces the predecessor by pairwise subtraction from `end()` to `begin()`,
		assuming the entries of `this` are finite differences/derivatives.
		*/
		XTAL_VAL_(inline,let)
		operator -- ()
		noexcept -> T &
		{
			bond::seek_to_e<1 - (int) size>([this]<constant_q I> (I)
			XTAL_0FN -> void {
				auto           &s = S_::self();
				auto constexpr I0 = 0 + I{};
				auto constexpr I1 = 1 + I{};
				using          U0 = XTAL_ALL_(get<I0>(s));
				using          U1 = XTAL_ALL_(get<I1>(s));
				if constexpr (quantity_multiplies_q<U0, U1>) {get<I0>(s) /= get<I1>(s);}
				else                                         {get<I0>(s) -= get<I1>(s);}
			});
			return self();
		}

	};
	using type = bond::derive_t<homotype>;

};


////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
}/////////////////////////////////////////////////////////////////////////////
XTAL_ENV_(pop)
