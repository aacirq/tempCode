//
// Created by renxin on 2021/6/21.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "varlib.h"

static char *new_string(const char *name, const char *val);

static struct var *find_item(const char *name, int first_blank);

int VLstore(const char *name, const char *value) {
    struct var *item;
    char *p;
    int rv = 1;

    if ((item = find_item(name, 1)) != NULL && (p = new_string(name, value)) != NULL) {
        if (item->str != NULL)
            free(item->str);
        item->str = p;
        rv = 0;
    }
    return rv;
}

/**
 * get a new string in form "name=val"
 * @param name 变量名
 * @param val 值
 * @return first address of new string if ok, or NULL if trouble
 */
char *new_string(const char *name, const char *val) {
    char *str;
    str = malloc(strlen(name) + strlen(val) + 2);
    if (str != NULL) {
        sprintf(str, "%s=%s", name, val);
    }
    return str;
}

/**
 * find item which variable is `name`
 * @param name variable name
 * @param first_blank if want first blank item, set 1; otherwise, set 0
 * @return address of item which variable is name, or NULL if not found
 *         OR if(first_blank) then ptr to first blank one
 */
struct var *find_item(const char *name, int first_blank) {
    char *ptr;
    size_t len = strlen(name);
    int i;

    for (i = 0; i < MAXVARS && table[i].str != NULL; i++) {
        ptr = table[i].str;
        if (strncmp(ptr, name, len) == 0 && ptr[len] == '=') {
            return &table[i];
        }
    }
    if ((i < MAXVARS) && (first_blank != 0)) {
        return &table[i];
    }
    return NULL;
}

void VLlist() {
    for (int i = 0; i < MAXVARS && table[i].str != NULL; i++) {
        if (table[i].global == 1) {
            printf("*%s\n", table[i].str);
        } else {
            printf("%s\n", table[i].str);
        }
    }
}

int VLexport(const char *str) {
    // TODO
}

char *VLlookup(const char *var) {
    // TODO
}