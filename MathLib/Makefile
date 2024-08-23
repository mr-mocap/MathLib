INCLUDE_DIRS = ./include

INC_PARAMS = $(INCLUDE_DIRS:%=-I%)
DEBUG_FLAGS = -g3

CXXFLAGS=-std=c++20 -W -Wall -pedantic -I . $(INC_PARAMS) $(DEBUG_FLAGS)

TEST_OBJS = MathLib.o \
            DualNumberTests.o \
            DualQuaternionTests.o \
            HierarchicalCoordinateSystemTests.o \
            QuaternionTests.o \
            SceneNodeTests.o

TEST_EXE  = code_tests

default: run_tests

$(TEST_EXE): $(TEST_OBJS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $^ -o $(TEST_EXE) $(LDFLAGS)

.PHONY: test
test: $(TEST_EXE)

run_tests: $(TEST_EXE)
	./$(TEST_EXE)

.PHONY: clean
clean:
	rm -f $(TEST_OBJS) $(TEST_EXE)

