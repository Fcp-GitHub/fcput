#ifndef FCPUT_COMPUTATIONAL_VEC
#define FCPUT_COMPUTATIONAL_VEC

#include "common/common.hpp"

#include <type_traits>
#include <array>
#include <iostream>

START_FCP_NAMESPACE
START_COMPUTATIONAL_NAMESPACE

template <typename T, std::size_t N>
class Vector
{
	public:
		// Compile-Time Properties
		constexpr static std::size_t size_v = N;

		// Constructors & Destructor

		/// @brief Construct Vector object from single-components list
		template <typename ...U>//, typename CT = std::common_type_t<U...>>	this should be not needed because of bracket initialization
		Vector(const U&... args): m_data{args...} {}
		
		/// @brief Copy constructor
		Vector(const Vector<T, N>& o)
		{
			this->m_data = o.m_data;
		}

		// Logic & Arithmetic Operators

	private:
		std::array<T, N> m_data;
};

template <typename T> using Vec3 = Vector<T, 3>;
template <typename T> using Vec4 = Vector<T, 4>;

// Utility operator for pretty-print of a Vector object
template <typename T, std::size_t N>
std::ostream& operator<<(std::ostream& out, const Vector<T, N>& v)
{
	out << "Vector object:\n";
	out << "Dimensions: " << N << '\n';
	out << '(';
	for (std::size_t i{0}; i < Vector<T, N>::size_v; i++)
		out << v[i] << ' ';
	out << ')' << std::endl;
}

END_COMPUTATIONAL_NAMESPACE
END_FCP_NAMESPACE

#endif // FCPUT_COMPUTATIONAL_VEC
