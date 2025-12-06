/**
 * @file libcurrent_context.h
 * @brief Implementation of the context used to manage test cases
 */

#ifndef LIBCURRENT_CONTEXT_H
#define LIBCURRENT_CONTEXT_H

#include "libcurrent/libcurrent_types.h"

#include <stdbool.h>
#include <stddef.h>

// =============================================================================
// == TYPES ====================================================================
// =============================================================================

/**
 * @brief Test case registered by an entry in the .test_array section
 */
typedef struct LIBCURRENT_testcase {
	LIBCURRENT_testimpl test; /**< Actual implementation of the test */
	const char         *name; /**< Test name for reporting */
} LIBCURRENT_testcase;

/**
 * @brief Runtime information about the test cases.
 */
typedef struct LIBCURRENT_teststatus {
	int num_asserts_run;    /**< Total number of assertions */
	int num_asserts_failed; /**< Number of failed assertions */
} LIBCURRENT_teststatus;

/**
 * @brief Information for when a test case failed.
 */
typedef struct LIBCURRENT_testfailure {
	size_t      index;         /**< Index in the testcases array */
	const char *file;          /**< __FILE__ in which the test failed */
	int         line;          /**< __LINE__ in which the test failed */
	const char *expected_expr; /**< Expected expression  */
	const char *actual_expr;   /**< Actual expression */
	char       *expected_val;  /**< Expected value as a string */
	char       *actual_val;    /**< Actual value as a string */
} LIBCURRENT_testfailure;

/**
 * @brief Context used to manage and run test cases
 */
struct LIBCURRENT_context {
	size_t num_tests;            /**< Total number of test, capacity for the dynamic arrays */
	size_t num_registered_tests; /**< Current number of registered testcases */
	size_t num_failures;         /**< Current number of failed assertions */
	LIBCURRENT_testcase    *testcases; /**< Registered testcases */
	LIBCURRENT_teststatus  *statuses;  /**< Runtime information of the tests */
	LIBCURRENT_testfailure *failures;  /**< Information about failed tests */
};

// =============================================================================
// == LIFE CYCLE ===============================================================
// =============================================================================

/**
 * @brief Allocates and initializes the context.
 * @param num_tests number of entries in the .test_array section.
 * @returns The context on success, NULL on failure.
 */
LIBCURRENT_context *LIBCURRENT_context_create(size_t num_tests);
/**
 * @brief Frees the internal resources and then the context itself.
 */
void LIBCURRENT_context_destroy(LIBCURRENT_context *ctx);

/**
 * @brief Allocates the resources of the test failure,
 * @note It is assumed that the value strings got `malloc`d and
 *       they will be `free`d on finalize.
 */
bool LIBCURRENT_testfailure_initialize(
	LIBCURRENT_testfailure *failure,       /**< Failure to initializes */
	size_t                  index,         /**< Index of the failed test */
	const char             *file,          /**< __FILE__ */
	int                     line,          /**< __LINE__ */
	const char             *expected_expr, /**< Expected expression as a string */
	const char             *actual_expr,   /**< Actual expression as a string */
	char                   *expected_val,  /**< Expected value as an allocated string */
	char                   *actual_val     /**< Actual value as an allocated string */
);
/**
 * @brief Deallocates the internal resources of the test failure
 */
void LIBCURRENT_testfailure_finalize(LIBCURRENT_testfailure *failure);

// =============================================================================
// == INTERNAL API =============================================================
// =============================================================================

/**
 * @brief Registers the tests to be run later.
 */
void LIBCURRENT_context_register(
	LIBCURRENT_context *ctx,  /**< Context in which the test is registered */
    LIBCURRENT_testimpl test, /**< Implementation to actually run */
	const char         *name  /**< Name of the test */
);

/**
 * @brief Runs all registered test cases.
 *
 * By default, this runs all tests in parallel and outputs a status indicator
 * for every passed/failed/skipped assertion.
 * TODO: Make the behavior configurable.
 */
void LIBCURRENT_context_run(LIBCURRENT_context *ctx);
/**
 * @brief Pints a more detailed summary of tests & assertions run and which ones failed
 */
void LIBCURRENT_context_print_summary(const LIBCURRENT_context *ctx);

#endif // LIBCURRENT_CONTEXT_H

