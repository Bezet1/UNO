export module DataBaseModule;
import GlobalModule;
#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>

namespace fs = std::filesystem;

const std::string DATABASE_FILE = "user_database.txt";

export struct UserData {
    std::string username;
    std::string password;
};
export std::vector<UserData> users;

export void createDatabaseFile() {
    if (!fs::exists(DATABASE_FILE)) {
        std::ofstream newFile(DATABASE_FILE);
        if (!newFile.is_open()) {
            std::cerr << "Error: Could not create database file." << std::endl;
        }
    }
}

// Function to check if a user exists in the database
export bool userExists(std::string& username) {
    return std::any_of(users.begin(), users.end(), [&](const UserData& user) {
        return user.username == username;
    });
}

// Function to check if the password matches for a given username
export bool passwordMatches(std::string& username, std::string& password) {
    std::ifstream file(DATABASE_FILE);
    std::string line;
    while (std::getline(file, line)) {
        if (line.substr(0, line.find(',')) == username) {
            std::string storedPassword = line.substr(line.find(',') + 1);
            return storedPassword == password;
        }
    }
    return false;
}

// Function to add a new user to the database
export void addUser(std::string& username, std::string& password) {
    std::ofstream file(DATABASE_FILE, std::ios_base::app);
    file << username << ',' << password << std::endl;
}

// Function to perform login authentication
export bool authenticateLogin() {
    if (userExists(username)) {
        return passwordMatches(username, password);
    }
    else {
        addUser(username, password);
        return true;
    }
}

export void readUsersFromDataBase() {
    std::ifstream file(DATABASE_FILE);
    std::string line;
    while (std::getline(file, line)) {
        size_t pos = line.find(',');
        if (pos != std::string::npos) {
            UserData user;
            user.username = line.substr(0, pos);
            user.password = line.substr(pos + 1);
            users.push_back(user);
        }
    }
}