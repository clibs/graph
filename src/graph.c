#include "graph.h"

static void
_graph_adjancency_list_append(graph_graph_t *, graph_edge_t *);

static void
_graph_adjancency_list_init(graph_graph_t *, graph_vertex_t *);

static void
_graph_edge_delete(graph_edge_t *);

static void
_graph_setup_store(graph_graph_t *);

static void
_graph_teardown_store(graph_graph_t *);

static void
_graph_vertex_delete(graph_vertex_t *);

static inline uint8_t
_uint_num_digits(uintptr_t);

graph_edge_t *
graph_add_edge(
  graph_graph_t * graph,
  const char * label,
  graph_vertex_t * from,
  graph_vertex_t * to,
  int64_t weight
) {
  graph_edge_t * edge = malloc(sizeof(graph_edge_t));

  if (! edge) { return NULL; }

  edge->id     = (uintptr_t) &edge[0];
  edge->label  = label;
  edge->from   = from;
  edge->to     = to;
  edge->weight = weight;
  edge->data   = NULL;

  switch (graph->store_type) {
    case GRAPH_STORE_ADJANCENCY_LIST:
      _graph_adjancency_list_append(graph, edge);

      break;
  }

  list_rpush(
    graph->edges,
    list_node_new(edge)
  );

  return edge;
}

graph_vertex_t *
graph_add_vertex(graph_graph_t * graph, const char * label) {
  graph_vertex_t * vertex = malloc(sizeof(graph_vertex_t));

  if (! vertex) { return NULL; }

  vertex->id       = (uintptr_t) &vertex[0];
  vertex->label    = label;
  vertex->data     = NULL;
  vertex->edge_ids = list_new();

  switch (graph->store_type) {
    case GRAPH_STORE_ADJANCENCY_LIST:
      _graph_adjancency_list_init(graph, vertex);

      break;
  }

  list_rpush(
    graph->vertices,
    list_node_new(vertex)
  );

  graph->cardinality++;

  return vertex;
}

void
graph_delete(graph_graph_t * graph) {
  list_destroy(graph->edges);
  list_destroy(graph->vertices);

  _graph_teardown_store(graph);

  free(graph);
}

graph_graph_t *
graph_new(const char * label, graph_store_t store_type) {
  graph_graph_t * graph = malloc(sizeof(graph_graph_t));

  if (! graph) { return NULL; }

  graph->label      = label;
  graph->edges      = list_new();
  graph->vertices   = list_new();
  graph->store_type = store_type;

  _graph_setup_store(graph);

  graph->cardinality = 0;

  graph->edges->free    = _graph_edge_delete;
  graph->vertices->free = _graph_vertex_delete;

  return graph;
}

void
graph_remove_edge(graph_graph_t * graph, uintptr_t id) {
  //
}

void
graph_remove_vertex(graph_graph_t * graph, uintptr_t id) {
  //
}

void
_graph_adjancency_list_append(graph_graph_t * graph, graph_edge_t * edge) {
  char id_key[
    _uint_num_digits(edge->from->id)
  ];

  sprintf(id_key, ("%" PRIuPTR), edge->from->id);

  list_rpush(
    edge->from->edge_ids,
    list_node_new(edge->id)
  );

  list_rpush(
    hash_get(
      graph->store.adjacency_list_hash,
      id_key
    ),
    list_node_new(edge->to->id)
  );
}

static void
_graph_adjancency_list_init(graph_graph_t * graph, graph_vertex_t * vertex) {
  char id_key[
    _uint_num_digits(vertex->id)
  ];

  sprintf(id_key, ("%" PRIuPTR), vertex->id);

  hash_set(
    graph->store.adjacency_list_hash,
    id_key,
    list_new()
  );
}

static void
_graph_edge_delete(graph_edge_t * edge) {
  free(edge);
}

static void
_graph_setup_store(graph_graph_t * graph) {
  switch (graph->store_type) {
    case GRAPH_STORE_ADJANCENCY_LIST:
      graph->store.adjacency_list_hash = hash_new();

      break;

    default:
      graph->store_type = GRAPH_STORE_ADJANCENCY_LIST;

      _graph_setup_store(graph);

      break;
  }
}

static void
_graph_teardown_store(graph_graph_t * graph) {
  switch (graph->store_type) {
    case GRAPH_STORE_ADJANCENCY_LIST:
      hash_each_val(graph->store.adjacency_list_hash, {
        list_destroy(val);
      })

      hash_free(graph->store.adjacency_list_hash);

      break;
  }
}

static void
_graph_vertex_delete(graph_vertex_t * vertex) {
  list_destroy(vertex->edge_ids);
  free(vertex);
}

static inline uint8_t
_uint_num_digits(uintptr_t num) {
  uint8_t digits = 0;

  if (num == 0) { return 1; }

  while (num) {
    num = num / 10;

    digits++;
  }

  return digits;
}
