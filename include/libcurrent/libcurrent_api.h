#ifndef LIBCURRENT_API_H
#define LIBCURRENT_API_H

#include "libcurrent/libcurrent_platform.h"
#include "libcurrent/libcurrent_types.h"

// =============================================================================
// == MACROS ===================================================================
// =============================================================================

/**
 * @brief Define a test case.
 */
#define I_TEST(Name) \
    void LIBCURRENT_TESTCASE_##Name(LIBCURRENT_context *ctx);               \
    void LIBCURRENT_TESTIMPL_##Name(LIBCURRENT_context *ctx, size_t index); \
    \
    void LIBCURRENT_TESTCASE_##Name(LIBCURRENT_context *ctx) \
    { \
        LIBCURRENT_context_register(ctx, LIBCURRENT_TESTIMPL_##Name, #Name); \
    } \
    LIBCURRENT_testarrayentry LIBCURRENT_TESTENTRY_##Name LIBCURRENT_TESTARRAY_ATTRIBUTE = LIBCURRENT_TESTCASE_##Name; \
    \
    void LIBCURRENT_TESTIMPL_##Name(                    \
        LIBCURRENT_context *LIBCURRENT_CURRENT_CONTEXT, \
        size_t              LIBCURRENT_CURRENT_INDEX)

#endif // LIBCURRENT_API_H
