#include <iostream>

#include "tree.h"
#include "validation.h"


void addDataInTree(Node*&);
void deleteDataFromTree(Node*&);
void findDataInTree(Node*);
void selectViewTree(Node*);
int doTask(Node*);


int main() {
    Node* node = nullptr;

    while (true) {
        std::cout << "1 - add data." << std::endl;
        std::cout << "2 - delete data." << std::endl;
        std::cout << "3 - view tree." << std::endl;
        std::cout << "4 - find data." << std::endl;
        std::cout << "5 - do task." << std::endl;
        std::cout << "Else - exit." << std::endl;

        int choice = read<int>();

        switch (choice) {
            case 1:
                addDataInTree(node);
                break;
            case 2:
                deleteDataFromTree(node);
                break;
            case 3:
                selectViewTree(node);
                break;
            case 4:
                findDataInTree(node);
                break;
            case 5:
                doTask(node);
                break;
            default:
                clearTree(node);
                return 0;
        }
    }
}


void addDataInTree(Node*& p) {
    std::cout << "Input number of elements: ";
    int n = read<int>(0);

    while (n > 0) {
        std::cout << "Input data: ";
        fflush(stdout);
        int key = read<int>();

        p = insertTree(p, key);
        --n;

        viewTree(p);
    }
}


void deleteDataFromTree(Node*& p) {
    std::cout << "Input data to delete: ";
    int key = read<int>();

    if (findKey(p, key)) {
        p = remove(p, key);
    } else {
        std::cout << "There is no such key in tree." << std::endl;
    }
}


void findDataInTree(Node* p) {
    std::cout << "Input data to find: ";
    int key = read<int>();

    if (findKey(p, key)) {
        std::cout << "Such key found in tree." << std::endl;
    } else {
        std::cout << "There is no such key in tree." << std::endl;
    }
}


void selectViewTree(Node* p) {
    std::cout << "Select way of view tree:" << std::endl;
    std::cout << "1 - straight way." << std::endl;
    std::cout << "2 - reverse way." << std::endl;
    std::cout << "3 - by increasing way." << std::endl;
    std::cout << "4 - by decreasing way." << std::endl;
    std::cout << "5 - view tree." << std::endl;
    std::cout << "Else - exit." << std::endl;

    int choice = read<int>();

    switch (choice) {
        case 1:
            std::cout << "Straight view:";
            straightViewTree(p);
            std::cout << std::endl;
            break;
        case 2:
            std::cout << "Reverse view:";
            reverseViewTree(p);
            std::cout << std::endl;
            break;
        case 3:
            std::cout << "Increasing view:";
            increasingViewTree(p);
            std::cout << std::endl;
            break;
        case 4:
            std::cout << "Decreasing view:";
            decreasingViewTree(p);
            std::cout << std::endl;
            break;
        case 5:
            viewTree(p);
            break;
        default:
            return;
    }
}


int doTask(Node* p) {
    std::cout << "Leaves count in tree are equals " << countLeavesInTree(p) << std::endl;
}