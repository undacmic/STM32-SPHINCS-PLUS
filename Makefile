# Toolchain
CC = arm-none-eabi-gcc
SIZE = arm-none-eabi-size
OBJCOPY = arm-none-eabi-objcopy
STFLASH = st-flash
CPPCHECK = cppcheck

GCCLIB := $(shell $(CC) --print-search-dirs | 	\
		   sed -E -n '/^libraries: =([^:]*)\/.*/s//\1/p')

LIBGCC := $(word 1, $(wildcard 					\
		   $(GCCLIB)/thumb/v6-m/libgcc.a 	  	\
		   $(GCCLIB)/thumb/v6-m/nofp/libgcc.a 	\
		   UNKNOWN))
KECCAC_ROOT_DIR = ./external/XKCP
LIBKECCAC = $(KECCAC_ROOT_DIR)/libXKCP.a

# Directories
BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/obj
BIN_DIR = $(BUILD_DIR)/bin
INCLUDE_DIRS = ./src \
			   ./external/ \
			   ./	

# Files
TARGET_NAME = program.elf
TARGET = $(BIN_DIR)/$(TARGET_NAME)

MAIN_FILE = src/main.c

SOURCES_WITH_HEADERS := $(shell find . \( -path ./src/test  -o -path ./external/XKCP -o -name "main.c" \) -prune -o -name "*.c" -print)
SOURCES =  $(MAIN_FILE) \
		   $(SOURCES_WITH_HEADERS)
HEADERS := $(wildcard $(KECCAC_ROOT_DIR)/libXKCP.a.headers/*.h) \
		$(SOURCES_WITH_HEADERS:.c=.h) \
		./src/common/stm32g0b1re.h

INCLUDES = $(addprefix -I, $(INCLUDE_DIRS))

OBJ_NAMES = $(SOURCES:.c=.o)
OBJECTS := $(addprefix $(OBJ_DIR)/, $(OBJ_NAMES)) 

LINKER_SCRIPT = src/STM32G0B1RE.ld

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
DEFINES = -DPRINTF_INCLUDE_CONFIG_H \
		  -DDISABLE_ENUM_STRINGS \
		  -DDISABLE_TRACE \
		  -DHASH_SHA3

# Flags
WFLAGS = -Wall -Wextra -Wno-override-init -Werror -Wshadow
CFLAGS = -march=armv6-m -mcpu=cortex-m0 -mthumb -mfloat-abi=soft -O0 -g $(INCLUDES) $(DEFINES)
LDFLAGS = -Xlinker -Map=$(BUILD_DIR)/bin/program.map -T $(LINKER_SCRIPT) -nostartfiles -specs=nano.specs -specs=nosys.specs $(INCLUDES) -lc -lgcc -lm

# Linking
$(BIN_DIR)/%.elf: $(OBJECTS)
	@mkdir -p $(dir $@)
	$(CC) $^ $(LIBGCC) $(LIBKECCAC) $(LDFLAGS) -o $@
	$(SIZE) $@

# Compilation
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(WFLAGS) -c -o $@ $^


.PHONY: all clean flash check

all: $(TARGET)

clean:
	rm -rf $(BUILD_DIR)

flash: $(TARGET)
	@openocd -f interface/stlink.cfg -f target/stm32g0x.cfg -c "program $(TARGET) verify reset exit"
 
check:
	$(CPPCHECK) $(CPPCHECK_FLAGS) $(SOURCES_FORMAT_CHECK) 


