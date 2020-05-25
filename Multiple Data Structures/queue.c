#include "cda.h"
#include "queue.h"
#include "integer.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
// This queue uses a CDA for storage

    typedef struct queue {
    CDA *itemsCDA;    
    int debug;
    void (*display)(void *, FILE *);
    void (*free)(void *);
}QUEUE;
      
 
// Initialization of new queue
    QUEUE *newQUEUE(void){
           QUEUE *items = malloc(sizeof(QUEUE));
        items->itemsCDA = newCDA();
        setCDAfree(items->itemsCDA,freeINTEGER);
        assert(items->itemsCDA != 0);
        items->debug = 0;
        items->display = NULL;
        items->free = NULL;
        return items;
    }

//This method is passed a function that knows how to display the generic value stored in an array slot.
  void  setQUEUEdisplay(QUEUE *items,void (*d)(void *,FILE *)){
         setCDAdisplay(items->itemsCDA, d);
        items->display = d;
        return;
  }

//This method is passed a function that knows how to free the generic value stored in an array slot.
void  setQUEUEfree(QUEUE *items,void (*f)(void *)){
        items->free = f;
        setCDAfree(items->itemsCDA, f);
        return;
    }

// The value to be enqueued is stored in the underlying data structure. Runs in constant/amortized constant time.
void  enqueue(QUEUE *items,void *value){
        insertCDAback(items->itemsCDA, value);
}

//The value to be dequeued is removed in the underlying data structure. Runs in constant/amortized constant time.
void *dequeue(QUEUE *items){
         assert(sizeCDA(items->itemsCDA) > 0);
        void *temp = removeCDAfront(items->itemsCDA);
        return temp;
}

//Returns the value ready to come off the queue, but leaves the queue unchanged. Runs in constant time.
void *peekQUEUE(QUEUE *items){
      assert(sizeCDA(items->itemsCDA) > 0);
    void *temp = getCDA(items->itemsCDA, 0);
    return temp;
}

//Prints the items stored in the queue.
void  displayQUEUE(QUEUE *items,FILE *fp){
        if(items->debug == 1){
        debugCDA(items->itemsCDA, 0);
        displayCDA(items->itemsCDA, fp);
        return;
    }
    else if(items->debug == 2){ 
        debugCDA(items->itemsCDA, 1);
        displayCDA(items->itemsCDA, fp);
        return;
    }
     else{

    fprintf(fp, "<");
      
    for(int i = 0; i < sizeCDA(items->itemsCDA); i++){
  
         
            if(items->display == NULL){
                fprintf(fp, "@%p,", getCDA(items->itemsCDA, i));
            }
            
                
            
            else{
            
            items->display(getCDA(items->itemsCDA, i), fp);
            if(i >= 0 && i < sizeCDA(items->itemsCDA) - 1){
            fprintf(fp, ",");
            }
            }
    }
    
            fprintf(fp, ">");
     }

return;    
}

    
//An internal flag in the object to the given value. If the flag > 0, the display method adds a comma and the number of empty slots immediately after the last element.
int   debugQUEUE(QUEUE *items,int level){
         int temp = items->debug;
        items->debug = level;
    
    return temp;
    }

//If no free method is set, the individual items are not freed. In any case, the queue and its supporting allocations are freed.
void  freeQUEUE(QUEUE *items){
         freeCDA(items->itemsCDA);
    return;
    }
//Returns the number of items stored in the queue
 int   sizeQUEUE(QUEUE *items){
         return sizeCDA(items->itemsCDA);
    }

