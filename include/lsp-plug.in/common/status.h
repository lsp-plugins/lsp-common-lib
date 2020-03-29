/*
 * status.h
 *
 *  Created on: 25 марта 2016 г.
 *      Author: sadko
 */

#ifndef LSP_PLUG_IN_COMMON_STATUS_H_
#define LSP_PLUG_IN_COMMON_STATUS_H_

#include <lsp-plug.in/common/types.h>

namespace lsp
{
    /**
     * Status type
     */
    typedef int         status_t;

    /**
     * Definition of different status codes used in LSP project
     */
    enum status_codes
    {
        STATUS_OK,                    //!< STATUS_OK successful status
        STATUS_UNSPECIFIED,           //!< STATUS_UNSPECIFIED
        STATUS_LOADING,               //!< STATUS_LOADING
        STATUS_IN_PROCESS,            //!< STATUS_IN_PROCESS
        STATUS_UNKNOWN_ERR,           //!< STATUS_UNKNOWN_ERR
        STATUS_NO_MEM,                //!< STATUS_NO_MEM
        STATUS_NOT_FOUND,             //!< STATUS_NOT_FOUND
        STATUS_BAD_FORMAT,            //!< STATUS_BAD_FORMAT
        STATUS_UNSUPPORTED_FORMAT,    //!< STATUS_UNSUPPORTED_FORMAT
        STATUS_CORRUPTED_FILE,        //!< STATUS_CORRUPTED_FILE
        STATUS_NO_DATA,               //!< STATUS_NO_DATA
        STATUS_INVALID_UID,           //!< STATUS_INVALID_UID
        STATUS_DISCONNECTED,          //!< STATUS_DISCONNECTED
        STATUS_BAD_ARGUMENTS,         //!< STATUS_BAD_ARGUMENTS
        STATUS_NOT_BOUND,             //!< STATUS_NOT_BOUND
        STATUS_BAD_STATE,             //!< STATUS_BAD_STATE
        STATUS_NOT_IMPLEMENTED,       //!< STATUS_NOT_IMPLEMENTED
        STATUS_ALREADY_EXISTS,        //!< STATUS_ALREADY_EXISTS
        STATUS_OVERFLOW,              //!< STATUS_OVERFLOW
        STATUS_BAD_HIERARCHY,         //!< STATUS_BAD_HIERARCHY
        STATUS_DUPLICATED,            //!< STATUS_DUPLICATED
        STATUS_TOO_BIG,               //!< STATUS_TOO_BIG
        STATUS_PERMISSION_DENIED,     //!< STATUS_PERMISSION_DENIED
        STATUS_IO_ERROR,              //!< STATUS_IO_ERROR
        STATUS_NO_FILE,               //!< STATUS_NO_FILE
        STATUS_EOF,                   //!< STATUS_EOF
        STATUS_CLOSED,                //!< STATUS_CLOSED
        STATUS_NOT_SUPPORTED,         //!< STATUS_NOT_SUPPORTED
        STATUS_INVALID_VALUE,         //!< STATUS_INVALID_VALUE
        STATUS_BAD_LOCALE,            //!< STATUS_BAD_LOCALE
        STATUS_NO_DEVICE,             //!< STATUS_NO_DEVICE
        STATUS_UNSUPPORTED_DEVICE,    //!< STATUS_UNSUPPORTED_DEVICE
        STATUS_OPENED,                //!< STATUS_OPENED
        STATUS_BAD_TYPE,              //!< STATUS_BAD_TYPE
        STATUS_CORRUPTED,             //!< STATUS_CORRUPTED
        STATUS_INSUFFICIENT,          //!< STATUS_INSUFFICIENT
        STATUS_KILLED,                //!< STATUS_KILLED
        STATUS_TIMED_OUT,             //!< STATUS_TIMED_OUT
        STATUS_FAILED,                //!< STATUS_FAILED
        STATUS_SKIP,                  //!< STATUS_SKIP
        STATUS_CANCELLED,             //!< STATUS_CANCELLED
        STATUS_NOT_EMPTY,             //!< STATUS_NOT_EMPTY
        STATUS_IS_DIRECTORY,          //!< STATUS_IS_DIRECTORY
        STATUS_NOT_DIRECTORY,         //!< STATUS_NOT_DIRECTORY
        STATUS_REMOVED,               //!< STATUS_REMOVED
        STATUS_BREAK_POINT,           //!< STATUS_BREAK_POINT  This is special status for step-by-step tracing algorithms
        STATUS_READONLY,              //!< STATUS_READONLY
        STATUS_NULL,                  //!< STATUS_NULL
        STATUS_LOCKED,                //!< STATUS_LOCKED
        STATUS_REJECTED,              //!< STATUS_REJECTED
        STATUS_ALREADY_BOUND,         //!< STATUS_ALREADY_BOUND
        STATUS_NO_CAPTURES,           //!< STATUS_NO_CAPTURES
        STATUS_NO_SOURCES,            //!< STATUS_NO_SOURCES
        STATUS_BAD_PATH,              //!< STATUS_BAD_PATH
        STATUS_PROTOCOL_ERROR,        //!< STATUS_PROTOCOL_ERROR
        STATUS_BAD_TOKEN,             //!< STATUS_BAD_TOKEN
        STATUS_NO_GRAB,               //!< STATUS_NO_GRAB
        STATUS_UNDERFLOW,             //!< STATUS_UNDERFLOW

        STATUS_TOTAL,
        STATUS_MAX = STATUS_TOTAL - 1,
        STATUS_SUCCESS = STATUS_OK    //!< STATUS_SUCCESS an alias to STATUS_OK
    };

    /**
     * Get string definition of the corresponding status
     * @param code status code
     * @return pointer to status string or NULL if the value is invalid
     */
    const char *get_status(status_t code);

    /**
     * Get localized key of the corresponding status which may be used
     * while performing localized dictionary lookup
     * @param code status code
     * @return pointer to localization key string or NULL if the value is invalid
     */
    const char *get_status_lc_key(status_t code);

    /**
     * Check that status code is successful
     * @param code status code
     * @return true if status code is successful
     */
    bool        status_is_success(status_t code);

    /**
     * Check that status code is preliminary
     * @param code status code
     * @return true if status code is preliminary
     */
    bool        status_is_preliminary(status_t code);

    /**
     * Check that status code is failure
     * @param code status code
     * @return true if status code is failure
     */
    bool        status_is_error(status_t code);
}

#endif /* CORE_STATUS_H_ */
