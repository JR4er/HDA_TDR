#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

vertex_t* hda_attack(graph_t*, vertex_t* []);

vertex_t* simple_assign(graph_t*, vertex_t*, vertex_t* []);
vertex_t* sort_assign(graph_t*, vertex_t*, vertex_t* []);

vertex_t* simple_recover(vertex_t*, vertex_t*);
vertex_t* tdr_recover(vertex_t*, vertex_t*);

double robust(vertex_t*, size_t n);
void   dump(graph_t*, vertex_t*, vertex_t*, int);

vertex_t* (*attack) (graph_t*, vertex_t* []) = hda_attack;
vertex_t* (*assign) (graph_t*, vertex_t*, vertex_t* []) = simple_assign;
vertex_t* (*recover) (vertex_t*, vertex_t*) = simple_recover;
const char* filename = NULL;
int ps = 0;

static
int usage(const char* name) {
    printf("usage: %s [-o|-O] [-p] <filename>\n", name);
    puts( "\t-o : use simple optimization\n"
          "\t-O : use tree depth reduction optimization\n"
          "\t-p : print q ~ s(q) plot"
          "\t-s : print attack sequence"
        );
    return -1;
}

static
int parse_args(int argc, char* argv[]) {
    int i;
    for (i=1; i!=argc; ++i) {
        if (argv[i][0]=='-') {
            switch (argv[i][1]) {
                case 'O': recover = tdr_recover;
                case 'o': assign = sort_assign; break;
                case 'p': ps |=  1; break;
                case 's': ps |=  2; break;
                default: return 1;
            } 
        } else if (filename == NULL) {
            filename = argv[i];
        } else return 1;
    }
    return 0;
}

int main(int argc, char* argv[]) {
    if (parse_args(argc, argv)) return usage(argv[0]);
    graph_t* graph = graph_read_csv(filename);
    size_t n = graph->vertex_count;
    vertex_t** buffer = (vertex_t**) calloc(n, sizeof(vertex_t*));
    vertex_t* sequence = attack(graph, buffer);

    sequence = assign(graph, recover(sequence, buffer[0]), buffer);

    if (ps) dump(graph, sequence, buffer[0], ps);
    else printf("%lf\n", robust(sequence, n));

    free(buffer);
    return 0;
} 
