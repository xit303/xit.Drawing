################################################################################
# Global Project Settings
################################################################################

PROJECT_NAME = test

CC = g++
LD = ld
ASM = g++
AR = ar
AS = as
CP = objcopy
OD = objdump
SIZE = size

################################################################################
# Directories
################################################################################

BIN_DIR = .bin
OBJECT_DIR = $(BIN_DIR)/Debug

################################################################################
# Include Directories
################################################################################

INCLUDES := -Iinclude \
			-I../include \
			-I../OpenGL/glad/include/ \
			-I../OpenGL/glm-0.9.7.1/glm/ \
			-I../FreeType2/include/ \
			-I/usr/include/GLFW/include/ \
			-I/usr/include/ \
			-I/usr/include/freetype2/ \
			-I/usr/include/openssl/ \
			-I/usr/include/gtest/

################################################################################
# Source Files
################################################################################

SRC_DIRS = 	src \
			src/IO \
			src/Security \
			src/Drawing

SRCS = $(foreach dir, $(SRC_DIRS), $(wildcard $(dir)/*.cpp) $(wildcard $(dir)/*.c) $(wildcard $(dir)/*.s))

################################################################################
# Object Files
################################################################################

OBJS = $(patsubst %.cpp, $(OBJECT_DIR)/%.o, $(SRCS)) \
       $(patsubst %.c, $(OBJECT_DIR)/%.o, $(SRCS)) \
       $(patsubst %.s, $(OBJECT_DIR)/%.o, $(SRCS))

# extract only .o files for linker
LINK_OBJS = $(filter %.o, $(OBJS))

################################################################################
# Flags
################################################################################

ALL_FLAGS = -g -std=c++23 -Wall
LINKER_FLAGS = $(PREDEFINED_SYMBOLS)
COMPILER_OPTIONS = $(ALL_FLAGS) $(PREDEFINED_SYMBOLS) $(INCLUDES)
ASSEMBLER_FLAGS = $(ALL_FLAGS) $(PREDEFINED_SYMBOLS) $(INCLUDES)
CPP_FLAGS = $(ALL_FLAGS) $(GPP_MISRA_RULES) $(PREDEFINED_SYMBOLS) $(INCLUDES)

LIBS = /usr/lib/x86_64-linux-gnu/libgtest.a ../$(BIN_DIR)/libxit.so -lglfw -lX11 -lfreetype -lssl -lcrypto

################################################################################
# Default Target
################################################################################

all: $(BIN_DIR)/$(PROJECT_NAME)

################################################################################
# Target Generation
################################################################################

$(BIN_DIR)/$(PROJECT_NAME): $(OBJS)
	@mkdir -p "$(dir $@)" 
	@echo Building target: $@
	$(CC) -o $@ $(LINK_OBJS) $(LINKER_FLAGS) $(LIBS) $(INCLUDES)
	@echo Finished building target: $@

$(OBJECT_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CC) $(DEPFLAGS) $(COMPILER_OPTIONS) $(CPP_FLAGS) -c -o $@ $<
	@echo Finished building: $@

$(OBJECT_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(DEPFLAGS) $(COMPILER_OPTIONS) -c -o $@ $<
	@echo Finished building: $@

$(OBJECT_DIR)/%.o: %.s
	@mkdir -p $(dir $@)
	$(CC) $(DEPFLAGS) $(ASSEMBLER_FLAGS) -c -o $@ $<
	@echo Finished building: $@

################################################################################
# Additional Targets
################################################################################

run:
	@echo Running tests
	./$(BIN_DIR)/test

clean:
	rm -rf $(BIN_DIR)
	-@echo 'Finished clean'

size:
	$(SIZE) $(BIN_DIR)/$(PROJECT_NAME)

info:
	@echo "INCLUDES"
	@echo $(INCLUDES)
	@echo
	@echo "SRCS"
	@echo $(SRCS)
	@echo
	@echo "OBJS"
	@echo $(OBJS)
	@echo
	@echo "CPP_DEPFILES"
	@echo $(CPP_DEPFILES)

.PHONY: all clean size info run