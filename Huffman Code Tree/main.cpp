
// Charity Brown - Project 4 CS 101 - Dixon

#include <iostream>
#include <fstream>
#include "Huffman.cpp"


using namespace std;

int main(int argc, char *argv[]) {
    int i;
    if (argc != 2) {
        cout << "./encode <filename>" << endl;  // Reads in file puts frequency and character into arrays and passes to the class to form heap and huffman
        return 1;
    }
    ifstream in(argv[1], ios::in|ios::binary|ios::ate);
    unsigned char ch;
    int ascii[128], size = 0, index = 0;

    int file = in.tellg();
    in.seekg(0, ios::beg);
i = 0;
    while(i < 128){
        ascii[i] = 0;
        i++;
    }
    i = 0;
    while(i < file) {    
        ch = in.get();
        ascii[ch]++;
        i++;
    }
    i = 0;
    while(i < 128) {     
        if (ascii[i] > 0){
            size++;
        }
    i++;
    }

    Node **array = new Node *[size];
    i = 0;
    while(i < size){
        array[i] = new Node;
    i++;
    }
    i = 0;
    while(i < 128) {
        if (ascii[i] > 0) {     
            Node *temp = new Node;  
            
            temp->identifier = (unsigned char) i; 
            temp->freq = ascii[i];      
            temp->left = NULL;      
            temp->right = NULL;     
            array[index] = temp;        
            index++;            
        }
        i++;
    }
    Huffman Heap(array, size);     
    Heap.createHuffman();              
    Node *root = Heap.remove();
    Heap.addTo(root);

    ofstream out1, out2, out3, out4;
    out1.open("inorder.txt");
    out2.open("preorder.txt");
    out3.open("code.txt");
    out4.open("tree.txt");

    Heap.createCode(root, "", out4);
    out4 << endl;

    out4 << "Pre-order: ";              
    Heap.preOrder(root, out2);         
    Heap.preOrder(root, out4);         
    out4 << endl;                   
    out4 << "In-order: ";               
    Heap.inOrder(root, out1);          
    Heap.inOrder(root, out4);      

    in.seekg(0, ios::beg);              
    i = 0;
    while(i < file) {        
        ch = in.get();              
        Heap.encode(root, ch, out3);
    i++;
    }


    in.close();
    out1.close();
    out2.close();
    out3.close();
    out4.close();

    return 0;
}

