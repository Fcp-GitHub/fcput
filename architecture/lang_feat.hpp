#ifndef FCPUT_ARCHITECTURE_LANGFEAT
#define FCPUT_ARCHITECTURE_LANGFEAT

/* Header for detecting C++ features availability
 */

// `constexpr` specifier availability
#if defined(__cpp_constexpr) and __cpp_constexpr >= 201603L
#define FCPUT_CPP17_CONSTEXPR constexpr
#else
#define FCPUT_CPP17_CONSTEXPR
#endif

#if defined(__cpp_constexpr) and __cpp_constexpr >= 201304L
#define FCPUT_CPP14_CONSTEXPR constexpr
#else
#define FCPUT_CPP14_CONSTEXPR
#endif

#if defined(__cpp_constexpr) and __cpp_constexpr >= 200704L
#define FCPUT_CPP11_CONSTEXPR constexpr
#else
#define FCPUT_CPP11_CONSTEXPR
#endif

// `inline` specifier for variables availability
#if defined(__cpp_inline_variables) and __cpp_inline_variables >= 201606L
#define FCPUT_CPP17_INLINE inline
#else
#define FCPUT_CPP17_INLINE
#endif

#endif	// FCPUT_ARCHITECTURE_LANGFEAT
