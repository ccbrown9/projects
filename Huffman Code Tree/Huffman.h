//Charity Brown - Project 4 CS 101 - Dixon

#ifndef HUFF_H
#define HUFF_H

#include <iostream>
#include <fstream>
#include <string>

using namespace std;


struct Node {
    unsigned char identifier;
    int freq;
    string code;
    struct Node *left;
    struct Node *right; 
};

class Huffman {
    private:
        Node **child;
        int size;
    public:
        Huffman(Node* [], int);
        void bubbleDown(int);
        void addTo(Node*); 
        void createHuffman();
        void createCode(Node*, string, ofstream&);
        void inOrder(Node*, ofstream&);
        void preOrder(Node*, ofstream&);
        void encode(Node*, unsigned char, ofstream&);               
        Node *remove();
};
#endif
