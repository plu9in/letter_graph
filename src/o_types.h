#ifndef __O_TYPES_H__
#define __O_TYPES_H__
  #include <string.h>
  #include <stdio.h>
  #ifdef DEBUG
    #define DEBUG_ACTIVE 1
  #else
    #define DEBUG_ACTIVE 0
  #endif

  #ifdef DMEMORY
    #define DMEMORY_ACTIVE 1
  #else
    #define DMEMORY_ACTIVE 0
  #endif


  typedef char ncontent; // like node_content

  #define COMPARE_NCONTENT(a, b) memcmp(a, b, sizeof(ncontent))

  #define debug_print(fmt, ...) \
                do { if (DEBUG_ACTIVE) fprintf(stderr, fmt, __VA_ARGS__); } while (0)
  #define debug_memory(fmt, ...) \
                do { if (DMEMORY_ACTIVE) fprintf(stderr, fmt, __VA_ARGS__); } while (0)
#endif