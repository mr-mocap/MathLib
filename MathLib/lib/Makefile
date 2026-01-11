BUILD_DIR = build
LIB_BASENAME = Math
LIB_NAME  = lib$(LIB_BASENAME).a
LIB_PATH  = $(BUILD_DIR)

INCLUDE_DIR = ./include
SRC_DIR     = ./src/$(LIB_BASENAME)
INC_PARAMS  = $(INCLUDE_DIR:%=-I%) -I.
DEBUG_FLAGS = -g3

CXXFLAGS=-std=c++20 -W -Wall -pedantic -MMD -MP $(INC_PARAMS) $(DEBUG_FLAGS)

TARGET = $(LIB_PATH)/$(LIB_NAME)

LIB_SRC = $(wildcard $(SRC_DIR)/color/*.cpp)

LIB_OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,${LIB_SRC})

LIB_DEP  = $(patsubst $(BUILD_DIR)/%.o,$(BUILD_DIR)/%.d,${LIB_OBJS})

.PHONY: all
all: lib

default: lib

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

.PHONY: lib
lib: $(TARGET) | $(BUILD_DIR)

$(TARGET): $(LIB_OBJS)
	@ar -crs $@ $(LIB_OBJS)
	@ranlib $@

$(BUILD_DIR)/%.o : $(SRC_DIR)/%.cpp
	@mkdir -p ${dir $@}
	$(CXX) -o $@ $< -c $(CPPFLAGS) $(CXXFLAGS)

.PHONY: clean
clean:
	@rm -rf $(BUILD_DIR)

-include $(LIB_DEP)