#include <iostream>
#include <exception>
using namespace std;

class BankingException : public exception {
public:
    const char* what() const noexcept {
        return "Banking Error!";
    }
};

class InsufficientBalance : public BankingException {
public:
    const char* what() const noexcept {
        return "Insufficient Balance!";
    }
};

int main() {
    int balance = 5000;
    int withdraw;

    cout << "Enter withdrawal amount: ";
    cin >> withdraw;

    try {
        if (withdraw > balance)
            throw InsufficientBalance();

        balance = balance - withdraw;

        cout << "Transaction Successful!" << endl;
        cout << "Remaining Balance: " << balance << endl;
    }

    catch (BankingException &e) {
        cout << e.what() << endl;
    }

    return 0;
}