#include "graph.h"

vertex_t* simple_assign(graph_t* __attribute__((unused)) graph, vertex_t* seq, vertex_t* __attribute__((unused)) buffer[]) {
    unsigned max_size = 0;
    vertex_t* u;
    vertex_t* l = NULL;
    while ((u=seq)) {
        seq = seq->next;
        if (u->size > max_size) max_size = u->size;
        else u->size = max_size;
        u->next = l;
        l = u;
    }
    return l;
}
