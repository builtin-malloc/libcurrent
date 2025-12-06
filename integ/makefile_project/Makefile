LIBSRC  := $(filter-out *test.c,$(wildcard *.c))
TESTSRC := $(filter     *test.c,$(wildcard *.c))
LIBOBJ  := $(LIBSRC:.c=.o)
TESTOBJ := $(TESTSRC:.c=.o)
LIB     := libfib.a
TEST    := test-fib

CC      ?= cc
CCLD    ?= $(CC)
AR      ?= ar
CFLAGS  += -c -std=c99
LDFLAGS += -L. -lfib -L../../bin -lcurrent -lcurrent-main
ARFLAGS := rcs

.PHONY: all clean

all: $(TEST)

$(TEST): $(TESTOBJ) $(LIB)
	$(CCLD) -o $@ $(filter %.o,$^) $(LDFLAGS)
$(LIB): $(LIBOBJ)
	$(AR) $(ARFLAGS) $@ $^

%.o: %.c
	$(CC) -o $@ $< $(CFLAGS) 

clean:
	rm -rf $(LIBOBJ) $(TESTOBJ) $(LIB) $(TEST)

