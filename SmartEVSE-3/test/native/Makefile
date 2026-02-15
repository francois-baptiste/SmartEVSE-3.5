# SmartEVSE-3 Native Test Suite
# Builds and runs state machine tests on macOS/Linux without embedded toolchain
#
# Usage:
#   make          - build all tests
#   make test     - build and run all tests
#   make clean    - remove build artifacts
#   make test_state_transitions  - build+run single suite

CC       ?= cc
CFLAGS   := -std=c11 -Wall -Wextra -Wpedantic -Werror -O0 -g $(CFLAGS_EXTRA)
INCLUDES := -Iinclude -I../../src

SRC_DIR  := ../../src
TEST_DIR := tests
BUILD    := build

# Source files
EVSE_SRC := $(SRC_DIR)/evse_state_machine.c

# Discover all test files
TEST_SRCS := $(wildcard $(TEST_DIR)/test_*.c)
TEST_BINS := $(patsubst $(TEST_DIR)/%.c,$(BUILD)/%,$(TEST_SRCS))
TEST_NAMES := $(patsubst $(TEST_DIR)/test_%.c,%,$(TEST_SRCS))

.PHONY: all test clean help $(TEST_NAMES)

all: $(TEST_BINS)

# Build each test binary
$(BUILD)/test_%: $(TEST_DIR)/test_%.c $(EVSE_SRC) include/*.h $(SRC_DIR)/*.h | $(BUILD)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $(TEST_DIR)/test_$*.c $(EVSE_SRC)

$(BUILD):
	mkdir -p $(BUILD)

# Run all tests
test: $(TEST_BINS)
	@echo ""
	@echo "============================================"
	@echo "  SmartEVSE-3 Native Test Suite"
	@echo "============================================"
	@total_pass=0; total_fail=0; total_suites=0; failed_suites=""; \
	for bin in $(TEST_BINS); do \
		total_suites=$$((total_suites + 1)); \
		if $$bin; then \
			total_pass=$$((total_pass + 1)); \
		else \
			total_fail=$$((total_fail + 1)); \
			failed_suites="$$failed_suites $$(basename $$bin)"; \
		fi; \
	done; \
	echo ""; \
	echo "============================================"; \
	echo "  TOTAL: $$total_suites suites, $$total_pass passed, $$total_fail failed"; \
	if [ $$total_fail -gt 0 ]; then \
		echo "  FAILED:$$failed_suites"; \
		echo "============================================"; \
		exit 1; \
	else \
		echo "  ALL SUITES PASSED"; \
		echo "============================================"; \
	fi

# Convenience targets: make <suite_name> runs that suite
$(TEST_NAMES): %: $(BUILD)/test_%
	@$(BUILD)/test_$*

clean:
	rm -rf $(BUILD)

help:
	@echo "Available targets:"
	@echo "  make          - build all tests"
	@echo "  make test     - build and run all tests"
	@echo "  make clean    - remove build artifacts"
	@echo ""
	@echo "Individual suites:"
	@for name in $(TEST_NAMES); do echo "  make $$name"; done
