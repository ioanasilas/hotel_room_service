#ifndef ROOM_H
#define ROOM_H

#include <string>

struct Room {
    int roomID;
    std::string features;
    double price;
    bool availability;
};

#endif // ROOM_H
