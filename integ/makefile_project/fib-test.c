#include "fib.h"

#include "libcurrent/libcurrent.h"

#include <stdio.h>

I_TEST(fib_for_a_few_values) {
    LIBCURRENT_CURRENT_CONTEXT->statuses[LIBCURRENT_CURRENT_INDEX].num_asserts_run    = 20;
    LIBCURRENT_CURRENT_CONTEXT->statuses[LIBCURRENT_CURRENT_INDEX].num_asserts_failed = 2;
}

I_TEST(fib_for_a_few_other_values) {
    LIBCURRENT_CURRENT_CONTEXT->statuses[LIBCURRENT_CURRENT_INDEX].num_asserts_run    = 10;
    LIBCURRENT_CURRENT_CONTEXT->statuses[LIBCURRENT_CURRENT_INDEX].num_asserts_failed = 0;
}

I_TEST(fib_for_a_few_invalid_values) {
    LIBCURRENT_CURRENT_CONTEXT->statuses[LIBCURRENT_CURRENT_INDEX].num_asserts_run    = 1;
    LIBCURRENT_CURRENT_CONTEXT->statuses[LIBCURRENT_CURRENT_INDEX].num_asserts_failed = 0;
}
