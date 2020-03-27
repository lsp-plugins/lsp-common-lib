CONFIG                 := $(CURDIR)/.config.mk

include $(CONFIG)
include $(CURDIR)/../project.mk

rwildcard				= $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2) $(filter $(subst *,%,$2),$d))
CXX_SRC                 = $(call rwildcard, main, *.cpp)
CXX_OBJ                 = $(patsubst %.cpp, $($(ARTIFACT_VARS)_BIN)/%.o, $(CXX_SRC))
CXX_FILE                = $(patsubst $($(ARTIFACT_VARS)_BIN)/%.o,%.cpp, $(@))

ARTIFACT_BIN            = $($(ARTIFACT_VARS)_BIN)
ARTIFACT_LIB            = $(ARTIFACT_BIN)/$($(ARTIFACT_VARS)_NAME)-$($(ARTIFACT_VARS)_VERSION)$(LIBRARY_EXT)
ARTIFACT_TEST           = $(ARTIFACT_BIN)/$($(ARTIFACT_VARS)_NAME)-$($(ARTIFACT_VARS)_VERSION)-test$(EXECUTABLE_EXT)
ARTIFACT_OBJ            = $($(ARTIFACT_VARS)_OBJ)

INCLUDE_DEPS            = $(foreach dep, $(DEPENDENCIES) $(ARTIFACT_VARS), $(if $($(dep)_INC), -I$($(dep)_INC)))
BUILD_DEPS              = $(foreach dep, $(DEPENDENCIES), $(if $($(dep)_OBJ), $(dep)))
LINKER_OBJS             = $(foreach dep, $(DEPENDENCIES), $(if $($(dep)_OBJ), $($(dep)_OBJ)))
LINKER_LIBS             = $(foreach dep, $(DEPENDENCIES), $(if $($(dep)_LIB), $($(dep)_LIB)))
BUILD_ALL               = $(ARTIFACT_LIB)

ifeq ($(TEST),1)
  CXX_SRC                += $(call rwildcard, test, *.cpp)
  BUILD_ALL              += $(ARTIFACT_TEST)
endif

.DEFAULT_GOAL = all
.PHONY: compile depend all
.PHONY: $(BUILD_DEPS)

compile: $(ARTIFACT_OBJ)

all: $(BUILD_ALL)

depend:
	$(foreach dep,$(DEPENDENCIES) $(ARTIFACT_VARS),\
	  $(if $($(dep)_INC), \
	    $(eval SED_RULES += s/$(shell echo "$($(dep)_INC)" | sed "s/\\//\\\\\//g")/\$$$$\\($(dep)_INC\\)/g;)\
	  )\
	  $(if $($(dep)_BIN), \
	    $(eval SED_RULES += s/$(shell echo "$($(dep)_BIN)" | sed "s/\\//\\\\\//g")/\\$$$$\\($(dep)_BIN\\)/g;)\
	  )\
	)
	$(foreach dep, $(DEPENDENCIES), \
	  $(if $($(dep)_OBJ), \
	    $(MAKE) -s -C "$($(@)_PATH)" depend CONFIG="$(CONFIG)"\
	  ) \
	)
	@$(CXX) -MM -MF "$(ARTIFACT_BIN)/Makefile.deps" $(CXX_SRC) $(CXXFLAGS) $(INCLUDE) $(INCLUDE_DEPS)
	@sed -E "$(SED_RULES)" "$(ARTIFACT_BIN)/Makefile.deps" >Makefile.d
	@-rm "$(ARTIFACT_BIN)/Makefile.deps"

$(BUILD_DEPS):
	@echo "$(MAKE) $(notdir $($(@)_OBJ))"
	@$(MAKE) -s -C "$($(@)_PATH)" compile CONFIG="$(CONFIG)"

$(ARTIFACT_OBJ): $(BUILD_DEPS) $(CXX_OBJ)
	@echo "  $(LD)   $(notdir $(ARTIFACT_OBJ))"
	@$(LD) -o $(ARTIFACT_OBJ) -r $(CXX_OBJ)

$(ARTIFACT_LIB): $(ARTIFACT_OBJ)
	@echo "  $(CXX)  $(notdir $(ARTIFACT_LIB))"
	@$(CXX) -o $(ARTIFACT_LIB) $(LINKER_OBJS) $(ARTIFACT_OBJ) $(SO_FLAGS) $(LINKER_LIBS)

$(ARTIFACT_TEST): $(ARTIFACT_OBJ)
	@echo "  $(CXX)  $(notdir $(ARTIFACT_TEST))"
	@$(CXX) -o $(ARTIFACT_TEST) $(LINKER_OBJS) $(ARTIFACT_OBJ) $(EXE_FLAGS) $(LINKER_LIBS)

$(CXX_OBJ):
	@echo "  $(CXX)  $(CXX_FILE)"
	@mkdir -p $(dir $@)
	@$(CXX) -o $(@) -c $(CXX_FILE) -fPIC $(CXXFLAGS) $(INCLUDE) $(INCLUDE_DEPS)

