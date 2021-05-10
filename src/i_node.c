#include <assert.h>
#include <stdio.h>
#include "o_types.h"
#include "o_node.h"
#include "i_node.h"

int compare_inodes(i_node* inode1, i_node* inode2) {
  assert(inode1 != 0 && inode1->node != 0);
  assert(inode2 != 0 && inode2->node != 0);

  o_node *node1 = inode1->node;
  o_node *node2 = inode2->node;
  return compare_nodes(node1, node2);
}

void deallocate_index(i_node* index){
  debug_print("*-- calling deallocate_index with index at %p\n", index);
  if(index == 0){
    return;
  }
  // links deallocation
  i_node *current_inode = index;
  i_node *next_inode;
  debug_print("*-- trying to free current_node at %p\n", current_inode);
  while(current_inode != 0) {
    next_inode = current_inode->next;
    deallocate_links(current_inode->node);
    current_inode->node = 0;
    debug_memory("<-- freeing: %p\n", current_inode);
    free(current_inode);
    current_inode = next_inode;
  }
  index = 0;
}

void initialize_inode(i_node **inode, o_node *node) {
    assert(*inode == 0 && node != 0);

    *inode = (struct i_node*)calloc(1, sizeof(struct i_node));
    debug_memory("<-- allocating inode: %p\n", *inode);
    set_compare_inode(*inode, &compare_inodes);
    (*inode)->previous = 0;
    (*inode)->next = 0;
    (*inode)->node = node;
}

o_node* find_onode(i_node *inode, ncontent* content) {
  debug_print("searching for content %c\n", *content);
  if(inode == 0){
    debug_print("Index not initialized %p. Not found.\n", inode);
    return 0;
  };

  i_node* current_inode = inode;
  o_node* current_onode = inode->node;
  while(current_inode != 0) {
    int p = COMPARE_NCONTENT(&(current_onode->letter), content);
    if(p == 0){
      debug_print("|---- content  found: %c at %p\n", current_onode->letter, current_onode);
      return current_onode;
    }
    current_inode = current_inode->next;
    if(current_inode != 0){
      current_onode = current_inode->node;
    }
  }
  debug_print("|- content not found: %c\n", *content);
  return 0;
}

int index_node(i_node** inode, o_node* node) {
  assert(node != 0);

  debug_print("|-- indexing content %c at %p\n", node->letter, node);

  if(*inode == 0){
    initialize_inode(inode, node);
    debug_print("initialize index %p\n", *inode);
    return 1;
  }
  i_node* start = *inode;
  i_node* current_inode = *inode;
  i_node* inode_to_insert = 0;
  initialize_inode(&inode_to_insert, node);
  int p = current_inode->compare_inodes(current_inode, inode_to_insert);
  // change this comparison to reverse the order
  while(p < 0){
    if(current_inode->next == 0) {
      current_inode->next = inode_to_insert;
      inode_to_insert->previous = current_inode;
      debug_print("|-- inserting at the end %p\n", current_inode->next);
      return 1;
    }
    current_inode = current_inode->next;
    p = current_inode->compare_inodes(current_inode, inode_to_insert);
  }

  if(p == 0) {
    debug_print("|-- not indexing %c ... already exists\n", inode_to_insert->node->letter);
    debug_memory("<-- freeing: %p - %c\n", inode_to_insert, inode_to_insert->node->letter);
    free(inode_to_insert);
    return 0;
  }

  // current_inode < inode_to_insert
  // previous->next -----------> current_inode
  // previous       <----------- current_inode->previous
  // -----------------------------------------------------
  // previous->next -----------> inode_to_insert          , inode_to_insert->next ------------> current_inode
  // previous       <----------- inode_to_insert->previous, inode_to_insert       <------------ current_inode->previous
  i_node *previous_inode = current_inode->previous;

  inode_to_insert->next = current_inode;
  inode_to_insert->previous = previous_inode;

  current_inode->previous = inode_to_insert;
  if(previous_inode != 0) {
    previous_inode->next = inode_to_insert;
  }

  // Reset to the beginning of the index.
  while(start->previous != 0) start = start->previous;
  *inode = start;

  return 1;
}