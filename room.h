//Room.h
#ifndef ROOM_H
#define ROOM_H

#include <string>

const int MAX_ROOMS = 100; // Maximum number of rooms the hotel can have

struct Room {
    int roomID;
    std::string features;
    double price;
    bool availability;
};

#endif // ROOM_H
