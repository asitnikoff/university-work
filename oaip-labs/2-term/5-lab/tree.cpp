#include <iostream>

#include "tree.h"


int getHeight(Node *p) {
    return (p == nullptr) ? 0 : p->height;
}


int getBalanceFactor(Node *p)
{
    return getHeight(p->right) - getHeight(p->left);
}


void fixHeight(Node *p) {
    int height_left = getHeight(p->left);
    int height_right = getHeight(p->right);

    p->height = ((height_left > height_right) ? height_left : height_right) + 1;
}


Node *rotateRight(Node *p) {
    Node* q = p->left;
    p->left = q->right;
    q->right = p;
    fixHeight(p);
    fixHeight(q);

    return q;
}


Node *rotateLeft(Node *q) {
    Node *p = q->right;
    q->right = p->left;
    p->left = q;
    fixHeight(q);
    fixHeight(p);

    return p;
}


Node *balanceTree(Node *p) {
    fixHeight(p);

    if (getBalanceFactor(p) == 2) {
        if (getBalanceFactor(p->right) < 0) {
            p->right = rotateRight(p->right);
        }
        return rotateLeft(p);
    }
    if (getBalanceFactor(p) == -2) {
        if (getBalanceFactor(p->left) > 0) {
            p->left = rotateLeft(p->left);
        }
        return rotateRight(p);
    }
    return p;
}


Node *insertTree(Node *p, int key) {
    if (p == nullptr) {
        return new Node(key);
    }

    if (key < (p->key)) {
        p->left = insertTree(p->left, key);
    } else {
        p->right = insertTree(p->right, key);
    }

    return balanceTree(p);
}


Node *findMin(Node *p) {
    return (p->left != nullptr) ? findMin(p->left) : p;
}


Node *removeMin(Node *p) {
    if (p->left == nullptr) {
        return p->right;
    }

    p->left = removeMin(p->left);
    return balanceTree(p);
}


Node *remove(Node *p, int key) {
    if (p == nullptr) {
        return nullptr;
    }

    if (key < (p->key)) {
        p->left = remove(p->left, key);
    } else if (key > (p->key)) {
        p->right = remove(p->right, key);
    } else {
        Node* q = p->left;
        Node* r = p->right;
        delete p;

        if (r == nullptr) {
            return q;
        }

        Node* min_element = findMin(r);
        min_element->right = removeMin(r);
        min_element->left = q;
        return balanceTree(min_element);
    }
    return balanceTree(p);
}


void clearTree(Node *&p) {
    if (p->left != nullptr) {
        clearTree(p->left);
    }
    if (p->right != nullptr) {
        clearTree(p->right);
    }

    p->left = p->right = nullptr;
    delete p;
    p = nullptr;
}


void viewTree(Node *p, int space) {
    if (p == nullptr) {
        return;
    }

    const int COUNT = 2;

    space += COUNT;

    viewTree(p->right, space);

    for (int i = COUNT; i < space; ++i) {
        std::cout << "  ";
    }
    std::cout << p->key << std::endl;

    viewTree(p->left, space);
}


bool findKey(Node *p, int key) {
    return (key < p->key) ? findKey(p->left, key) :
           (key > p->key) ? findKey(p->right, key) :
           (key == p->key);
}


void straightViewTree(Node *p) {
    if (p == nullptr) {
        return;
    }

    std::cout << " [" << p->key << "]";

    straightViewTree(p->left);
    straightViewTree(p->right);
}


void reverseViewTree(Node *p) {
    if (p == nullptr) {
        return;
    }

    reverseViewTree(p->left);
    reverseViewTree(p->right);

    std::cout << " [" << p->key << "]";
}

void increasingViewTree(Node *p) {
    if (p == nullptr) {
        return;
    }

    increasingViewTree(p->left);
    std::cout << " [" << p->key << "]";
    increasingViewTree(p->right);
}


void decreasingViewTree(Node *p) {
    if (p == nullptr) {
        return;
    }

    increasingViewTree(p->right);
    std::cout << " [" << p->key << "]";
    increasingViewTree(p->left);
}


int countLeavesInTree(Node *p) {
    if (p == nullptr) {
        return 0;
    }

    if ((p->left == nullptr) && (p->right == nullptr)) {
        return 1;
    }

    return countLeavesInTree(p->left) + countLeavesInTree(p->right);
}


