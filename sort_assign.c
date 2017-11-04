#include "graph.h"

vertex_t* sort_assign(graph_t* graph, vertex_t* b[]) {
    vertex_t* u = graph->vertices;
    size_t n = graph->vertex_count;
    size_t i = n;
    unsigned k;
    while (i--) if ((k = u->size - 1)) {
        u->next = b[k];
        b[k] = u->next;
        u++;
    }

    vertex_t* seq = NULL;
    vertex_t** end = &seq;
    while (--n) while ((u=b[n])) {
        b[n] = u->next;
        *end = u;
        end = &u->next;
    }
    *end = NULL;
    return seq;
}
