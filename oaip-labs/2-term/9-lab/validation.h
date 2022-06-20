#ifndef VALIDATION_H
#define VALIDATION_H


template <typename Type>
Type read();
template <typename Type>
Type read(Type, Type);
void clearInputBuffer();

bool inputInt(int&);
bool inputStr(char*);
bool isCorrectPosition(int, int, int);


#endif