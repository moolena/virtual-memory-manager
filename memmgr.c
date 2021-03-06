//
//  memmgr.c
//  memmgr
//
//  Created by William McCarthy on 17/11/20.
//  Copyright © 2020 William McCarthy. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define ARGC_ERROR 1
#define FILE_ERROR 2
#define BUFLEN 256
#define FRAME_SIZE  256


int TLB[TLB_SIZE][3];

//-------------------------------------------------------------------
unsigned getpage(unsigned x) { return (0xff00 & x) >> 8; }

unsigned getoffset(unsigned x) { return (0xff & x); }

void getpage_offset(unsigned x) {
  unsigned  page   = getpage(x);
  unsigned  offset = getoffset(x);
  printf("x is: %u, page: %u, offset: %u, address: %u, paddress: %u\n", x, page, offset,
         (page << 8) | getoffset(x), page * 256 + offset);
}


int main(int argc, const char* argv[]) {
  FILE* fadd = fopen("addresses.txt", "r");    // open file addresses.txt  (contains the logical addresses)
  if (fadd == NULL) { fprintf(stderr, "Could not open file: 'addresses.txt'\n");  exit(FILE_ERROR);  }

  FILE* fcorr = fopen("correct.txt", "r");     // contains the logical and physical address, and its value
  if (fcorr == NULL) { fprintf(stderr, "Could not open file: 'correct.txt'\n");  exit(FILE_ERROR);  }

  char buf[BUFLEN];
  unsigned   page, offset, physical_add, frame = 0;
  unsigned   logic_add;                  // read from file address.txt
  unsigned   virt_add, phys_add, value;  // read from file correct.txt

  printf("ONLY READ FIRST 20 entries -- TODO: change to read all entries\n\n");


  while (frame < 20) {
  
  int TLB_hit = 0; // Flag variable
      for(int i = 0; i < TLB_SIZE; i++) {
          if(page_number == TLB[i][0]) {
             TLB_hit = 1;
             hitCount++;
             frame_number = TLB[i][1];
             TLB[i][2] = counter;
             break;
        }
    }

      if(TLB_hit == 0) {           
          frame_number = pagetable[page_number];

          int index = -1; // Which TLB to replace
          for(int i = 0; i < TLB_SIZE; i++) { // Incase TLB is empty
              if(TLB[i][0] == -1) {
                  index = i;
                  break;
              }
          }
          if(index == -1) { // Incase TLB is not empty
              int min = 9999;
              for(int i = 0; i < TLB_SIZE; i++) {
                  if(min > TLB[i][2]) {
                      min = TLB[i][2];
                      index = i;
                  }
              }
          }
          if(frame_number != -1) {
              TLB[index][0] = page_number;
              TLB[index][1] = frame_number;
              TLB[index][2] = counter;
          }

          if(frame_number == -1) {
              pageFault++;
              frame_number = freePage;
              freePage++;
              memcpy(MEMORY + frame_number * PAGE_SIZE, ptr + page_number * PAGE_SIZE, PAGE_SIZE);
              pagetable[page_number] = frame_number;

              TLB[index][0] = page_number;
              TLB[index][1] = frame_number;
              TLB[index][2] = counter;
          }
      }
    

    fscanf(fcorr, "%s %s %d %s %s %d %s %d", buf, buf, &virt_add,
           buf, buf, &phys_add, buf, &value);  // read from file correct.txt

    fscanf(fadd, "%d", &logic_add);  // read from file address.txt
    page   = getpage(  logic_add);
    offset = getoffset(logic_add);
    
    physical_add = frame++ * FRAME_SIZE + offset;
    
    assert(physical_add == phys_add);
    
    // todo: read BINARY_STORE and confirm value matches read value from correct.txt
    
    printf("logical: %5u (page: %3u, offset: %3u) ---> physical: %5u -- passed\n", logic_add, page, offset, physical_add);
    if (frame % 5 == 0) { printf("\n"); }
  }
  fclose(fcorr);
  fclose(fadd);
  
  printf("ONLY READ FIRST 20 entries -- TODO: change to read all entries\n\n");
  
  printf("ALL logical ---> physical assertions PASSED!\n");
  printf("!!! This doesn't work passed entry 24 in correct.txt, because of a duplicate page table entry\n");
  printf("--- you have to implement the PTE and TLB part of this code\n");

//  printf("NOT CORRECT -- ONLY READ FIRST 20 ENTRIES... TODO: MAKE IT READ ALL ENTRIES\n");

  printf("\n\t\t...done.\n");
  return 0;
}
