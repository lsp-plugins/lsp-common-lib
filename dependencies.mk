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

#------------------------------------------------------------------------------
# List of common dependencies
DEPENDENCIES = \
  LIBPTHREAD 

TEST_DEPENDENCIES = \
  LSP_TEST_FW

#------------------------------------------------------------------------------
# Linux dependencies
LINUX_DEPENDENCIES =

LINUX_TEST_DEPENDENCIES =

ifeq ($(PLATFORM),Linux)
  DEPENDENCIES             += $(LINUX_DEPENDENCIES)
  TEST_DEPENDENCIES        += $(LINUX_TEST_DEPENDENCIES)
endif


#------------------------------------------------------------------------------
# BSD dependencies
BSD_DEPENDENCIES =

BSD_TEST_DEPENDENCIES =

ifeq ($(PLATFORM),BSD)
  DEPENDENCIES             += $(BSD_DEPENDENCIES)
  TEST_DEPENDENCIES        += $(BSD_TEST_DEPENDENCIES)
endif

#------------------------------------------------------------------------------
# Windows dependencies
WINDOWS_DEPENDENCIES = \
  LIBSHLWAPI

WINDOWS_TEST_DEPENDENCIES =

ifeq ($(PLATFORM),Windows)
  TEST_DEPENDENCIES += \
    LIBSHLWAPI
endif

#------------------------------------------------------------------------------
# Overall system dependencies
ALL_DEPENDENCIES = \
  $(DEPENDENCIES) \
  $(LINUX_DEPENDENCIES) \
  $(BSD_DEPENDENCIES) \
  $(WINDOWS_DEPENDENCIES) \
  $(TEST_DEPENDENCIES) \
  $(TEST_LINUX_DEPENDENCIES) \
  $(TEST_WINDOWS_DEPENDENCIES) \
  $(TEST_BSD_DEPENDENCIES)
