#include "bpred.h"
#define TAKEN   true
#define NOTTAKEN false

/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////

BPRED::BPRED(uint32_t policy) {
if(policy==0) this->policy = BPRED_PERFECT;	
if(policy==1) this->policy = BPRED_ALWAYS_TAKEN;
if(policy==2) {
    this->policy = BPRED_GSHARE;

    GHR = 0;
    for (int i =0; i<8192; i++) 
    {
        Table[i]=2;
}
}
stat_num_branches=0;
stat_num_mispred=0;  
}

/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////

bool BPRED::GetPrediction(uint32_t PC){
    if (policy == BPRED_ALWAYS_TAKEN || policy== BPRED_PERFECT) 
	 {
	    return TAKEN;  
	 } 
	else if (policy == BPRED_GSHARE) 
	{
		if(Table[(PC^GHR)&0xFFF]==0 || Table[(PC^GHR)&0xFFF]==1) 		
		return NOTTAKEN;

        if(Table[(PC^GHR)&0xFFF]==2 || Table[(PC^GHR)&0xFFF]==3) 		
		return TAKEN;
	}
	
	 
      
}


/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////

void  BPRED::UpdatePredictor(uint32_t PC, bool resolveDir, bool predDir) {
if (policy == BPRED_ALWAYS_TAKEN || policy== BPRED_PERFECT) 
	 {
	    return;  
	 } 

 else if(policy == BPRED_GSHARE)
    {
        if(resolveDir==predDir &&  predDir==TAKEN){
        if((Table[(PC^GHR)&0xFFF])<3)
        Table[(PC^GHR)&0xFFF]=3;
        GHR= (GHR<<1)+1; }

        if(resolveDir==predDir &&  predDir==NOTTAKEN){
        if(Table[(PC^GHR)&0xFFF]>0)
        Table[(PC^GHR)&0xFFF]=0;
        GHR= (GHR<<1); }

        if(resolveDir!=predDir &&  predDir==TAKEN) {
        Table[(PC^GHR)&0xFFF]--;
        GHR= (GHR<<1); }

        if(resolveDir!=predDir &&  predDir==NOTTAKEN) {
        Table[(PC^GHR)&0xFFF]++;
        GHR= (GHR<<1)+1; }
        
    }
} 


/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////

