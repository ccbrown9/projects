#include "stack.h"
#include "da.h"
#include "integer.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

    typedef struct stack {
    DA *itemsDA;    
    int capacity;
    int debug;
    void (*display)(void *, FILE *);
    void (*free)(void *);
}STACK;
    
    
    
     STACK *newSTACK(void){
             //d is the display function
            //f is the freeing function
        STACK *items = malloc(sizeof(STACK));
        items->itemsDA = newDA();
        setDAfree(items->itemsDA,freeINTEGER);
        assert(items != 0);
        items->debug = 0;
        items->display = NULL;
        items->free = NULL;
        return items;
    }
    
void  setSTACKdisplay(STACK *items, void (*d)(void *,FILE *)){
    setDAdisplay(items->itemsDA, d);
    items->display = d;
    return;
}

void  setSTACKfree(STACK *items, void (*f)(void *)){
    items->free = f;
    setDAfree(items->itemsDA, f);
    return;
    }
  
void  push(STACK *items,void *value){
    insertDA(items->itemsDA, sizeDA(items->itemsDA), value);
    return;
}

void *pop(STACK *items){
    assert(sizeDA(items->itemsDA) > 0);
    void *temp = removeDA(items->itemsDA, sizeDA(items->itemsDA) - 1);
    return temp;
}

void *peekSTACK(STACK *items){
    assert(sizeDA(items->itemsDA) > 0);
    void *temp = getDA(items->itemsDA, 0);
    return temp;
}
void displaySTACK(STACK *items,FILE *fp){
    if(items->debug == 1){
        debugDA(items->itemsDA, 0);
        displayDA(items->itemsDA, fp);
        return;
    }
    else if(items->debug == 2){ 
        debugDA(items->itemsDA, 1);
        displayDA(items->itemsDA, fp);
        return;
    }
     else{

    fprintf(fp, "|");

    for(int i = sizeDA(items->itemsDA)-1; i >= 0; i--){
         
            if(items->display == NULL){
                fprintf(fp, "@%p,", getDA(items->itemsDA, i));
            }
            
                
            
            else{
            
            items->display(getDA(items->itemsDA, i), fp);
            if((i < sizeDA(items->itemsDA)) && (i != 0)){
            fprintf(fp, ",");
            }
            }
    }
            fprintf(fp, "|");
     }

return;    
}



int debugSTACK(STACK *items,int level){
    int temp = items->debug;
    items->debug = level;
    
    return temp;
}

void  freeSTACK(STACK *items){
    freeDA(items->itemsDA);
    return;
}

int  sizeSTACK(STACK *items){
    return sizeDA(items->itemsDA);
  
}