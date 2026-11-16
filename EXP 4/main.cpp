#include <iostream>
using namespace std;

class Person {
public:
    string name;

    void showPerson() {
        cout << "Name: " << name << endl;
    }
};

class Student : public Person {
public:
    int roll;

    void showStudent() {
        cout << "Roll No: " << roll << endl;
    }
};

class GraduateStudent : public Student {
public:
    string degree;

    void showGraduate() {
        cout << "Degree: " << degree << endl;
    }
};

int main() {
    GraduateStudent g;

    g.name = "Rahul";
    g.roll = 101;
    g.degree = "B.Tech";

    g.showPerson();
    g.showStudent();
    g.showGraduate();

    return 0;
}