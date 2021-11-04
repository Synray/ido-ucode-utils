default: all

SRC_DIRS := . src src/libp

ENDIAN ?= little

ifeq ($(ENDIAN),little)
CC := gcc
OPTIMIZATION := -O2 -march=native -mtune=native -flto 
#OPTIMIZATION := -ggdb3
CFLAGS := -I src -Wall $(OPTIMIZATION) -DLE
LDFLAGS := $(OPTIMIZATION)
else
CC := mips-linux-gnu-gcc
CFLAGS := -fPIC -I src -mips2 -mfp32 -ggdb3 -Wall -O2
endif

BUILD_DIR := build
ALL_DIRS := $(addprefix $(BUILD_DIR)/,$(SRC_DIRS))

C_FILES := $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.c))
O_FILES := $(addprefix $(BUILD_DIR)/,$(C_FILES:.c=.o))
DEP_FILES := $(O_FILES:.o=.d)

# Ensure build directories exist before compiling anything
DUMMY != mkdir -p $(ALL_DIRS)

TARGET := $(BUILD_DIR)/udis

all: $(TARGET)

$(TARGET): $(O_FILES)
	$(CC) -o $@ $^ $(LDFLAGS)

$(BUILD_DIR)/%.o: %.c
	$(CC) -MMD -c $(CFLAGS) -o $@ $<

clean:
	$(RM) -r $(BUILD_DIR)

.PHONY: all clean default

-include $(DEP_FILES)
