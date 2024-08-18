#pragma once

/*
 * This file is used to define the platform that the program is running on.
 * This is used to determine which platform-specific code to use.
 */
// WINDOWS_SYSTEM
#if defined(_WIN32) || defined(_WIN64)
#define WINDOWS_SYSTEM
#pragma message("Compiling for Windows")
#endif

// UNIX_SYSTEM
#if defined(__unix__) || defined(__APPLE__)
#define UNIX_SYSTEM
#pragma message("Compiling for Unix or macOS")
#endif

// LINUX_SYSTEM
#if defined(_LINUX) || defined(linux) || defined(__linux) || defined(__linux__)
#define LINUX_SYSTEM
#endif

// DARWIN_SYSTEM
#if defined(__APPLE__) || defined(_DARWIN)
#define DARWIN_SYSTEM
#endif
