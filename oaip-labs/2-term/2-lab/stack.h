#ifndef LAB_STACK_H
#define LAB_STACK_H


struct StackProperties {
    int info;
    StackProperties *next;
};


void pushStack(StackProperties*&, int);
void popStack(StackProperties*&);
int topStack(const StackProperties*&);
bool isEmptyStack(StackProperties*&);
void clearStack(StackProperties*&);
void showStack(StackProperties*&);
StackProperties* getMinElementStack(StackProperties*);
StackProperties* getMaxElementStack(StackProperties*);
bool isEarlyStack(StackProperties*, StackProperties*, StackProperties*);
void swapElementsStack(StackProperties*&, StackProperties*&);
void sortStack(StackProperties*&);


#endif