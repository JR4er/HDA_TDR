#include "graph.h"

static
void set_parent(vertex_t* v, vertex_t* p) {
    while (v) { v->parent = p; v = v->next; }
}

static
void mark(vertex_t* v) {
    while (!v->marked) {
        v->marked = 1;
        vertex_t* p = v->parent;
        p->path = v;
        p->sum_marked_child_size += v->size;
        v = p;
    }
    v->path = NULL;
}

static
void unmark(vertex_t* v) {
    while (v->marked) {
        v->marked = 0;
        v->path = NULL;
        v->sum_marked_child_size = 0;
        v = v->parent;
    }
}

static
vertex_t* lca(vertex_t* root) {
    while (root->path) {
        root->size++;
        root = root->path;
    }
    return root;
}

static 
vertex_t* move_marked(vertex_t* dst, vertex_t** src) {
    vertex_t *u, *l = *src;
    vertex_t* s = NULL;
    while ((u=l)) {
        l = l->next;
        if (u->marked) { u->next = dst; dst = u; }
        else { u->next = s; s = u; }
    }
    *src = s;
    return dst;
}

static
vertex_t** max_size_at(vertex_t** p) {
    vertex_t** max_at = NULL;
    vertex_t* x;
    unsigned max_size = 0;
    while ((x = *p)) {
        if (x->size > max_size) {
            max_size = x->size;
            max_at = p;
        }
        p = &(*p)->next;
    }
    return max_at;
}

static inline
void add_child(vertex_t* p, vertex_t* u) {
    u->next = p->child;
    p->child = u;
    u->parent = p;
}

static
void insert(vertex_t* u, vertex_t* p) {
    vertex_t* child = move_marked(NULL, &p->child);
    unsigned sum = p->sum_marked_child_size;
    while (child) {

        vertex_t** max_at = max_size_at(&child);
        vertex_t* max = *max_at;
        unsigned max_size = max->size;
        unsigned smcs = max->sum_marked_child_size;

        if (sum - max_size > max_size - smcs - 1) break;

        *max_at = max->next;

        add_child(p, max);
    
        max->size += sum - max_size + 1;

        child = move_marked(child, &max->child);
        sum -= max_size - smcs;
        p = max;
    }
    if (child) {
        u->child = child;
        set_parent(child, u);
        u->size += sum;
    }
    add_child(p, u);
}

void tdr(vertex_t* seq, vertex_t* isolate) {
    vertex_t gaurd;
    vertex_t root = { NULL, isolate, &gaurd, NULL, NULL, 0,0,0,0,0 };

    set_parent(isolate, &root);

    vertex_t* u;
    while ((u=seq)) {

        seq = seq->next;

        vertex_t** nb = u->neighbors;
        unsigned i = u->k;

        gaurd.marked = 1;
        while (i--) mark(nb[i]);

        u->size = 1;
        insert(u, lca(&root));

        gaurd.marked = 0;
        u->marked = 1;
        i = u->k;
        while (i--) unmark(nb[i]);
        unmark(u);
    }
}
