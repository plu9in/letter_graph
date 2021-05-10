#include <assert.h>

#include "i_node.h"
#include "o_types.h"
#include "o_graph.h"

o_graph* init_graph() {
  o_graph *result;
  result = calloc(1, sizeof(struct o_graph));
  debug_memory("<-- allocating graph %p\n", result);
  result->start_node = 0;
  result->current_node = 0;
  result->index = 0;
  return result;
}

void deallocate_graph(o_graph *g){
  assert(g != 0);

  deallocate_index(g->index);
  debug_memory("<-- freeing: %p\n", g);
  free(g);
  g = 0;
}

o_graph* add_content_to_graph(o_graph *g, ncontent content) {
  assert(g != 0);

  o_node *current_node = g->current_node;

  if(current_node == 0){
    o_node *new_node = find_onode(g->index, &content);
    if(new_node == 0){
      new_node = create_node(content);
    }
    index_node(&(g->index), new_node);
    g->start_node = new_node;
    g->current_node = new_node;
    return g;
  }

  o_node *node_to_link_with = find_onode(g->index, &content);
  if(node_to_link_with == 0){
    node_to_link_with = create_node(content);
    index_node(&(g->index), node_to_link_with);
  }
  debug_print("|-- link btw %p = <%c> // %p = <%c>\n", g->current_node, g->current_node->letter, node_to_link_with, node_to_link_with->letter);
  o_node* new_current_node = create_link(g->current_node, node_to_link_with);
  g->current_node = new_current_node;
}