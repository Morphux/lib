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
# include <string.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>


/* Real functions */
static void     *(*real_malloc)(size_t)                     = &malloc;
static ssize_t  (*real_write)(int, const void *, size_t)    = &write;
static ssize_t  (*real_read)(int, void *, size_t)           = &read;
static int      (*real_close)(int)                          = &close;
static char     *(*real_strdup)(const char *)               = &strdup;
static int      (*real_fstat)(int, struct stat *)           = &fstat;
static void     *(*real_calloc)(size_t, size_t)             = &calloc;
static char     *(*real_strcpy)(char *, const char *)       = &strcpy;
static char     *(*real_strcat)(char *, const char *)       = &strcat;
static int      (*real_mkdir)(const char *, mode_t)         = &mkdir;
static pid_t    (*real_fork)(void)                          = &fork;

# include <fail_test.h>

MOCK_SET_IMP(malloc);
MOCK_SET_IMP(write);
MOCK_SET_IMP(read);
MOCK_SET_IMP(close);
MOCK_SET_IMP(strdup);
MOCK_SET_IMP(fstat);
MOCK_SET_IMP(calloc);
MOCK_SET_IMP(strcpy);
MOCK_SET_IMP(strcat);
MOCK_SET_IMP(mkdir);
MOCK_SET_IMP(fork);

void    *fl_malloc(size_t alloc) {
    if (g_malloc_fail == -1)
        return real_malloc(alloc);
    if (g_malloc_fail == 0) {
        g_malloc_fail = -1;
        return NULL;
    }
    g_malloc_fail--;
    return real_malloc(alloc);
}

void    *fl_calloc(size_t nmemb, size_t size) {
    if (g_calloc_fail == -1)
        return real_calloc(nmemb, size);
    if (g_calloc_fail == 0)
    {
        g_calloc_fail = -1;
        return NULL;
    }
    g_calloc_fail--;
    return real_calloc(nmemb, size);
}

ssize_t fl_write(int fd, const void *ptr, size_t len) {
    if (g_write_fail == -1)
        return real_write(fd, ptr, len);
    if (g_write_fail == 0) {
        g_write_fail = -1;
        return -1;
    }
    g_write_fail--;
    return real_write(fd, ptr, len);
}

ssize_t fl_read(int fd, void *ptr, size_t len) {
    if (g_read_fail == -1)
        return real_read(fd, ptr, len);
    if (g_read_fail == 0) {
        g_read_fail = -1;
        return -1;
    }
    g_read_fail--;
    return real_read(fd, ptr, len);
}

int fl_close(int fd) {
    if (g_close_fail == -1)
        return real_close(fd);
    if (g_close_fail == 0) {
        g_close_fail = -1;
        return -1;
    }
    g_close_fail--;
    return real_close(fd);
}

char *fl_strdup(const char *str) {
    if (g_strdup_fail == -1)
        return real_strdup(str);
    if (g_strdup_fail == 0) {
        g_strdup_fail = -1;
        return NULL;
    }
    g_strdup_fail--;
    return real_strdup(str);
}

int fl_fstat(int fd, struct stat *buf) {
    if (g_fstat_fail == -1)
        return real_fstat(fd, buf);
    if (g_fstat_fail == 0)
    {
        g_fstat_fail = -1;
        return -1;
    }
    g_fstat_fail--;
    return real_fstat(fd, buf);
}

char *fl_strcpy(char *dst, const char *src) {
    if (g_strcpy_fail == -1)
        return real_strcpy(dst, src);
    if (g_strcpy_fail == 0)
    {
        g_strcpy_fail = -1;
        return NULL;
    }
    g_strcpy_fail--;
    return real_strcpy(dst, src);
}

char *fl_strcat(char *dst, const char *src) {
    if (g_strcat_fail == -1)
        return real_strcat(dst, src);
    if (g_strcat_fail == 0)
    {
        g_strcat_fail = -1;
        return NULL;
    }
    g_strcat_fail--;
    return real_strcat(dst, src);
}

int fl_mkdir(const char *path, mode_t mode) {
    if (g_mkdir_fail == -1)
        return real_mkdir(path, mode);
    if (g_mkdir_fail == 0)
    {
        g_mkdir_fail = -1;
        /* Emptying ERRNO, in order to prevent real errors */
        errno = 0;
        return -1;
    }
    g_mkdir_fail--;
    return real_mkdir(path, mode);
}

pid_t fl_fork(void) {
    if (g_fork_fail == -1)
        return real_fork();
    if (g_fork_fail == 0)
    {
        g_fork_fail = -1;
        return -1;
    }
    g_fork_fail--;
    return real_fork();
}

#endif /* COMPILE_WITH_TEST */
