#ifndef __O_NODE_H__
#define __O_NODE_H__

  #include <stdlib.h>
  #include "o_types.h"

  // a graph node
  typedef struct o_node {
    struct    o_link *first_link;
    struct    o_link *last_link;
    int       (*compare)(struct o_node *);
    int       nb_branches;
    ncontent  letter;
  } o_node;

  #define INITIALIZE_NODE(k) \
            (k) = calloc(1, sizeof(struct o_node)); \
            debug_memory("<-- allocating node %p\n", (k)); \
            (k)->first_link    = 0; \
            (k)->last_link  = 0; \
            (k)->nb_branches = 0;

  #define INITIALIZE_NODE_CHAR(k, c) INITIALIZE_NODE(k); \
            (k)->letter = c;

  int compare_nodes(o_node* node1, o_node* node2);
  o_node* create_node(ncontent content);
  void deallocate_links(o_node *node);
  o_node* create_link(o_node* n1, o_node* n2);

#endif