#include "libcurrent/libcurrent_context.h"
#include "libcurrent/libcurrent_threads.h"

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

// =============================================================================
// == LIFE CYCLE ===============================================================
// =============================================================================

LIBCURRENT_context *LIBCURRENT_context_create(size_t num_tests)
{
	assert(num_tests > 0);

	LIBCURRENT_context     *ctx      = malloc(sizeof(*ctx));
    LIBCURRENT_testcase    *cases    = calloc(num_tests, sizeof(*cases));
    LIBCURRENT_teststatus  *statuses = calloc(num_tests, sizeof(*statuses));
    LIBCURRENT_testfailure *failures = calloc(num_tests, sizeof(*failures));

    if (ctx == NULL || cases == NULL || statuses == NULL || failures == NULL)
        goto failure;

    ctx->num_tests            = num_tests;
    ctx->num_registered_tests = 0;
    ctx->num_failures         = 0;
    ctx->testcases            = cases;
    ctx->statuses             = statuses;
    ctx->failures             = failures;

    return ctx;

failure:
    if (ctx      != NULL) free(ctx);
    if (cases    != NULL) free(cases);
    if (statuses != NULL) free(statuses);
    if (failures != NULL) free(failures);

    return NULL;
}

void LIBCURRENT_context_destroy(LIBCURRENT_context *ctx)
{
    assert(ctx            != NULL);
    assert(ctx->testcases != NULL);
    assert(ctx->statuses  != NULL);
    assert(ctx->failures  != NULL);

    for (size_t i = 0; i < ctx->num_failures; ++i) {
        LIBCURRENT_testfailure_finalize(&ctx->failures[i]);
    }

    free(ctx->testcases);
    free(ctx->statuses);
    free(ctx->failures);
    free(ctx);
}

bool LIBCURRENT_testfailure_initialize(
	LIBCURRENT_testfailure *failure,
	size_t                  index,
	const char             *file,
	int                     line,
	const char             *expected_expr,
	const char             *actual_expr,
	char                   *expected_val,
	char                   *actual_val)
{
    assert(failure       != NULL);
    assert(file          != NULL);
    assert(line           > 0);
    assert(failure       != NULL);
    assert(expected_expr != NULL);
    assert(actual_expr   != NULL);

    if (expected_val == NULL) return false;
    if (actual_expr   == NULL) return false;

    failure->index         = index;
    failure->file          = file;
    failure->line          = line;
    failure->expected_expr = expected_expr;
    failure->actual_expr   = actual_expr;
    failure->expected_val  = expected_val;
    failure->actual_expr   = actual_val;

    return true;
}

void LIBCURRENT_testfailure_finalize(LIBCURRENT_testfailure *failure)
{
    assert(failure != NULL);

    if (failure->expected_val != NULL) {
        free(failure->expected_val);
        failure->expected_val = NULL;
    }

    if (failure->actual_val != NULL) {
        free(failure->actual_val);
        failure->actual_val = NULL;
    }
}

// =============================================================================
// == INTERNAL API =============================================================
// =============================================================================

void LIBCURRENT_context_register(
	LIBCURRENT_context *ctx,
    LIBCURRENT_testimpl test,
	const char         *name)
{
    assert(ctx  != NULL);
    assert(test != NULL);
    assert(name != NULL);
    assert(ctx->num_registered_tests < ctx->num_tests);

    size_t i = ctx->num_registered_tests;

    ctx->testcases[i].test              = test;
    ctx->testcases[i].name              = name;
    ctx->statuses[i].num_asserts_run    = 0;
    ctx->statuses[i].num_asserts_failed = 0;
    ctx->num_registered_tests          += 1;

    assert(ctx->num_registered_tests <= ctx->num_tests);
}

void LIBCURRENT_context_run(LIBCURRENT_context *ctx)
{
    assert(ctx != NULL);
    assert(ctx->num_registered_tests == ctx->num_tests);

    LIBCURRENT_threadpool threadpool;
    LIBCURRENT_threadpool_run_tests(&threadpool, ctx);
}

void LIBCURRENT_context_print_summary(const LIBCURRENT_context *ctx)
{
    assert(ctx != NULL);
    assert(ctx->num_registered_tests == ctx->num_tests);

    size_t num_tests = ctx->num_tests;
    size_t num_tests_success = 0;
    size_t num_tests_failure = 0;

    int num_assertions = 0;
    int num_assertions_success = 0;
    int num_assertions_failure = 0;

    for (size_t i = 0; i < num_tests; ++i) {
        LIBCURRENT_teststatus *status = &ctx->statuses[i];

        num_assertions         += status->num_asserts_run;
        num_assertions_success += (status->num_asserts_run - status->num_asserts_failed);
        num_assertions_failure += status->num_asserts_failed;
        
        if (status->num_asserts_failed == 0) {
            num_tests_success += 1;
        } else {
            num_tests_failure += 1;
        }
    }

    printf("====================[ SUMMARY ]====================\n");
    printf("== %zu Test Cases Ran\n", num_tests);
    printf("== => %zu Successes \n",  num_tests_success);
    printf("== => %zu Failures \n",   num_tests_failure);
    printf("== %d Assertions Ran\n",  num_assertions);
    printf("== => %d Successes \n",   num_assertions_success);
    printf("== => %d Failures \n",    num_assertions_failure);
}
