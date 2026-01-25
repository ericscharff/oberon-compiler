BUILDDIR=build
CFLAGS=-g -std=c17 -Wall -Wextra -Wpedantic
TEST_CFLAGS=$(CFLAGS) -Wno-unused-parameter
CXXFLAGS=-g -Wall -Wextra -Wpedantic
TEST_CXXFLAGS=$(CXXFLAGS) -Wno-unused-parameter

RUNTIME=base/runtime.c
COMPILER_SRCS=$(wildcard compiler/*.ob) $(RUNTIME)
TEST_SRCS=$(wildcard tests/*.ob)
C_TEST_BINS=$(patsubst tests/%.ob, $(BUILDDIR)/c_test_%, $(TEST_SRCS))
C_BOUNDS_TEST_BINS=$(patsubst tests/%.ob, $(BUILDDIR)/c_bounds_test_%, $(TEST_SRCS))
CXX_TEST_BINS=$(patsubst tests/%.ob, $(BUILDDIR)/cpp_test_%, $(TEST_SRCS))
RISC_TEST_BINS=$(patsubst tests/%.ob, $(BUILDDIR)/risc_test_%, $(TEST_SRCS))
TEST_NAMES=$(patsubst tests/%.ob, %, $(TEST_SRCS))

$(BUILDDIR)/c_test_%: tests/%.ob $(BUILDDIR)/oberon
	$(BUILDDIR)/oberon $(<) > $(BUILDDIR)/$(*).c
	$(CC) $(TEST_CFLAGS) -o $(@) -Ibase $(BUILDDIR)/$(*).c

$(BUILDDIR)/c_bounds_test_%: tests/%.ob $(BUILDDIR)/oberon
	$(BUILDDIR)/oberon -bounds $(<) > $(BUILDDIR)/$(*)_bounds.c
	$(CC) $(TEST_CFLAGS) -o $(@) -Ibase $(BUILDDIR)/$(*)_bounds.c

$(BUILDDIR)/cpp_test_%: tests/%.ob $(BUILDDIR)/oberon
	$(BUILDDIR)/oberon -cpp $(<) > $(BUILDDIR)/$(*).cpp
	$(CXX) $(TEST_CXXFLAGS) -o $(@) -Ibase $(BUILDDIR)/$(*).cpp

$(BUILDDIR)/risc_test_%: tests/%.ob $(BUILDDIR)/oberonr risc_runner/runner.c
	$(BUILDDIR)/oberonr -dumpcode $(<) > $(BUILDDIR)/$(*)_risc_code.txt
	$(CC) $(CFLAGS) -o $(@) -DMAX_MEM=65536 -DCODE_FILE=\"$(*)_risc_code.txt\" -I$(BUILDDIR) risc_runner/runner.c

$(BUILDDIR)/oberonr: $(BUILDDIR)/oberon $(COMPILER_SRCS)
	$(BUILDDIR)/oberon compiler/RCompiler.ob > $(BUILDDIR)/rcompiler.c
	$(CC) $(CFLAGS) -o $(@) -Ibase $(BUILDDIR)/rcompiler.c

$(BUILDDIR)/oberon: $(BUILDDIR)/oberon1 $(COMPILER_SRCS)
	$(BUILDDIR)/oberon1 compiler/Compiler.ob > $(BUILDDIR)/compiler.c
	$(CC) $(CFLAGS) -o $(@) -Ibase $(BUILDDIR)/compiler.c
	# Final test, compiler should compile itself
	$(@) compiler/Compiler.ob > $(BUILDDIR)/compiler_self.c
	diff $(BUILDDIR)/compiler_self.c $(BUILDDIR)/compiler.c

$(BUILDDIR)/oberon1: $(BUILDDIR)/oberon0 $(COMPILER_SRCS)
	$(BUILDDIR)/oberon0 compiler/Compiler.ob > $(BUILDDIR)/compiler0.c
	$(CC) $(CFLAGS) -o $(@) -Ibase $(BUILDDIR)/compiler0.c

$(BUILDDIR)/oberon0: risc_runner/runner.c risc_bootstrap/risc_code.txt | $(BUILDDIR)
	$(CC) $(CFLAGS) -DMAX_MEM=624288 -Irisc_bootstrap -o $(@) $(<)

$(BUILDDIR):
	mkdir -p $(BUILDDIR)

clean:
	rm -rf build

test: $(C_TEST_BINS) \
	$(C_BOUNDS_TEST_BINS) \
	$(CXX_TEST_BINS) \
	$(RISC_TEST_BINS)
	@echo "Running all tests"
	@for test_name in $(TEST_NAMES); do \
		echo "Running $$test_name"; \
		./$(BUILDDIR)/c_test_$$test_name < tests/stdin.txt > $(BUILDDIR)/$$test_name.output 2>&1 ; \
		diff $(BUILDDIR)/$$test_name.output tests/goldens/$$test_name.output || exit 1; \
		echo "Running $$test_name (Bounds checking)"; \
		./$(BUILDDIR)/c_bounds_test_$$test_name < tests/stdin.txt > $(BUILDDIR)/$$test_name.output 2>&1 ; \
		diff $(BUILDDIR)/$$test_name.output tests/goldens/$$test_name.output || exit 1; \
		echo "Running $$test_name (RISC)"; \
		./$(BUILDDIR)/risc_test_$$test_name < tests/stdin.txt > $(BUILDDIR)/$$test_name.output 2>&1 ; \
		diff $(BUILDDIR)/$$test_name.output tests/goldens/$$test_name.output || exit 1; \
		echo "Running $$test_name (C++)"; \
		./$(BUILDDIR)/cpp_test_$$test_name < tests/stdin.txt > $(BUILDDIR)/$$test_name.output 2>&1 ; \
		diff $(BUILDDIR)/$$test_name.output tests/goldens/$$test_name.output || exit 1; \
	done
	@echo "All tests passed"
