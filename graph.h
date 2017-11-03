#ifndef JRIVER_HDATDR_GRAPH_H
#define JRIVER_HDATDR_GRAPH_H

#include <stddef.h>

typedef struct vertex {
    struct vertex *next, *child, *parent, *path;
    struct vertex** neighbors;
    unsigned neigbhor_count, k;
    unsigned size;
    unsigned marked;
    unsigned sum_marked_child_size;
} vertex_t;

typedef struct {
    size_t vertex_count;
    vertex_t vertices[0];
} graph_t;

graph_t* graph_read_csv(const char* filename);
void graph_free(graph_t* graph);

#endif
