#include "graph.h"

double robust(vertex_t* seq, size_t n) {
    if (seq == NULL) return (double) (n-1) / n / n;
    size_t R = n - seq->size;
    while (seq) {
        R += seq->size - 1;
        seq = seq->next;
    }
    return (double) R / n / n;
}
