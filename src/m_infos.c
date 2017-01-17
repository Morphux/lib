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

#include <m_infos.h>


/* Globals */
static char		program[INFOS_G_LEN_MAX] = "";
static char		version[INFOS_G_LEN_MAX] = "";
static char		maintainer[INFOS_G_LEN_MAX] = "";

/*!
 * Set the program name to a string
 */
void	set_program_name(const char *str) {
	memcpy(program, str, strlen(str));
}

/*!
 * Set the version name to a string
 */
void	set_version(const char *str) {
	memcpy(version, str, strlen(str));
}

/*!
 * Set the maintainer name to a string
 */
void	set_maintainer(const char *str) {
	memcpy(maintainer, str, strlen(str));
}

/*!
 * Get the program name
 * \note If the program is not set, return NULL
 */
const char	*get_program_name(void) {
	if (strlen(program) != 0)
		return program;
	return NULL;
}

/*!
 * Get the version
 * \note If the version is not set, return NULL
 */
const char	*get_version(void) {
	if (strlen(version) != 0)
		return version;
	return NULL;
}

/*!
 * Get the maintainer
 * \note If the maintainer is not set, return NULL
 */
const char	*get_maintainer(void) {
	if (strlen(maintainer) != 0)
		return maintainer;
	return NULL;
}
