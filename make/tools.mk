# Define tool variables
CC                 := gcc
CXX                := g++
LD                 := ld
GIT                := git

# Patch flags and tools
FLAG_RELRO          = -Wl,-z,relro,-z,now
ifeq ($(PLATFORM),Solaris)
  FLAG_RELRO              =
  LD                      = gld
endif

# Define flags
CFLAGS             := \
  -fdata-sections \
  -ffunction-sections \
  -fno-asynchronous-unwind-tables \
  -fvisibility=hidden \
  -pipe \
  -Wall
  
CXXFLAGS           := \
  -std=c++98 \
  -exceptions \
  -fno-rtti \
  -fdata-sections \
  -ffunction-sections \
  -fno-asynchronous-unwind-tables \
  -fvisibility=hidden \
  -pipe \
  -Wall

INCLUDE            :=
LDFLAGS            := -r
EXE_FLAGS          := $(FLAG_RELRO) -Wl,--gc-sections
SO_FLAGS           := $(FLAG_RELRO) -Wl,--gc-sections -shared -Llibrary -lc -fPIC 


TOOL_VARS := \
  CC CXX LD GIT \
  CFLAGS CXXFLAGS LDFLAGS EXE_FLAGS SO_FLAGS \
  INCLUDE

ifeq ($(TEST),1)
  $CFLAGS            += -DLSP_TESTING
  $CXXFLAGS          += -DLSP_TESTING
endif

.PHONY: toolvars
toolvars:
	@echo "List of tool variables:"
	@echo "  CC                        C compiler execution command line"
	@echo "  CFLAGS                    C compiler build flags"
	@echo "  CXX                       C++ compiler execution command line"
	@echo "  CXXFLAGS                  C++ compiler build flags"
	@echo "  EXE_FLAGS                 Flags to link executable files"
	@echo "  GIT                       The name of the Git version control tool"
	@echo "  INCLUDE                   Additional paths for include files"
	@echo "  LD                        Linker execution command line"
	@echo "  LDFLAGS                   Linker flags for merging object files"
	@echo "  SO_FLAGS                  Flags to link shared object/library files"
	@echo ""
