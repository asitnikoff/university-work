#ifndef TREE_H
#define TREE_H


struct Node {
    int key, height;
    Node *left, *right;
    Node(int key_) {
        key = key_;
        left = right = nullptr;
        height = 1;
    }
};


int getHeight(Node*);
int getBalanceFactor(Node*);
void fixHeight(Node*);
Node* rotateRight(Node*);
Node* rotateLeft(Node*);
Node* balanceTree(Node*);
Node* insertTree(Node*, int);
Node* findMin(Node*);
Node* removeMin(Node*);
Node* remove(Node*, int);
bool findKey(Node*, int);
void viewTree(Node*, int = 0);
void clearTree(Node*&);
void straightViewTree(Node*);
void reverseViewTree(Node*);
void increasingViewTree(Node*);
void decreasingViewTree(Node*);
int countLeavesInTree(Node*);


#endif