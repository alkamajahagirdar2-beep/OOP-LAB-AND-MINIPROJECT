// ============================================================
//  LIBRARY MANAGEMENT SYSTEM  (C++ console project)
//  Features : Add, Display, Search, Update, Delete,
//             Issue, Return, permanent file storage,
//             duplicate-ID check and input validation
//  Compile  : g++ LibraryManagementSystem.cpp -o library
//  Run      : ./library        (Windows: library.exe)
// ============================================================
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

const string DATA_FILE = "books.txt";

// ---------------------------- Book class ----------------------------
class Book {
public:
    unsigned int id = 0;
    string title, author, publisher;
    int quantity = 1;   // total copies
    int issued = 0;     // copies currently issued

    int available() const { return quantity - issued; }
};

vector<Book> books;

// ------------------------- Input helpers -----------------------------
void clearLine() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int readInt(const string &prompt, int minVal, int maxVal) {
    int x;
    while (true) {
        cout << prompt;
        if (cin >> x && x >= minVal && x <= maxVal) {
            clearLine();
            return x;
        }
        cout << "  Invalid input. Enter a number between " << minVal
             << " and " << maxVal << ".\n";
        clearLine();
    }
}

string readText(const string &prompt) {
    string s;
    while (true) {
        cout << prompt;
        getline(cin, s);
        // trim spaces
        size_t a = s.find_first_not_of(" \t");
        size_t b = s.find_last_not_of(" \t");
        if (a != string::npos) return s.substr(a, b - a + 1);
        cout << "  Input cannot be blank.\n";
    }
}

// ------------------------- File handling -----------------------------
// File format (one book per line): id|title|author|publisher|quantity|issued
void saveBooks() {
    ofstream out(DATA_FILE);
    if (!out) {
        cout << "  Warning: could not save data to file.\n";
        return;
    }
    for (const auto &b : books)
        out << b.id << '|' << b.title << '|' << b.author << '|'
            << b.publisher << '|' << b.quantity << '|' << b.issued << '\n';
}

void loadBooks() {
    ifstream in(DATA_FILE);
    if (!in) return;  // first run, no file yet
    string line;
    while (getline(in, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string f[6];
        bool ok = true;
        for (int i = 0; i < 6; i++)
            if (!getline(ss, f[i], '|')) { ok = false; break; }
        if (!ok) continue;
        try {
            Book b;
            b.id = stoul(f[0]);
            b.title = f[1];
            b.author = f[2];
            b.publisher = f[3];
            b.quantity = stoi(f[4]);
            b.issued = stoi(f[5]);
            books.push_back(b);
        } catch (...) { /* skip corrupted line */ }
    }
}

// ----------------------------- Utilities -----------------------------
int findIndexById(unsigned int id) {
    for (size_t i = 0; i < books.size(); i++)
        if (books[i].id == id) return (int)i;
    return -1;
}

string lower(string s) {
    transform(s.begin(), s.end(), s.begin(), ::tolower);
    return s;
}

void printHeader() {
    cout << left << setw(8) << "ID" << setw(28) << "Title" << setw(22)
         << "Author" << setw(18) << "Publisher" << setw(7) << "Total"
         << setw(8) << "Issued" << "Avail\n";
    cout << string(98, '-') << '\n';
}

void printBook(const Book &b) {
    auto cut = [](const string &s, size_t n) {
        return s.size() > n ? s.substr(0, n - 2) + ".." : s;
    };
    cout << left << setw(8) << b.id << setw(28) << cut(b.title, 27)
         << setw(22) << cut(b.author, 21) << setw(18) << cut(b.publisher, 17)
         << setw(7) << b.quantity << setw(8) << b.issued << b.available()
         << '\n';
}

// ----------------------------- Operations ----------------------------
void addBook() {
    cout << "\n--- ADD BOOK ---\n";
    Book b;
    while (true) {
        b.id = (unsigned int)readInt("Enter unique book ID: ", 1, 999999999);
        if (findIndexById(b.id) == -1) break;
        cout << "  This ID already exists. Use a different ID.\n";
    }
    b.title = readText("Enter title     : ");
    b.author = readText("Enter author    : ");
    b.publisher = readText("Enter publisher : ");
    b.quantity = readInt("Enter quantity  : ", 1, 100000);
    b.issued = 0;
    books.push_back(b);
    saveBooks();
    cout << "\nBook recorded successfully.\n";
}

void displayBooks() {
    cout << "\n--- ALL BOOKS ---\n";
    if (books.empty()) {
        cout << "No books available.\n";
        return;
    }
    printHeader();
    for (const auto &b : books) printBook(b);
    cout << "\nTotal records: " << books.size() << '\n';
}

void searchBooks() {
    cout << "\n--- SEARCH BOOK ---\n";
    cout << "1. By ID\n2. By Title\n3. By Author\n";
    int c = readInt("Enter choice: ", 1, 3);
    vector<const Book *> found;

    if (c == 1) {
        unsigned int id = (unsigned int)readInt("Enter ID: ", 1, 999999999);
        int i = findIndexById(id);
        if (i != -1) found.push_back(&books[i]);
    } else {
        string key = lower(readText(c == 2 ? "Enter title keyword : "
                                           : "Enter author keyword: "));
        for (const auto &b : books) {
            const string &field = (c == 2) ? b.title : b.author;
            if (lower(field).find(key) != string::npos) found.push_back(&b);
        }
    }

    if (found.empty()) {
        cout << "No matching book found.\n";
        return;
    }
    cout << '\n';
    printHeader();
    for (auto p : found) printBook(*p);
}

void updateBook() {
    cout << "\n--- UPDATE BOOK ---\n";
    unsigned int id = (unsigned int)readInt("Enter ID of book to update: ", 1, 999999999);
    int i = findIndexById(id);
    if (i == -1) {
        cout << "Book not found.\n";
        return;
    }
    Book &b = books[i];
    cout << "Current record:\n";
    printHeader();
    printBook(b);

    cout << "\n1. Title\n2. Author\n3. Publisher\n4. Quantity\n";
    int c = readInt("What do you want to update? ", 1, 4);
    switch (c) {
    case 1: b.title = readText("New title    : "); break;
    case 2: b.author = readText("New author   : "); break;
    case 3: b.publisher = readText("New publisher: "); break;
    case 4: {
        int q = readInt("New total quantity: ", 1, 100000);
        if (q < b.issued)
            cout << "Quantity cannot be less than issued copies (" << b.issued << ").\n";
        else
            b.quantity = q;
        break;
    }
    }
    saveBooks();
    cout << "Record updated.\n";
}

void deleteBook() {
    cout << "\n--- DELETE BOOK ---\n";
    unsigned int id = (unsigned int)readInt("Enter ID of book to delete: ", 1, 999999999);
    int i = findIndexById(id);
    if (i == -1) {
        cout << "Book not found.\n";
        return;
    }
    if (books[i].issued > 0) {
        cout << "Cannot delete: " << books[i].issued << " copy(ies) currently issued.\n";
        return;
    }
    cout << "Delete \"" << books[i].title << "\"? (1 = Yes, 2 = No): ";
    int ans = readInt("", 1, 2);
    if (ans == 1) {
        books.erase(books.begin() + i);
        saveBooks();
        cout << "Book deleted.\n";
    } else {
        cout << "Cancelled.\n";
    }
}

void issueBook() {
    cout << "\n--- ISSUE BOOK ---\n";
    unsigned int id = (unsigned int)readInt("Enter book ID: ", 1, 999999999);
    int i = findIndexById(id);
    if (i == -1) {
        cout << "Book not found.\n";
        return;
    }
    if (books[i].available() <= 0) {
        cout << "Sorry, no copies of \"" << books[i].title << "\" are available.\n";
        return;
    }
    books[i].issued++;
    saveBooks();
    cout << "Book issued. Copies left: " << books[i].available() << '\n';
}

void returnBook() {
    cout << "\n--- RETURN BOOK ---\n";
    unsigned int id = (unsigned int)readInt("Enter book ID: ", 1, 999999999);
    int i = findIndexById(id);
    if (i == -1) {
        cout << "Book not found.\n";
        return;
    }
    if (books[i].issued <= 0) {
        cout << "No copies of this book are currently issued.\n";
        return;
    }
    books[i].issued--;
    saveBooks();
    cout << "Book returned. Copies available: " << books[i].available() << '\n';
}

// ------------------------------- Menu --------------------------------
void bookMenu() {
    while (true) {
        cout << "\n********* BOOK MENU *********\n"
             << "1. ADD BOOK\n"
             << "2. DISPLAY ALL BOOKS\n"
             << "3. SEARCH BOOK\n"
             << "4. UPDATE BOOK\n"
             << "5. DELETE BOOK\n"
             << "6. ISSUE BOOK\n"
             << "7. RETURN BOOK\n"
             << "8. BACK TO MAIN MENU\n";
        int c = readInt("Enter your choice: ", 1, 8);
        switch (c) {
        case 1: addBook(); break;
        case 2: displayBooks(); break;
        case 3: searchBooks(); break;
        case 4: updateBook(); break;
        case 5: deleteBook(); break;
        case 6: issueBook(); break;
        case 7: returnBook(); break;
        case 8: return;
        }
    }
}

void mainMenu() {
    while (true) {
        cout << "\n******** LIBRARY MANAGEMENT SYSTEM ********\n"
             << "1. BOOKS\n"
             << "2. EXIT\n";
        int c = readInt("Enter your choice: ", 1, 2);
        if (c == 1)
            bookMenu();
        else {
            saveBooks();
            cout << "Data saved. Thank you!\n";
            return;
        }
    }
}

int main() {
    loadBooks();
    mainMenu();
    return 0;
}
