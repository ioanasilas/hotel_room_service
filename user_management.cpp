#include "user_management.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <limits> // for std::numeric_limits

// constructor
User::User() : firstName(""), lastName("") {}

// param constr
User::User(const std::string &first, const std::string &last) : firstName(first), lastName(last) {}

bool User::isValid() const
{
    return !firstName.empty() && !lastName.empty();
}

bool registerUser(const std::string &filename, const User &newUser)
{
    auto users = readUsers(filename);

    // check for existing user
    for (const auto &user : users)
    {
        if (user.firstName == newUser.firstName && user.lastName == newUser.lastName)
        {
            std::cout << "User " << newUser.firstName << " " << newUser.lastName << " is already registered." << std::endl;
            return false;
        }
    }

    users.push_back(newUser);
    writeUsers(filename, users);
    std::cout << "User registered successfully!" << std::endl;
    return true;
}

bool loginUser(const std::string &filename, const std::string &firstName, const std::string &lastName)
{
    auto users = readUsers(filename);

    for (const auto &user : users)
    {
        if (user.firstName == firstName && user.lastName == lastName)
        {
            std::cout << "Login successful! Welcome, " << firstName << " " << lastName << "!" << std::endl;
            return true;
        }
    }

    std::cout << "Login failed. User not found." << std::endl;
    return false;
}

void displayUserMenu()
{
    std::string filename = "users.csv";
    std::string first, last;
    std::cout << "Enter First Name: ";
    std::cin >> first;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // clear input buffer
    std::cout << "Enter Last Name: ";
    std::cin >> last;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // clear input buffer

    User newUser(first, last);
    if (!newUser.isValid())
    {
        std::cerr << "Invalid user data provided." << std::endl;
        return;
    }

    registerUser(filename, newUser);
}
