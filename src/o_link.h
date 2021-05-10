#ifndef __O_LINK_H__
#define __O_LINK_H__
  #include "o_node.h"
  // graph link between node
  typedef struct o_link {
    long long unsigned counter;
    struct     o_link *next;
    o_node     *ptr_onode;
  } o_link;

  #define INITIALIZE_PLINK(k) (k) = calloc(1, sizeof(struct o_link)); \
                  debug_memory("<-- allocating link: %p\n", (k)); \
			      (k)->counter =  0; \
			      (k)->next = 0; \
			      (k)->ptr_onode = 0;

#endif