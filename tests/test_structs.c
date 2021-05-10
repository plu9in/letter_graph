#include <stdio.h>
#include "o_graph.h"
#include "o_link.h"

int main(int argc, char **argv){
  o_graph *g = init_graph();
  o_node* previous = 0;
  char ch;
  FILE *fp;

  fp = fopen("../texts/words_alpha.txt", "r"); // read mode

  if (fp == NULL) {
    perror("Error while opening the file.\n");
    exit(EXIT_FAILURE);
  }

  while((ch = fgetc(fp)) != EOF){
    if((ch < 'a' || ch > 'z') && (ch < 'A' || ch > 'Z')) {
      g->current_node = 0;
      continue;
    };
    g = add_content_to_graph(g, ch);
  }
  fclose(fp);

  i_node *index = g->index;
  while(index != 0){
    o_node *node = index->node;
    o_link *link = node->first_link;
    printf("letter %c - nb links:%d\n", node->letter, node->nb_branches);
    while(link != 0){
      printf("       |---%c - counter:%llu\n", link->ptr_onode->letter, link->counter);
      link = link->next;
    }
    index = index->next;
  }

  deallocate_graph(g);

  return 0;
}
