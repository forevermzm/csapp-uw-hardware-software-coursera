/*
Coursera HW/SW Interface
Lab 4 - Mystery Caches

Mystery Cache Geometries (for you to keep notes):
mystery0:
    block size = 64
    cache size = 4096
    associativity = 32
mystery1:
    block size = 8
    cache size = 8192
    associativity = 8
mystery2:
    block size = 32
    cache size = 32768
    associativity = 2
mystery3:
    block size = 16
    cache size = 4096
    associativity = 1
*/

#include <stdlib.h>
#include <stdio.h>

#include "mystery-cache.h"

/*
 * NOTE: When using access_cache() you do not need to provide a "real"
 * memory addresses. You can use any convenient integer value as a
 * memory address, you should not be able to cause a segmentation
 * fault by providing a memory address out of your programs address
 * space as the argument to access_cache.
 */

/*
   Returns the size (in B) of each block in the cache.
*/
int get_block_size(void) {
  /* YOUR CODE GOES HERE */
  addr_t start = 0x0L;
  addr_t i;
  access_cache(start);    //First is a miss, this fetches the block into cache.
  for (i = start ;; i ++)
  {
    if (access_cache(i) == FALSE)
      break;
  }
  flush_cache();
  return i - start;
}

/*
   Returns the size (in B) of the cache.
*/
int get_cache_size(int size) {
  /* YOUR CODE GOES HERE */
  addr_t start = 0x0L;
  int i, j;
  for (i = 2 ; ; i ++)
  {
    flush_cache();
    access_cache(start);
    for (j = 1 ; j < i; j ++){
      access_cache(start + j * size);   //Increment the index and to check when the start address will be replaced.
    }
    if (access_cache(start) == FALSE)
      break;
  }
  flush_cache();
  return (j - 1) * size;
}

/*
   Returns the associativity of the cache.
*/
int get_cache_assoc(int size) {
  /* YOUR CODE GOES HERE */
  addr_t start = size;
  int i, j;
  for (i = 2 ;; i ++)
  {
    flush_cache();
    access_cache(start);
    for (j = 1 ; j < i ; j ++){
      access_cache(start + size * j);
    }
    if (access_cache(start) == FALSE)
      break;
  }
  return i - 1;
}

//// DO NOT CHANGE ANYTHING BELOW THIS POINT
int main(void) {
  int size;
  int assoc;
  int block_size;

  /* The cache needs to be initialized, but the parameters will be
     ignored by the mystery caches, as they are hard coded.  You can
     test your geometry paramter discovery routines by calling
     cache_init() w/ your own size and block size values. */
  cache_init(0,0);

  block_size=get_block_size();
  size=get_cache_size(block_size);
  assoc=get_cache_assoc(size);

  printf("Cache block size: %d bytes\n", block_size);
  printf("Cache size: %d bytes\n", size);
  printf("Cache associativity: %d\n", assoc);

  return EXIT_SUCCESS;
}
