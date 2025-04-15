#ifndef FCPUT_COMPUTATIONAL_DIFFERENTIATION
#define FCPUT_COMPUTATIONAL_DIFFERENTIATION

#include "computational/common/common.hpp"
#include "computational/mesh/grid.hpp"

#include <type_traits>
#include <cmath>
#include <array>
#include <vector>

START_FCP_NAMESPACE
START_COMPUTATIONAL_NAMESPACE

// Tags
struct central_difference{};  
struct forward_difference{};  
struct backward_difference{}; 

template <typename T, class Functor, class Grid,
				  typename Method = central_difference, std::size_t TruncationOrder = 2,
					std::size_t DiffOrder = 1, std::size_t Dimensions = 1>	// TODO
class Differentiate
{
	// Pre C++20 Concepts
	static_assert(internal::is_valid_grid<Grid>, "class Differentiate: invalid Grid class passed.\n");
	static_assert(std::is_copy_constructible<Grid>::value, "class Differentiate: Grid class is not copy constructible.\n");
	static_assert(internal::is_valid_math_function<Functor>, "class Differentiate: invalid Function class passed.\n");
	static_assert(std::is_same_v<Method, central_difference> or
								std::is_same_v<Method, backward_difference> or
								std::is_same_v<Method, forward_difference>,
								"class Differentiate: unsupported approximation method requested.\n");

	public:
		/// @brief Generate a `Differentiate` object
		/// @detail During generation the `Grid` object will be copy-constructed and the `Functor` object will be default-initialized
		Differentiate(const Grid& grid): m_grid{grid}, m_functor() {}
		Differentiate(const Grid&& grid): m_grid{grid}, m_functor() {}
		Differentiate(const Differentiate&) = delete;
		Differentiate& operator=(const Differentiate&) = delete;
		Differentiate& operator=(Differentiate&&) = delete;

		/// @brief Returns differential at `i`-th grid point while providing bounds checking through `Grid::at()` method (only if in debug mode)
		/// @details The points that may not be computable by the chosen method will be approximated by the other ones. For example, the central method of the second order will use the forward difference approximation for the first point and the backward difference approximation for the last one 
		template <std::size_t DOrder = DiffOrder, std::size_t TOrder = TruncationOrder>
		FCP_COMPUTATIONAL_API T at(const std::size_t& i) const 
		{ 
			return _finite_diff_single_value<DOrder, TOrder>(i, true, Method());
		}

		/// @brief Returns differential at `i`-th grid point without any bounds checking
		template <std::size_t DOrder = DiffOrder, std::size_t TOrder = TruncationOrder>
		FCP_COMPUTATIONAL_API T operator[](const std::size_t& i) const 
		{ 
			return _finite_diff_single_value<DOrder, TOrder>(i, false, Method()); 
		}
		
		/// @brief Compute array of values in the specified range of grid points
		template <std::size_t DOrder = DiffOrder, std::size_t TOrder = TruncationOrder>
		FCP_COMPUTATIONAL_API std::vector<T> at_range(const std::size_t& from, const std::size_t& to) const
		{
			std::vector<T> temp;
			for (std::size_t i{from}; i < to; i++)
				temp.push_back(this->at<DOrder, TOrder>(i));
			return temp;
		}

		/// @brief Compute array of values over all grid points and return it
		/// @details For an object `diff`, this is the same as
		/// `diff.at_range(diff.begin(), diff.end())`
		template <std::size_t DOrder = DiffOrder, std::size_t TOrder = TruncationOrder>
		FCP_COMPUTATIONAL_API std::vector<T> data(void) const 
		{ 
			return this->at_range<DOrder, TOrder>(m_grid.begin(), m_grid.end());
		}

	private:
		// Private implementation of differentiation methods

		// Lookup table for pre-calculated values used by the central difference method
		static constexpr std::array<T, 6> _cd_lut {
			std::array<T, 4> {	// First differentiation order 
				std::array<T, 3> { -1/2, 0, 1/2 },	// Second truncation order
				std::array<T, 5> { 1/12, -2/3, 0, 2/3, -1/12},	// Fourth truncation order
				std::array<T, 7> { -1/60, 3/20, -3/4, 0, 3/4, -3/20, 1/60},	// Sixth truncation order
				std::array<T, 9> { 1/280,	-4/105,	1/5,	-4/5,	0,	4/5,	-1/5,	4/105,	-1/280}	// Eighth truncation order
			},
			std::array<T, 4> {	// Second differentiation order
				std::array<T, 3> { 1, -2, 1 },	// Second truncation order
				std::array<T, 5> { -1/12, 4/3, -5/2, 4/3, -1/12 },	// Fourth truncation order
				std::array<T, 7> { 1/90, -3/20, 3/2, -49/18, 3/2, -3/20, 1/90 },	// Sixth truncation order
				std::array<T, 9> { -1/560, 8/315, -1/5, 8/5, -205/72, 8/5, -1/5, 8/315, -1/560 }	// Eighth truncation order
			},
			std::array<T, 3> {	// Third differentiation order
				std::array<T, 5> { -1/2, 1, 0, -1, 1/2 },	// Second truncation order
				std::array<T, 7> { 1/8, -1, 13/8, 0, -13/8, 1, -1/8 },	// Fourth truncation order
				std::array<T, 9> { -7/240, 3/10, -169/120, 61/30, 0, -61/30, 169/120, -3/10, 7/240 }	// Sixth truncation order
			},
			std::array<T, 3> {	// Fourth differentiation order
				std::array<T, 5> { 1, -4, 6, -4, 1 },	// Second truncation order		
				std::array<T, 7> { -1/6, 2, -13/2, 28/3, -13/2, 2, -1/6 },	// Fourth truncation order
				std::array<T, 9> { 7/240, -2/5, 169/60, -122/15, 91/8, -122/15, 169/60, -2/5, 7/240 }	// Sixth truncation order
			},
			std::array<T, 3> {	// Fifth differentiation order
				std::array<T, 7> { -1/2, 2, -5/2, 0, 5/2, -2, 1/2 },	// Second truncation order
				std::array<T, 9> { 1/6, -3/2, 13/3, -29/6, 0, 29/6, -13/3, 3/2, -1/6 },	// Fourth truncation order
				std::array<T, 11> { -13/288, 19/36, -87/32, 13/2, -323/48, 0, 323/48, -13/2, 87/32, -19/36, 13/288 }	// Sixth truncation order
			},
			std::array<T, 3> {	// Sixth differentiation order
				std::array<T, 7> { 1, -6, 15, -20, 15, -6, 1 },	// Second truncation order
				std::array<T, 9> { -1/4, 3, -13, 29, -75/2, 29, -13, 3, -1/4 },	// Fourth truncation order
				std::array<T, 11> { 13/240, -19/24, 87/16, -39/2, 323/8, -1023/20, 323/8, -39/2, 87/16, -19/24, 13/240 }	// Sixth truncation order
			}
		};

		// Lookup table for pre-calculated values used by the forward difference method
		static constexpr std::array<T, 6> _fd_lut {
			std::array<T, 6> {  // First differentiation order
    		std::array<T, 2> { -1,1 },	// First truncation order
    		std::array<T, 3> { -3/2, 2, -1/2 },	// Second truncation order
    		std::array<T, 4> { -11/6, 3, -3/2, 1/3 },	// Third truncation order
    		std::array<T, 5> { -25/12, 4, -3, 4/3, -1/4 },	// Fourth truncation order
    		std::array<T, 6> { -137/60, 5, -5, 10/3, -5/4, 1/5 },	// Fith truncation order
    		std::array<T, 7> { -49/20, 6, -15/2, 20/3, -15/4, 6/5, -1/6 }	// Sixth truncation order
			},
			std::array<T, 6> {  // Second differentiation order
			  std::array<T, 3> { 1, -2, 1 },	// First truncation order
			  std::array<T, 4> { 2, -5, 4, -1 },	// Second truncation order
			  std::array<T, 5> { 35/12, -26/3, 19/2, -14/3, 11/12 },	// Third truncation order
			  std::array<T, 6> { 4, 15/4, -77/6, 107/6, -13, 61/12, -5/6 },	// Fourth truncation order
			  std::array<T, 7> {203/45, -87/5, 117/4, -254/9, 33/2, -27/5, 137/180 },	// Fith truncation order
			  std::array<T, 8> {469/90, -223/10, 879/20, -949/18, 41, -201/10, 1019/180, -7/10 }	// Sixth truncation order
			},
			std::array<T, 6> {  // Third differentiation order
			  std::array<T, 4> { -1, 3, -3, 1 }, 	// First truncation order
			  std::array<T, 5> { -5/2, 9, -12, 7, -3/2 },	// Second truncation order
			  std::array<T, 6> { -17/4, 71/4, -59/2, 49/2, -41/4, 7/4 },	// Third truncation order
			  std::array<T, 7> { -49/8, 29, -461/8, 62, -307/8, 13, -15/8 },	// Fourth truncation order
			  std::array<T, 8> { -967/120, 638/15, -3929/40, 389/3, -2545/24, 268/5, -1849/120, 29/15 },	// Fith truncation order
			  std::array<T, 9> { -801/80, 349/6, -18353/120, 2391/10, -1457/6, 4891/30, -561/8, 527/30, -469/240 }	// Sixth truncation order
			},
			std::array<T, 6> {  // Fourth differentiation order
			  std::array<T, 5> { 1, -4, 6, -4, 1 },	// First truncation order
			  std::array<T, 6> { 3, -14, 26, -24, 11, -2 },	// Second truncation order
			  std::array<T, 7> { 35/6, -31, 137/2, -242/3, 107/2, -19, 17/6 },	// Third truncation order
			  std::array<T, 8> { 28/3, -111/2, 142, -1219/6, 176, -185/2, 82/3, -7/2 },	// Fourth truncation order
			  std::array<T, 9> { 1069/80, -1316/15, 15289/60, -2144/5, 10993/24, -4772/15, 2803/20, -536/15, 967/240 }	// Fifth truncation order
			}
		};

		// Lookup table for pre-calculated values used by the backward difference method
		static constexpr std::array<T, 6> _bd_lut {
			std::array<T, 3> { // First differentiation order
		    std::array<T, 2> { -1, 1 },    // First truncation order
		    std::array<T, 3> { 1/2, -2, 3/2 }, // Second truncation order
		    std::array<T, 4> { -1/3, 3/2, -3, 11/6 }   // Third truncation order
			},
			std::array<T, 2> {  // Second differentiation order
		    std::array<T, 3> { 1, -2, 1 },  // First truncation order
		    std::array<T, 4> { -1, 4, -5, 2 }   // Second truncation order
			},
			std::array<T, 3> {  // Third differentiation order
		    std::array<T, 4> { -1, 3, -3, 1 },  // First truncation order
		    std::array<T, 5> { 3/2, -7, 12, -9, 5/2 }    // Second truncation order
			},
			std::array<T, 4> {  // Fourth differentiation order
		    std::array<T, 5> { 1, -4, 6, -4, 1 },   // First truncation order
		    std::array<T, 6> { -2, 11, -24, 26, -14, 3 }    // Second truncation order
			}
		};

		// TODO: vectorize the following internal methods ...

		// Method for finding finite difference derivative
		template <std::size_t DOrder, std::size_t TOrder>
		FCP_COMPUTATIONAL_API T _finite_diff_single_value(const std::size_t& i, const bool& bounds_check, central_difference) const
		{
			static_assert(TOrder > 0, "class Differentiate: truncation order must be a positive number.\n");
			static_assert(DOrder > 0, "class Differentiate: differential order must be a positive number.\n");
			static_assert(TOrder % 2 == 0, "class Differentiate: truncation order for central difference approximation must be even.\n");

			constexpr auto coeff = _cd_lut[DOrder][TOrder];	
			T _res;	
			constexpr bool _use_precalc_val = DOrder <= 6 and ( DOrder <= 2 ? (TOrder <= 8) : (TOrder >= 6) );
			if constexpr ( _use_precalc_val and Grid::is_uniform_v )
			{
				// Central difference coefficients are symmetric with respect to the index 0
				constexpr std::size_t _first_i{ 0 - ( coeff.size() - 1 ) / 2 };
				const T _h{ m_grid[1] - m_grid[0] };
				for (std::size_t i{0}; i < coeff.size(); i++)
					_res += coeff[i] * m_functor(0 + (_first_i + i) * _h);
				return _res / std::pow(_h, TOrder);
			} else {
				// TODO else solve linear system
			}
		}

		template <std::size_t DOrder, std::size_t TOrder>
		FCP_COMPUTATIONAL_API T _finite_diff_single_value(const std::size_t& i, const bool& bounds_check, forward_difference) const
		{
			static_assert(TOrder > 0, "class Differentiate: truncation order must be a positive number.\n");
			static_assert(DOrder > 0, "class Differentiate: differential order must be a positive number.\n");
			
			constexpr auto coeff = _fd_lut[DOrder][TOrder];	
			T _res;
			constexpr bool _use_precalc_val = DOrder <= 4 and ( DOrder <= 3 ? (TOrder <= 6) : (TOrder <= 5) );
			if constexpr ( _use_precalc_val and Grid::is_uniform_v )
			{
				const T _h{ m_grid[1] - m_grid[0] };
				for (std::size_t i{0}; i < coeff.size(); i++)
					_res += coeff[i] * m_functor(i*_h);
				return _res / std::pow(_h, TOrder);	
			} else {
				// TODO else solve linear system
			}
		}

		template <std::size_t DOrder, std::size_t TOrder>
		FCP_COMPUTATIONAL_API T _finite_diff_single_value(const std::size_t& i, const bool& bounds_check, backward_difference) const
		{
			static_assert(TOrder > 0, "class Differentiate: truncation order must be a positive number.\n");
			static_assert(DOrder > 0, "class Differentiate: differential order must be a positive number.\n");
				
			constexpr auto coeff = _bd_lut[DOrder][TOrder];
			T _res;
			constexpr bool _use_precalc_val = DOrder >= 4 and ( DOrder == 1 ? (TOrder <= 3) : (TOrder <= 2) ); 
			if constexpr ( _use_precalc_val and Grid::is_uniform_v )
			{
				const T _h{ m_grid[1] - m_grid[0] };
				for (std::size_t i{0}; i < coeff.size(); i++)
					_res += coeff[i] * m_functor(0 - i*_h);
				return _res / std::pow(_h, TOrder);
			} else {
				// TODO else solve linear system
			}
		}


		Grid m_grid;
		Functor m_functor;
};

END_COMPUTATIONAL_NAMESPACE
END_FCP_NAMESPACE


#endif	// FCPUT_COMPUTATIONAL_DIFFERENTIATION
