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

#include <m_util.h>
#include <fts.h>

bool recursive_delete(const char *dir) {
    FTS         *ftsp = NULL;
    FTSENT      *curr = NULL;
    const char  *files[] = { (char *)dir, NULL };

    ftsp = fts_open((char * const *)files, FTS_NOCHDIR | FTS_PHYSICAL | FTS_XDEV, NULL);
    assert(ftsp != NULL);

    while ((curr = fts_read(ftsp))) {
        switch (curr->fts_info) {
#ifndef COMPILE_WITH_TEST
            case FTS_NS:
            /* FALLTROUGH */
            case FTS_DNR:
            /* FALLTROUGH */
            case FTS_ERR:
                goto error;

            case FTS_DC:
            /* FALLTROUGH */
            case FTS_DOT:
            /* FALLTROUGH */
            case FTS_NSOK:
                break ;
#endif /* COMPILE_WITH_TEST */

            case FTS_DP:
            /* FALLTROUGH */
            case FTS_F:
            /* FALLTROUGH */
            case FTS_SL:
            /* FALLTROUGH */
            case FTS_SLNONE:
            /* FALLTROUGH */
            case FTS_DEFAULT:
                if (remove(curr->fts_accpath) < 0)
                    goto error;
                break;
        }
    }

    fts_close(ftsp);
    return true;

error:
    fts_close(ftsp);
    return false;
}

int exec_line(const char *str) {
    mlist_t     *list = NULL;
    char        *cmd;
    size_t      j, i, len;

    if (str == NULL)
        return 0;

    cmd = strdup(str);
    if (cmd == NULL)
        return 0;

    len = strlen(cmd);
    for (i = 0, j = 0; i < len; i++)
    {
        if (cmd[i] == ' ')
        {
            while (i < len && cmd[i] == ' ')
                i++;

            i--;
            cmd[i] = '\0';
            list_add(list, cmd + j, i - j + 1);
            cmd[i] = ' ';
            j = i + 1;
        }
    }
    list_add(list, cmd + j, i - j + 1);

    /* TODO: exec */
    list_free(list, NULL);
    free(cmd);
    return 0;
}
