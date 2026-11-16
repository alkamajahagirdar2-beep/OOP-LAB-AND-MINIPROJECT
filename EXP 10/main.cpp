#include <iostream>
#include <fstream>
using namespace std;

int main() {
    fstream file;

    // Writing CSV file
    file.open("student.csv", ios::out);

    file << "101,Rahul,85\n";
    file << "102,Aman,90\n";

    cout << "File Position: " << file.tellp() << endl;

    file.close();

    // Reading CSV file
    file.open("student.csv", ios::in);

    string line;

    cout << "Student Records:" << endl;

    while (getline(file, line)) {
        cout << line << endl;
    }

    cout << "Read Position: " << file.tellg() << endl;

    // Using seekg
    file.clear();
    file.seekg(0);

    cout << "After seekg: " << file.tellg() << endl;

    file.close();

    // Using seekp
    file.open("student.csv", ios::in | ios::out);

    file.seekp(0, ios::end);
    cout << "Write Position: " << file.tellp() << endl;

    file.close();

    return 0;
}