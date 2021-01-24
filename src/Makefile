#
# Copyright (C) 2020 Linux Studio Plugins Project <https://lsp-plug.in/>
#           (C) 2020 Vladimir Sadovnikov <sadko4u@gmail.com>
#
# This file is part of lsp-common-lib
#
# lsp-common-lib is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# any later version.
#
# lsp-common-lib is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with lsp-common-lib.  If not, see <https://www.gnu.org/licenses/>.
#

CONFIG                 := $(CURDIR)/.config.mk

include $(CONFIG)
include $($(ARTIFACT_ID)_PATH)/project.mk
include $($(ARTIFACT_ID)_PATH)/make/functions.mk

ifeq ($(TEST),1)
  UNIQ_DEPENDENCIES      := $(call uniq, $(DEPENDENCIES) $(TEST_DEPENDENCIES))
  DEPENDENCIES            = $(UNIQ_DEPENDENCIES)
endif

CXX_SRCMAIN             = $(call rwildcard, main, *.cpp)
CXX_SRCEXT              =
CXX_SRCALL              = $(call rwildcard, main, *.cpp)
CXX_SRCTEST             = $(call rwildcard, test, *.cpp)
CXX_SRC                 = $(CXX_SRCMAIN)

CXX_OBJ                 = $(patsubst %.cpp, $($(ARTIFACT_ID)_BIN)/%.o, $(CXX_SRC))
CXX_OBJEXT              = $(patsubst %.cpp, $($(ARTIFACT_ID)_BIN)/%.o, $(CXX_SRCEXT))

ALL_HEADERS             = $(call rwildcard, $($(ARTIFACT_ID)_INC), *.h)
CXX_FILE                = $(patsubst $($(ARTIFACT_ID)_BIN)/%.o,%.cpp, $(@))
CXX_HDR_PATHS           = $(foreach hdr,$(ARTIFACT_HEADERS),$($(ARTIFACT_ID)_INC)/$(hdr))
CXX_HEADERS             = $(foreach path,$(CXX_HDR_PATHS),$(call rwildcard, $(path), *.h))
CXX_INSTHEADERS         = $(patsubst $($(ARTIFACT_ID)_INC)/%,$(DESTDIR)$(INCDIR)/%,$(CXX_HEADERS))

ARTIFACT_BIN            = $($(ARTIFACT_ID)_BIN)
ARTIFACT_LIB            = $(ARTIFACT_BIN)/$(LIBRARY_PREFIX)$($(ARTIFACT_ID)_NAME)-$($(ARTIFACT_ID)_VERSION)$(LIBRARY_EXT)
ARTIFACT_SLIB           = $(ARTIFACT_BIN)/$(LIBRARY_PREFIX)$($(ARTIFACT_ID)_NAME)-$($(ARTIFACT_ID)_VERSION)$(STATICLIB_EXT)
ARTIFACT_LIBLINK        = $(LIBRARY_PREFIX)$($(ARTIFACT_ID)_NAME)$(LIBRARY_EXT)
ARTIFACT_SLIBLINK       = $(LIBRARY_PREFIX)$($(ARTIFACT_ID)_NAME)$(STATICLIB_EXT)
ARTIFACT_PC             = $(ARTIFACT_BIN)/$($(ARTIFACT_ID)_NAME)$(PKGCONFIG_EXT)
ARTIFACT_TESTBIN        = $(ARTIFACT_BIN)/$($(ARTIFACT_ID)_NAME)-test$(EXECUTABLE_EXT)
ARTIFACT_OBJ            = $($(ARTIFACT_ID)_OBJ)
ARTIFACT_MFLAGS         = $($(ARTIFACT_ID)_MFLAGS) $(foreach dep,$(DEPENDENCIES),-DUSE_$(dep))

CFLAGS_DEPS             = $(foreach dep, $(DEPENDENCIES) $(ARTIFACT_ID), $(if $($(dep)_CFLAGS), $($(dep)_CFLAGS)))
BUILD_DEPS              = $(foreach dep, $(DEPENDENCIES), $(if $($(dep)_OBJ), $(dep)))
LINKER_DEPS             = $(foreach dep, $(DEPENDENCIES), $(if $($(dep)_LDFLAGS), $($(dep)_LDFLAGS)))
LINKER_OBJS             = $(foreach dep, $(DEPENDENCIES), $(if $($(dep)_OBJ), $($(dep)_OBJ)))
BUILD_ALL               = $(ARTIFACT_LIB) $(ARTIFACT_SLIB) $(ARTIFACT_PC)

ifeq ($($(ARTIFACT_ID)_TESTING),1)
  CXX_SRC                += $(CXX_SRCTEST)
  BUILD_ALL              += $(ARTIFACT_TESTBIN)
endif

CXX_DEPS                = $(foreach src,$(CXX_SRCALL) $(CXX_SRCTEST),$(patsubst %.cpp,$(ARTIFACT_BIN)/%.d,$(src)))
CXX_DEPFILE             = $(patsubst $(ARTIFACT_BIN)/%.d,%.cpp,$(@))
CXX_DEPTARGET           = $(patsubst $(ARTIFACT_BIN)/%.d,%.o,$(@))

.DEFAULT_GOAL = all
.PHONY: compile depend dep_clean all install uninstall
.PHONY: $(BUILD_DEPS)

compile: $(ARTIFACT_OBJ)

all: $(BUILD_ALL)

dep_clean:

$(CXX_DEPS): dep_clean
	@echo "  dep  [$(ARTIFACT_NAME)] $(CXX_DEPFILE)"
	@mkdir -p $(dir $(@))
	$(CXX) -MM -MT "\$$($(ARTIFACT_ID)_BIN)/$(CXX_DEPTARGET)" -MF $(@) $(CXX_DEPFILE) $(CXXFLAGS) $(INCLUDE) $(CFLAGS_DEPS)

depend: $(CXX_DEPS)
	$(foreach dep,$(DEPENDENCIES) $(ARTIFACT_ID),\
	  $(if $($(dep)_INC), \
	    $(eval SED_RULES += s/$(shell echo "$($(dep)_INC)" | sed "s/\\//\\\\\//g")/\$$$$\\($(dep)_INC\\)/g;)\
	  )\
	  $(if $($(dep)_BIN), \
	    $(eval SED_RULES += s/$(shell echo "$($(dep)_BIN)" | sed "s/\\//\\\\\//g")/\\$$$$\\($(dep)_BIN\\)/g;)\
	  )\
	)
	@cat $(CXX_DEPS) | sed -E "$(SED_RULES)" >Makefile.d

$(BUILD_DEPS):
	@echo "make $(notdir $($(@)_OBJ))"
	@$(MAKE) -s -C "$($(@)_PATH)" compile CONFIG="$(CONFIG)" DEMO_TEST="0"

$(ARTIFACT_OBJ): $(CXX_OBJ) $(CXX_OBJEXT)
	@echo "  $(LD)   [$(ARTIFACT_NAME)] $(notdir $(ARTIFACT_OBJ))"
	@$(LD) -o $(ARTIFACT_OBJ) -r $(CXX_OBJ) $(CXX_OBJEXT)

$(ARTIFACT_LIB): $(BUILD_DEPS) $(ARTIFACT_OBJ)
	@echo "  $(CXX)  [$(ARTIFACT_NAME)] $(notdir $(ARTIFACT_LIB))"
	@$(CXX) -o $(ARTIFACT_LIB) $(LINKER_OBJS) $(ARTIFACT_OBJ) $(SO_FLAGS) $(LINKER_DEPS)
	
$(ARTIFACT_SLIB): $(BUILD_DEPS) $(ARTIFACT_OBJ)
	@echo "  $(AR)   [$(ARTIFACT_NAME)] $(notdir $(ARTIFACT_SLIB))"
	@$(AR) rcs $(ARTIFACT_SLIB) $(LINKER_OBJS) $(ARTIFACT_OBJ)

$(ARTIFACT_TESTBIN): $(ARTIFACT_OBJ)
	@echo "  $(CXX)  [$(ARTIFACT_NAME)] $(notdir $(ARTIFACT_TESTBIN))"
	@$(CXX) -o $(ARTIFACT_TESTBIN) $(LINKER_OBJS) $(ARTIFACT_OBJ) $(EXE_FLAGS) $(LINKER_DEPS)

$(CXX_OBJ) $(CXX_OBJEXT):
	@echo "  $(CXX)  [$(ARTIFACT_NAME)] $(CXX_FILE)"
	@mkdir -p $(dir $@)
	@$(CXX) -o $(@) -c $(CXX_FILE) -fPIC $(CXXFLAGS) $(ARTIFACT_MFLAGS) $(EXT_FLAGS) $(INCLUDE) $(CFLAGS_DEPS)

$(ARTIFACT_PC):
	@mkdir -p $(dir $(ARTIFACT_PC))
	@echo "prefix=$(PREFIX)" > "$(ARTIFACT_PC)"
	@echo "exec_prefix=$(BINDIR)" >> "$(ARTIFACT_PC)"
	@echo "includedir=$(INCDIR)" >> "$(ARTIFACT_PC)"
	@echo "libdir=$(LIBDIR)" >> "$(ARTIFACT_PC)"
	@echo "" >> $(ARTIFACT_PC) >> "$(ARTIFACT_PC)"
	@echo "Name: $($(ARTIFACT_ID)_NAME)" >> "$(ARTIFACT_PC)"
	@echo "Description: $($(ARTIFACT_ID)_DESC)" >> "$(ARTIFACT_PC)"
	@echo "Version: $($(ARTIFACT_ID)_VERSION)" >> "$(ARTIFACT_PC)"
	@echo "Cflags: -I\$${includedir}" >> "$(ARTIFACT_PC)"
	@echo "Libs: -L\$${libdir} -l$(notdir $($(ARTIFACT_ID)_NAME))" >> "$(ARTIFACT_PC)"

install: all
	@echo "Installing $($(ARTIFACT_ID)_NAME)"
	@mkdir -p "$(DESTDIR)$(INCDIR)"
	@mkdir -p "$(DESTDIR)$(LIBDIR)/pkgconfig"
	@cp -r "$(CXX_HDR_PATHS)" "$(DESTDIR)$(INCDIR)/"
	@cp $(ARTIFACT_PC) "$(DESTDIR)$(LIBDIR)/pkgconfig/"
	@echo $(INSTALL) $(ARTIFACT_LIB) -t "$(DESTDIR)$(LIBDIR)"
	@$(INSTALL) $(ARTIFACT_LIB) -t "$(DESTDIR)$(LIBDIR)"
	@echo cp $(ARTIFACT_SLIB) -t "$(DESTDIR)$(LIBDIR)"
	@cp $(ARTIFACT_SLIB) -t "$(DESTDIR)$(LIBDIR)"
	@ln -sf $(notdir $(ARTIFACT_LIB)) "$(DESTDIR)$(LIBDIR)/$(ARTIFACT_LIBLINK)"
	@ln -sf $(notdir $(ARTIFACT_SLIB)) "$(DESTDIR)$(LIBDIR)/$(ARTIFACT_SLIBLINK)"
	@echo "Install OK"

uninstall:
	@echo "Uninstalling $($(ARTIFACT_ID)_NAME)"
	@-rm -f "$(DESTDIR)$(LIBDIR)/$(notdir $(ARTIFACT_LIB))"
	@-rm -f "$(DESTDIR)$(LIBDIR)/$(notdir $(ARTIFACT_SLIB))"
	@-rm -f "$(DESTDIR)$(LIBDIR)/$(ARTIFACT_LIBLINK)"
	@-rm -f "$(DESTDIR)$(LIBDIR)/$(ARTIFACT_SLIBLINK)"
	@-rm -f "$(DESTDIR)$(LIBDIR)/pkgconfig/$(notdir $(ARTIFACT_PC))"
	@-rm -f $(CXX_INSTHEADERS)
	@echo "Uninstall OK"

# Dependencies
-include $(CURDIR)/Makefile.d
