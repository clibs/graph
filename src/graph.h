#ifndef GRAPH_H
#define GRAPH_H

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "hash/hash.h"
#include "list/list.h"

struct _graph_vertex {
  uint32_t id;
  const char * label;
  void * data;
  list_t * edge_ids;
};

struct _graph_edge {
  uint64_t id;
  const char * label;
  struct _graph_vertex * from;
  struct _graph_vertex * to;
  int64_t weight;
  void * data;
};

enum _graph_stores {
  GRAPH_STORE_ADJANCENCY_LIST //,
  // GRAPH_STORE_ADJANCENCY_MATRIX
};

struct _graph_graph {
  const char * label;
  list_t * vertices;
  list_t * edges;
  enum _graph_stores store_type;

  union {
    hash_t * adjacency_list_hash;
    // matrix_t * adjacency_matrix;
  } store;

  uint32_t cardinality;
  uint32_t _last_vertex_auto_inc_id;
  bool _freed_vertex_auto_inc_id;
  uint32_t _last_freed_vertex_auto_inc_id;
  uint64_t _last_edge_auto_inc_id;
  bool _freed_edge_auto_inc_id;
  uint64_t _last_freed_edge_auto_inc_id;
};

typedef struct _graph_vertex graph_vertex_t;
typedef struct _graph_edge graph_edge_t;
typedef struct _graph_graph graph_graph_t;
typedef enum _graph_stores graph_store_t;

extern graph_graph_t *
graph_new(const char *, graph_store_t);

extern graph_vertex_t *
graph_new_vertex(const char *);

extern graph_edge_t *
graph_new_edge(
  const char *,
  graph_vertex_t *,
  graph_vertex_t *,
  int64_t
);

extern void
graph_add_vertex(graph_graph_t *, graph_vertex_t *);

extern void
graph_add_edge(graph_graph_t *, graph_edge_t *);

extern void
graph_remove_vertex(graph_graph_t *, uint32_t);

extern void
graph_remove_edge(graph_graph_t *, uint64_t);

extern void
graph_destroy(graph_graph_t *);

#endif
