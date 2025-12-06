/**
 * @file libcurrent_platform.h
 * @brief Magic macros implementing platform specific behavior.
 */

#ifndef LIBCURRENT_PLATFORM_H
#define LIBCURRENT_PLATFORM_H

#include "libcurrent/config.h"

// =============================================================================
// == LINUX SPECIFIC ===========================================================
// =============================================================================

#ifdef LIBCURRENT_PLATFORM_LINUX

/** Linux version of the __attribute__ needed to refer to the .test_array section */
#define LIBCURRENT_TESTARRAY_ATTRIBUTE __attribute__((used, section(".test_array")))

/** Linux version of the identifier referring to the start of the .test_array section */
#define LIBCURRENT_TESTARRAY_BEGIN __start_test_array
/** Linux version of the identifier referring to the end of the .test_array section */
#define LIBCURRENT_TESTARRAY_END   __stop_test_array

/** On Linux, we do not need any assembly to find the start symbol for the .test_array */
#define LIBCURRENT_TESTARRAY_BEGIN_ASM
/** On Linux, we do not need any assembly to find the end symbol for the .test_array */
#define LIBCURRENT_TESTARRAY_END_ASM

#endif

// =============================================================================
// == MACOS SPECIFIC ===========================================================
// =============================================================================

#ifdef LIBCURRENT_PLATFORM_MACOS

/** MacOS version of the __attribute__ needed to refer to the __test_array section */
#define LIBCURRENT_TESTARRAY_ATTRIBUTE __attribute__((used, section("__DATA,__test_array")))

/** MacOS version of the identifier referring to the start of the __test_array section */
#define LIBCURRENT_TESTARRAY_BEGIN __DATA_test_array_start
/** MacOS version of the identifier referring to the end of the __test_array section */
#define LIBCURRENT_TESTARRAY_END   __DATA_test_array_end

/** MacOS version of the assembly needed to find the start symbol for the __test_array */
#define LIBCURRENT_TESTARRAY_BEGIN_ASM __asm("section$start$__DATA$__test_array")
/** MacOS version of the assembly needed to find the end symbol for the __test_array */
#define LIBCURRENT_TESTARRAY_END_ASM   __asm("section$end$__DATA$__test_array")

#endif

#endif // LIBCURRENT_PLATFORM_H
