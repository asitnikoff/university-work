#ifndef FILES_WORK_H
#define FILES_WORK_H


#include <stdio.h>

#include "book.h"

int getTotalNumberOfDataInFile(FILE*);
void openFile(FILE**, const char*, const char*);
void closeFile(FILE**);
void createNewFile();
void modifyDataInFile();
void addDataInFile();
void editDataInFile();
void deleteDataInFile();
void showAll();
void printSomeBooks();

#endif