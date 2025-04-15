#ifndef FCPUT_ARCHITECTURE_OS
#define FCPUT_ARCHITECTURE_OS

/* Header for detecting the operating system and its inherent features
 */

// Check if running on system based on the Linux kernel
#ifdef __linux__
#define FCPUT_LINUX __linux__
#else
#define FCPUT_LINUX 0
#endif

// Check if running on Windows (multiple defines based on the environment)
#ifdef _WIN16
#define FCPUT_WIN16 _WIN16
#else
#define FCPUT_WIN16 0
#endif
#ifdef _WIN32
#define FCPUT_WIN32 _WIN32
#else
#define FCPUT_WIN32 0
#endif
#ifdef _WIN64
#define FCPUT_WIN64 _WIN64
#define FCPUT_WIN32 0	// This macro is defined in both 32 and 64 bit Windows environments
#else
#define FCPUT_WIN64 0
#endif

// General Windows macro
#if 0 != (FCPUT_WIN16 + FCPUT_WIN32 + FCPUT_WIN64)
#define FCPUT_WINDOWS 1
#else
#define FCPUT_WINDOWS 0
#endif

#endif	// FCPUT_ARCHITECTURE_OS
