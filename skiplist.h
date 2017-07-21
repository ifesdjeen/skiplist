#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
typedef void *any_t;

// Comparator function
typedef int (*cmp_fn)(any_t, any_t);

typedef struct sl_node {
    struct sl_node *next;
    struct sl_node *prev_level;
    uint32_t        number;
    any_t           key;
    any_t           value;
} sl_node_t;

typedef struct skiplist {
    sl_node_t     **levels;
    cmp_fn          comparator;
    size_t          levels_num;
    // size_t length; TODO
} skiplist_t;

typedef struct sl_iterator {
    any_t           min;
    any_t           max;
} sl_iter_t;

skiplist_t *create_skiplist(size_t levels_num, cmp_fn comparator);
void        free_skiplist(skiplist_t *skiplist);

void        insert(skiplist_t *s, any_t k, any_t value_ptr);
void        remove_key(skiplist_t *s, any_t k);
bool        contains(skiplist_t *s, any_t k);
sl_node_t  *find_prev(skiplist_t *s, any_t k);
any_t       find(skiplist_t *s, any_t k);

sl_iter_t  *make_range_iterator(skiplist_t *s, any_t min, any_t max);
bool       *iterator_has_next(sl_iter_t *min);
any_t       iterator_next(sl_iter_t *min);

// TODO: make concurrent?
