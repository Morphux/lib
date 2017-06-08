/*********************************** LICENSE **********************************\
 *                            Copyright 2017 Morphux                            *
 *                                                                              *
 *        Licensed under the Apache License, Version 2.0 (the "License");       *
 *        you may not use this file except in compliance with the License.      *
 *                  You may obtain a copy of the License at                     *
 *                                                                              *
 *                 http://www.apache.org/licenses/LICENSE-2.0                   *
 *                                                                              *
 *      Unless required by applicable law or agreed to in writing, software     *
 *       distributed under the License is distributed on an "AS IS" BASIS,      *
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  *
 *        See the License for the specific language governing permissions and   *
 *                       limitations under the License.                         *
 \******************************************************************************/

#ifndef M_UTIL
# define M_UTIL

# include <stdint.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <morphux.h>
# include <sys/wait.h>

# define COMP_FLAGS_NONE   1 << 0x0
# define COMP_FLAGS_FILE   1 << 0x1
# define COMP_FLAGS_STDOUT 1 << 0x2


# define STR_OR_EMPTY(str) (str ? str : "")
# define STR_NULL_OR_EMPTY(str) (str == NULL || (str != NULL && *str == '\0'))

# define FREE(ptr) free(ptr); ptr = NULL;

/*!
 * \brief Set flags for compilation output
 *
 * \param[in] flags Flags to set
 *
 * \note If COMP_FLAGS_FILE is used, the compilations will call m_log.
 * Caller must init the logging first.
 */
void set_execute_flags(u8_t flags);

/*!
 * \brief Delete a directory recursively
 *
 * \param[in] dir Path of the directory to delete
 *
 * \return true on success, false on failure
 */
bool recursive_delete(const char *dir);

/*!
 * \brief Check if a file is there or not
 *
 * \param[in] str File path
 *
 * \return true if the file exist, false otherwise
 */
static inline bool file_exist(const char *str) {
    int         fd = open(str, O_RDONLY);
    bool        result = (fd != -1);

    if (result == true)
        close(fd);
    return result;
}

/*!
 * \brief Execute a command from a string
 *
 * \param[in] str Command to execute
 *
 * \return 0 success, error on failure
 */
int exec_line(const char *str);

int exec_list(mlist_t *list);

#endif /* M_UTIL */
