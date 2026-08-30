/*
 * TASK 4: Banking System
 * CodeAlpha C++ Programming Internship
 *
 * Logic (OOP based):
 * 1. Customer class -> stores customer details (name, ID)
 * 2. Account class -> stores balance, linked to a customer, has
 *    deposit(), withdraw(), transfer() methods
 * 3. Transaction class -> represents a single transaction record
 *    (used to build transaction history)
 * 4. Bank class -> manages a collection of Accounts, handles
 *    creating accounts and finding accounts by ID
 */

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

// ---------- Transaction ----------
class Transaction {
public:
    string type;     // "Deposit", "Withdraw", "Transfer-Out", "Transfer-In"
    double amount;
    string detail;   // extra info, e.g. "to Account 102"

    Transaction(string t, double a, string d = "")
        : type(t), amount(a), detail(d) {}

    void display() const {
        cout << left << setw(15) << type << setw(12) << amount << detail << "\n";
    }
};

// ---------- Customer ----------
class Customer {
public:
    int customerId;
    string name;

    Customer(int id, string n) : customerId(id), name(n) {}
};

// ---------- Account ----------
class Account {
public:
    int accountNumber;
    Customer owner;
    double balance;
    vector<Transaction> history;

    Account(int accNo, Customer cust, double initialBalance = 0.0)
        : accountNumber(accNo), owner(cust), balance(initialBalance) {}

    void deposit(double amount) {
        if (amount <= 0) {
            cout << "Deposit amount must be positive.\n";
            return;
        }
        balance += amount;
        history.push_back(Transaction("Deposit", amount));
        cout << "Deposited Rs." << amount << " successfully. New balance: Rs." << balance << "\n";
    }

    bool withdraw(double amount) {
        if (amount <= 0) {
            cout << "Withdrawal amount must be positive.\n";
            return false;
        }
        if (amount > balance) {
            cout << "Insufficient balance!\n";
            return false;
        }
        balance -= amount;
        history.push_back(Transaction("Withdraw", amount));
        cout << "Withdrew Rs." << amount << " successfully. New balance: Rs." << balance << "\n";
        return true;
    }

    void showBalance() const {
        cout << "Account " << accountNumber << " (" << owner.name << ") Balance: Rs." << balance << "\n";
    }

    void showHistory() const {
        cout << "\n--- Transaction History for Account " << accountNumber << " ---\n";
        if (history.empty()) {
            cout << "No transactions yet.\n";
            return;
        }
        cout << left << setw(15) << "Type" << setw(12) << "Amount" << "Detail" << "\n";
        for (const auto &t : history) t.display();
    }
};

// ---------- Bank ----------
class Bank {
private:
    vector<Account> accounts;
    int nextAccountNumber = 101;
    int nextCustomerId = 1;

public:
    Account* findAccount(int accNo) {
        for (auto &acc : accounts) {
            if (acc.accountNumber == accNo) return &acc;
        }
        return nullptr;
    }

    void createAccount() {
        string name;
        double initialDeposit;
        cout << "Enter customer name: ";
        cin >> ws;
        getline(cin, name);
        cout << "Enter initial deposit amount: ";
        cin >> initialDeposit;

        Customer cust(nextCustomerId++, name);
        Account acc(nextAccountNumber, cust, initialDeposit);
        accounts.push_back(acc);

        cout << "Account created successfully! Account Number: " << nextAccountNumber << "\n";
        nextAccountNumber++;
    }

    void deposit() {
        int accNo;
        double amount;
        cout << "Enter account number: ";
        cin >> accNo;
        Account* acc = findAccount(accNo);
        if (!acc) { cout << "Account not found!\n"; return; }
        cout << "Enter amount to deposit: ";
        cin >> amount;
        acc->deposit(amount);
    }

    void withdraw() {
        int accNo;
        double amount;
        cout << "Enter account number: ";
        cin >> accNo;
        Account* acc = findAccount(accNo);
        if (!acc) { cout << "Account not found!\n"; return; }
        cout << "Enter amount to withdraw: ";
        cin >> amount;
        acc->withdraw(amount);
    }

    void transfer() {
        int fromAcc, toAcc;
        double amount;
        cout << "Enter your account number: ";
        cin >> fromAcc;
        cout << "Enter recipient account number: ";
        cin >> toAcc;

        Account* src = findAccount(fromAcc);
        Account* dest = findAccount(toAcc);

        if (!src || !dest) { cout << "One or both accounts not found!\n"; return; }

        cout << "Enter amount to transfer: ";
        cin >> amount;

        if (src->withdraw(amount)) {
            dest->balance += amount;
            src->history.back() = Transaction("Transfer-Out", amount, "to Account " + to_string(toAcc));
            dest->history.push_back(Transaction("Transfer-In", amount, "from Account " + to_string(fromAcc)));
            cout << "Transfer successful!\n";
        }
    }

    void checkBalance() {
        int accNo;
        cout << "Enter account number: ";
        cin >> accNo;
        Account* acc = findAccount(accNo);
        if (!acc) { cout << "Account not found!\n"; return; }
        acc->showBalance();
    }

    void viewHistory() {
        int accNo;
        cout << "Enter account number: ";
        cin >> accNo;
        Account* acc = findAccount(accNo);
        if (!acc) { cout << "Account not found!\n"; return; }
        acc->showHistory();
    }
};

int main() {
    Bank bank;
    int choice;

    do {
        cout << "\n===== Banking System =====\n";
        cout << "1. Create Account\n";
        cout << "2. Deposit\n";
        cout << "3. Withdraw\n";
        cout << "4. Transfer Funds\n";
        cout << "5. Check Balance\n";
        cout << "6. View Transaction History\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input! Please enter a number.\n";
            continue;
        }

        switch (choice) {
            case 1: bank.createAccount(); break;
            case 2: bank.deposit(); break;
            case 3: bank.withdraw(); break;
            case 4: bank.transfer(); break;
            case 5: bank.checkBalance(); break;
            case 6: bank.viewHistory(); break;
            case 7: cout << "Thank you for banking with us!\n"; break;
            default: cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 7);

    return 0;
}
