# Toolchain
CC = arm-none-eabi-gcc
SIZE = arm-none-eabi-size
OBJCOPY = arm-none-eabi-objcopy
STFLASH = st-flash
CPPCHECK = cppcheck
CXX = g++

# Directories
BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/obj
BIN_DIR = $(BUILD_DIR)/bin
INCLUDE_DIRS = ./src/ \
				./
# Files
TARGET = $(BIN_DIR)/program.elf
MAIN_FILE = src/main.c

SOURCES_WITH_HEADERS := $(shell find . \( -path ./src/test  -o -path ./lib/XKCP -o -name "main.c" \) -prune -o -name "*.c" -print)
SOURCES =  $(MAIN_FILE) \
		   $(SOURCES_WITH_HEADERS)

INCLUDES = $(addprefix -I, $(INCLUDE_DIRS))

OBJ_NAMES = $(SOURCES:.c=.o)
OBJECTS := $(addprefix $(OBJ_DIR)/, $(OBJ_NAMES)) 

LINKER_SCRIPT = src/STM32G0B1RE.ld

# Tests
GTEST_INCLUDE_DIRS = /usr/local/include/gtest/ \
					./lib/XKCP/generic64/libXKCP.a.headers/ \
					 $(INCLUDE_DIRS)
GTEST_INCLUDES := $(addprefix -I, $(GTEST_INCLUDE_DIRS))

TEST_SOURCES := $(shell find ./src/common -name "*.c" -print)
UNIT_TESTS := $(shell find ./src/test -name "*.cpp" -print)
TESTS = $(UNIT_TESTS) \
		$(TEST_SOURCES)
TEST_OBJECTS = $(notdir $(UNIT_TESTS:.cpp=.o)) \
			   $(notdir $(TEST_SOURCES:.c=.o))

# Static Analysis
CPPCHECK_INCLUDES = ./src
IGNORE_FILES := $(shell find ./external -name "*.c")
SOURCES_FORMAT_CHECK := $(filter-out $(IGNORE_FILES), $(SOURCES))
CPPCHECK_FLAGS = \
	--quiet --enable=all --error-exitcode=1 \
	--inline-suppr \
	--suppress=missingIncludeSystem \
	--suppress=unmatchedSuppression \
	--suppress=unusedFunction \
	--checkers-report=cppcheck.report \
	$(addprefix -I,$(CPPCHECK_INCLUDES)) \

# Defines
DEFINES = -DDISABLE_ENUM_STRINGS \
		  -DDISABLE_TRACE \
		  -DHASH_SHA3

# Flags
WFLAGS = -Wall -Wextra -Wno-override-init -Werror
CFLAGS = -march=armv6-m -mcpu=cortex-m0 -mthumb -mfloat-abi=soft -O0 -g $(INCLUDES) $(DEFINES)
LDFLAGS = -Xlinker -Map=$(BUILD_DIR)/bin/program.map \
		  -T $(LINKER_SCRIPT) \
		  -nostartfiles \
		  -specs=nano.specs \
		  -specs=nosys.specs \
		  -L./lib/XKCP/armv6-m/ -lXKCP

CXXWFLAGS = -Wall -Wextra -Werror
CXXFLAGS = -fprofile-arcs -ftest-coverage -DTEST_SETUP -DHASH_SHA3
CXXLDFLAGS = -L/usr/local/lib -lgtest -L./lib/XKCP/generic64 -lXKCP

# Linking
$(BIN_DIR)/%.elf: $(OBJECTS)
	@mkdir -p $(dir $@)
	$(CC) $^ $(LDFLAGS) -o $@
	$(SIZE) $@

# Compilation
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(WFLAGS) -c -o $@ $^

.PHONY: all clean flash check test

all: $(BIN_DIR)/program.elf

clean:
	rm -rf $(BUILD_DIR)

flash: $(TARGET)
	@openocd -f interface/stlink.cfg -f target/stm32g0x.cfg -c "program $(TARGET) verify reset exit"
 
check:
	$(CPPCHECK) $(CPPCHECK_FLAGS) $(SOURCES_FORMAT_CHECK)

test:
	@mkdir -p $(BIN_DIR)
	@for FILE in $(TESTS); do \
		$(CXX) $(GTEST_INCLUDES) $(CXXFLAGS) $(CXXWFLAGS) -c $$FILE; \
	done
	$(CXX) -o $(BIN_DIR)/test $(CXXFLAGS) $(CXXWFLAGS) $(TEST_OBJECTS) $(CXXLDFLAGS) && \
	./$(BIN_DIR)/test
	@gcovr --exclude src/test/ -d --html --html-details -o coverage.html && \
	rm *.o *.gcno

list:
	echo $(TARGET)