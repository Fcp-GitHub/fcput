#ifndef FCPUT_COMPUTATIONAL_DIFFERENTIATE_UTILITY
#define FCPUT_COMPUTATIONAL_DIFFERENTIATE_UTILITY

#define START_FCP_NAMESPACE namespace fcp {
#define END_FCP_NAMESPACE }

#define START_COMPUTATIONAL_NAMESPACE namespace computational {
#define END_COMPUTATIONAL_NAMESPACE }

#define FCP_COMPUTATIONAL_API inline

#include <type_traits>

START_FCP_NAMESPACE
START_COMPUTATIONAL_NAMESPACE

namespace internal
{
	// Pre C++20 math function concept
	template <typename, typename = void>
	constexpr bool is_valid_math_function = false;

	template <typename T>
	constexpr bool is_valid_math_function<
		T,
		std::void_t<decltype(&T::operator())>
	> = true;
}

END_COMPUTATIONAL_NAMESPACE
END_FCP_NAMESPACE

#endif	//FCPUT_COMPUTATIONAL_DIFFERENTIATE_UTILITY
