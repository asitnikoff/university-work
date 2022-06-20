#include <iostream>


#include "files-work.h"
#include "validation.h"
#include "sorts.h"
#include "searches.h"


int main() {
    while (true) {
        printf("Create new file - 1\n");
        printf("Modify data in file - 2\n");
        printf("View list of all books - 3\n");
        printf("Print some list of books - 4\n");
        printf("Find book in file by author name - 5\n");
        printf("Find book in array by author name - 6\n");
        printf("Sort file by author name - 7\n");
        printf("Sort array by author name - 8\n");
        printf("Exit - another number\n");
        fflush(stdout);

        int choice;
        inputInt(choice);

        switch (choice) {
            case 1:
                createNewFile();
                break;
            case 2:
                modifyDataInFile();
                break;
            case 3:
                showAll();
                break;
            case 4:
                printSomeBooks();
                break;
            case 5:
                findBookInFile();
                break;
            case 6:
//                findBookInArray();
                break;
            case 7:
//                sortFile();
                break;
            case 8:
//                sortArrayFromFile();
            default:
                return 0;
        }
    }
}
