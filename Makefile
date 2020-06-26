# platform and YAHAL location
PLATFORM  = msp432
YAHAL_DIR = vendor/YAHAL
DSLITE=~/ti/ccs1000/ccs/ccs_base/DebugServer/bin/DSLite

# name of final target
TARGET = main.out

# folder for build artifacts
# (same as eclipse build folder)
BUILD_DIR = build

# all source folders of our project
SRC_DIRS = src

# include dirs
INC_DIRS += $(YAHAL_DIR)/src/platform/$(PLATFORM)
INC_DIRS += $(YAHAL_DIR)/include/interface
INC_DIRS += $(YAHAL_DIR)/src/driver
INC_DIRS += $(YAHAL_DIR)/src/util
INC_DIRS += vendor
INC_DIRS += include

# linked in libraries
LINK_LIBS = $(YAHAL_DIR)/libYAHAL_msp432.a

FLAGS_CXX = -Wall -Wextra -pedantic -pedantic-errors -fno-threadsafe-statics -fno-exceptions -std=c++2a
# FLAGS_CXX = -Wall -Wextra -fno-threadsafe-statics -fno-exceptions -std=c++14



##########################
# Platform configuration #
##########################

# Toolchain location
TOOLCHAIN_PATH   = /usr
TOOLCHAIN_PREFIX = arm-none-eabi

# Various path variables
MSP_INC_DIR = $(YAHAL_DIR)/include/platform/$(PLATFORM)

# Flag helper variables
FLAGS_F        += -ffunction-sections -fdata-sections -fno-unwind-tables -fno-asynchronous-unwind-tables
FLAGS_F		   += -fno-strict-aliasing
FLAGS_M        += -mcpu=cortex-m4 -march=armv7e-m -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -mabi=aapcs
FLAGS_DEBUG    += #-g -gdwarf-3 -gstrict-dwarf
FLAGS_WARN     += -Wall -Wextra
FLAGS_OPT      += -Os

FLAGS_C         =
FLAGS_ASM       =

LN_SCRIPT_FLASH = msp432p401r.lds
FLAGS_LD        = -Wl,-T$(MSP_INC_DIR)/$(LN_SCRIPT_FLASH)
FLAGS_LD       += -Wl,-Map,$(basename $(TARGET)).map
FLAGS_LD       += -Wl,--gc-sections

# Cross-tools
#############
CC      = $(TOOLCHAIN_PATH)/bin/$(TOOLCHAIN_PREFIX)-gcc
CXX     = $(TOOLCHAIN_PATH)/bin/$(TOOLCHAIN_PREFIX)-g++
LD      = $(TOOLCHAIN_PATH)/bin/$(TOOLCHAIN_PREFIX)-g++
AR      = $(TOOLCHAIN_PATH)/bin/$(TOOLCHAIN_PREFIX)-ar
RANLIB  = $(TOOLCHAIN_PATH)/bin/$(TOOLCHAIN_PREFIX)-ranlib

# Compiler/Linker flags ans libraries
#####################################
CXXFLAGS = $(FLAGS_F) $(FLAGS_M) $(FLAGS_DEBUG) $(FLAGS_WARN) $(FLAGS_OPT) $(FLAGS_CXX)
CFLAGS   = $(FLAGS_F) $(FLAGS_M) $(FLAGS_DEBUG) $(FLAGS_WARN) $(FLAGS_OPT) $(FLAGS_C)
ASMFLAGS = $(FLAGS_M) $(FLAGS_DEBUG) $(FLAGS_ASM)
LDFLAGS  = $(CXXFLAGS) $(FLAGS_LD) $(LIBS)
#LIBS     = -lstdc++ -lgcc -lc -lm -lnosys
LIBS     = -lstdc++_nano -lgcc -lc_nano -lm -lnosys

# Compiler defines
##################
DEFINES   = -D__MSP432P401R__ -DTARGET_IS_MSP432P4XX
DEFINES  += -DARM_MATH_CM4 -D__FPU_PRESENT=1
#DEFINES += -DNDEBUG

# Platform includes
###################
PLATFORM_INC_DIRS  = $(MSP_INC_DIR)
PLATFORM_INC_DIRS += $(MSP_INC_DIR)/CMSIS

# Additional rules (e.g. for upload)
####################################
define PLATFORM_RULES
.PHONY: upload
upload: all
	$(DSLITE) load -c $(MSP_INC_DIR)/MSP432P401R.ccxml -f $(TARGET)
endef

#####################
## GENERIC SECTION ##
#####################

# Utility to control output (detailed if VERBOSE defined).
ifdef VERBOSE
HIDE :=
else
HIDE := @
endif

# all source files
SOURCES += $(foreach dir, $(SRC_DIRS), $(wildcard $(dir)/*.cpp))
SOURCES += $(foreach dir, $(SRC_DIRS), $(wildcard $(dir)/*.c  ))
SOURCES += $(foreach dir, $(SRC_DIRS), $(wildcard $(dir)/*.S  ))
# all objects files
OBJECTS  = $(foreach obj, $(SOURCES), $(BUILD_DIR)/$(notdir $(obj)).o)
# all dependency files
DEPS     = $(OBJECTS:.o=.d)
# all include flags
INCLUDES += $(foreach dir, $(INC_DIRS), -I$(dir)) 
INCLUDES += $(foreach dir, $(PLATFORM_INC_DIRS), -I$(dir))

#####################
### RULES section ###
#####################

# Unix commands
RM        = rm -f
RMDIR     = rm -rf
MKDIR     = mkdir -p
MAKE      = make
ERRIGNORE = 2>/dev/null

# Indicate to make which targets are not files
.PHONY: all clean directories

all: directories $(TARGET)

# rule for executable targets
%.out : $(OBJECTS) $(LINK_LIBS) $(LINK_DEPS)
	@echo "LD  $@"
	$(HIDE) $(LD) $(LDFLAGS) -Wl,--start-group $(OBJECTS) $(LINK_LIBS) $(LIBS) -Wl,--end-group -o $@

# rule for library targets
%.a :   $(OBJECTS)
	@echo "AR  $@"
	$(HIDE) $(AR) cru $@ $^
	$(HIDE) $(RANLIB) $@

# compiler rules
define compileRules
$(BUILD_DIR)/%.cpp.o : $(1)/%.cpp
	@echo "C++ $$(notdir $$<)"
	$$(eval EXTRA_FLAGS := $$(shell cat $$(dir $$<)CPPFLAGS 2>/dev/null))
	$(HIDE) $$(CXX) $$(DEFINES) $$(INCLUDES) $$(CXXFLAGS) $$(EXTRA_FLAGS) -c -o $$@ $$< -MMD

$(BUILD_DIR)/%.c.o : $(1)/%.c
	@echo "C   $$(notdir $$<)"
	$$(eval EXTRA_FLAGS := $$(shell cat $$(dir $$<)CFLAGS 2>/dev/null))
	$(HIDE) $$(CC)  $$(DEFINES) $$(INCLUDES) $$(CFLAGS) $$(EXTRA_FLAGS) -c -o $$@ $$< -MMD

$(BUILD_DIR)/%.S.o : $(1)/%.S
	@echo "ASM $$(notdir $$<)"
	$$(eval EXTRA_FLAGS := $$(shell cat $$(dir $$<)ASMFLAGS 2>/dev/null))
	$(HIDE) $$(CC)  $$(DEFINES) $$(INCLUDES) $$(ASMFLAGS) $$(EXTRA_FLAGS) -c -o $$@ $$< -MMD
endef
$(foreach srcdir, $(SRC_DIRS), $(eval $(call compileRules, $(srcdir))))

# rules for link-in libraries
define libraryRule
$(1):
	@echo "Building $$(notdir $(1))"
	$(HIDE) $(MAKE) PLATFORM=$(PLATFORM) -C $$(dir $(1)) all
endef
$(foreach lib, $(LINK_LIBS), $(eval $(call libraryRule, $(lib))))

# create needed directories
directories:
	$(HIDE) $(MKDIR) $(BUILD_DIR) $(ERRIGNORE)

# 'clean up'-rule
clean:
	@echo "Cleaning files ..."
	$(HIDE) $(RM) $(basename $(TARGET)).* *~ $(ERRIGNORE)
	$(HIDE) $(RMDIR) $(BUILD_DIR) $(ERRIGNORE)

# include the platform-specific rules
$(eval $(PLATFORM_RULES))

# include the dependency files
-include $(DEPS)
