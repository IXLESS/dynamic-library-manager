#include <iostream>
#include <limits>
#include <string>
#include "library.hpp"


int main() {
    Library lib;

    // Ob zagonu poskusimo naložiti knjige iz datoteke (če obstaja)
    lib.loadFromFile("books.txt");

    bool run = true;
    int user_input;

    // Glavna zanka programa (meni teče dokler uporabnik ne izbere 0)
    while (run) {
        // Branje izbire z osnovno validacijo vnosa
        do {
            std::cout << "=== Dynamic Library Manager ===\n"
                      << "1 - Dodaj knjigo\n"
                      << "2 - Izbriši knjigo\n"
                      << "3 - Najdi knjigo\n"
                      << "4 - Izpiši vse knjige\n"
                      << "0 - Izhod\n"
                      << "Izbira: ";

            std::cin >> user_input;

            // Če uporabnik ne vnese številke (npr. črko), popravimo stanje cin
            while (std::cin.fail()) {
                std::cin.clear(); 
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Neveljaven vnos. Vnesi številko med 0 in 4: ";
                std::cin >> user_input;
            }

            if (user_input < 0 || user_input > 4) {
                std::cout << "Neveljavna izbira. Poskusi znova.\n";
            }

        } while (user_input < 0 || user_input > 4);

        // Obdelava izbire uporabnika
        switch (user_input) {
            case 0: {  // izhod iz programa
                run = false;
                break;
            }

            case 1: {  // dodaj novo knjigo
                std::string title, author;
                int year;

                // počistimo buffer zaradi prejšnjega >> user_input
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                std::cout << "Vnesi naslov: ";
                std::getline(std::cin, title);

                std::cout << "Vnesi avtorja: ";
                std::getline(std::cin, author);

                std::cout << "Vnesi leto: ";
                std::cin >> year;

                lib.addBook(title, author, year);
                break;
            }

            case 2: {  // izbriši knjigo po indeksu
                lib.printAll();
                int index;

                std::cout << "Indeks za brisanje: ";
                std::cin >> index;

                lib.removeBook(index);
                break;
            }

            case 3: {  // iskanje knjige po naslovu (ali delu naslova)
                std::string query;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                std::cout << "Vnesi iskalni niz: ";
                std::getline(std::cin, query);

                lib.findBook(query);
                break;
            }

            case 4: {  // izpis vseh knjig v knjižnici
                lib.printAll();
                break;
            }
        }

        std::cout << "\n\n";
    }

    // Ob izhodu shranimo trenutno stanje knjižnice v datoteko
    lib.saveToFile("books.txt");

    return 0;
}
