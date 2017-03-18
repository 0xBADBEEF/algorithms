/* This is an abstract expression parser.
 * Input:
 * Text file with expression of the following format:
 *
 * - first line: space sepatarated operation symbols (one sym per operator
 *   supported), like (for common case):
 * + - * /
 *
 * - second line: space separated operations that can be number modifyers, like:
 * -
 *
 * - all other lines: expressions
 *
 * Returned value:
 * On success peorgarm returns 0, on error - error code.
 *
 *
 *
 *   Alexander Aksenov <alexander.aksenov@mail.ru> 2017(c)
 */

enum {
    MAXIMUM_STRING_LENGTH = 1000
};


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/queue.h>


struct file_line {
    SLIST_ENTRY(file_line) entry;
    char *str;
};

static int get_operators(char *str, ssize_t len, int *cnt, char **store)
{
    /* TODO Should be totally different for multi-symbol operators */

    unsigned int c = 0;

    *cnt = 0;

    for (int i = 0; i < len; i++) {
        if (str[i] != ' ' && str[i] != '\n')
            (*cnt)++;
    }

    *store = malloc(*cnt);
    if (*store == NULL) {
        printf("No enough memory!\n");
        return ENOMEM;
    }

    for (int i = 0; i < len; i++) {
        if (str[i] != ' ' && str[i] != '\n') {
            (*store)[c] = str[i];
            c++;
        }
    }

    return 0;
}

static int parse_file(char *path, int *syms_cnt, char **syms,
                      int *mods_cnt, char **mods, int *exps_cnt, char ***exps)
{
    FILE *f;
    char *str = NULL;
    int ret = 0;
    unsigned int lines_cnt = 0;
    size_t len;
    ssize_t read;
    SLIST_HEAD(entry, file_line) head = SLIST_HEAD_INITIALIZER(head);
    struct file_line *el;

    f = fopen(path, "r");
    if (f == NULL) {
        printf("Target file is not specified!\n");
        return EINVAL;
    }

    *exps_cnt = 0;

    while ((read = getline(&str, &len, f)) != -1) {
        if (*syms == NULL) {
            ret = get_operators(str, read, syms_cnt, syms);
            if (ret)
                goto free_str;
            continue;
        } else if (*mods == NULL) {
            ret = get_operators(str, read, mods_cnt, mods);
            if (ret)
                goto free_str;
            continue;
        } else {
            struct file_line *fl = NULL; 
            char *data;
            
            lines_cnt++;

            data = malloc(read);
            if (data == NULL) {
                printf("No enough memory!\n");
                ret = ENOMEM;
                goto free_str;
            }

            fl = malloc(sizeof(*fl));
            if (fl == NULL) {
                printf("No enough memory!\n");
                ret = ENOMEM;
                free(data);
                goto free_str;
            }

            memcpy(data, str, read);
            fl->str = data;
            SLIST_INSERT_HEAD(&head, fl, entry);
        }
    }

    if (lines_cnt == 0) {
        printf("No expression lines!\n");
        ret = EINVAL;
        goto free_str;
    }

    *exps = malloc(lines_cnt);
    if (*exps == NULL) {
        printf("No enough memory!\n");
        ret = ENOMEM;
        goto list_cleanup;
    }

    SLIST_FOREACH(el, &head, entry) {
        (*exps)[*exps_cnt] = el->str;
        (*exps_cnt)++;
    }

list_cleanup:
    while(!SLIST_EMPTY(&head)) {
        el = SLIST_FIRST(&head);
        SLIST_REMOVE_HEAD(&head, entry);
        if (ret != 0)
            free(el->str);
        free(el);
    }

free_str:
    free(str);
    fclose(f);

    return ret;
}

int main(int argv, char *argc[])
{
    int ret;
    unsigned int syms_cnt = 0;
    unsigned int mods_cnt = 0;
    unsigned int exps_cnt = 0;
    char *syms = NULL;
    char *mods = NULL;
    char **exps = NULL;

    if (argv < 2) {
        printf("Target file is not specified!\n");
        return EINVAL;
    }

    ret = parse_file(argc[1], &syms_cnt, &syms, &mods_cnt, &mods, &exps_cnt,
                     &exps);
    if (ret < 0)
        return ret;

    printf("syms %s\n", syms);
    printf("mods %s\n", mods);
    printf("strings cnt %d\n", exps_cnt);
    for (int i = 0; i < exps_cnt; i++)
        printf(" %s", exps[i]);

    return 0;
}
