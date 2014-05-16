#include "graph.h"

static void
_graph_destroy_vertex(graph_vertex_t *);

static void
_graph_destroy_edge(graph_edge_t *);

graph_graph_t *
graph_new(const char * label, graph_store_t store_type) {
  graph_graph_t * graph = malloc(sizeof(graph_graph_t));

  if (! graph) {
    return NULL;
  }

  graph->label                          = label;
  graph->vertices                       = list_new();
  graph->edges                          = list_new();
  graph->store_type                     = store_type;
  graph->cardinality                    = 0;
  graph->_last_vertex_auto_inc_id       = 0;
  graph->_freed_vertex_auto_inc_id      = false;
  graph->_last_freed_vertex_auto_inc_id = 0;

  graph->vertices->free = _graph_destroy_vertex;
  graph->edges->free    = _graph_destroy_edge;

  goto setup_graph_store;

  return graph;

setup_graph_store:

  switch (graph->store_type) {
    case GRAPH_STORE_ADJANCENCY_LIST:
      graph->store.adjacency_list_hash = hash_new();

      break;

    // case GRAPH_STORE_ADJANCENCY_MATRIX:


    //   break;

    default:
      graph->store_type = GRAPH_STORE_ADJANCENCY_LIST;

      goto setup_graph_store;

      break;
  }
}

graph_vertex_t *
graph_new_vertex(const char * label) {
  graph_vertex_t * vertex = malloc(sizeof(graph_vertex_t));

  if (! vertex) {
    return NULL;
  }

  vertex->id       = 0;
  vertex->label    = label;
  vertex->data     = NULL;
  vertex->edge_ids = list_new();

  return vertex;
}

graph_edge_t *
graph_new_edge(
  const char * label,
  graph_vertex_t * from,
  graph_vertex_t * to,
  int64_t weight
) {
  graph_edge_t * edge = malloc(sizeof(graph_edge_t));

  if (! edge) {
    return NULL;
  }

  edge->label  = label;
  edge->from   = from;
  edge->to     = to;
  edge->weight = weight;
  edge->data   = NULL;

  return edge;
}

void
graph_add_vertex(graph_graph_t * graph, graph_vertex_t * vertex) {
  if (graph->_freed_vertex_auto_inc_id) {
    vertex->id = graph->_last_freed_vertex_auto_inc_id;
  } else {
    vertex->id = graph->_last_vertex_auto_inc_id;
  }

  switch (graph->store_type) {
    case GRAPH_STORE_ADJANCENCY_LIST:
      goto init_vertex_adjancency_list;

      break;

    // case GRAPH_STORE_ADJANCENCY_MATRIX:
    //   goto init_vertex_adjancency_matrix;

    //   break;
  }

  list_rpush(
    graph->vertices,
    list_node_new(vertex)
  );

  graph->cardinality++;
  graph->_last_vertex_auto_inc_id++;

init_vertex_adjancency_list:

  ;

  char id_key[25];

  sprintf(id_key, ("%" PRIu64), vertex->id);

  hash_set(
    graph->store.adjacency_list_hash,
    id_key,
    list_new()
  );

// init_vertex_adjancency_matrix:


}

void
graph_add_edge(graph_graph_t * graph, graph_edge_t * edge) {
  if (graph->_freed_edge_auto_inc_id) {
    edge->id = graph->_last_freed_edge_auto_inc_id;
  } else {
    edge->id = graph->_last_edge_auto_inc_id;
  }

  switch (graph->store_type) {
    case GRAPH_STORE_ADJANCENCY_LIST:
      goto store_edge_adjancency_list;

      break;

    // case GRAPH_STORE_ADJANCENCY_MATRIX:
    //   goto store_edge_adjancency_matrix;

    //   break;
  }

  list_rpush(
    graph->edges,
    list_node_new(edge)
  );

  graph->_last_edge_auto_inc_id++;

store_edge_adjancency_list:

  ;

  char id_key[25];

  sprintf(id_key, ("%" PRIu64), edge->from->id);

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

// store_edge_adjancency_matrix:


}

void
graph_remove_vertex(graph_graph_t * graph, uint32_t id) {
  //
}

void
graph_remove_edge(graph_graph_t * graph, uint64_t id) {
  //
}

void
graph_destroy(graph_graph_t * graph) {
  list_destroy(graph->vertices);
  list_destroy(graph->edges);

  goto teardown_graph_store;

  free(graph);

teardown_graph_store:

  switch (graph->store_type) {
    case GRAPH_STORE_ADJANCENCY_LIST:
      hash_each_val(graph->store.adjacency_list_hash, {
        list_destroy(val);
      })

      hash_free(graph->store.adjacency_list_hash);

      break;

    // case GRAPH_STORE_ADJANCENCY_MATRIX:


    //   break;
  }
}

static void
_graph_destroy_vertex(graph_vertex_t * vertex) {
  list_destroy(vertex->edge_ids);
  free(vertex);
}

static void
_graph_destroy_edge(graph_edge_t * edge) {
  free(edge);
}
