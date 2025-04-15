#ifndef FCPUT_ARCHITECTURE_SIMD
#define FCPUT_ARCHITECTURE_SIMD

/* Detect SIMD extensions */

// Depends on the OS because Windows is weird
#if 1 == FCPUT_WINDOWS
// Detect SIMD for Windows
#else
// Detect SIMD for Linux/Unix
#endif

#endif	// FCPUT_ARCHITECTURE_SIMD
