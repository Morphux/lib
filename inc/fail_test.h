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

#ifdef COMPILE_WITH_TEST
# ifndef M_FAIL_TEST_H
#  define M_FAIL_TEST_H

# undef strdup

# define malloc(size)           fl_malloc(size)
# define write(fd, ptr, len)    fl_write(fd, ptr, len)
# define read(fd, ptr, len)     fl_read(fd, ptr, len)
# define close(fd)              fl_close(fd)
# define strdup(str)            fl_strdup(str)
# define fstat(fd, buf)         fl_fstat(fd, buf)
# define calloc(memb, size)     fl_calloc(memb, size)
# define strcpy(dst, src)       fl_strcpy(dst, src)
# define strcat(dst, src)       fl_strcat(dst, src)
# define mkdir(path, mode)      fl_mkdir(path, mode)
# define fork fl_fork

#include <errno.h>

#define MOCK_SET_DECL(fn_name)      void set_##fn_name##_fail(int val);
#define MOCK_SET_IMP(fn_name)       static int g_##fn_name##_fail = -1; \
                                    void set_##fn_name##_fail(int val) { \
                                        if (g_##fn_name##_fail == -1) \
                                            g_##fn_name##_fail = val; \
                                    }

void    *fl_malloc(size_t alloc);
ssize_t fl_write(int fd, const void *ptr, size_t len);
ssize_t fl_read(int fd, void *ptr, size_t len);
int     fl_close(int fd);
char    *fl_strdup(const char *str);
int     fl_fstat(int fd, struct stat *buf);
void    *fl_calloc(size_t nmemb, size_t size);
char    *fl_strcpy(char *dst, const char *src);
char    *fl_strcat(char *dst, const char *src);
int     fl_mkdir(const char *pathname, mode_t mode);
pid_t   fl_fork(void);

MOCK_SET_DECL(malloc);
MOCK_SET_DECL(write);
MOCK_SET_DECL(read);
MOCK_SET_DECL(close);
MOCK_SET_DECL(strdup);
MOCK_SET_DECL(fstat);
MOCK_SET_DECL(calloc);
MOCK_SET_DECL(strcpy);
MOCK_SET_DECL(strcat);
MOCK_SET_DECL(mkdir);
MOCK_SET_DECL(fork);

# endif /* M_FAIL_TEST_H */
#endif /* COMPILE_WITH_TEST */
