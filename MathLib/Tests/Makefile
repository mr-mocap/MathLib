INCLUDE_DIRS  = ../lib/include
LIB_BUILD_DIR = ../lib/build
LIB_BASENAME  = Math
LIB_NAME      = $(LIB_BASENAME).a
LIB_TARGET    = $(LIB_BUILD_DIR)/$(LIB_NAME)
INC_PARAMS = $(INCLUDE_DIRS:%=-I%)
DEBUG_FLAGS = -g3

EXTERNAL_LIBS = -lMath
CXXFLAGS      = -std=c++20 -W -Wall -Wextra -MMD -MP -pedantic -I . $(INC_PARAMS) $(DEBUG_FLAGS)
LDFLAGS       = -L$(LIB_BUILD_DIR)

TESTS = Angle \
	ColorConversion \
	ColorTypes \
	DualNumber \
	DualQuaternion \
	HierarchicalCoordinateSystem \
	Quaternion \
	SceneNode \
	Vector2D \
	Vector3D

TEST_BINARIES = $(patsubst %,Test%,${TESTS})
PASSING_TESTS = $(patsubst %,%.pass,${TEST_BINARIES})

default: all

$(LIB_TARGET): 
	@$(MAKE) --directory=.. lib --quiet

lib: $(LIB_TARGET)

all: lib $(PASSING_TESTS)

.PHONY: clean
clean:
	@rm -f ./*.o
	@rm -f ./*.d
	@rm -f $(TEST_BINARIES)
	@rm -f $(PASSING_TESTS)

.PHONY: cleanlib
cleanlib:
	@$(MAKE) --directory=.. cleanlib --quiet

$(TEST_BINARIES): %: %.cpp
	@echo -n $@ [BUILDING] ...
	@$(CXX) -o $@ $< $(CPPFLAGS) $(CXXFLAGS) $(LDFLAGS) $(EXTERNAL_LIBS)

$(PASSING_TESTS): %.pass: %
	@./$< >/dev/null 2>/dev/null
	@echo [PASSED]
	@touch $@

-include *.d
