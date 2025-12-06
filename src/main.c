#include "libcurrent/libcurrent_context.h"
#include "libcurrent/libcurrent_platform.h"
#include "libcurrent/libcurrent_types.h"

#include <stdio.h>
#include <stdlib.h>

// =============================================================================
// == ANCHORS ==================================================================
// =============================================================================

// These anchors refer to the start and end of the .test_array (or __test_array)
// section.
//
// That section contains entries registering the actual test.

extern LIBCURRENT_testarrayentry LIBCURRENT_TESTARRAY_BEGIN[] LIBCURRENT_TESTARRAY_BEGIN_ASM;
extern LIBCURRENT_testarrayentry LIBCURRENT_TESTARRAY_END[]   LIBCURRENT_TESTARRAY_END_ASM;

#define LIBCURRENT_NUM_TESTS (LIBCURRENT_TESTARRAY_END - LIBCURRENT_TESTARRAY_BEGIN)

// =============================================================================
// == MAIN =====================================================================
// =============================================================================

int
main(void)
{
	LIBCURRENT_context *ctx = LIBCURRENT_context_create(LIBCURRENT_NUM_TESTS);
	if (ctx == NULL) {
		fprintf(stderr, "[FATAL] Could not create test context\n");
		return EXIT_FAILURE;
	}

	LIBCURRENT_testarrayentry *begin = LIBCURRENT_TESTARRAY_BEGIN;
	LIBCURRENT_testarrayentry *end   = LIBCURRENT_TESTARRAY_END;

	for (LIBCURRENT_testarrayentry *entry = begin; entry < end; ++entry) {
		(*entry)(ctx);
	}

	LIBCURRENT_context_run(ctx);
	LIBCURRENT_context_print_summary(ctx);

	LIBCURRENT_context_destroy(ctx);
	return EXIT_SUCCESS;
}
