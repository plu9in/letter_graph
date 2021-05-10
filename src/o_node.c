#include <assert.h>
#include <string.h>
#include <stdio.h>
#include "o_types.h"
#include "o_link.h"
#include "o_node.h"

int compare_nodes(o_node* node1, o_node* node2){
  return COMPARE_NCONTENT(&(node1->letter), &(node2->letter));
}

o_node* create_node(ncontent content) {
  o_node *result = 0;
  INITIALIZE_NODE_CHAR(result, content);
  return result;
}

// This function returns the link between two nodes
o_link* find_link(o_node* node, o_node* node_to_link) {
  assert(node != 0);
  assert(node_to_link != 0);
  o_link* current_link = node->first_link;
  if(current_link == 0) {
    return 0;
  }
  o_node* linked_node = current_link->ptr_onode;
  assert(linked_node != 0); // otherwise, we have an empty link (between an actual node and nothing)
  int p = compare_nodes(node_to_link, linked_node);
  while(p != 0 && current_link->next != 0) {
    current_link = current_link->next;
    linked_node = current_link->ptr_onode;
    assert(linked_node != 0);
    p = compare_nodes(node_to_link, linked_node);
  }
  if(p == 0){
    return current_link;
  }
  return 0;

}

o_link* set_link_end_with_node(o_node *node){
  assert(node != 0);
  o_link* new_link;
  INITIALIZE_PLINK(new_link);
  new_link->ptr_onode = node;
  new_link->counter = 1;
  return new_link;
}

void link_nodes(o_node* node, o_node* node_to_link){
  assert(node != 0);
  assert(node_to_link != 0);

  o_link *olink = set_link_end_with_node(node_to_link);
  o_link *link = node->first_link;
  if(link == 0) {
    node->first_link = olink;
    node->last_link = olink;
    node->nb_branches = 1;
    return;
  }
  o_link *last_link = node->last_link;
  last_link->next = olink;
  node->last_link = olink;
  node->nb_branches = node->nb_branches + 1;
}

o_node* create_link(o_node *node, o_node *node_to_link){
  assert(node != 0);
  assert(node_to_link != 0);

  o_node *new_node;
  o_link *link = find_link(node, node_to_link);
  o_node* result = 0;

  if(link == 0) {
    link_nodes(node, node_to_link);
    result = node_to_link;
  }
  else{
    link->counter = link->counter + 1;
    result = link->ptr_onode;
  }

  assert(result != 0);
  return result;
}

void deallocate_links(o_node *node){
  debug_print("*-- deallocate_node called: %p -- letter: %c\n", node, node->letter);
  if(node == 0){
    return;
  }
  // links deallocation
  o_link *current_link = node->first_link;
  o_link *next_link;
  while(current_link != 0) {
    next_link = current_link->next;
    debug_memory(">-- freeing: %p\n", current_link);
    free(current_link);
    current_link = next_link;
  }
  debug_memory(">-- freeing: %p\n", node);
  free(node);
  node = 0;
}