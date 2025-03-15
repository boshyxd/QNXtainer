ARTIFACT_TYPE = exe
PROJECT_NAME = QNXtainer

LDFLAGS_shared = -shared -o
ARTIFACT_NAME_shared = lib$(PROJECT_NAME).so

LDFLAGS_static = -static -a
ARTIFACT_NAME_static = lib$(PROJECT_NAME).a

LDFLAGS_exe = -o
ARTIFACT_NAME_exe = $(PROJECT_NAME)

ARTIFACT = $(ARTIFACT_NAME_$(ARTIFACT_TYPE))

PLATFORM ?= x86_64

BUILD_PROFILE ?= debug

CONFIG_NAME ?= $(PLATFORM)-$(BUILD_PROFILE)
OUTPUT_DIR = build/$(CONFIG_NAME)
TARGET = $(OUTPUT_DIR)/$(ARTIFACT)


CC = qcc
CFLAGS = -Wall -fmessage-length=0 -fPIC
LDFLAGS = 

BUILD_PROFILE ?= debug
PLATFORM ?= x86_64

SRC_DIR = src
BUILD_DIR = build/$(PLATFORM)-$(BUILD_PROFILE)
BIN_DIR = bin/$(PLATFORM)-$(BUILD_PROFILE)

RUNTIME_SRC = $(wildcard $(SRC_DIR)/runtime/*.c)
CLI_SRC = $(SRC_DIR)/cli/main.c

RUNTIME_OBJ = $(patsubst $(SRC_DIR)/runtime/%.c,$(BUILD_DIR)/runtime/%.o,$(RUNTIME_SRC))
CLI_OBJ = $(BUILD_DIR)/cli/main.o

TARGET = $(BIN_DIR)/qnxtainer

ifeq ($(BUILD_PROFILE),debug)
CFLAGS += -g -O0 -fno-builtin
else
CFLAGS += -O2
endif

ifeq ($(PLATFORM),x86_64)
CC_OPTS = -Vgcc_ntox86_64
else ifeq ($(PLATFORM),aarch64)
CC_OPTS = -Vgcc_ntoaarch64
else
$(error Unsupported platform: $(PLATFORM))
endif

all: directories $(TARGET)

directories:
	@mkdir -p $(BUILD_DIR)/runtime
	@mkdir -p $(BUILD_DIR)/cli
	@mkdir -p $(BIN_DIR)

$(BUILD_DIR)/runtime/%.o: $(SRC_DIR)/runtime/%.c
	$(CC) $(CC_OPTS) -c $(CFLAGS) -Wp,-MMD,$(@:.o=.d),-MT,$@ -o $@ $<

$(BUILD_DIR)/cli/%.o: $(SRC_DIR)/cli/%.c
	$(CC) $(CC_OPTS) -c $(CFLAGS) -Wp,-MMD,$(@:.o=.d),-MT,$@ -o $@ $<

$(TARGET): $(RUNTIME_OBJ) $(CLI_OBJ)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CC_OPTS) $(LDFLAGS) $^ -o $@

clean:
	rm -rf build bin

-include $(RUNTIME_OBJ:.o=.d) $(CLI_OBJ:.o=.d)

.PHONY: all clean directories