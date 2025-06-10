#pragma once
#ifndef LOGINSYSTEM_H
#define LOGINSYSTEM_H

#include <string>
using namespace std;

class LoginSystem {
private:
    string usersFile;

public:
    LoginSystem();

    bool updatePassword(const std::string& username, const std::string& newPassword);
    bool usernameExists(const string& username);
    bool validatePasswordStrength(const string& password);
    bool loginPlayer(const string& username, const string& password);
    void registerPlayer(const string& username, const string& password);

};

#endif // LOGINSYSTEM_H
