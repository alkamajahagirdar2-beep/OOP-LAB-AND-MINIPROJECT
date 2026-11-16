#include <iostream>
using namespace std;

class BankAccount {
private:
    int balance;

public:
    void setBalance(int b) {
        balance = b;
    }

    void display() {
        cout << "Balance: " << balance << endl;
    }
};

int main() {
    BankAccount obj;

    obj.setBalance(5000);
    obj.display();

    return 0;
}