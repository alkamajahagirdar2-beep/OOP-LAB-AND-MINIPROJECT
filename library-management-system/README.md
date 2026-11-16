# Library Management System (C++)

A simple console-based Library Management System built in C++ as a B.Tech mini-project. It manages book records with permanent file storage, so data is kept after the program closes.

## Features

- Add, display, update and delete books
- Search by ID, title or author (case-insensitive, partial match)
- Issue and return books with automatic tracking of available copies
- Duplicate book ID check
- Input validation (no blank fields, only valid numbers)
- Data saved automatically to `books.txt` and loaded on the next start

## Concepts used

- Object-oriented programming (`Book` class)
- STL `vector` for dynamic storage
- File handling (`ifstream` / `ofstream`)
- Menu-driven programming with functions, loops and `switch`

## Getting started

Requirements: a C++11 (or newer) compiler such as g++.

```bash
git clone https://github.com/<your-username>/library-management-system.git
cd library-management-system
g++ LibraryManagementSystem.cpp -o library
./library          # on Windows: library.exe
```

## Sample run

```
******** LIBRARY MANAGEMENT SYSTEM ********
1. BOOKS
2. EXIT
Enter your choice: 1

********* BOOK MENU *********
1. ADD BOOK
2. DISPLAY ALL BOOKS
3. SEARCH BOOK
4. UPDATE BOOK
5. DELETE BOOK
6. ISSUE BOOK
7. RETURN BOOK
8. BACK TO MAIN MENU
```

## Data format

Records are stored one per line in `books.txt`:

```
id|title|author|publisher|quantity|issued
```

## Future improvements

- Member records and due dates / fines
- Login for librarian and student roles
- GUI or database (SQLite) version

## License

Released under the MIT License. See [LICENSE](LICENSE).
