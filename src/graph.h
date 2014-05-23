/**
 * The MIT License (MIT).
 *
 * Copyright (c) 2014 clibs
 * Copyright (c) 2014 Jonathan Barronville <jonathan@scrapum.photos>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef __GRAPH_H__
#define __GRAPH_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <inttypes.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "hash/hash.h"
#include "list/list.h"

#if defined(__GNUC__)

#if __GNUC__ >= 3
#define _UNUSED_VAR __attribute__ ((unused))
#endif

#else
#define _UNUSED_VAR
#endif

#ifdef __cplusplus
#define _MALLOC(type, count) ((type *) malloc(sizeof(type) * count))
#else
#define _MALLOC(type, count) (malloc(sizeof(type) * count))
#endif

#define _FREE free

struct _graph_edge {
  uintptr_t id;
  const char * label;
  struct _graph_vertex * from;
  struct _graph_vertex * to;
  int64_t weight;
  void * data;
};

struct _graph_vertex {
  uintptr_t id;
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
graph_remove_edge(graph_graph_t *, uintptr_t);

extern void
graph_remove_vertex(graph_graph_t *, uintptr_t);

#ifdef __cplusplus
}
#endif

#endif
