#include <stdio.h>
#include "graph/graph.h"

int
main(void) {
  graph_graph_t * graph = graph_new("test", GRAPH_STORE_ADJANCENCY_LIST);

  graph_vertex_t * vertex1 = graph_add_vertex(graph, NULL);
  graph_vertex_t * vertex2 = graph_add_vertex(graph, "vertex2");

  graph_edge_t * edge1 = graph_add_edge(
    graph,
    "edge1",
    vertex1,
    vertex2,
    0
  );

  printf("[graph]: %s\n", graph->label);
  printf("[vertex1]: %s\n", vertex1->label);
  printf("[vertex2]: %s\n", vertex2->label);
  printf("[edge1]: %s\n", edge1->label);
  graph_delete(graph);

  return 0;
}
