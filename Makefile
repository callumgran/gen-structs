# Nicolai Brand (lytix.dev), Callum Gran 2022-2023
# See LICENSE for license info

OBJDIR = .obj
TESTDIR = tests
SRC = datastructures

DIRS := $(shell find $(SRC) $(TESTDIR) -type d)

SRCS := $(shell find $(SRC) -type f -name "*.c")
BENCHSRCS := $(shell find $(TESTDIR) -type f -name "*.c")

OBJS := $(SRCS:%.c=$(OBJDIR)/%.o)
BENCHOBJS := $(BENCHSRCS:%.c=$(OBJDIR)/%.o)

CFLAGS = -Iinclude -Wall -Wextra -Wshadow -std=c11

.PHONY: format clean tags bear $(OBJDIR)
TARGET_STACK_TEST = stack_test

clean:
	rm -rf $(OBJDIR) $(TARGET_STACK_TEST)

tags:
	@ctags -R

bear:
	@bear -- make

format:
	python format.py

stack_test:
	$(CC) ./datastructures/stack.c ./tests/stack_test.c $(CFLAGS) -o $(TARGET_STACK_TEST)

$(OBJDIR):
	$(foreach dir, $(DIRS), $(shell mkdir -p $(OBJDIR)/$(dir)))

$(OBJDIR)/%.o: ./%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/$(TESTDIR)/%.o: $(TESTDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@