#ifndef ROOM_H
#define ROOM_H

#include <iostream> // iostream for ostream
#include <iomanip>  // iomanip for setw
#include <string>
struct Room
{
    int roomID;
    std::string features;
    double price;
    bool availability;

    // operator overloading
    friend std::ostream &operator<<(std::ostream &os, const Room &room);
};
#endif // ROOM_H
