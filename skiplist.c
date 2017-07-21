#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

#include "skiplist.h"
#include <assert.h>

static bool node_has_next (sl_node_t *node) {
    return node->next != NULL;
}

static bool node_has_prev_level (sl_node_t *node) {
    return node->prev_level != NULL;
}

uint32_t node_number = 0;

static sl_node_t* make_node (sl_node_t *next, sl_node_t *prev_level, any_t key, any_t value) {
    sl_node_t *n = (sl_node_t *) malloc(sizeof(sl_node_t));
    n->number = node_number++;
    n->next = next;
    n->prev_level = prev_level;
    n->key = key;
    n->value = value;
    return n;
}

skiplist_t *create_skiplist(size_t levels_num, cmp_fn comparator) {
    skiplist_t *skiplist = (skiplist_t *)malloc(sizeof(skiplist_t));

    // if (skiplist == NULL) // TODO: error recovery
    skiplist->levels_num = levels_num;
    skiplist->levels = (sl_node_t**) calloc(levels_num, sizeof(sl_node_t*));
    /* skiplist->length = 0; */
    skiplist->comparator = comparator;

    // TODO: maybe abstract?
    sl_node_t *prev_level = NULL;
    for (uint32_t i = 0; i < levels_num; ++i) {
        prev_level = skiplist->levels[i] = make_node(NULL, prev_level, NULL, NULL);
    }

    return skiplist;
    /* cleanup: */
    /* 	delete skiplist; */
}

// INLINE
void assign_kv (sl_node_t *node, any_t key_ptr, any_t value_ptr) {
    node->key = key_ptr;
    node->value = value_ptr;
}

int cnt = 0;
int heights[] = {2, 4, 2, 4};

static size_t calculate_height (size_t max_height) {
    return heights[cnt++];

    /* size_t size = 0; */
    /* while (rand() % (1 << size) == 0 && size < max_height) { */
    /*     size++; */
    /* } */

    /* return size; */
}

void insert (skiplist_t *skiplist, any_t key_ptr, any_t value_ptr) {
    // Start from upper left
    uint32_t lvl = skiplist->levels_num - 1;
    sl_node_t* tower[skiplist->levels_num];
    sl_node_t *current = skiplist->levels[lvl];

    // Empty skiplist
    if (current->key == NULL) {
        while(node_has_prev_level(current)) {
            assign_kv(current, key_ptr, value_ptr);
            current = current->prev_level;
        }

        assign_kv(current, key_ptr, value_ptr);
        return;
    }

    int cmp; // TODO: special-case equality as replacement
    while (true) {

        while (node_has_next(current) &&
            	 current->next->key != NULL &&
            	 (cmp = (*skiplist->comparator)(current->next->key, key_ptr) <= 0)) {
            printf("NEXT HORISONTAL \n");
            current = current->next;
        }

        if (node_has_prev_level(current)) {
            assert(current != NULL);
            printf("ASSIGNING %d %d\n", current->number, lvl);
            tower[lvl--] = current;
            printf("NEXT VERTICAL \n");
            current = current->prev_level;

        } else {
            break;
        }
    }

    // At least one key has to be inserted by now
    assert(current->key != NULL);

    sl_node_t *new_bottom = make_node(current->next, NULL, key_ptr, value_ptr);
    assert(current->prev_level == NULL);
    current->next = new_bottom;

    size_t height = calculate_height(skiplist->levels_num);
    sl_node_t *prev_level = new_bottom;
    printf("Building up %zu\n", height);
    printf("lvl %d\n", lvl);

    for (int i = 1; i < height; i++) {
        tower[i]->next = prev_level = make_node(tower[i]->next, prev_level, key_ptr, value_ptr);
    }




// TODO: build levels up with 50% wahrsheinlichkeit
}
