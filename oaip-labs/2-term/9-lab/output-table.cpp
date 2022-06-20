#include "output-table.h"


void outputResult(FILE* txt_file, const Book& book, int position) {
//    fprintf(txt_file, "kek\n");
    fprintf(txt_file, "%d. Book number: [%d], Author: [%s], Title: [%s], Year: [%d], Publish hose: [%s], Page number: [%d]\n",
            position, book.book_number, book.author, book.title, book.year, book.publish_house, book.page_number);
}