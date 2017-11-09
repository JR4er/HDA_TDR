#include "graph.h"

static inline
vertex_t* make_set(vertex_t* v) {
    v->marked = 0;
    v->sum_marked_child_size = 1;
    return v->path = v;
}

static
vertex_t* find_set(vertex_t* u) {
    while (u->path->path != u->path) {
        u = u->path = u->path->path;
    }
    return u->path;
}

static inline
vertex_t* union_set(vertex_t* x, vertex_t* y) {
    if (x == y) return x;
    if (x->marked < y->marked) {
        y->sum_marked_child_size += x->sum_marked_child_size;
        return x->path = y;
    }
    if (x->marked == y->marked) x->marked++;
    x->sum_marked_child_size += y->sum_marked_child_size;
    return y->path = x;
}

vertex_t* simple_recover(vertex_t* attack, vertex_t* isolate) {

    while (isolate) isolate = make_set(isolate)->next;

    vertex_t* seq = attack;
    while (seq) {
        vertex_t** nb = seq->neighbors;
        unsigned i = seq->k;
        vertex_t* set = make_set(seq);
        while (i--) {
            vertex_t* v = find_set(nb[i]);
            set = union_set(set, v);
        }
        seq->size = set->sum_marked_child_size;
        seq = seq->next;
    }
    return attack;
}
