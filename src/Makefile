rwildcard				= $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2) $(filter $(subst *,%,$2),$d))
CXX_SRC                 = $(call rwildcard, , *.cpp)
CXX_OBJ                 = $(patsubst %.cpp, $($(ARTIFACT_VARS)_BIN)/%.o, $(CXX_SRC))
CXX_FILE                = $(patsubst $($(ARTIFACT_VARS)_BIN)/%.o, %.cpp, $(@))

CONFIG                 := "$(CURDIR)/.config.mk"

include $(CONFIG)

INCLUDE_DEPS            = $(foreach dep, $(DEPENDENCIES) $(ARTIFACT_VARS), $(if $($(dep)_INC), -I$($(dep)_INC)))
LINKER_DEPS             = $(foreach dep, $(DEPENDENCIES) $(ARTIFACT_VARS), $($(dep)_OBJ))
LINKER_LIBS             = $(foreach dep, $(DEPENDENCIES) $(ARTIFACT_VARS), $($(dep)_LIB))
ARTIFACT_LIB            = $($(ARTIFACT_VARS)_BIN)/$($(ARTIFACT_VARS)_NAME)-$($(ARTIFACT_VARS)_VERSION)$(LIBRARY_EXT)


$(info $($(ARTIFACT_VARS)_OBJ))
$(info CXX_SRC = $(CXX_SRC))
$(info CXX_OBJ = $(CXX_OBJ))
$(info INCLUDE_DEPS = $(INCLUDE_DEPS))
$(info LINKER_DEPS = $(LINKER_DEPS))
$(info LINKER_LIBS = $(LINKER_LIBS))

.PHONY: compile depend all

compile: $($(ARTIFACT_VARS)_OBJ)

all: $(ARTIFACT_LIB)

$($(ARTIFACT_VARS)_OBJ): $(CXX_OBJ)
	@echo "  $(LD)  $(notdir $($(ARTIFACT_VARS)_OBJ))"
	@$(LD) -o $($(ARTIFACT_VARS)_OBJ) -r $(CXX_OBJ)

$(ARTIFACT_LIB): $($(ARTIFACT_VARS)_OBJ)
	@echo "  $(CXX) $(notdir $(ARTIFACT_LIB))"
	@$(CXX) -o $(ARTIFACT_LIB) $(LINKER_DEPS) $(SO_FLAGS) $(LINKER_LIBS)

$(CXX_OBJ):
	@echo "  $(CXX) $(CXX_FILE)"
	@mkdir -p $(dir $@)
	@echo $(CXX) -o $(@) -c $(CXX_FILE) -fPIC $(CXXFLAGS) $(INCLUDE) $(INCLUDE_DEPS)
	@$(CXX) -o $(@) -c $(CXX_FILE) -fPIC $(CXXFLAGS) $(INCLUDE) $(INCLUDE_DEPS)

