#ifndef UTILITIES_H
#define UTILITIES_H

#include "Room.h"
#include <vector>
#include <string>

class Utilities
{
public:
    static std::vector<Room> readCSV(const std::string &fileName);
    static void writeCSV(const std::string &fileName, const std::vector<Room> &rooms);
};

#endif // UTILITIES_H
