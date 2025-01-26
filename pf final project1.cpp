#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// User authentication
struct User {
    string username;
    string password;
};

User users[] = { {"admin", "admin123"} };

bool login() {
    string username, password;
    cout << "\n--- Login ---\n";
    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;

    for (int i = 0; i < sizeof(users) / sizeof(users[0]); ++i) {
        if (users[i].username == username && users[i].password == password) {
            cout << "Login successful!\n";
            return true;
        }
    }
    cout << "Invalid username or password.\n";
    return false;
}
