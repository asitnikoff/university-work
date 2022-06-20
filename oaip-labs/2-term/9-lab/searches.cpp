#include "searches.h"
#include "files-work.h"
#include "validation.h"
#include "sorts.h"


template <typename Type1, typename Type2> int compareStrings(Type1 str1, Type2 str2) {
    while (((*str1) != '\0') && ((*str1) == (*str2))) {
        ++str1;
        ++str2;
    }

    return (*str1) - (*str2);
}


void findBookInFile() {
    FILE* data_file = nullptr;
    openFile(&data_file, "data.dat", "rb");


    printf("Input author you want to find: ");
    char author[100];
    inputStr(author);

    Book book;
    while (fread(&book, sizeof(Book), 1, data_file)) {
        if (compareStrings(book.author, author) == 0) {
            printf("This author is in catalog.\n");
            return;
        }
    }
    printf("There is no such author in catalog.\n");

    closeFile(&data_file);
}


void findBookInArray() {
    FILE* data_file = nullptr;
    openFile(&data_file, "data.dat", "rb");


    printf("Input author you want to find: ");
    char author[100];
    inputStr(author);

    int total = getTotalNumberOfDataInFile(data_file);
    Book* books = new Book[total];

    total = 0;
    while (fread(&books[total], sizeof(Book), 1, data_file)) {
        ++total;
    }

    sortArray(books, 0, total);

    int l = 0, r = total - 1;
    while (l < r) {
        int md = (l + r) >> 1;

        if (compareStrings(books[md].author, author) < 0) {
            l = md + 1;
        } else {
            r = md;
        }
    }

    if (compareStrings(books[l].author, author) == 0) {
        printf("This author is in catalog.\n");
    } else {
        printf("There is no such author in catalog.\n");
    }
}
