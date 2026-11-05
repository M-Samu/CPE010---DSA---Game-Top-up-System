// login.h - Registration and login, saved in users.json

#ifndef LOGIN_H
#define LOGIN_H

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

const std::size_t LOGIN_NOT_FOUND = std::string::npos;  // find() returns this when nothing is found

struct LoginAccount {
    std::string username;
    std::string password;
};

// Read all accounts from users.json
inline std::vector<LoginAccount> loadLoginAccounts() {
    std::vector<LoginAccount> users;
    std::ifstream in("users.json");
    std::vector<std::string> info;  // every "quoted string" in the file, in order
    std::string line;

    while (std::getline(in, line)) {
        size_t pos = 0;
        while ((pos = line.find('"', pos)) != LOGIN_NOT_FOUND) {
            size_t end = line.find('"', pos + 1);
            if (end == LOGIN_NOT_FOUND) break;
            info.push_back(line.substr(pos + 1, end - pos - 1));
            pos = end + 1;
        }
    }

    // info: users, then pairs of key/value: username, <name>, password, <pass>, username
    for (size_t i = 1; i + 1 < info.size(); i += 2) {
        std::string key = info[i];
        std::string value = info[i + 1];

        if (key == "username") {
            LoginAccount account;
            account.username = value;
            users.push_back(account);
        } else if (!users.empty()) {
            if (key == "password") users.back().password = value;
        }
    }
    return users;
}

// Write all accounts to users.json
inline void saveLoginAccounts(const std::vector<LoginAccount>& users) {
    std::ofstream out("users.json");
    out << "{\n  \"users\": [\n";
    for (size_t i = 0; i < users.size(); i++) {
        out << "    {\"username\": \"" << users[i].username
            << "\", \"password\": \"" << users[i].password << "\"}";
        if (i + 1 < users.size()) out << ",";
        out << "\n";
    }
    out << "  ]\n}\n";
}

// Input cannot be empty or contain a quote mark
inline bool isBadInput(const std::string& text) {
    return text.empty() || text.find('"') != LOGIN_NOT_FOUND;
}

inline void registerLogin() {
    std::vector<LoginAccount> users = loadLoginAccounts();
    LoginAccount account;

    std::cout << "Choose a username: ";
    std::getline(std::cin, account.username);
    std::cout << "Choose a password: ";
    std::getline(std::cin, account.password);

    if (isBadInput(account.username) || isBadInput(account.password)) {
        std::cout << "Invalid input (cannot be empty or contain quotes).\n";
        return;
    }
    for (const LoginAccount& u : users) {
        if (u.username == account.username) {
            std::cout << "Username already taken.\n";
            return;
        }
    }

    users.push_back(account);
    saveLoginAccounts(users);
    std::cout << "Registered successfully!\n";
}

// Returns true if the login is correct. The account that logged in is copied into loggedIn.
inline bool checkLogin(LoginAccount& loggedIn) {
    std::vector<LoginAccount> users = loadLoginAccounts();
    std::string username, password;

    std::cout << "Username: ";
    std::getline(std::cin, username);
    std::cout << "Password: ";
    std::getline(std::cin, password);

    for (const LoginAccount& u : users) {
        if (u.username == username && u.password == password) {
            loggedIn = u;
            std::cout << "Login successful. Welcome, " << username << "!\n";
            return true;
        }
    }
    std::cout << "Wrong username or password.\n";
    return false;
}

// Forgot password: the user types a username and the saved password is shown
inline void forgotPassword() {
    std::vector<LoginAccount> users = loadLoginAccounts();
    std::string username;

    std::cout << "Enter your username: ";
    std::getline(std::cin, username);

    for (const LoginAccount& u : users) {
        if (u.username == username) {
            std::cout << "Your password is: " << u.password << "\n";
            return;
        }
    }
    std::cout << "Username not found.\n";
}

#endif