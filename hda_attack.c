#include "graph.h"
#include <memory.h>

static void
tidy_neighbor(vertex_t* v[], size_t k, size_t n) {
    if (k==0 || n==k) return;
    vertex_t* x = v[0];
    size_t i = 0, j = k;
    while (1) {
        while (j<n && !v[j]->size) j++;
        if (j==n) break;
        v[i++] = v[j];
        while (i<k &&  v[i]->size) i++;
        if (i==k) break;
        v[j++] = v[i];
    }
    if (j==n) v[i] = x;
    else v[j] = x;
}

static inline
void push(vertex_t** at, vertex_t* u) {
    u->next = *at;
    if (u->next) u->next->parent = u;
    *at = u;
}

vertex_t* hda(graph_t* graph, vertex_t* b[]) {
    size_t n = graph->vertex_count;
    memset(b, 0, n * sizeof(vertex_t*));

    vertex_t* u = graph->vertices;
    size_t i = n;

    while (i--) {
        unsigned k = u->k;
        push(&b[k], u++);
    }

    vertex_t* seq = NULL;
    while (--n) while ( (u=b[n]) ) {
        b[n] = u->next;

        u->next = seq;
        seq = u;
        u->size = 0;

        i = u->k;
        vertex_t** nb = u->neighbors;
        tidy_neighbor(nb, i, u->neigbhor_count);

        while (i--) {
            vertex_t* v = nb[i];
            unsigned k = v->k--;

            if (v->next) v->next->parent = v->parent;
            if (b[k] == v) b[k] = v->next;
            else v->parent->next = v->next;

            push(&b[--k], v);
        }
    }
    return seq;
}
