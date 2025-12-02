#ifndef LIBRARY_HPP
#define LIBRARY_HPP

#include "book.hpp"
#include <fstream>
#include <iostream>
#include <sstream>

// Razred Library upravlja dinamični seznam kazalcev na Book
class Library {
private:
    Book** books;   // dinamična tabela kazalcev na knjige
    int size;       // trenutno število knjig
    int capacity;   // kapaciteta tabele

    // Povečamo kapaciteto tabele, ko je polna
    void resize() {
        int newCapacity = capacity * 2;
        Book** newArray = new Book*[newCapacity];

        for (int i = 0; i < size; ++i) {
            newArray[i] = books[i];
        }

        delete[] books;
        books = newArray;
        capacity = newCapacity;
    }

public:
    // Konstruktor: inicializiramo prazno knjižnico z začetno kapaciteto 2
    Library()
        : size(0), capacity(2) {
        books = new Book*[capacity];
    }

    // Destruktor: sprostimo vse knjige in tabelo kazalcev
    ~Library() {
        for (int i = 0; i < size; ++i) {
            delete books[i];
        }
        delete[] books;
    }

    // Dodaj novo knjigo v knjižnico (po potrebi razširi tabelo)
    void addBook(const std::string& title, const std::string& author, int year) {
        if (size == capacity)
            resize();

        books[size] = new Book(title, author, year);
        size++;
    }

    // Izbriši knjigo na podanem indeksu in zapolni "luknjo"
    void removeBook(int index) {
        if (index < 0 || index >= size) {
            std::cout << "Napaka: neveljaven indeks.\n";
            return;
        }

        delete books[index];

        for (int i = index; i < size - 1; ++i) {
            books[i] = books[i + 1];
        }

        size--;
    }

    // Poišči knjige, ki v naslovu vsebujejo iskani niz
    void findBook(const std::string& query) const {
        bool found = false;

        for (int i = 0; i < size; ++i) {
            if (books[i]->getTitle().find(query) != std::string::npos) {
                std::cout << "[" << i << "] ";
                books[i]->print();
                std::cout << "\n";
                found = true;
            }
        }

        if (!found)
            std::cout << "Ni zadetkov.\n";
    }

    // Izpiši vse knjige v knjižnici
    void printAll() const {
        if (size == 0) {
            std::cout << "Knjižnica je prazna.\n";
            return;
        }

        for (int i = 0; i < size; ++i) {
            std::cout << "[" << i << "] ";
            books[i]->print();
            std::cout << "\n";
        }
    }

    // Shrani vse knjige v tekstovno datoteko v formatu: naslov|avtor|leto
    void saveToFile(const std::string& filename) const {
        std::ofstream out(filename);

        if (!out) {
            std::cout << "Napaka: ne morem odpreti datoteke za pisanje.\n";
            return;
        }

        for (int i = 0; i < size; ++i) {
            out << books[i]->getTitle() << "|"
                << books[i]->getAuthor() << "|"
                << books[i]->getYear() << "\n";
        }
    }

    // Naloži knjige iz tekstovne datoteke (vsaka vrstica je ena knjiga)
    void loadFromFile(const std::string& filename) {
        std::ifstream in(filename);

        if (!in) {
            // Datoteke ni – verjetno prvi zagon programa
            return;
        }

        std::string line;

        while (std::getline(in, line)) {
            if (line.empty()) continue; // preskočimo prazne vrstice

            std::stringstream ss(line);
            std::string title, author, yearStr;

            std::getline(ss, title, '|');
            std::getline(ss, author, '|');
            std::getline(ss, yearStr, '|');

            // tukaj predpostavimo, da je leto veljavno število
            int year = std::stoi(yearStr);

            addBook(title, author, year);
        }
    }
};

#endif
