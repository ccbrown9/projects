//Charity Brown - Project 4 CS 101 - Dixon

#include <iostream>
#include <fstream>
#include <string>
#include "Huffman.h"

using namespace std;

Huffman :: Huffman(Node **arr, int len) { //Allocates Space
    size = len;
    int i;
    child = new Node *[size];      
    i = 0;
    while(i < size){
       child[i] = new Node;
       i++;
}
i = 0;
    while(i < size){      
        child[i] = arr[i];   
        i++;
        }

    for ( i = size - 1; i >= 0; i--) {
        bubbleDown(i);
}
}
void Huffman :: bubbleDown(int index) { //Swaps out of order nodes
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    int min = index;

    if (left >= size){
        return; 
        }

    if (child[index]->freq >= child[left]->freq){            
        min = left;                     
    }
    
    if (right < size && (child[index]->freq > child[right]->freq)){  
        min = right;                       
    }
    if (min != index) {
        Node *temp = child[index];     
        child[index] = child[min];
        child[min] = temp;
        bubbleDown(min);
    }
}

void Huffman :: addTo(Node *newNode) { //Creating Heap
    child[size] = new Node;        
    child[size] = newNode;
    size++;

    for (int i = size - 1; i >= 0; i--) {
        bubbleDown(i);
        }
}

Node *Huffman :: remove() {  // Removes root from heap 
    Node *temp = child[0];     
    child[0] = child[size-1]; 
    size--;
    bubbleDown(0);

    return temp;
}

void Huffman :: createHuffman() { //Changes heap to huffman
    Node *x = new Node;
    Node *y = new Node;

    int ch = 128;       
    while (size > 1) {
        x = remove();
        y = remove();
        Node *temp = new Node;      
        temp->identifier = ch;
        temp->freq = x->freq + y->freq;
        temp->left = x;
        temp->right = y;
        addTo(temp);
        ch++;
    }
}

void Huffman :: createCode(Node *root, string str, ofstream& out) { // Makes code from left huffman 0 and right huffman 1
    if (root == NULL){           
        return;
        }
    if (root->identifier < 128) {
        root->code = str;
        out << (int)root->identifier << ": " << str << endl;
    }

    createCode(root->left, str + "0", out);
    createCode(root->right, str + "1", out);
}

void Huffman :: inOrder(Node *root, ofstream& out) {
    if (root == NULL){
        return;
        }

    inOrder(root->left, out);       
    out << (char)root->identifier;
    inOrder(root->right, out);
}

void Huffman :: preOrder(Node *root, ofstream& out) {
    if (root == NULL){
        return;
        }

    out << (char)root->identifier;      
    preOrder(root->left, out);
    preOrder(root->right, out);
}

void Huffman :: encode(Node *root, unsigned char ch, ofstream& out) { //moves through tree to assign code
    if (root->left == NULL && root->right == NULL) {    
        if (root->identifier == ch)               
            out << root->code;
    }

    if (root->left != NULL) {                
        encode(root->left, ch, out);
}
    if (root->right != NULL) {               
        encode(root->right, ch, out);
}
}


