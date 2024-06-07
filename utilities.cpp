#include "Utilities.h"
#include "Room.h"
#include "Booking.h"
#include "user_management.h"
#include <fstream>
#include <sstream>
#include <iostream>


// user data
std::vector<User> readUsers(const std::string &filename)
{
    std::vector<User> users;
    std::ifstream file(filename);
    std::string line, firstName, lastName;

    if (!file.is_open())
    {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return users;
    }

    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        if (std::getline(iss, firstName, ',') && std::getline(iss, lastName))
        {
            users.emplace_back(firstName, lastName);
        }
    }

    file.close();
    return users;
}

void writeUsers(const std::string &filename, const std::vector<User> &users)
{
    std::ofstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Failed to open file for writing: " << filename << std::endl;
        return;
    }

    for (const auto &user : users)
    {
        file << user.firstName << "," << user.lastName << "\n";
    }

    file.close();
}

// Read Room data from CSV
std::vector<Room> Utilities::readCSV(const std::string &fileName)
{
  std::vector<Room> rooms;
  std::ifstream file(fileName);
  if (!file.is_open())
  {
    std::cerr << "Failed to open file: " << fileName << "\n";
    return rooms;
  }

  std::string line;
  std::getline(file, line); // skip the header line

  while (std::getline(file, line))
  {
    std::istringstream ss(line);
    Room room;
    std::string token;

    std::getline(ss, token, ',');
    room.roomID = std::stoi(token);
    std::getline(ss, room.features, ',');
    std::getline(ss, token, ',');
    room.price = std::stod(token);
    std::getline(ss, token, ',');
    room.availability = (token == "1");

    rooms.push_back(room);
  }
  file.close();
  return rooms;
}

// Write Room data to CSV
void Utilities::writeCSV(const std::string &fileName, const std::vector<Room> &rooms)
{
  std::ofstream file(fileName);
  if (!file.is_open())
  {
    std::cerr << "Failed to open file for writing: " << fileName << "\n";
    return;
  }

  file << "roomID,features,price,availability for rental\n";
  for (const Room &room : rooms)
  {
    file << room.roomID << ","
         << room.features << ","
         << room.price << ","
         << (room.availability ? "1" : "0") << "\n";
  }
  file.close();
}

// Read Booking data from CSV
std::vector<Booking> Utilities::readBookingsCSV(const std::string &fileName)
{
  std::vector<Booking> bookings;
  std::ifstream file(fileName);
  if (!file.is_open())
  {
    std::cerr << "Failed to open file: " << fileName << "\n";
    return bookings;
  }

  std::string line;
  std::getline(file, line); // skip the header

  while (std::getline(file, line))
  {
    std::istringstream ss(line);
    std::string token;
    std::getline(ss, token, ',');
    int bookingID = std::stoi(token);
    std::string customerName;
    std::getline(ss, customerName, ',');
    std::getline(ss, token, ',');
    int roomID = std::stoi(token);
    std::string checkInDate, checkOutDate;
    std::getline(ss, checkInDate, ',');
    std::getline(ss, checkOutDate, ',');
    std::getline(ss, token, ',');
    int guests = std::stoi(token);
    std::getline(ss, token, ',');
    double totalCost = std::stod(token);
    std::string status;
    std::getline(ss, status, ',');

    Booking booking(bookingID, customerName, roomID, checkInDate, checkOutDate, guests, totalCost, status);
    bookings.push_back(booking);
  }
  file.close();
  return bookings;
}

// Write Booking data to CSV
void Utilities::writeBookingsCSV(const std::string &fileName, const std::vector<Booking> &bookings)
{
  std::ofstream file(fileName);
  if (!file.is_open())
  {
    std::cerr << "Failed to open file for writing: " << fileName << "\n";
    return;
  }

  file << "bookingID,customerName,roomID,checkInDate,checkOutDate,guests,totalCost,status\n";
  for (const Booking &booking : bookings)
  {
    file << booking.bookingID << ","
         << booking.customerName << ","
         << booking.roomID << ","
         << booking.checkInDate << ","
         << booking.checkOutDate << ","
         << booking.guests << ","
         << booking.totalCost << ","
         << booking.status << "\n";
  }
  file.close();
}