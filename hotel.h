#pragma once
#include <string>
#include <vector>
#include "Utilities.h"

const int MAX_ROOMS = 100; // max number of rooms the hotel can have

class Hotel
{
private:
    std::vector<Room> rooms;

public:
    Hotel();
    void loadRoomsFromCSV(const std::string &filename);
    void displayRooms() const;
    void displayRoomDetails(int roomID) const;
    int searchRoomsByCriteria(double maxPrice, bool availableOnly, Room *results) const;
    bool isAdminPasswordCorrect(const std::string &password) const;
    void closeRoomForRenovation(int roomID);
    void reopenRoomForRenovation(int roomID);
    void addRoom(const Room &newRoom);
    void modifyRoomFeatures(int roomID, const std::string &newFeatures);
    void modifyRoomPrice(int roomID, double newPrice);
    void saveRoomsToCSV(const std::string &filename) const;
    void printRoomDetails(const Room &room) const;
    // new
    double getRoomPrice(int roomID) const;
    static int dateDifference(const std::string &startDate, const std::string &endDate);
};
