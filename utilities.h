#ifndef UTILITIES_H
#define UTILITIES_H

#include "Room.h"
#include <vector>
#include <string>

// Forward declaration of the Booking class
class Booking;

class Utilities
{
public:
    // for general hotel stuff
    static std::vector<Room> readCSV(const std::string &fileName);
    static void writeCSV(const std::string &fileName, const std::vector<Room> &rooms);
    // for bookings
    static std::vector<Booking> readBookingsCSV(const std::string &fileName);
    static void writeBookingsCSV(const std::string &fileName, const std::vector<Booking> &bookings);
};

#endif // UTILITIES_H
