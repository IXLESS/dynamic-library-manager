#ifndef BOOK_HPP
#define BOOK_HPP

#include <string>
#include <iostream>

class Book {
private:
    std::string title;
    std::string author;
    int year;

public:
    // Preprost konstruktor, ki inicializira vse atribute
    Book(const std::string& t, const std::string& a, int y)
        : title(t), author(a), year(y) {}

    std::string getTitle() const {
        return title;
    }

    std::string getAuthor() const {
        return author;
    }

    int getYear() const {
        return year;
    }

    // Izpišemo knjigo v eni vrstici v berljivi obliki
    void print() const {
        std::cout << "\"" << title << "\" - " << author << " (" << year << ")";
    }
};

#endif
