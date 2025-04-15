#ifndef FCPUT_COMPUTATIONAL_GRID
#define FCPUT_COMPUTATIONAL_GRID

#include "computational/common/common.hpp"

#include <cstddef>
#include <type_traits>
#include <stdexcept>
#include <iostream>
#include <vector>

START_FCP_NAMESPACE
START_COMPUTATIONAL_NAMESPACE

namespace internal
{
	// Pre C++20 Grid concept
	template <typename, typename = void>	
	constexpr bool is_valid_grid = false;

	template <typename T>
	constexpr bool is_valid_grid<
		T,
		std::void_t<decltype(&T::at),
								decltype(&T::operator[]),
								decltype(&T::at_range),
								decltype(&T::data)
		>
	> = true;
}	// namespace internal

/// @brief Uniform grid
template <typename T>
class UniformGrid
{
	public:
		constexpr static bool is_uniform_v = true;
		
		/// @brief Generate an uniform grid
		/// @param from
		/// @param to
		/// @param number_of_points
		UniformGrid(const T& from, const T& to, const std::size_t& number_of_points): m_from{from}, m_to{to}, m_n_points{number_of_points} {}
			
		UniformGrid(const UniformGrid& other)
		{
			this->m_from = other.m_from;
			this->m_to = other.m_to;
			this->m_n_points = other.m_n_points;
		}

		/// @brief Returns `i`-th grid point performing bounds checking first
		const T at(const std::size_t& i) const
		{
			if (i > m_to) throw std::out_of_range("UniformGrid::at(): Index out of range was requested.\n");
			return m_from + i*(m_to - m_from)/m_n_points;
		}
		
		/// @brief Returns `i`-th grid point without performing bounds checking first
		const T operator[](const std::size_t& i) const
		{
			return m_from + i*(m_to - m_from)/m_n_points;
		}

		const std::size_t begin(void) const
		{
			return static_cast<std::size_t>(0);
		}

		const std::size_t end(void) const
		{
			return m_n_points;
		}
	
		std::vector<T> at_range(const T& from, const T& to) const
		{
			std::vector<T> temp;	
			for (std::size_t i{from}; i < to; i++)
				temp.push_back(this->at(i));
			return temp;
		}
	
		std::vector<T> data(void) const
		{
			return this->at_range(this->begin(), this->end());
		}

		template <typename U>
		friend std::ostream& operator<<(std::ostream& out, const UniformGrid<U>& grid);

	private:
		T m_from, m_to;
		std::size_t m_n_points;
};

template <typename T>
std::ostream& operator<<(std::ostream& out, const UniformGrid<T>& grid)
{
	out << "UniformGrid template object:\n";
	out << "From: " << grid.m_from << '\n';
	out << "To: " << grid.m_to << '\n';
	out << "Number of points: " << grid.m_n_points << '\n';
	for (std::size_t i{grid.begin()}; i < grid.end(); i++)
		out << grid[i] << ' ';
	out << std::endl;

	return out;
}

/// @brief Grid generated from custom array
template <std::size_t Dimensions = 1>
class FromArrayGrid
{



};

END_COMPUTATIONAL_NAMESPACE
END_FCP_NAMESPACE

#endif	// FCPUT_COMPUTATIONAL_GRID
