#ifndef FCPUT_ARCHITECTURE_COMPILER
#define FCPUT_ARCHITECTURE_COMPILER

/* Header for detecting compilers and their inherent features
 */

// Identify any compiler that implements the GNU compiler extensions
// Macro format: VVRRPP (VV = Version, RR = Revision, PP = Patch)
#ifdef __GNUC__
	#ifdef __GNUC_PATCHLEVEL
	#define FCPUT_ARCH_GCC (__GNUC__ * 10000 \
													+ __GNUC_MINOR__ * 100 \
													+ __GNUC_PATCHLEVEL__)
	#else
	#define FCPUT_ARCH_GCC (__GNUC__ * 10000 \
													+ __GNUC_MINOR__ * 100)
	#endif
#else
#define FCPUT_ARCH_GCC 0
#endif

// MSVC compiler
// 'For compatibility with existing code that compiles with MSVC, clang defines the _MSC_VER and _MSC_FULL_VER macros' 
// (see: http://clang.llvm.org/docs/UsersManual.html)
// Therefore detect MSVC with the macro value, but filtering out clang-cl
#if defined(_MSC_VER) and not defined(__clang__)
#define FCPUT_ARCH_MSVC _MSC_VER
#else
#define FCPUT_ARCH_MSVC 0
#endif

// Check if at least one compiler was detected
#if 0 == (FCPUT_ARCH_GCC + FCPUT_ARCH_MSVC)
#error "Unsupported compiler."
#endif

// Check if more than one compiler was detected
#define _FCPUT_NORMALIZE(x) !!x
#if 1 < (_FCPUT_NORMALIZE(FCPUT_ARCH_GCC) + _FCPUT_NORMALIZE(FCPUT_ARCH_MSVC))
#error "Multiple compilers were detected."
#endif

#endif	// FCPUT_ARCHITECTURE_COMPILER
