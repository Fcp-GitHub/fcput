#ifndef FCPUT_COMPUTATIONAL_MATRIX
#define FCPUT_COMPUTATIONAL_MATRIX

#include "computational/common/common.hpp"

#include <type_traits>
#include <array>

START_FCP_NAMESPACE
START_COMPUTATIONAL_NAMESPACE

struct column_major {};
struct row_major {};

template <typename T, std::size_t N, std::size_t M, typename Ordering = column_major>
class Matrix
{
	private:
		using _row_major = std::array<std::array<T, M>, N>;
		using _col_major = std::array<std::array<T, N>, M>;
		constexpr static bool _col_was_chosen = std::is_same_v<Ordering, column_major>;
		using _inner_mat = typename std::conditional<_col_was_chosen, _col_major, _row_major>::type;
		_inner_mat m_mat;
};

template <typename T> using mat4x4 = Matrix<T, 4, 4>;
template <typename T> using mat3x3 = Matrix<T, 3, 3>;
template <typename T> using mat2x2 = Matrix<T, 2, 2>;

END_COMPUTATIONAL_NAMESPACE
END_FCP_NAMESPACE

#endif	// FCPUT_COMPUTATIONAL_MATRIX
