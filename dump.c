#include "graph.h"
#include <stdio.h>

typedef void (*dumper_t)(vertex_t*, vertex_t*, size_t, size_t);

static
void ps_dumper(vertex_t* u, vertex_t* o, size_t n, size_t i) {
    printf("%lu %lf %lf\n", u-o, (double)i/n, (double) u->size/n);
}

static
void p_dumper(vertex_t* u, vertex_t* __attribute__((unused)) o, 
        size_t n, size_t i) {
    printf("%lf %lf\n",  (double)i/n, (double) u->size/n);
}
static 
void s_dumper(vertex_t* u, vertex_t* o, 
        size_t __attribute__((unused)) n,
        size_t __attribute__((unused)) i) {
    printf("%lu\n", u - o);
}

static 
void dummy(
        vertex_t* __attribute__((unused)) u, 
        vertex_t* __attribute__((unused)) o, 
        size_t __attribute__((unused)) n,
        size_t __attribute__((unused)) i) {}



static
size_t seq_dump(vertex_t* seq, dumper_t dumper, vertex_t* o, size_t n, size_t i) {
    while (seq) {
        dumper(seq, o, n, i++);
        seq = seq->next;
    }
    return i;
}

void dump(graph_t* g, vertex_t* seq, vertex_t* iso, int ps) {
    dumper_t dumps[] = {dummy, p_dumper, s_dumper, ps_dumper};
    dumper_t dumper = dumps[ps];
    vertex_t* o = g->vertices;
    size_t n = g->vertex_count;
    size_t qc = seq_dump(seq, dumper, o, n, 0);
    seq_dump(iso, dumper, o, n, qc);
}
