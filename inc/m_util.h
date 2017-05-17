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

# define STR_OR_EMPTY(str) (str ? str : "")
# define STR_NULL_OR_EMPTY(str) (str == NULL || (str != NULL && *str == '\0'))

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

#endif /* M_UTIL */
