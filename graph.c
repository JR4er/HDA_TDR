#include "graph.h"
#include <stdlib.h>
#include <stdio.h>
#include <memory.h>

graph_t* graph_read_csv(const char* filename) {
    FILE* csv = fopen(filename, "r");
    size_t n = 0, m = 0;
    unsigned a, b;
    while (fscanf(csv, "%u,%u", &a, &b) != EOF) {
        if (a >= n) n = a+1;
        if (b >= n) n = b+1;
        m++;
    }
    fseek(csv, 0, SEEK_SET);

    graph_t* g = (graph_t*) malloc(sizeof(graph_t) + n * sizeof(vertex_t));
    vertex_t* v = g->vertices;
    memset(v, 0, n * sizeof(vertex_t));

    while (fscanf(csv, "%u,%u", &a, &b) != EOF) {
        v[a].neigbhor_count++;
        v[b].neigbhor_count++;
    }
    fseek(csv, 0, SEEK_SET);

    vertex_t** e = (vertex_t**) malloc(2*m*sizeof(vertex_t**));
    for (size_t i=0; i!=n; ++i) {
        v[i].size = 1;
        v[i].neighbors = e;
        e += v[i].neigbhor_count;
    }

    while (fscanf(csv, "%u,%u", &a, &b) != EOF) {
        v[a].neighbors[v[a].k++] = &v[b];
        v[b].neighbors[v[b].k++] = &v[a];
    }
    fclose(csv);

    g->vertex_count = n;
    return g;
}

void graph_free(graph_t* graph) {
    free(graph->vertices[0].neighbors);
    free(graph);
}
