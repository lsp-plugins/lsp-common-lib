/*
 * Copyright (C) 2020 Linux Studio Plugins Project <https://lsp-plug.in/>
 *           (C) 2020 Vladimir Sadovnikov <sadko4u@gmail.com>
 *
 * This file is part of lsp-common-lib
 * Created on: 25 марта 2016 г.
 *
 * lsp-common-lib is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * lsp-common-lib is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with lsp-common-lib. If not, see <https://www.gnu.org/licenses/>.
 */

#include <stddef.h>

#include <lsp-plug.in/common/status.h>

namespace lsp
{
    typedef struct str_tatus_t
    {
        const char *key;
        const char *desc;
    } str_status_t;

    #define S(k, v) { k, v }

    static const str_tatus_t statuses[] =
    {
        S("ok", "Success"),
        S("unspecified", "Unspecified"),
        S("loading", "Loading"),
        S("in_process", "In process"),
        S("unknown_error", "Unknown error"),
        S("no_memory", "Not enough memory"),
        S("not_found", "Not found or does not exist"),
        S("bad_format", "Bad format"),
        S("unsupported_format", "Unsupported format"),
        S("corrupted_file", "Corrupted file"),
        S("no_data", "No data"),
        S("invalid_uid", "Invalid unique identifier"),
        S("disconnected", "Disconnected"),
        S("bad_arguments", "Bad arguments"),
        S("not_bound", "Not bound"),
        S("bad_state", "Bad state"),
        S("not_implemented", "Not implemented"),
        S("already_exists", "Already exists"),
        S("overflow", "Overflow"),
        S("bad_hierarchy", "Bad hierarchy"),
        S("duplicated", "Duplicated"),
        S("too_big", "Too big"),
        S("permission_denied", "Permission denied"),
        S("io_error", "I/O error"),
        S("no_file", "No file"),
        S("end_of_file", "End of file"),
        S("closed", "The resource is closed"),
        S("not_supported", "The feature is not supported"),
        S("invalid_value", "Invalid value"),
        S("bad_locale", "Bad locale"),
        S("no_device", "No device"),
        S("unsupported_device", "Unsupported device"),
        S("opened", "Opened"),
        S("bad_type", "Bad type"),
        S("corrupted", "Corrupted data"),
        S("insufficient", "Insufficient data"),
        S("killed", "Killed"),
        S("timed_out", "Timeout"),
        S("failed", "Failed"),
        S("skip", "Skip"),
        S("cancelled", "Execution has been cancelled"),
        S("not_empty", "Not empty"),
        S("is_directory", "Is a directory"),
        S("not_directory", "Not a directory"),
        S("removed", "Removed"),
        S("breakpoint", "Debugging breakpoint"),
        S("readonly", "Read-only device or file system"),
        S("null", "The value is NULL"),
        S("locked", "The object is currently locked"),
        S("rejected", "The operation has been rejected"),
        S("already_bound", "Already bound"),
        S("no_captures", "No valid captures"),
        S("no_sources", "No valid sources"),
        S("bad_path", "Bad path"),
        S("protocol_error", "Protocol error"),
        S("bad_token", "Bad token"),
        S("no_grab", "No grab is currently obtained"),
        S("underflow", "Underflow"),
        S("incompatible", "Incompatible module/function"),
        S("not_mapped", "Resource is not mapped"),
        S("retry", "Retry a call"),
        S("interrupted", "Interrupted"),

        S(NULL, NULL)
    };

    #undef S

    LSP_COMMON_LIB_PUBLIC
    const char *get_status(status_t code)
    {
        return ((code >= 0) && (code < STATUS_TOTAL)) ? statuses[code].desc: NULL;
    }

    LSP_COMMON_LIB_PUBLIC
    const char *get_status_lc_key(status_t code)
    {
        return ((code >= 0) && (code < STATUS_TOTAL)) ? statuses[code].key : NULL;
    }

    LSP_COMMON_LIB_PUBLIC
    bool status_is_success(status_t code)
    {
        return code == STATUS_OK;
    }

    LSP_COMMON_LIB_PUBLIC
    bool status_is_preliminary(status_t code)
    {
        switch (code)
        {
            case STATUS_IN_PROCESS:
            case STATUS_LOADING:
                return true;
        }
        return false;
    }

    LSP_COMMON_LIB_PUBLIC
    bool status_is_error(status_t code)
    {
        if (status_is_success(code))
            return true;

        return ! status_is_preliminary(code);
    }

    LSP_COMMON_LIB_PUBLIC
    status_t update_status(status_t status, status_t new_status)
    {
        return (status == STATUS_OK) ? new_status : status;
    }
}


