#include <iostream>
using namespace std;

class Demo {
    int *p;

public:
    // Default constructor
    Demo() {
        p = new int(10);
        cout << "Default Constructor" << endl;
    }

    // Parameterized constructor
    Demo(int x) {
        p = new int(x);
        cout << "Parameterized Constructor" << endl;
    }

    // Copy constructor
    Demo(const Demo &d) {
        p = new int(*d.p);
        cout << "Copy Constructor" << endl;
    }

    // Copy assignment
    Demo& operator=(const Demo &d) {
        if (this != &d)
            *p = *d.p;
        return *this;
    }

    // Move constructor
    Demo(Demo &&d) {
        p = d.p;
        d.p = nullptr;
        cout << "Move Constructor" << endl;
    }

    // Move assignment
    Demo& operator=(Demo &&d) {
        if (this != &d) {
            delete p;
            p = d.p;
            d.p = nullptr;
        }
        return *this;
    }

    void display() {
        if (p)
            cout << "Value: " << *p << endl;
    }

    // Destructor
    ~Demo() {
        delete p;
        cout << "Destructor Called" << endl;
    }
};

int main() {
    Demo d1;
    Demo d2(20);
    Demo d3 = d2;
    Demo d4 = move(d2);

    d1.display();
    d3.display();
    d4.display();

    return 0;
}