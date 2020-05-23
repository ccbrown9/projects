

#include "da.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// Bulds "da" struct with pointers
typedef struct da {
    int size;
    int capacity;
    int debug;
    void **array;
    void (*display)(void *, FILE *);
    void (*free)(void *);
}DA;

//Constructor to build da
DA *newDA(void){
    DA *newDA = (DA*) malloc(sizeof(DA));
    assert(newDA != 0);
    newDA->size = 0;
    newDA->capacity = 1;
    newDA->debug = 0;
    newDA->array = ((void**)malloc(sizeof(void*) * newDA->capacity));
    newDA->display = NULL;
    newDA->free = NULL;
    return newDA;
}

//Displays generic value stored in the array slot
void  setDAdisplay(DA *items,void (*d)(void *,FILE *)){
    items->display = d;
    return;
}

void  setDAfree(DA *items,void (*f)(void *)){
    items->free = f;
    return;
}

void insertDA(DA *items,int index, void *value){


    assert(items->array != 0);
 //If size is equal to capacity double size of array by two by using function realloc
    if(items->size == items->capacity){
       
       items->array = realloc(items->array, sizeof(void*) * (items->capacity * 2));
        items->capacity = items->capacity * 2;
        for(int i = items->size + 1; i < items->capacity; i++){
            items->array[i] = (void*) malloc(sizeof(void*));
        } 
    }


    //Case 1: If index insert is the last element in array execute in constant time.
    if(index == items->size){
     
        items->array[index] = value;
        items->size++;
    }
    //Case 2: insert at index and move remaining elements higher in array. Executes in linear time
  
       
    else{
     
        void *temp, *temp2;
         temp = items->array[index];
         items->array[index] = value;
         items->size++;
         for(int i = index; i < items->size; i++){
             temp2 = items->array[i+1];
             items->array[i+1] = temp;
             temp = temp2;
         }
          
    
    }
    

   
   
    return;
}

void *removeDA(DA *items,int index){   //Add code to not shrink below 1
    
    assert(items->size > 0);
    
    //Sets value to be removed in temp.
   
    void *temp = items->array[index];
    items->array[index] = NULL;
    items->size--;
    //int ratio = items->capacity / 4;
    
    // Case 1: If value to be removed is in the back, execute in constant time.
    if(index == items->size) {
        //return temp;
    }
    
    // Case 2: Otherwise execute in linear time.
    else{
        for(int i = index + 1; i <= items->size; i++){
            items->array[i-1] = items->array[i];
        }
    }
    
    // If size to capacity ratio drops below 25% shrink the array by half
    if(items->size < (items->capacity) / 4 ) {
        if(items->size == 0){
            items->capacity = 1;
            items->array = realloc(items->array, sizeof(void*) * (items->capacity));
        }
        else{
           
        items->array = realloc(items->array, sizeof(DA) * (items->capacity/2));
        items->capacity = items->capacity / 2;
        }
        
        //for(int i = items->size; i <= items->capacity; i++){
          // items->array[i] = NULL;
        //}
    }
     
    //Returns value to be removed
    return temp;
}

void unionDA(DA *recipient,DA *donor){
    // Case 1: If donor is empty do nothing
    if(donor->size == 0){
        return;
    }
    
    for(int i = 0; i < donor->size; i++){
        insertDA(recipient, recipient->size, donor->array[i]);
    }
    return;
}

//The get method returns the value at the given index. It should run in constant time.
void *getDA(DA *items,int index){
    
    assert((index >= 0) && (index < items->size));
    if(items->array[index] == NULL){
        return NULL;
    }
    void *temp = items->array[index];
    return temp;
}

//If the given index is equal to the size, the value is inserted via the insert method. The method returns the replaced value or the null pointer if no value was replaced. It should run in constant or amortized constant time (in the case of the insert method being called).
void *setDA(DA *items,int index,void *value){
    assert((index >= 0) && (index <= items->size));
    if(index == items->size){
        insertDA(items, index, value);
        void *temp = getDA(items, index);
        return temp;
    }
    
    void *temp = items->array[index];
    insertDA(items, index, value);
    return temp;
    
}

int sizeDA(DA *items){
    return items->size;
}

void  displayDA(DA *items,FILE *fp){
    int emptySlots = 0;
    fprintf(fp, "[");

    for(int i = 0; i < items->size; i++){
         
            if(items->display == NULL){
                fprintf(fp, "@%p,", items->array[i]);
            }
            
                
            
            else{
           
            items->display(items->array[i], fp);
            if(i < items->size-1){
            fprintf(fp, ",");
            }
            }
    }
            if(items->debug > 0){
               emptySlots = items->capacity - items->size;
               if(items->size != 0){
                   printf(",");
               }
               fprintf(fp, "[%i]", emptySlots);
            }
            fprintf(fp, "]");


return;    
}


//Frees all elements of the array.
void freeDA(DA *items){
    for(int i = 0; i <= items->size; i++){
        items->array[i] = NULL;
    }
    items->size = 0;
    items = realloc(items, sizeof(DA) * 1);
    items->capacity = 1;
    return;
}


int debugDA(DA *items,int level){
    int temp = items->debug;
    items->debug = level;
    
    return temp;
}