#include "cda.h"
#include "queue.h"
#include "integer.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

    typedef struct queue {
    CDA *itemsCDA;    
    int debug;
    void (*display)(void *, FILE *);
    void (*free)(void *);
}QUEUE;
      
 

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

  void  setQUEUEdisplay(QUEUE *items,void (*d)(void *,FILE *)){
         setCDAdisplay(items->itemsCDA, d);
        items->display = d;
        return;
  }
void  setQUEUEfree(QUEUE *items,void (*f)(void *)){
        items->free = f;
        setCDAfree(items->itemsCDA, f);
        return;
    }
void  enqueue(QUEUE *items,void *value){
        insertCDAback(items->itemsCDA, value);
}
void *dequeue(QUEUE *items){
         assert(sizeCDA(items->itemsCDA) > 0);
        void *temp = removeCDAfront(items->itemsCDA);
        return temp;
}
void *peekQUEUE(QUEUE *items){
      assert(sizeCDA(items->itemsCDA) > 0);
    void *temp = getCDA(items->itemsCDA, 0);
    return temp;
}
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

    

int   debugQUEUE(QUEUE *items,int level){
         int temp = items->debug;
        items->debug = level;
    
    return temp;
    }

void  freeQUEUE(QUEUE *items){
         freeCDA(items->itemsCDA);
    return;
    }

 int   sizeQUEUE(QUEUE *items){
         return sizeCDA(items->itemsCDA);
    }

