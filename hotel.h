//hotel.h
#ifndef HOTEL_H
#define HOTEL_H

#include <string>
#include "Room.h"

class Hotel {
private:
    Room rooms[MAX_ROOMS];
    int numRooms;

public:
    Hotel();
    void loadRoomsFromCSV(const std::string& filename);
    void displayRooms() const;
    void displayRoomDetails(int roomID) const;
    int searchRoomsByCriteria(double maxPrice, bool availableOnly, Room* results) const;
    int getNumRooms() const;
};

void displayMenu();
void printRoomDetails(const Room& room);

#endif // HOTEL_H
