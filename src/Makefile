rwildcard				= $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2) $(filter $(subst *,%,$2),$d))
CXX_SRC                 = $(call rwildcard, , *.cpp)
CXX_OBJ                 = $(patsubst %.cpp, $($(ARTIFACT_VARS)_BIN)/%.o, $(CXX_SRC))
CXX_FILE                = $(patsubst $($(ARTIFACT_VARS)_BIN)/%.o, %.cpp, $(@))

CONFIG                 := "$(CURDIR)/.config.mk"

include $(CONFIG)

ARTIFACT_LIB           := $($(ARTIFACT_VARS)_BIN)/$($(ARTIFACT_VARS)_NAME)-$($(ARTIFACT_VARS)_VERSION)$(LIBRARY_EXT)
ARTIFACT_OBJ           := $($(ARTIFACT_VARS)_OBJ)

INCLUDE_DEPS            = $(foreach dep, $(DEPENDENCIES) $(ARTIFACT_VARS), $(if $($(dep)_INC), -I$($(dep)_INC)))
BUILD_DEPS              = $(foreach dep, $(DEPENDENCIES), $(if $($(dep)_OBJ), $(dep)))
LINKER_OBJS             = $(foreach dep, $(DEPENDENCIES), $(if $($(dep)_OBJ), $($(dep)_OBJ)))
LINKER_LIBS             = $(foreach dep, $(DEPENDENCIES), $(if $($(dep)_LIB), $($(dep)_LIB)))

$(info BUILD_DEPS = $(BUILD_DEPS))

.PHONY: compile depend all
.PHONY: $(BUILD_DEPS)

compile: $(ARTIFACT_OBJ)

all: $(ARTIFACT_LIB)

$(BUILD_DEPS):
	@echo "Building dependency $(notdir $($(@)_OBJ))"
	@echo $(MAKE) -s -C "$($(@)_PATH)" compile CONFIG="$(CONFIG)" DESTDIR="$(DESTDIR)"
	@$(MAKE) -s -C "$($(@)_PATH)" compile CONFIG="$(CONFIG)" DESTDIR="$(DESTDIR)" ARTIFACT_OBJ="$($(@)_OBJ)"

$(ARTIFACT_OBJ): $(BUILD_DEPS) $(CXX_OBJ)
	@echo "  $(LD)  $(notdir $(ARTIFACT_OBJ))"
	@$(LD) -o $(ARTIFACT_OBJ) -r $(CXX_OBJ)

$(ARTIFACT_LIB): $(ARTIFACT_OBJ)
	@echo "  $(CXX) $(notdir $(ARTIFACT_LIB))"
	@$(CXX) -o $(ARTIFACT_LIB) $(LINKER_OBJS) $(ARTIFACT_OBJ) $(SO_FLAGS) $(LINKER_LIBS)

$(CXX_OBJ):
	@echo "  $(CXX) $(CXX_FILE)"
	@mkdir -p $(dir $@)
	@$(CXX) -o $(@) -c $(CXX_FILE) -fPIC $(CXXFLAGS) $(INCLUDE) $(INCLUDE_DEPS)

