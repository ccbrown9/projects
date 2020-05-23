#include <iostream>
#include <stdio.h>
using namespace std;

template<typename keytype,typename valuetype>
class Node
{
private:
public:
    keytype key;
    valuetype value;
    Node *left , *right, *parent;
    bool color, Red = true, Black = false;
    int size, heightN;
    Node(){
        value = NULL;
        key = NULL;
        left = right = parent = NULL;
        color = true;
        size = 1; heightN = 1;
    };
    Node(keytype key,valuetype value){
        this->key = key;
        this->value = value;
        left = right = parent = NULL;
        this->color = true;
        this->size = 1; this->heightN = 1;
    }
    void operator=(Node* x){
        key = x->key;
        value = x->value;
        parent = x->parent;
        left = x->left;
        right = x->right;
        color = x->color;
        //Rank = x->Rank; // this should not be here 
        size = x->size;
        heightN = x->heightN;
    }
};



template<typename keytype,typename valuetype>
class RBTree 
{
    private:
        Node <keytype,valuetype> *Root;
        bool Red = true;
        bool Black = false;
        int black_height;
        
    public:
        RBTree();
        RBTree(keytype[],valuetype[],int);
        ~RBTree();
        void destroyTree(Node<keytype,valuetype>*);
        void insert(keytype,valuetype);
        Node<keytype,valuetype>* insert_help(Node<keytype,valuetype>*,keytype,valuetype);
        valuetype* search(keytype);
        Node<keytype,valuetype>* search_help(Node<keytype,valuetype>*,keytype);
        int rank(keytype);
        int rank(keytype , Node<keytype, valuetype>*);
        int rank_help(Node<keytype,valuetype>*,keytype);
        int size();
        int size_from_here(Node<keytype,valuetype>*);
        int t_height();
        int tree_height(Node<keytype,valuetype>*);
        Node<keytype,valuetype>* fix_size_of_Node(Node<keytype,valuetype>*);
        int remove(keytype);
        Node<keytype,valuetype>* remove_help(Node<keytype,valuetype>*,keytype);
        Node<keytype,valuetype>* moveRedRight(Node<keytype,valuetype>*);
        Node<keytype,valuetype>* moveRedLeft(Node<keytype,valuetype>*);
        keytype min(Node<keytype,valuetype>*);
        keytype max(Node<keytype,valuetype>*);
        Node<keytype,valuetype>* deleteMin(Node<keytype,valuetype>*);
        Node<keytype,valuetype>* deleteMax(Node<keytype,valuetype>*);
        valuetype get(Node<keytype,valuetype>*,keytype);
        keytype select(int);
        Node<keytype,valuetype>* select_help(Node<keytype,valuetype>*,int);
        void split(keytype, RBTree<keytype,valuetype>&, RBTree<keytype,valuetype>&);
        void preorder();
        void inorder();
        void postorder();
        void pre_help(Node<keytype,valuetype>*);
        void in_help(Node<keytype,valuetype>*);
        void post_help(Node<keytype,valuetype>*);
        void operator=(RBTree&);
        bool operator>(keytype&);
        bool operator<(valuetype&);
        bool &operator[](valuetype&);
        Node<keytype,valuetype>* rotate_left(Node<keytype,valuetype>*);
        Node<keytype,valuetype>* rotate_right(Node<keytype,valuetype>*);
        Node<keytype,valuetype>* color_flip(Node<keytype,valuetype>*);
        bool isRed(Node<keytype,valuetype>*);

        Node<keytype,valuetype>* cleanUP(Node<keytype,valuetype>*);
};

template<typename keytype, typename valuetype>
valuetype RBTree<keytype,valuetype>::get(Node<keytype,valuetype>* node, keytype key){
    if(node == NULL) {
        return '\0';
    }

    if(key == node->key){ 
        return node->value;}

    if(key < node->key){
     return this->get(node->left, key);
    }
    else
    {
        return this->get(node->right,key);
    }
    
}


template<typename keytype, typename valuetype>
Node<keytype,valuetype>* RBTree<keytype,valuetype>::deleteMax(Node<keytype,valuetype>* node){
    if(this->isRed(node->left)){
        node = this->rotate_right(node);
    }

    if(node->right == NULL){
        return NULL;
    }
    if(!this->isRed(node->right) && !this->isRed(node->right->left)){
        node = moveRedRight(node);
    }
    node->right = this->deleteMax(node->right);
    node = this->cleanUP(node);
    return node;
}

template<typename keytype, typename valuetype>
Node<keytype,valuetype>* RBTree<keytype,valuetype>::deleteMin(Node<keytype,valuetype>* node){
    if(node->left == NULL) return NULL;

    if(!this->isRed(node->left) && !this->isRed(node->left->left)){
        node = this->moveRedLeft(node);
    }
    node->left = this->deleteMin(node->left);
    node = this->cleanUP(node);
    return node;
}


template<typename keytype, typename valuetype>
keytype RBTree<keytype,valuetype>::min(Node<keytype,valuetype>* node){
    if(node->left == NULL) return node->key;
    else
    {
        return min(node->left);
    } 
}

template<typename keytype, typename valuetype>
keytype RBTree<keytype,valuetype>::max(Node<keytype,valuetype>* node){
    if(node->right == NULL) return node->key;
    else
    {
        return max(node->right);
    } 
}


template<typename keytype, typename valuetype>
int RBTree<keytype,valuetype>::remove(keytype key){
    Node<keytype,valuetype>* temp = this->Root;
    temp = this->remove_help(temp,key);
    //this->Root = this->remove_help(this->Root,key);
    if(temp == NULL) return 0;
    else
    {
        return 1;
    }
    this->Root->color = Black;
    
}
template<typename keytype, typename valuetype>
Node<keytype,valuetype>* RBTree<keytype,valuetype>::remove_help(Node<keytype,valuetype>* node,keytype key){
    Node<keytype,valuetype>* evict = this->search_help(node,key);
    if(evict == NULL){
        return NULL;
    }
    if (key < evict->key)
    {
        if(!this->isRed(evict->left) && !this->isRed(evict->left->left)){
            evict = this->moveRedLeft(evict);
        }
        evict->left = this->remove_help(evict->left,key);
    }
    else
    {
        if(this->isRed(evict->left)){
            evict = this->rotate_right(evict);
        }
        if(key == evict->key && evict->right == NULL){
            return NULL;
        }
        if(!this->isRed(evict->right) && !this->isRed(evict->right->left)){
            evict = this->moveRedRight(evict);
        }
        if(key == evict->key){
            evict->value = this->get(evict->right,this->min(evict->right));
            evict->key = this->min(evict->right);
            evict->right = this->deleteMin(evict->right);
        }
        else
        {
            evict->right = this->remove_help(evict->right,key);
        }
    }
    evict = this->cleanUP(evict);
    return evict;
}

template<typename keytype, typename valuetype>
Node<keytype,valuetype>* RBTree<keytype,valuetype>::moveRedRight(Node<keytype,valuetype>* node){
    node = this->color_flip(node);
    if(this->isRed(node->left->left)){
        node = rotate_right(node);
        node = this->color_flip(node);
    }
    return node;
}

template<typename keytype, typename valuetype>
Node<keytype,valuetype>* RBTree<keytype,valuetype>::moveRedLeft(Node<keytype,valuetype>* node){
    node = this->color_flip(node);
    if(this->isRed(node->right->left)){
        node->right = rotate_right(node->right);
        node = rotate_left(node);
        node = this->color_flip(node);
    }
    return node;
}

template<typename keytype, typename valuetype>
Node<keytype,valuetype>* RBTree<keytype,valuetype>::cleanUP(Node<keytype,valuetype>* node){
    if(this->isRed(node->right)){
        node = this->rotate_left(node);
    }
    if(this->isRed(node->left) && this->isRed(node->left->left)){
        node = this->rotate_right(node);
    }
    if(this->isRed(node->left) && this->isRed(node->right)){
        node = this->color_flip(node);
    }
    return this->fix_size_of_Node(node);
}


template<typename keytype, typename valuetype>
keytype RBTree<keytype,valuetype>::select(int pos){
    Node<keytype,valuetype>* slt = this->Root;
    slt = select_help(slt,pos);
    return slt->key;
}
template<typename keytype, typename valuetype>
Node<keytype,valuetype>* RBTree<keytype,valuetype>::select_help(Node<keytype,valuetype>*node ,int pos){
    int r = this->size_from_here(node->left) + 1;
    if(pos == r){
        return node;
    }
    if(pos < r){ return select_help(node->left,pos);}
    if(pos > r){ return select_help(node->right,pos-r);}
}



template<typename keytype, typename valuetype>
int RBTree<keytype,valuetype>::size(){
    return this->size_from_here(this->Root);
}
template<typename keytype, typename valuetype>
int RBTree<keytype,valuetype>::size_from_here(Node<keytype,valuetype>* node){
    if(node == NULL){
        return 0;
    }
    else
    {
        return node->size;
    } 
}
template<typename keytype, typename valuetype>
int RBTree<keytype,valuetype>::t_height(){
    return tree_height(this->Root);
}

template<typename keytype, typename valuetype>
int RBTree<keytype,valuetype>::tree_height(Node<keytype,valuetype>* node){
    if(node == NULL)return 0;
    else return node->heightN;
}

template<typename keytype, typename valuetype>
Node<keytype,valuetype>* RBTree<keytype,valuetype>::fix_size_of_Node(Node<keytype,valuetype>* node){
    node->size = this->size_from_here(node->left) + this->size_from_here(node->right) + 1;
    if(this->tree_height(node->left) > this->tree_height(node->right)){
        node->heightN = this->tree_height(node->left) + 1;
    }
    else
    {
        node->heightN = this->tree_height(node->right) + 1;
    }
    return node;
}

template<typename keytype,typename valuetype>
RBTree<keytype,valuetype>::RBTree(){
    this->Root = NULL;
}

/*For this constructor the tree should be built using
the arrays K and V containing s items of keytype
and valuetype*/
template<typename keytype, typename valuetype>
RBTree<keytype,valuetype>::RBTree(keytype key[], valuetype val[],int s){
    for (int i = 0; i < s; i++)
    {
        this->insert(key[i],val[i]);
    }
    
}

template<typename keytype, typename valuetype>
void RBTree<keytype,valuetype>::destroyTree(Node<keytype,valuetype> *ptr){
    if(ptr){
        destroyTree(ptr->left);
        destroyTree(ptr->right);
        delete ptr;
    }
    //cout << "\n Tree is destroyed\n";
}

template<typename keytype, typename valuetype>
RBTree<keytype,valuetype>::~RBTree(){
    this->destroyTree(this->Root);
}


//insert from BST


template<typename keytype, typename valuetype>
void RBTree<keytype,valuetype>::insert(keytype key,valuetype value){
    this->Root = this->insert_help(this->Root,key,value);
    if(this->isRed(this->Root)){
        black_height++;
    }
    this->Root->color = Black;
    this->fix_size_of_Node(this->Root);
}

template<typename keytype, typename valuetype>
Node<keytype,valuetype>* RBTree<keytype,valuetype>::insert_help(Node<keytype,valuetype>* node , keytype key, valuetype value){
    //Node<keytype,valuetype> *newnode  = new Node<keytype,valuetype>(key,value);
    if(node == NULL){
        //Node<keytype,valuetype> *newnode  = new Node<keytype,valuetype>(key,value);
        //node = newnode;
        //return node;
        return new Node<keytype,valuetype>(key,value);
    }
    if(node->key == key){
        node->value = value;
    }
    else if(key < node->key){
        node->left = insert_help(node->left,key,value);
    }
    else if(key > node->key){
        node->right = insert_help(node->right,key,value);
    }
    if(this->isRed(node->left) && this->isRed(node->right)){
        node = this->color_flip(node);   
    }
    if(this->isRed(node->right)){
        node = this->rotate_left(node);
       
    }
    if(this->isRed(node->left) && this->isRed(node->left->left)){
        node = this->rotate_right(node);
        
    }
 
    return this->fix_size_of_Node(node);
}

template<typename keytype, typename valuetype>
valuetype* RBTree<keytype,valuetype>::search(keytype key){
       Node<keytype,valuetype>* check = this->Root;
       valuetype* item;
       check = this->search_help(check,key);
       if(check != NULL && check->key == key){
           item = &check->value;
           return item;
       }
       else
       {
           return NULL;
       }
}

template<typename keytype, typename valuetype>
Node<keytype,valuetype>* RBTree<keytype,valuetype>::search_help(Node<keytype,valuetype>* node, keytype key){
    if(node == NULL){return NULL;}
    if(node->key == key){return node;}
    if(key < node->key){
        return this->search_help(node->left,key);
    }
    if(key > node->key){
        return this->search_help(node->right,key);
    }
}

template<typename keytype, typename valuetype>
void RBTree<keytype,valuetype>::inorder(){
    Node<keytype,valuetype> *current = this->Root; 
    this->in_help(current);  
}
template<typename keytype, typename valuetype>
void RBTree<keytype,valuetype>::in_help(Node<keytype,valuetype>* node){
    if(node == NULL){
        return;
    }
    this->in_help(node->left);
    cout << node->key;
    this->in_help(node->right);
}
template<typename keytype, typename valuetype>
void RBTree<keytype,valuetype>::postorder(){
    Node<keytype,valuetype> *current = this->Root; 
    this->post_help(current);  
}
template<typename keytype, typename valuetype>
void RBTree<keytype,valuetype>::post_help(Node<keytype,valuetype>* node){
    if(node == NULL){
        return;
    }
    this->post_help(node->left);
    this->post_help(node->right);
    cout << node->key;
}
template<typename keytype, typename valuetype>
void RBTree<keytype,valuetype>::preorder(){
    Node<keytype,valuetype> *current = this->Root; 
    this->pre_help(current);  
}
template<typename keytype, typename valuetype>
void RBTree<keytype,valuetype>::pre_help(Node<keytype,valuetype>* node){
    if(node == NULL){
        return;
    }
    cout << node->key;
    this->pre_help(node->left);
    this->pre_help(node->right);
}
template<typename keytype, typename valuetype>
Node<keytype,valuetype>* RBTree<keytype,valuetype>::rotate_left(Node<keytype,valuetype>* node){
    Node<keytype,valuetype>* x = node->right;
    node->right = x->left;
    x->left = this->fix_size_of_Node(node);
    x->color = x->left->color;
    x->left->color = Red;
    return this->fix_size_of_Node(x);
}

template<typename keytype, typename valuetype>
Node<keytype,valuetype>* RBTree<keytype,valuetype>::rotate_right(Node<keytype,valuetype>* node){
    Node<keytype,valuetype>* x = node->left;
    node->left = x->right;
    x->right = this->fix_size_of_Node(node);
    x->color = x->right->color;
    x->right->color = Red;
    return this->fix_size_of_Node(x);
}
template<typename keytype, typename valuetype>
Node<keytype,valuetype>* RBTree<keytype,valuetype>::color_flip(Node<keytype,valuetype>* node){
    Node<keytype,valuetype>* x = node;
    x->color = !x->color;
    x->left->color = !x->left->color;
    x->right->color = !x->right->color;
    return x;
}

template<typename keytype, typename valuetype>
bool RBTree<keytype,valuetype>::isRed(Node<keytype,valuetype>* node){
    if(node == NULL){return false;}
    else{
        return (node->color == Red );
    }
}

template<typename keytype, typename valuetype>
int RBTree<keytype, valuetype>::rank(keytype k){
	return 1+rank(k, Root);
}
template<typename keytype, typename valuetype>
int RBTree<keytype, valuetype>::rank(keytype k, Node<keytype, valuetype>* x){
	if (x == nullptr){
        return 0;
    } 
	if (k < x->key){
         return rank(k, x->left);
    }
	if (k > x->key) {
        return 1 + x->left->size + rank(k, x->right);}
	else {
		if (x->left == nullptr) return 0;
		else return x->left->size;
	}
}