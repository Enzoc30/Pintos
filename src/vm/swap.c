#include "vm/swap.h"
#include <bitmap.h>
#include <debug.h>
#include <stdio.h>
#include "vm/frame.h"
#include "vm/page.h"
#include "threads/synch.h"
#include "threads/vaddr.h"


struct block * swap_block;
struct bitmap * swap_bitmap;
// Lock para race condition
struct lock locki;

/* Sets up swap. */
void swap_init (void) {
  swap_block = block_get_role(BLOCK_SWAP);
  const size_t sizesz = PGSIZE / BLOCK_SECTOR_SIZE;
  lock_init(&locki);
  lock_acquire(&locki);
  swap_bitmap = bitmap_create(block_size(swap_block) / sizesz );
  lock_release(&locki);
}

/* Swaps in page P, which must have a locked frame
   (and be swapped out). */
void swap_in (struct page *p) {
  ASSERT(p != NULL);
  ASSERT(p->frame == NULL);
  const size_t sizesz = (PGSIZE/BLOCK_SECTOR_SIZE);
  lock_init(&locki);
  lock_acquire(&locki);
  // copy from the swapping device to the frame
  for(size_t i = 0 ; i < sizesz; i++){ 
    block_read(swap_block, p->sector + i , p->frame->base + i * BLOCK_SECTOR_SIZE);
  }
  // mark the swap slot as free
  bitmap_reset(swap_bitmap, p->sector / sizesz);
  // reset the sector flag on the page
  p->sector = (block_sector_t) -1;
  lock_release(&locki);

}

/* Swaps out page P, which must have a locked frame. */
bool swap_out (struct page *p) {
  ASSERT (p->frame != NULL);
  ASSERT (lock_held_by_current_thread (&p->frame->lock));

  const size_t sizesz = (PGSIZE/BLOCK_SECTOR_SIZE);
  lock_init(&locki);
  // Race Condition
  lock_acquire(&locki);

  size_t idx = bitmap_scan_and_flip(swap_bitmap,0, 1, false);

  // Was this process successful
  if(idx == BITMAP_ERROR){
    return false;
  }

  // Save the starting sector to the page
  p->sector = idx * sizesz;

  // write page content to the swap 
  for(size_t i = 0 ; i < sizesz; i ++){
    block_write(swap_block, p->sector + i , p->frame->base + i * BLOCK_SECTOR_SIZE );
  }  

  // unlock locki
  lock_release(&locki);

  // Reset page flags
  p->file_offset = 0;
  p->file_bytes = 0;
  p->private = true;
  p->file = NULL;

  return true ;
}
