#include <stdio.h>
#include <assert.h>

#include "rest.h"

extern int32_t NUM_REST_ENTRIES;

/////////////////////////////////////////////////////////////
// Init function initializes the Reservation Station
/////////////////////////////////////////////////////////////

REST* REST_init(void){
  int ii;
  REST *t = (REST *) calloc (1, sizeof (REST));
  for(ii=0; ii<MAX_REST_ENTRIES; ii++){
    t->REST_Entries[ii].valid=false;
  }
  assert(NUM_REST_ENTRIES<=MAX_REST_ENTRIES);
  return t;
}

////////////////////////////////////////////////////////////
// Print State
/////////////////////////////////////////////////////////////
void REST_print_state(REST *t){
 int ii = 0;
  printf("Printing REST \n");
  printf("Entry  Inst Num  S1_tag S1_ready S2_tag S2_ready  Vld Scheduled\n");
  for(ii = 0; ii < NUM_REST_ENTRIES; ii++) {
    printf("%5d ::  \t\t%d\t", ii, (int)t->REST_Entries[ii].inst.inst_num);
    printf("%5d\t\t", t->REST_Entries[ii].inst.src1_tag);
    printf("%5d\t\t", t->REST_Entries[ii].inst.src1_ready);
    printf("%5d\t\t", t->REST_Entries[ii].inst.src2_tag);
    printf("%5d\t\t", t->REST_Entries[ii].inst.src2_ready);
    printf("%5d\t\t", t->REST_Entries[ii].valid);
    printf("%5d\n", t->REST_Entries[ii].scheduled);
    }
  printf("\n");
}

/////////////////////////////////////////////////////////////
//------- DO NOT CHANGE THE CODE ABOVE THIS LINE -----------
/////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////
// If space return true else return false
/////////////////////////////////////////////////////////////

bool  REST_check_space(REST *t){
  for (int ii=0; ii<NUM_REST_ENTRIES;ii++)
  {
  if(t->REST_Entries[ii].valid==0)
    {
      return 1;
    }
  }
   return 0;
}

/////////////////////////////////////////////////////////////
// Insert an inst in REST, must do check_space first
/////////////////////////////////////////////////////////////

void  REST_insert(REST *t, Inst_Info inst){
  for( int ii=0; ii<NUM_REST_ENTRIES; ii++)
  {
    if(t->REST_Entries[ii].valid==0)
    {
        t->REST_Entries[ii].valid=1;
        t->REST_Entries[ii].inst= inst;
        t->REST_Entries[ii].scheduled=0;
        break;
          
    }
  }
  assert(1);
}

/////////////////////////////////////////////////////////////
// When instruction finishes execution, remove from REST
/////////////////////////////////////////////////////////////

void  REST_remove(REST *t, Inst_Info inst){
  for(int ii=0; ii< NUM_REST_ENTRIES; ii++)
  {
    if(t->REST_Entries[ii].valid && t->REST_Entries[ii].scheduled)
    {
      if(t->REST_Entries[ii].inst.inst_num == inst.inst_num)
      {
        t->REST_Entries[ii].valid=0;
        t->REST_Entries[ii].scheduled= 0;
        break;    
      }
    }
  }
}

/////////////////////////////////////////////////////////////
// For broadcast of freshly ready tags, wakeup waiting inst
/////////////////////////////////////////////////////////////

void  REST_wakeup(REST *t, int tag){
  for( int ii=0; ii< NUM_REST_ENTRIES;ii++)
  {
    if((t->REST_Entries[ii].valid==1)&&(t->REST_Entries[ii].inst.src1_tag==tag))
    {
      t->REST_Entries[ii].inst.src1_ready=1;
    }
    if((t->REST_Entries[ii].valid==1)&&(t->REST_Entries[ii].inst.src2_tag==tag))
    {
      t->REST_Entries[ii].inst.src2_ready=1;
    }
  }

}

/////////////////////////////////////////////////////////////
// When an instruction gets scheduled, mark REST entry as such
/////////////////////////////////////////////////////////////

void  REST_schedule(REST *t, Inst_Info inst){
  for(int ii=0; ii< NUM_REST_ENTRIES; ii++)
  {
    if(t->REST_Entries[ii].valid && t->REST_Entries[ii].inst.inst_num == inst.inst_num)
    {
      t->REST_Entries[ii].scheduled = 1;
      break;
    }
  }
  assert(1);
}