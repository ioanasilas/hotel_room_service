#ifndef USER_MANAGEMENT_H
#define USER_MANAGEMENT_H

#include <string>
#include <vector>

struct User
{
  std::string firstName;
  std::string lastName;

  User();
  User(const std::string &first, const std::string &last);

  bool isValid() const;
};

// user operations
std::vector<User> readUsers(const std::string &filename);
void writeUsers(const std::string &filename, const std::vector<User> &users);
bool registerUser(const std::string &filename, const User &newUser);
bool loginUser(const std::string &filename, const std::string &firstName, const std::string &lastName);
void displayUserMenu();

#endif // USER_MANAGEMENT_H
