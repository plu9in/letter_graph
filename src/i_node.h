#ifndef __I_NODE_H__
#define __I_NODE_H__
  #include <stdlib.h>
  #include "o_node.h"
  // index of the double-linked list
  // We could use a b-tree
  typedef struct i_node{
    struct i_node               *previous;
    struct i_node               *next;
    int                         (*compare_inodes)(struct i_node *, struct i_node *);
    o_node                      *node;
  } i_node;

  #define set_compare_inode(t, f) ((t)->compare_inodes = (f))
  #define INITIALIZE_INODE(p) (p) = calloc(1, sizeof(struct i_node)); \
                  debug_memory(">-- allocating: %p\n", (p)); \
			      (p)->previous = 0; \
			      (p)->next = 0;

  #define INITIALIZE_INODE_WITH_NODE(i, n) INITIALIZE_INODE(i); (i)->node = node;

  int index_node(i_node** inode, o_node* node);
  void initialize_inode(i_node** inode, o_node* node);
  o_node* find_onode(i_node *inode, ncontent* content);
  void deallocate_index(i_node* index);

#endif