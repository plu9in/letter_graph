#ifndef __O_GRAPH_H__
#define __O_GRAPH_H__
  #include <stdlib.h>
  #include "i_node.h"
  #include "o_node.h"

  typedef struct o_graph {
    i_node *index;
    o_node *start_node;
    o_node *current_node;
  } o_graph;

  o_graph* init_graph();
  o_graph* add_content_to_graph(o_graph *g, ncontent content);
  void deallocate_graph(o_graph *g);

#endif