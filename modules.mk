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
# Variables that describe source code dependencies
LSP_TEST_FW_VERSION        := 1.0.17
LSP_TEST_FW_NAME           := lsp-test-fw
LSP_TEST_FW_TYPE           := src
LSP_TEST_FW_URL_RO         := https://github.com/lsp-plugins/$(LSP_TEST_FW_NAME).git
LSP_TEST_FW_URL_RW         := git@github.com:lsp-plugins/$(LSP_TEST_FW_NAME).git

#------------------------------------------------------------------------------
# Variables that describe system dependencies
LIBSHLWAPI_VERSION         := system
LIBSHLWAPI_NAME            := libshlwapi
LIBSHLWAPI_TYPE            := opt
LIBSHLWAPI_LDFLAGS         := -lshlwapi
