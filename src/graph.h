/**
 * The MIT License (MIT).
 *
 * https://github.com/clibs/graph
 *
 * Copyright (c) 2014 clibs, Jonathan Barronville (jonathan@scrapum.photos), and contributors.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef __GRAPH_H_INCLUDED__
#define __GRAPH_H_INCLUDED__

#ifdef __cplusplus
#include <cinttypes>
#include <cmath>
#include <cstdbool>
#include <cstdio>
#include <cstdlib>

using namespace std;
#else
#include <inttypes.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#endif

#include "hash/hash.h"
#include "list/list.h"

#if                         \
  defined(__GNUC__) &&      \
  (                         \
    (__GNUC__ > 2) ||       \
    (                       \
      (__GNUC__ == 2) &&    \
      (__GNUC_MINOR__ >= 7) \
    )                       \
  )
#define _UNUSED_VAR __attribute__ ((unused))
#else
#define _UNUSED_VAR
#endif

#ifdef __cplusplus
#define _MALLOC(type, count) ((type *) malloc(sizeof(type) * count))
#else
#define _MALLOC(type, count) (malloc(sizeof(type) * count))
#endif

#define _FREE free

#if                         \
  defined(__GNUC__) &&      \
  (                         \
    (__GNUC__ > 3) ||       \
    (                       \
      (__GNUC__ == 3) &&    \
      (__GNUC_MINOR__ >= 3) \
    )                       \
  )
#define GRAPH_ABI_EXPORT __attribute__ ((visibility ("default")))
#define GRAPH_ABI_HIDDEN __attribute__ ((visibility ("hidden")))
#else
#define GRAPH_ABI_EXPORT
#define GRAPH_ABI_HIDDEN
#endif

// #define _CAST_INT64_T(val) ((int64_t) val)
#define _CAST_UINT8_T(val) ((uint8_t) val)
// #define _CAST_UINT64_T(val) ((uint64_t) val)
#define _CAST_UINTMAX_T(val) ((uintmax_t) val)
#define _CAST_UINTPTR_T(val) ((uintptr_t) val)

#ifdef __cplusplus
extern "C" {
#endif

//==|||||||||||||||||||||
// + Type definitions. ||
//==|||||||||||||||||||||

typedef enum _graph_stores {
  GRAPH_STORE_ADJANCENCY_LIST
} graph_store_t;

typedef struct _graph_edge graph_edge_t;
typedef struct _graph_graph graph_graph_t;
typedef struct _graph_vertex graph_vertex_t;

//==|||||||||||||||||||||
// - Type definitions. ||
//==|||||||||||||||||||||

//==|||||||||||||
// + Core API. ||
//==|||||||||||||

GRAPH_ABI_EXPORT graph_edge_t *
graph_add_edge(
  graph_graph_t *,
  const char *,
  graph_vertex_t *,
  graph_vertex_t *,
  int64_t
);

GRAPH_ABI_EXPORT graph_vertex_t *
graph_add_vertex(
  graph_graph_t *,
  const char *
);

GRAPH_ABI_EXPORT void
graph_delete(
  graph_graph_t *
);

GRAPH_ABI_EXPORT graph_graph_t *
graph_new(
  const char *,
  graph_store_t
);

GRAPH_ABI_EXPORT void
graph_remove_edge(
  graph_graph_t *,
  uintptr_t
);

GRAPH_ABI_EXPORT void
graph_remove_vertex(
  graph_graph_t *,
  uintptr_t
);

//==|||||||||||||
// - Core API. ||
//==|||||||||||||

#ifdef __cplusplus
}
#endif

//==|||||||||||||||||||||||
// + Struct definitions. ||
//==|||||||||||||||||||||||

struct _graph_edge {
  void * data;
  graph_vertex_t * from;
  uintptr_t id;
  const char * label;
  graph_vertex_t * to;
  int64_t weight;
};

struct _graph_graph {
  uintmax_t cardinality;
  list_t * edges;
  const char * label;

  union {
    hash_t * adjacency_list_hash;
  } store;

  graph_store_t store_type;
  list_t * vertices;
};

struct _graph_vertex {
  void * data;
  list_t * edge_ids;
  uintptr_t id;
  const char * label;
};

//==|||||||||||||||||||||||
// - Struct definitions. ||
//==|||||||||||||||||||||||

#endif
