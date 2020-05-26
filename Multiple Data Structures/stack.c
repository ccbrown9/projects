#include "stack.h"
#include "da.h"
#include "integer.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


// This stack uses a Dynamic Array for storage
    typedef struct stack {
    DA *itemsDA;    
    int capacity;
    int debug;
    void (*display)(void *, FILE *);
    void (*free)(void *);
}STACK;
    
    
// Initialization of new stack 
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

// Pushes an item to the stack. Runs in constant or amortized constant time.
void  push(STACK *items,void *value){
    insertDA(items->itemsDA, sizeDA(items->itemsDA), value);
    return;
}

// Removes the item to be popped. Runs in constant or amortized constant time.
void *pop(STACK *items){
    assert(sizeDA(items->itemsDA) > 0);
    void *temp = removeDA(items->itemsDA, sizeDA(items->itemsDA) - 1);
    return temp;
}

// Returns the value ready to come off the stack, but leaves the stack unchanged. Runs in constant time.
void *peekSTACK(STACK *items){
    assert(sizeDA(items->itemsDA) > 0);
    void *temp = getDA(items->itemsDA, 0);
    return temp;
}

//Prints the items stored in the stack
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


// If debug level = 1, the display method uses the underlying data structure's display method. 
//If the debug method = 2, the display method uses the underlying data structure's debugged display method.
int debugSTACK(STACK *items,int level){
    int temp = items->debug;
    items->debug = level;
    
    return temp;
}


//If no free method is set, the individual items are not freed. In any case, the array and its supporting allocations are freed.
void  freeSTACK(STACK *items){
    freeDA(items->itemsDA);
    return;
}

//Returns the size of the stack.
int  sizeSTACK(STACK *items){
    return sizeDA(items->itemsDA);
  
}
