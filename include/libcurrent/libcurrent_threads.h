#ifndef LIBCURRENT_THREADS_H
#define LIBCURRENT_THREADS_H

#include "libcurrent/libcurrent_types.h"

#include <pthread.h>

// =============================================================================
// == CONSTANTS ================================================================
// =============================================================================

// TODO: Make this configurable
#define LIBCURRENT_NUM_THREADS 8

// =============================================================================
// == TYPES ====================================================================
// =============================================================================

/**
 * @brief Manager for the worker threads
 */
typedef struct LIBCURRENT_threadpool
{
    pthread_t threads[LIBCURRENT_NUM_THREADS];
} LIBCURRENT_threadpool;

/**
 * @brief Argument passed to the worker function
 */
typedef struct LIBCURRENT_threadcontext
{
    LIBCURRENT_context *context;      /**< Contains the tests */
    size_t              thread_index; /**< Determines which tests are handled by this worker */
} LIBCURRENT_threadcontext;

// =============================================================================
// == INTERNAL API =============================================================
// =============================================================================

/**
 * @brief Runs the registered test cases in parallel
 */
void LIBCURRENT_threadpool_run_tests(
    LIBCURRENT_threadpool *threadpool, /**< Threadpool to manage the threads */
    LIBCURRENT_context    *context     /**< Context in which the tests are registered */
);

// =============================================================================
// == IMPLEMENTATION ===========================================================
// =============================================================================

/**
 * @brief Function to run in each thread
 * @param arg Actually a `LIBCURRENT_threadcontext`
 */
void *LIBCURRENT_threadpool_worker(void *arg);

#endif // LIBCURRENT_THREADS_H
