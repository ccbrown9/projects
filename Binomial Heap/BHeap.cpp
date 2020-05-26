

#include <iostream>
#include <cstdlib>
using namespace std;
/*
 * Node Declaration
 */

/*
 * Class Declaration
 */
template<typename keytype, typename valuetype>
class BHeap
{
    struct node{
    //int n;
    keytype key;
    valuetype value;
    int degree;
    node* parent;
    node* child;
    node* sibling;
    };
    private:
        node *H;
        node *Hr;
        int count;
    public:
    
       
   
 
/*
 * Initialize Heap
 */
node* Initializeheap(){
    node* np;
    np = NULL;
    return np;
}
/*
 * Linking nodes in Binomial Heap
 */
int Binomial_link(node* y, node* z){
    y->parent = z;
    y->sibling = z->child;
    z->child = y;
    z->degree = z->degree + 1;
}
/*
 * Create Nodes in Binomial Heap
 */
BHeap(){

            H = Initializeheap();
            Hr = Initializeheap();
            int count = 0;
}
~BHeap(){
    H = NULL;
}

void operator=(BHeap<keytype, valuetype> &H1){
    this->H = H1->H;
    this->count = H1->count;
}
 BHeap(keytype k[], valuetype V[], int s){
     H = Initializeheap();
     count = 0;
    for(int i = 0;i < s;i++){
    node* p = new node;
    p->key = k[i];
    p->value = V[i];
     //H = NULL;
    H = Inserthelp(H,p);
    count++;
    }
  return;

}
node* Create_node(int k){
    node* p = new node;
    p->n = k;
    return p;
}
/*
 * Insert Nodes in Binomial Heap
 */
node* Inserthelp(node* H, node* x){
    node* H1 = Initializeheap();
    x->parent = NULL;
    x->child = NULL;
    x->sibling = NULL;
    x->degree = 0;
    H1 = x;
    H = Union(H, H1);
    return H;
}

void insert(keytype k, valuetype V){    
   
 node* p = new node;
    p->key = k;
    p->value = V;
   H = Inserthelp(H,p);
    return;

}
 
/*
 * Union Nodes in Binomial Heap
 */
node* Union(node* H1, node* H2){
    node *H = Initializeheap();
    H = mergeHelp(H1, H2);
    if (H == NULL)
        return H;
    node* prev_x;
    node* next_x;
    node* x;
    prev_x = NULL;
    x = H;
    next_x = x->sibling;
    while (next_x != NULL) {
        if ((x->degree != next_x->degree) || ((next_x->sibling != NULL)
            && (next_x->sibling)->degree == x->degree))
        {
            prev_x = x;
            x = next_x;
        }
        else
	    {
            if (x->key <= next_x->key)
            {
                x->sibling = next_x->sibling;
                Binomial_link(next_x, x);
            }
            else
            {
                if (prev_x == NULL)
                    H = next_x;
                else
                    prev_x->sibling = next_x;
                Binomial_link(x, next_x);
                x = next_x;
            }
	    }
        next_x = x->sibling;
    }
    return H;
}
/*
 * mergeHelp Nodes in Binomial Heap
 */
void merge(BHeap<keytype,valuetype> &H1){
    
    H = Union(H, H1.H);
    return;
    
}

node* mergeHelp(node* H1, node* H2){
    node* H = Initializeheap();
    node* y;
    node* z;
    node* a;
    node* b;
    y = H1;
    z = H2;
    if (y != NULL) {
        if (z != NULL){
            if (y->degree <= z->degree)
                H = y;
            else if (y->degree > z->degree)
                H = z;
        }
        else
            H = y;
    }
    else
        H = z;
    while (y != NULL && z != NULL) {
        if (y->degree < z->degree) {
            y = y->sibling;
        }
        else if (y->degree == z->degree) {
            a = y->sibling;
            y->sibling = z;
            y = a;
        }
        else{
            b = z->sibling;
            z->sibling = y;
            z = b;
        }
    }
    return H;
}
/*
 * Display Binomial Heap
 */
void preOrder(node *x){

 if (x != NULL) {
        //cout << "B" << x->degree;
        cout << x->key << " ";
           
        preOrder(x->child);
         
        preOrder(x->sibling);
        
        //preOrder(x->sibling);
    }
    
    return;
}


void printKey(){
    if (H == NULL)
    {
        cout<<"The Heap is empty"<<endl;
        return;
    }
    preOrder(H);
    cout << "roots are: ";
    node *p = H;
    while(p!= NULL){
        cout << p->key << " of degree B" << p->degree << " ";
        p = p->sibling;
    }
    //cout << "B" << H->sibling->degree << endl;
   //preOrder(H->sibling);
   cout << endl;
  // preOrderSibling(H);
   //cout << endl;
   

    /*
    node* p;
    p = H;
    while (p != NULL) {
        cout << "B"<< p->degree << endl;
        cout<<p->key << " ";
        node *temp = p;
        while(temp->child != NULL){
            cout << temp->child->key << " ";
            temp = temp->child;
        }

        
        if (p->sibling != NULL)
            cout<<endl;
        p = p->sibling;
    }
    */
    //cout<<endl;
}
/*
 * Extract Minimum
 */
keytype extractMin(){
    node *H1 = H;
    Hr = NULL;
    node* t = NULL;
    node* x = H1;
    if (x == NULL)
    {
        cout<<"Nothing to Extract"<<endl;
        return x->key;
    }
    keytype min = x->key;
    node* p = x;
    while (p->sibling != NULL)
    {
        if ((p->sibling)->key < min)
        {
            min = (p->sibling)->key;
            t = p;
            x = p->sibling;
        }
        p = p->sibling;
    }
    if (t == NULL && x->sibling == NULL)
        H1 = NULL;
    else if (t == NULL)
        H1 = x->sibling;
    else if (t->sibling == NULL)
        t = NULL;
    else
        t->sibling = x->sibling;
    if (x->child != NULL)
    {
        Revert_list(x->child);
        (x->child)->sibling = NULL;
    }
    H = Union(H1, Hr);
    return x->key;
}
/*
 * Reverse List
 */
int Revert_list(node* y){
    if (y->sibling != NULL)
    {
        Revert_list(y->sibling);
        (y->sibling)->sibling = y;
    }
    else
    {
        Hr = y;
    }
}
 
/*
 * Search Nodes in Binomial Heap
 */


keytype peakKey(){
 
    
    node *x = H;
    keytype temp = x->key;
    while(x->sibling != NULL){
        if(temp < x->sibling->key){
            temp = x->key;
        }
        else{
            temp = x->sibling->key;
        }
        x = x->sibling;
    }
    return temp;
    
}


valuetype peakValue(){
    node *x = H;
    valuetype temp = x->value;
    while(x->sibling != NULL){
        if(temp < x->sibling->value){
            temp = x->value;
        }
        else{
            temp = x->sibling->value;
        }
        x = x->sibling;
    }
    return temp;
}


};
