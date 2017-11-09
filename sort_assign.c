#include "graph.h"

static
void graph_to_b(graph_t* graph, vertex_t* b[]) {
    b[0] = NULL;
    vertex_t* u = graph->vertices;
    size_t n = graph->vertex_count;
    while (n--) {
        unsigned k = u->size - 1;
        u->next = b[k]; b[k] = u++; 
    }
}

static
void seq_to_b(vertex_t* seq, vertex_t* b[]) {
    vertex_t* u;
    while ((u=seq)) {
        seq = seq->next;
        unsigned k = u->size - 1;
        u->next = b[k]; b[k] = u;
    }
}

vertex_t* sort_assign(graph_t* graph, vertex_t* seq, vertex_t* b[]) {

    if (seq) seq_to_b(seq, b);
    else graph_to_b(graph, b);

    vertex_t* u;
    size_t n = graph->vertex_count;
    vertex_t** end = &seq;
    while (--n) while ((u=b[n])) {
        b[n] = u->next;
        *end = u;
        end = &u->next;
    }
    *end = NULL;
    return seq;
}
