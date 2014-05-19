#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <inttypes.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "hash/hash.h"
#include "list/list.h"

#if defined(__GNUC__) && (__GNUC__ >= 3)
#define _UNUSED_VAR __attribute__ ((unused))
#else
#define _UNUSED_VAR
#endif

struct _graph_edge {
  intptr_t id;
  const char * label;
  struct _graph_vertex * from;
  struct _graph_vertex * to;
  int64_t weight;
  void * data;
};

struct _graph_vertex {
  intptr_t id;
  const char * label;
  void * data;
  list_t * edge_ids;
};

enum _graph_stores {
  GRAPH_STORE_ADJANCENCY_LIST
};

struct _graph_graph {
  const char * label;
  list_t * edges;
  list_t * vertices;
  enum _graph_stores store_type;

  union {
    hash_t * adjacency_list_hash;
  } store;

  uintmax_t cardinality;
};

typedef struct _graph_edge graph_edge_t;
typedef struct _graph_vertex graph_vertex_t;
typedef struct _graph_graph graph_graph_t;
typedef enum _graph_stores graph_store_t;

extern graph_edge_t *
graph_add_edge(
  graph_graph_t *,
  const char *,
  graph_vertex_t *,
  graph_vertex_t *,
  int64_t
);

extern graph_vertex_t *
graph_add_vertex(graph_graph_t *, const char *);

extern void
graph_delete(graph_graph_t *);

extern graph_graph_t *
graph_new(const char *, graph_store_t);

extern void
graph_remove_edge(graph_graph_t *, intptr_t);

extern void
graph_remove_vertex(graph_graph_t *, intptr_t);

#endif
