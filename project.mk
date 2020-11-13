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

# Package version
ARTIFACT_NAME               = lsp-common-lib
ARTIFACT_DESC               = Common library for basic C/C++ language definitions
ARTIFACT_VARS               = LSP_COMMON_LIB
ARTIFACT_HEADERS            = lsp-plug.in
ARTIFACT_VERSION            = 1.0.11-devel

# List of dependencies
TEST_DEPENDENCIES := \
  LSP_TEST_FW \
  TEST_STDLIB
  
DEPENDENCIES := 

ALL_DEPENDENCIES = \
  $(DEPENDENCIES) \
  $(TEST_DEPENDENCIES)