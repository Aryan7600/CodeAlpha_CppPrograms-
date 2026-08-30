/*
 * TASK 2: Login and Registration System
 * CodeAlpha C++ Programming Internship
 *
 * Logic:
 * 1. Registration: username + password lo, check karo file me
 *    already exist toh nahi karta (duplicate check)
 * 2. Agar unique hai, credentials ek text file (users.txt) me store karo
 * 3. Login: username+password padho file se, match karo user ke input se
 * 4. Simple menu-driven system (console based)
 *
 * NOTE: Real-world me password ko hash karke store karna chahiye
 * (bcrypt/SHA-256 jaisa). Yahan simplicity ke liye plain text use
 * kiya hai — internship task ke liye acceptable hai, but isko
 * README/video explanation me mention karna important improvement point hai.
 */

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const string FILE_NAME = "users.txt";

// Check if username already exists in the file
bool usernameExists(const string &username) {
    ifstream file(FILE_NAME);
    string storedUser, storedPass;

    while (file >> storedUser >> storedPass) {
        if (storedUser == username) {
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}

// Register a new user
void registerUser() {
    string username, password;
    cout << "\n--- Registration ---\n";
    cout << "Enter a username: ";
    cin >> username;

    if (usernameExists(username)) {
        cout << "Registration failed! Username already taken.\n";
        return;
    }

    cout << "Enter a password: ";
    cin >> password;

    // Append new user to file
    ofstream file(FILE_NAME, ios::app);
    file << username << " " << password << "\n";
    file.close();

    cout << "Registration successful! You can now log in.\n";
}

// Login an existing user
void loginUser() {
    string username, password;
    cout << "\n--- Login ---\n";
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    ifstream file(FILE_NAME);
    string storedUser, storedPass;
    bool found = false;

    while (file >> storedUser >> storedPass) {
        if (storedUser == username) {
            found = true;
            if (storedPass == password) {
                cout << "Login successful! Welcome, " << username << ".\n";
            } else {
                cout << "Login failed! Incorrect password.\n";
            }
            break;
        }
    }

    if (!found) {
        cout << "Login failed! Username not found. Please register first.\n";
    }

    file.close();
}

int main() {
    int choice;

    do {
        cout << "\n===== Login & Registration System =====\n";
        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        // Handle non-numeric input gracefully so the menu doesn't loop forever
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input! Please enter a number.\n";
            continue;
        }

        switch (choice) {
            case 1: registerUser(); break;
            case 2: loginUser(); break;
            case 3: cout << "Exiting... Goodbye!\n"; break;
            default: cout << "Invalid choice! Try again.\n";
        }

    } while (choice != 3);

    return 0;
}
