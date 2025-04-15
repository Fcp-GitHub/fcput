#ifndef FCPUT_ALGODS_SIMD_SSE
#define FCPUT_ALGODS_SIMD_SSE

#include <immintrin.h>

#include "algo_ds/common/common.hpp"
#include "common_simd.hpp"

FCP_NAMESPACE_BEGIN
FCP_NAMESPACE_ALGODS_BEGIN
FCP_NAMESPACE_SIMD_BEGIN

/// @brief Compute dot product of four vectors passed to the function via four vectors of the components along a single axis each
inline FCPUT_CPP14_CONSTEXPR __m128 dot(
		const __m128& ax, const __m128& ay, const __m128& az, const __m128& aw,
	 	const __m128& bx, const __m128& by, const __m128& bz, const __m128& bw
		)
{
	__m128 _dx = _mm_mul_ps(ax, bx);
	__m128 _dy = _mm_mul_ps(ay, by);
	__m128 _dz = _mm_mul_ps(az, bz);
	__m128 _dw = _mm_mul_ps(aw, bw);

	__m128 _s1 = _mm_add_ps(_dx, _dy);
	__m128 _s2 = _mm_add_ps(_dz, _dw);

	return _mm_add_ps(_s1, _s2);
}	

FCP_NAMESPACE_SIMD_END
FCP_NAMESPACE_ALGODS_END
FCP_NAMESPACE_END

#endif	// FCPUT_ALGODS_SIMD_SSE
