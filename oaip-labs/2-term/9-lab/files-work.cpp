#include <iostream>
#include <cstdio>
#include <io.h>


#include "files-work.h"
#include "book.h"
#include "validation.h"
#include "sorts.h"
#include "output-table.h"


const char DATA_FILE_NAME[] = "data.dat";
const char RESULT_FILE_NAME[] = "result.txt";


int getTotalNumberOfDataInFile(FILE* data_file) {
    return _filelength(_fileno(data_file)) / sizeof(Book);
}

void openFile(FILE** data_file, const char* filename, const char* mode) {
    fopen_s(&*data_file, filename, mode);
    if (*data_file == nullptr) {
        printf("Open error!\n");
        fflush(stdout);
        exit(1);
    }
}

void closeFile(FILE** file) {
    fclose(*file);
}

void createNewFile() {
    FILE* data_file = nullptr;

    openFile(&data_file, DATA_FILE_NAME, "wb");

    printf("File %s created!\n", DATA_FILE_NAME);
    fflush(stdout);

    closeFile(&data_file);
}

void modifyDataInFile() {
    printf("What you want to do?\n");
    printf("Add data - 1\n");
    printf("Edit data - 2\n");
    printf("Delete data - 3\n");
    fflush(stdout);

    int choice;
    inputInt(choice);

    switch (choice) {
        case 1:
            addDataInFile();
            break;
        case 2:
            editDataInFile();
            break;
        case 3:
            deleteDataInFile();
            break;
    }
}

void addDataInFile() {
    Book book;

    do {
        printf("Input book number name: ");
        fflush(stdout);
    } while (!inputInt(book.book_number));

    do {
        printf("Input author's name: ");
        fflush(stdout);
    } while (!inputStr(book.author));

    do {
        printf("Input title: ");
        fflush(stdout);
    } while (!inputStr(book.title));

    do {
        printf("Input year: ");
        fflush(stdout);
    } while (!inputInt(book.year));

    do {
        printf("Input publish house name: ");
        fflush(stdout);
    } while (!inputStr(book.publish_house));

    do {
        printf("Input number of pages: ");
        fflush(stdout);
    } while (!inputInt(book.page_number));

    FILE* data_file = nullptr;
    openFile(&data_file, DATA_FILE_NAME, "ab");
    fwrite(&book, sizeof(Book), 1, data_file);
    closeFile(&data_file);
}

void editDataInFile() {
    FILE* data_file;
    openFile(&data_file, DATA_FILE_NAME, "rb+");

    int book_position;
    do {
        printf("Choose book to edit: ");
        fflush(stdout);
    } while (!inputInt(book_position) || !isCorrectPosition(book_position, 1, getTotalNumberOfDataInFile(data_file)));
    --book_position;

    fseek(data_file, sizeof(Book) * book_position, SEEK_SET);
    Book book;
    fread(&book, sizeof(Book), 1, data_file);

    printf("Select data you want to edit:\n");
    printf("Book number - 1\n");
    printf("Author name - 2\n");
    printf("Title - 3\n");
    printf("Year - 4\n");
    printf("Publish house name - 5\n");
    printf("Number of pages - 6\n");
    fflush(stdout);

    int choice = read<int>(1, 6);
    switch (choice) {
        case 1:
            do {
                printf("Input book number name: ");
                fflush(stdout);
            } while (!inputInt(book.book_number));
            break;
        case 2:
            do {
                printf("Input author's name: ");
                fflush(stdout);
            } while (!inputStr(book.author));
            break;
        case 3:
            do {
                printf("Input title: ");
                fflush(stdout);
            } while (!inputStr(book.title));
            break;
        case 4:
            do {
                printf("Input year: ");
                fflush(stdout);
            } while (!inputInt(book.year));
            break;
        case 5:
            do {
                printf("Input publish house name: ");
                fflush(stdout);
            } while (!inputStr(book.publish_house));
            break;
        case 6:
            do {
                printf("Input number of pages: ");
                fflush(stdout);
            } while (!inputInt(book.page_number));
        default:
            break;
    }

    fseek(data_file, sizeof(Book) * book_position, SEEK_SET);
    fwrite(&book, sizeof(Book), 1, data_file);
    closeFile(&data_file);
}

void deleteDataInFile() {
    showAll();
    FILE* data_file = nullptr;
    openFile(&data_file, DATA_FILE_NAME, "rb+");

    int book_position;
    do {
        printf("Choose book to delete: ");
        fflush(stdout);
    } while (!inputInt(book_position) || !isCorrectPosition(book_position, 1, getTotalNumberOfDataInFile(data_file)));
    book_position = read<int>(1, getTotalNumberOfDataInFile(data_file));

    Book book;
    fseek(data_file, sizeof(Book) * book_position, SEEK_SET);
    while (fread(&book, sizeof(Book), 1, data_file)) {
        fseek(data_file, sizeof(Book) * (book_position - 1), SEEK_SET);
        fwrite(&book, sizeof(Book), 1, data_file);
        fseek(data_file, sizeof(Book) * (++book_position), SEEK_SET);
    }
    _chsize(_fileno(data_file), sizeof(Book) * (book_position - 1));
    closeFile(&data_file);
}

void showAll() {
    FILE* data_file, *txt_file;

    openFile(&data_file, DATA_FILE_NAME, "rb");
    openFile(&txt_file, RESULT_FILE_NAME, "w");

    Book book;
    int position = 0;
    while (fread(&book, sizeof(Book), 1, data_file)) {
        ++position;
        outputResult(txt_file, book, position);
    }

    closeFile(&txt_file);
    closeFile(&data_file);
}

void printSomeBooks() {
    FILE* data_file, *txt_file;

    openFile(&data_file, DATA_FILE_NAME, "rb");
    openFile(&txt_file, RESULT_FILE_NAME, "w");

    int total = 0;
    printf("Input year: ");
    fflush(stdout);
    int year;
    inputInt(year);
    Book book;
    while (fread(&book, sizeof(Book), 1, data_file)) {
        if (book.year > year) {
            ++total;
        }
    }

    fseek(data_file, 0, SEEK_SET);

    Book* books = new Book[total];
    total = 0;
    while (fread(&book, sizeof(book), 1, data_file)) {
        if (book.year > year) {
            books[total] = book;
            ++total;
        }
    }

    sortArray(books, 0, total - 1);

    for (int i = 0; i < total; ++i) {
        outputResult(txt_file, books[i], i);
    }

    closeFile(&txt_file);
    closeFile(&data_file);
}