#ifndef DOUBLE_LINKED_LIST_H
#define DOUBLE_LINKED_LIST_H


struct DoubleLinkedListProperties {
    int info;
    DoubleLinkedListProperties *next, *prev;
};


void pushBeginList(DoubleLinkedListProperties*&, DoubleLinkedListProperties*&, int);
void pushEndList(DoubleLinkedListProperties*&, DoubleLinkedListProperties*&, int);
void popBeginList(DoubleLinkedListProperties*&, DoubleLinkedListProperties*&);
void popEndList(DoubleLinkedListProperties*&, DoubleLinkedListProperties*&);
int getBeginList(const DoubleLinkedListProperties*&);
int getEndList(const DoubleLinkedListProperties*&);
bool isEmptyList(DoubleLinkedListProperties*&);
void clearList(DoubleLinkedListProperties*&, DoubleLinkedListProperties*&);
void showList(DoubleLinkedListProperties*);
void showListFromBegin(DoubleLinkedListProperties*);
void showListFromEnd(DoubleLinkedListProperties*);
DoubleLinkedListProperties* getMinElementList(DoubleLinkedListProperties*);
DoubleLinkedListProperties* getMaxElementList(DoubleLinkedListProperties*);
bool isEarlyList(DoubleLinkedListProperties*, DoubleLinkedListProperties*);
void swapElementsList(DoubleLinkedListProperties*&, DoubleLinkedListProperties*&);
//void sortList(DoubleLinkedListProperties*&);


#endif