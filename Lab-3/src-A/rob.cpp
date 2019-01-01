#include <stdio.h>
#include <assert.h>

#include "rob.h"


extern int32_t NUM_ROB_ENTRIES;

/////////////////////////////////////////////////////////////
// Init function initializes the ROB
/////////////////////////////////////////////////////////////

ROB* ROB_init(void){
  int ii;
  ROB *t = (ROB *) calloc (1, sizeof (ROB));
  for(ii=0; ii<MAX_ROB_ENTRIES; ii++){
    t->ROB_Entries[ii].valid=false;
    t->ROB_Entries[ii].ready=false;
  }
  t->head_ptr=0;
  t->tail_ptr=0;
  return t;
}

/////////////////////////////////////////////////////////////
// Print State
/////////////////////////////////////////////////////////////
void ROB_print_state(ROB *t){
 int ii = 0;
  printf("Printing ROB \n");
  printf("Entry  Inst   Valid   ready\n");
  for(ii = 0; ii < 7; ii++) {
    printf("%5d ::  %d\t", ii, (int)t->ROB_Entries[ii].inst.inst_num);
    printf(" %5d\t", t->ROB_Entries[ii].valid);
    printf(" %5d\n", t->ROB_Entries[ii].ready);
  }
  printf("\n");
}

/////////////////////////////////////////////////////////////
//------- DO NOT CHANGE THE CODE ABOVE THIS LINE -----------
/////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////
// If there is space in ROB return true, else false
/////////////////////////////////////////////////////////////

bool ROB_check_space(ROB *t){

  if(t->ROB_Entries[t->tail_ptr].valid==0)
  {
  return -1; // no space
  }
  else 
  {
   return 0; // space available
  }

}

/////////////////////////////////////////////////////////////
// insert entry at tail, increment tail (do check_space first)
/////////////////////////////////////////////////////////////

int ROB_insert(ROB *t, Inst_Info inst){
  if(ROB_check_space(t)==1)
  {
      t->ROB_Entries[t->tail_ptr].valid=1;
      t->ROB_Entries[t->tail_ptr].inst= inst;
      t->tail_ptr++;
  }

}

/////////////////////////////////////////////////////////////
// Once an instruction finishes execution, mark rob entry as done
/////////////////////////////////////////////////////////////

void ROB_mark_ready(ROB *t, Inst_Info inst){
  if(t->ROB_Entries[inst.dr_tag].valid==1)
  {
    t->ROB_Entries[inst.dr_tag].ready = 1;
    t->ROB_Entries[inst.dr_tag]=inst = inst; //update in RoB
  }
  else assert (1);

}

/////////////////////////////////////////////////////////////
// Find whether the prf-rob entry is ready
/////////////////////////////////////////////////////////////

bool ROB_check_ready(ROB *t, int tag){
  int ii=0;
  while (ii<NUM_ROB_ENTRIES)
  {
    if(t->ROB_Entries[ii].ready && t->ROB_Entries[ii].valid)
    {
     if(t->ROB_Entries[ii].inst.dr_tag==tag)
     return 0;
     ii++;
    }
  }
  return -1;
}

/////////////////////////////////////////////////////////////
// Check if the oldest ROB entry is ready for commit
/////////////////////////////////////////////////////////////

bool ROB_check_head(ROB *t){
  if((t->ROB_Entries[t->head_ptr].valid==1)&&(t->ROB_Entries[t->head_ptr].ready==1))
  {
  return 0;
  }
  else  return -1;
}

/////////////////////////////////////////////////////////////
// Remove oldest entry from ROB (after ROB_check_head)
/////////////////////////////////////////////////////////////

Inst_Info ROB_remove_head(ROB *t)
{
  if(t->head_ptr>=NUM_ROB_ENTRIES-1)
  t->head_ptr=0;
  else 
  t->head_ptr=t->head_ptr +1;

  t->ROB_Entries[t->head_ptr-1].valid=0;
  t->ROB_Entries[t->head_ptr-1].ready=0;
  return t->ROB_Entries[t->head_ptr-1].inst;

}

/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
