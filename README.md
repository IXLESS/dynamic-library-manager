# Dynamic Library Manager (C++)

A simple console-based library management system written in C++.  
The project demonstrates object-oriented programming, manual memory management (`new` / `delete`), pointer manipulation, and a custom dynamic array implementation.  
Books are stored in a text file, allowing the program to load saved data on startup and persist changes on exit.

---

## Features

- Add new books (title, author, year)
- Remove books by index
- Search books by title (partial match supported)
- Display all stored books
- Automatic dynamic array resizing
- File persistence (`books.txt`)

---

## How to Build & Run

### Compile:
```bash
g++ main.cpp -o library_app
```

### Run:
```bash
./library_app
```

---

## How It Works

- On startup, the program loads book entries from `books.txt` (if it exists).  
- The user interacts with a simple menu in the terminal.  
- All memory for books is handled manually using pointers.  
- On exit (option `0`), the program saves all current books back to `books.txt`.

---

## Example `books.txt`

```
Clean Code|Robert C. Martin|2008
The Hobbit|J. R. R. Tolkien|1937
1984|George Orwell|1949
```

Each line represents one book in the format:

```
Title|Author|Year
```
