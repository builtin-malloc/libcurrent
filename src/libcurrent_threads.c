#include "libcurrent/libcurrent_threads.h"
#include "libcurrent/libcurrent_context.h"

#include <assert.h>
#include <stdio.h>

// =============================================================================
// == CONSTANTS ================================================================
// =============================================================================

#define LIBCURRENT_STATUS_CHAR_PASS '.'
#define LIBCURRENT_STATUS_CHAR_FAIL 'X'
#define LIBCURRENT_STATUS_CHAR_SKIP 'o'

// =============================================================================
// == INTERNAL API =============================================================
// =============================================================================

void LIBCURRENT_threadpool_run_tests(
    LIBCURRENT_threadpool *threadpool,
    LIBCURRENT_context    *context)
{
    assert(threadpool != NULL);
    assert(context    != NULL);

    LIBCURRENT_threadcontext threadcontexts[LIBCURRENT_NUM_THREADS];

    for (size_t i = 0; i < LIBCURRENT_NUM_THREADS; ++i) {
        LIBCURRENT_threadcontext *thread_context = &threadcontexts[i];
        pthread_t                *thread         = &threadpool->threads[i];

        thread_context->context      = context;
        thread_context->thread_index = i;

        pthread_create(thread, NULL, LIBCURRENT_threadpool_worker, thread_context);
    }

    for (size_t i = 0; i < LIBCURRENT_NUM_THREADS; ++i) {
        pthread_join(threadpool->threads[i], NULL);
    }

    putc('\n', stdout);
}

// =============================================================================
// == IMPLEMENTATION ===========================================================
// =============================================================================

void *LIBCURRENT_threadpool_worker(void *arg)
{
    assert(arg != NULL);

    LIBCURRENT_threadcontext *threadcontext = arg;
    LIBCURRENT_context       *context       = threadcontext->context;

    size_t thread_index = threadcontext->thread_index;
    size_t num_tests    = context->num_tests;

    for (size_t i = thread_index; i < num_tests; i += LIBCURRENT_NUM_THREADS) {
        LIBCURRENT_testcase   *testcase = &context->testcases[i];
        LIBCURRENT_teststatus *status   = &context->statuses[i];
        LIBCURRENT_testimpl    testfunc = testcase->test;

        assert(testfunc != NULL);
        testfunc(context, i);

        for (int j = 0; j < status->num_asserts_run; ++j) {
            putc(LIBCURRENT_STATUS_CHAR_PASS, stdout);
        }

        for (int j = 0; j < status->num_asserts_failed; ++j) {
            putc(LIBCURRENT_STATUS_CHAR_FAIL, stdout);
        }
    }

    return NULL;
}
