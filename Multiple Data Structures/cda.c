#include "cda.h"
#include "stdlib.h"
#include "stdio.h"
#include "assert.h"

 struct cda 
{
     void **array;
    int size;
    int capacity;
    int debug;
    int head;
    int tail;
    void (*display)(void *,FILE *);
    void (*free)(void *);

   
  
};


CDA *newCDA(void)
{
    CDA *newCDA = malloc(sizeof(CDA));

    assert(newCDA != 0);

    newCDA->size = 0;
    newCDA->capacity = 1;
    newCDA->debug = 0;
    newCDA->free = 0;
    newCDA->display = 0;
    newCDA->head = 0;
    newCDA->tail = 0;

    newCDA->array = malloc(sizeof(void*));
    
    return newCDA;
}


void setCDAdisplay(CDA *items, void (*d)(void *,FILE *))
{
    items->display = d;
}

void setCDAfree(CDA *items, void (*f)(void *))
{
    items->free = f;
}



void insertCDA(CDA *items,int index,void *value) 
{
   
    
   
    assert(index >= 0 && index <= items->size);
    
    if(items->size == items->capacity)
    {
        int grow = (items->capacity * 2);
        void **temp = malloc(sizeof(void*) * grow);
        assert(temp != 0);


        for(int i = 0; i < items->size; i++)
        {
            temp[i] = getCDA(items,i);
        }
        items->head = 0;
        items->tail = items->size-1;
        free(items->array);

        items->array = temp;

        items->capacity = grow;

    }

    if(index <= items->size/2 )
    {
        items->size++;
        items->head = (items->head - 1);
        items->head = (items->head+items->capacity) % items->capacity;
  
        for(int i = 0; i < index; i++)
        {
            setCDA(items,i,getCDA(items,(i+1)));
        }
           
            setCDA(items,index,value);
            
    }

    else
    {
        items->size++;
       
   
        items->tail++;
        
       items->tail = (items->tail+items->capacity) % items->capacity;
        
       for(int i = items->size-1;i > index; i--)
        {
          
            setCDA(items,i,getCDA(items,(i-1)));
           
        }
            
            setCDA(items,index,value);
           
    }
}

void *removeCDA(CDA *items,int index)
{
    assert(index >= 0 && index <= items->size);

    void *temp = getCDA(items,index);

    if(index == items->head)
    {
        items->head++;
        items->head = (items->head+items->capacity) % items->capacity;
        items->size--;
    }
    
    else if(index == items->size - 1)
    {
        items->size--;
        items->tail--;
        items->tail = (items->tail+items->capacity) % items->capacity;
    }

    else 
    {  
         for(int i = index; i < items->size; i++)
            {
                setCDA(items,i,getCDA(items,(i+1)));
            }
       
        items->size--;
    }

    if(items->size < (items->capacity/4.0))
    {
         void * temp = items->array;

        items->array = malloc(sizeof((items->capacity / 2)));
        
        for(int i = 0; i < items->size; i++)
        {
            items->array[i] = getCDA(temp,i);
        }

        items->capacity = items->capacity/2;
    }  
  
    return temp; 
}

void unionCDA(CDA *recipient,CDA *donor)
{
    for(int i = 0; i < donor->size; i++)
    {
        insertCDA(recipient,recipient->size,donor->array[i]);
    }

    donor->size = 0;
    donor->capacity = 1;
}

void *getCDA(CDA *items,int index)
{
    
    int get = ((index+items->head)+items->capacity) % items->capacity;
   
    return items->array[get];
}

void *setCDA(CDA *items,int index,void *value)
{
    assert(index >= (-1) && index<= items->size);
   
    int newIndex = ((index+items->head)+items->capacity) % items->capacity;
 
    void *temp = items->array[newIndex];
    items->array[newIndex] = value;
   
    return temp;
}

int  sizeCDA(CDA *items)
{
    return items->size;
}

void displayCDA(CDA *items,FILE *fp)
{   
    fprintf(fp,"(");
    
    
    
   
    if(items->debug != 0) 
    {
        if(items->display != 0) 
        {
            for (int i = 0; i < items->size; i++)
            {
            
                items->display(getCDA(items,i),fp);
                fprintf(fp,",");
            }
                fprintf(fp,"(%d)",items->capacity - items->size);
        }

        else if(items->display == 0)
        {
            for(int i = 0; i < items->size; i++)
            {
                items->display(getCDA(items,i),fp);
                if(i<items->size)
                {
                    printf(",");
                }
            }
                fprintf(fp,"(%d)",items->capacity - items->size);
        }
    }
    
    
    if(items->debug == 0)
    {
        if(items->display != 0)
        {
            
            for (int i = 0; i < items->size; i++)
            {
              
                items->display(getCDA(items,i),fp);
        
             
                if(i < items->size-1)
                {
                    fprintf(fp,",");
                }
            }            
        }

     
        if(items->display == 0)
        {
            for(int i = 0; i < items->size; i++)
            {
                fprintf(fp,"@");
                items->display(getCDA(items,i),fp);
                
                if(i < items->size-1)
                {
                    fprintf(fp,",");
                }
            }
                fprintf(fp,")");
        }  
    }
            
    fprintf(fp,")");

 
}


int  debugCDA(CDA *items,int level)
{
    int temp = items->debug;
    
    items->debug = level;

    return temp;
}


void freeCDA(CDA *items)
{
    if (items->free != 0)
    {
        for(int i = 0; i < items->size; i++)
        {
            items->free(getCDA(items,i)); 
        } 
    }
    
    free(items->array);
    free(items);
}
