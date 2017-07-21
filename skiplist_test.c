#include <time.h>

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>

#include "skiplist.h"

int compare_strings(void *a, void *b) {
    char *s_a = (char *)a;
    char *s_b = (char *)b;
    int res = strcmp(s_a, s_b);
    /* printf("Comparing %s and %s  = %d\n", s_a, s_b, res); */
    return res;
}

const char *nil = "nil";

char *cast_to_char(void *c) {
    if (c == NULL)
        return (char *)nil;

    return (char *)c;
}

size_t get_idx(skiplist_t *skiplist, sl_node_t *current) {
    any_t key = current->key;
    sl_node_t *bottom = skiplist->levels[0];
    size_t idx = 0;
    while (bottom->next != NULL) {
        if (compare_strings(key, bottom->key) == 0) {
            break;
        }

        bottom = bottom->next;
        idx++;
    }
    return idx;
}

void dump_kvp(bool *is_first, skiplist_t *skiplist, sl_node_t *current) {
    if (*is_first) {
        *is_first = false;
    } else {
        printf(" -> ");
    }

    printf(" | %3d %7s: %7s | ", current->number, (char *) current->key, (char *) current->value);
}


void dump_skiplist(skiplist_t *skiplist) {
    printf("Total levels: %zu \n", skiplist->levels_num);
    uint32_t i = skiplist->levels_num;
    while (i-- > 0) {
        sl_node_t *current = skiplist->levels[i];
        if (current->prev_level == NULL)
            printf("BOTTOM %u: ", i);
        else
            printf("Level  %u: ", i);
        bool is_first = true;
        int last_pos = get_idx(skiplist, current);
        while (current->next != NULL) {
            dump_kvp(&is_first, skiplist, current);
            current = current->next;
            int new_pos = get_idx(skiplist, current);
            for (int i = 0, diff = new_pos - last_pos - 1; i < diff; i++)
                printf("                              ");
            last_pos = new_pos;
        }
        dump_kvp(&is_first, skiplist, current);

        printf("\n");
    }

}

// TODO: mock function
int main(void) {
    skiplist_t *s = create_skiplist(4, &compare_strings);

    printf("CMP %d\n", strcmp("key1", "key2"));
    void *k1 = (void *)"key1";
    void *v1 = (void *)"value1";
    printf("Inserting \n");
    insert(s, k1, v1);

    void *k2 = (void *)"key2";
    void *v2 = (void *)"value2";
    printf("Inserting 2 \n");
    insert(s, k2, v2);

    void *k3 = (void *)"key3";
    void *v3 = (void *)"value3";
    printf("Inserting 3 \n");
    insert(s, k3, v3);

    void *k4 = (void *)"key4";
    void *v4 = (void *)"value4";
    printf("Inserting 4 \n");
    insert(s, k4, v4);

    void *k5 = (void *)"key5";
    void *v5 = (void *)"value5";
    printf("Inserting 5 \n");
    insert(s, k5, v5);

    dump_skiplist(s);
    // TODO: free!
    printf("\nTest OK!\n");
    return 0;
}
