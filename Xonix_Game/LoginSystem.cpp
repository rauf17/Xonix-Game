#include "LoginSystem.h"
#include <iostream>
#include <fstream>

LoginSystem::LoginSystem() {
    usersFile = "users.txt";
}

bool LoginSystem::usernameExists(const string& username) {
    ifstream file(usersFile);
    string u, p, n;
    while (getline(file, u, ',') && getline(file, p, ',') && getline(file, n)) {
        if (u == username) {
            return true;
        }
    }
    return false;
}

bool LoginSystem::validatePasswordStrength(const string& password) {
    return password.length() >= 5; // simple minimum length check
}

void LoginSystem::registerPlayer(const string& username, const string& password) {
    string nickname;

    if (usernameExists(username)) {
        std::cout << "Username already exists. Try again.\n";
        return;
    }

    if (!validatePasswordStrength(password)) {
        std::cout << "Password too weak. Try again.\n";
        return;
    }

    //std::cout << "Enter Nickname (optional): ";
    //std::cin.ignore();
    //getline(std::cin, nickname);

    ofstream file(usersFile, ios::app);
    file << username << "," << password << "," << nickname << endl;

    std::cout << "Registration Successful!\n";
}

bool LoginSystem::loginPlayer(const string& username, const string& password) {
    ifstream file(usersFile);
    string u, p, n;
    while (getline(file, u, ',') && getline(file, p, ',') && getline(file, n)) {
        if (u == username && p == password) {
            std::cout << "Login Successful! Welcome " << u << " (" << n << ")\n";
            return true;
        }
    }

    std::cout << "Invalid credentials. Please try again.\n";
    return false;
}

bool LoginSystem::updatePassword(const std::string& username, const std::string& newPassword) {
    std::ifstream infile(usersFile);
    std::ofstream tempFile("temp_users.txt");
    std::string u, p, n;
    bool updated = false;

    while (getline(infile, u, ',') && getline(infile, p, ',') && getline(infile, n)) {
        if (u == username) {
            tempFile << u << "," << newPassword << "," << n << "\n";
            updated = true;
        }
        else {
            tempFile << u << "," << p << "," << n << "\n";
        }
    }

    infile.close();
    tempFile.close();

    if (updated) {
        std::remove(usersFile.c_str());
        std::rename("temp_users.txt", usersFile.c_str());
    }
    else {
        std::remove("temp_users.txt");
    }

    return updated;
}
