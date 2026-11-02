

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

const string FILE_NAME = "users.json";

struct User {
    string username;
    string password;
};

// Read users.json and return all users in it
vector<User> loadUsers() {
    vector<User> users;
    ifstream in(FILE_NAME);
    if (!in) return users;  // file doesn't exist yet

    // Collect every "quoted string" in the file, in order
    vector<string> info;
    string line;
    while (getline(in, line)) {
        size_t pos = 0;
        while ((pos = line.find('"', pos)) != string::npos) {
            size_t end = line.find('"', pos + 1);
            if (end == string::npos) break;
            info.push_back(line.substr(pos + 1, end - pos - 1));
            pos = end + 1;
        }
    }

    // Info 
    for (size_t i = 1; i + 3 < info.size(); i += 4) {
        users.push_back({info[i + 1], info[i + 3]});
    }
    return users;
}

// Write all users to users.json
void saveUsers(const vector<User>& users) {
    ofstream out(FILE_NAME);
    out << "{\n  \"users\": [\n";
    for (size_t i = 0; i < users.size(); i++) {
        out << "    {\"username\": \"" << users[i].username
            << "\", \"password\": \"" << users[i].password << "\"}";
        if (i + 1 < users.size()) out << ",";
        out << "\n";
    }
    out << "  ]\n}\n";
}

bool hasBadChars(const string& s) {
    return s.empty() || s.find('"') != string::npos || s.find('\\') != string::npos;
}

void registerUser() {
    vector<User> users = loadUsers();

    string username, password;
    cout << "Choose a username: ";
    getline(cin, username);
    if (hasBadChars(username)) {
        cout << "Invalid username (no empty, quotes or backslashes).\n";
        return;
    }
    for (const User& u : users) {
        if (u.username == username) {
            cout << "Username already taken.\n";
            return;
        }
    }

    cout << "Choose a password: ";
    getline(cin, password);
    if (hasBadChars(password)) {
        cout << "Invalid password (no empty, quotes or backslashes).\n";
        return;
    }

    users.push_back({username, password});
    saveUsers(users);
    cout << "Registered successfully!\n";
}

void loginUser() {
    vector<User> users = loadUsers();

    string username, password;
    cout << "Username: ";
    getline(cin, username);
    cout << "Password: ";
    getline(cin, password);

    for (const User& u : users) {
        if (u.username == username && u.password == password) {
            cout << "Login successful. Welcome, " << username << "!\n";
            return;
        }
    }
    cout << "Wrong username or password.\n";
}

int main() {
    while (true) {
        cout << "\n1. Register\n2. Login\n3. Exit\nChoose: ";
        string choice;
        if (!getline(cin, choice)) break;

        if (choice == "1") registerUser();
        else if (choice == "2") loginUser();
        else if (choice == "3") break;
        else cout << "Invalid choice.\n";
    }
    return 0;
}