#include <iostream>
using namespace std;

class Calculator {
public:
    int add(int a, int b) {
        return a + b;
    }

    float add(float a, float b) {
        return a + b;
    }

    int multiply(int a, int b) {
        return a * b;
    }
};

class Complex {
public:
    int real, img;

    Complex(int r, int i) {
        real = r;
        img = i;
    }

    Complex operator+(Complex c) {
        return Complex(real + c.real, img + c.img);
    }

    void display() {
        cout << real << " + " << img << "i" << endl;
    }
};

int main() {
    Calculator c;

    cout << "Addition: " << c.add(10, 20) << endl;
    cout << "Float Addition: " << c.add(2.5f, 3.5f) << endl;
    cout << "Multiplication: " << c.multiply(5, 4) << endl;

    Complex c1(2, 3), c2(4, 5);
    Complex c3 = c1 + c2;

    cout << "Complex Addition: ";
    c3.display();

    return 0;
}