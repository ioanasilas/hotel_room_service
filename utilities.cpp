#include "Utilities.h"
#include <iostream>
#include <fstream>
#include <sstream>

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
  std::getline(file, line); // read then discard the header line

  while (std::getline(file, line))
  {
    std::istringstream ss(line);
    std::string token;
    Room room;

    std::getline(ss, token, ',');
    room.roomID = std::stoi(token);

    std::getline(ss, room.features, ',');

    std::getline(ss, token, ',');
    room.price = std::stod(token);

    std::getline(ss, token, ',');
    room.availability = token == "1";

    rooms.push_back(room);
  }
  file.close();
  return rooms;
}

void Utilities::writeCSV(const std::string &fileName, const std::vector<Room> &rooms)
{
  std::ofstream file(fileName);
  if (!file.is_open())
  {
    std::cerr << "Failed to open file for writing: " << fileName << "\n";
    return;
  }

  file << "roomID,features,price,availability\n";
  for (const auto &room : rooms)
  {
    file << room.roomID << ","
         << room.features << ","
         << room.price << ","
         << (room.availability ? "1" : "0") << "\n";
  }
  file.close();
}
