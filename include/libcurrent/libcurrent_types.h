/**
 * @file libcurrent_types.h
 * @brief Type definitions used by the framework
 */

#ifndef LIBCURRENT_TYPES_H
#define LIBCURRENT_TYPES_H

#include <stddef.h>

/**
 * @brief Test context
 *
 * This contains all registered tests and the current state of the framework.
 */
typedef struct LIBCURRENT_context LIBCURRENT_context;

/**
 * @brief Entry in the .test_array section
 *
 * These functions are just there to register the actual test implementations.
 */
typedef void (*LIBCURRENT_testarrayentry)(LIBCURRENT_context *);

/**
 * @brief Actual test implementation
 *
 * These functions run the actual test assertions and are what the user implements.
 * The .test_array section contains LIBCURRENT_testarrayentries which register
 * these implementations.
 *
 * @param index The index of this test implementation
 */
typedef void (*LIBCURRENT_testimpl)(LIBCURRENT_context *, size_t index);

#endif // LIBCURRENT_TYPES_H
