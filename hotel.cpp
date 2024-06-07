#include "Hotel.h"
#include "Utilities.h"
#include "Room.h"
#include <iostream>
#include <iomanip>
#include <ctime>
#include <sstream>

Hotel::Hotel() {}

void Hotel::loadRoomsFromCSV(const std::string &filename)
{
    rooms = Utilities::readCSV(filename);
    if (rooms.size() > MAX_ROOMS)
    {
        std::cerr << "Cannot load more than " << MAX_ROOMS << " rooms.\n";
        rooms.resize(MAX_ROOMS);
    }
}

void Hotel::displayRooms() const
{
    std::cout << "Room ID | Features        | Price    | Availability for Rental\n";
    std::cout << "---------------------------------------------------\n";
    for (const auto &room : rooms)
    {
        printRoomDetails(room);
    }
}

void Hotel::printRoomDetails(const Room &room) const
{
    std::cout << room;
}

void Hotel::displayRoomDetails(int roomID) const
{
    for (const auto &room : rooms)
    {
        if (room.roomID == roomID)
        {
            printRoomDetails(room);
            return;
        }
    }
    std::cerr << "Room with ID " << roomID << " not found.\n";
}

int Hotel::searchRoomsByCriteria(double maxPrice, bool availableOnly, Room *results) const
{
    int count = 0;
    for (const auto &room : rooms)
    {
        if (room.price <= maxPrice && (!availableOnly || room.availability))
        {
            results[count++] = room;
        }
    }
    return count;
}

bool Hotel::isAdminPasswordCorrect(const std::string &password) const
{
    return password == "admin123";
}

void Hotel::addRoom(const Room &newRoom)
{
    for (const auto &room : rooms)
    {
        if (room.roomID == newRoom.roomID)
        {
            std::cerr << "Room with ID " << newRoom.roomID << " already exists. Cannot add duplicate room ID.\n";
            return;
        }
    }

    if (rooms.size() < MAX_ROOMS)
    {
        rooms.push_back(newRoom);
        std::cout << "Room added successfully.\n";
        saveRoomsToCSV("rooms.csv");
    }
    else
    {
        std::cerr << "Cannot add more rooms. Hotel is at full capacity.\n";
    }
}

bool Hotel::isRoomAvailable(int roomID)
{
    for (const auto &room : rooms)
    {
        if (room.roomID == roomID)
        {
            return room.availability;
        }
    }
    return false;
}

void Hotel::modifyRoomFeatures(int roomID, const std::string &newFeatures)
{
    for (auto &room : rooms)
    {
        if (room.roomID == roomID)
        {
            room.features = newFeatures;
            std::cout << "Features for room " << roomID << " updated successfully.\n";
            saveRoomsToCSV("rooms.csv");
            return;
        }
    }
    std::cerr << "Room with ID " << roomID << " not found.\n";
}

void Hotel::modifyRoomPrice(int roomID, double newPrice)
{
    for (auto &room : rooms)
    {
        if (room.roomID == roomID)
        {
            room.price = newPrice;
            std::cout << "Price for room " << roomID << " updated successfully.\n";
            saveRoomsToCSV("rooms.csv");
            return;
        }
    }
    std::cerr << "Room with ID " << roomID << " not found.\n";
}

double Hotel::getRoomPrice(int roomID) const
{
    for (const auto &room : rooms)
    {
        if (room.roomID == roomID)
        {
            return room.price;
        }
    }
    return 0; // return 0 if room is not found
}

int Hotel::dateDifference(const std::string &startDate, const std::string &endDate)
{
    std::tm start_tm = {};
    std::tm end_tm = {};

    std::istringstream startStream(startDate);
    std::istringstream endStream(endDate);

    startStream >> std::get_time(&start_tm, "%Y-%m-%d");
    endStream >> std::get_time(&end_tm, "%Y-%m-%d");

    std::time_t start_time = std::mktime(&start_tm);
    std::time_t end_time = std::mktime(&end_tm);

    if (start_time == -1 || end_time == -1)
    {
        std::cerr << "Invalid date provided" << std::endl;
        return 0; // handle error scenario
    }

    const double secondsPerDay = 24 * 60 * 60;
    return static_cast<int>(difftime(end_time, start_time) / secondsPerDay);
}

void Hotel::saveRoomsToCSV(const std::string &filename) const
{
    Utilities::writeCSV(filename, rooms);
}

std::vector<int> Hotel::getRoomIDsInput()
{
    std::vector<int> roomIDs;
    std::string input;
    std::cout << "Enter room IDs (separated by space): ";
    std::getline(std::cin, input);

    std::stringstream ss(input);
    int id;
    while (ss >> id)
    {
        roomIDs.push_back(id);
    }
    return roomIDs;
}

void Hotel::updateRoomStatus(const std::vector<int> &roomIDs)
{
    for (const int roomID : roomIDs)
    {
        bool found = false;
        for (auto &room : rooms)
        {
            if (room.roomID == roomID)
            {
                room.availability = !room.availability;
                std::cout << "Room " << roomID << " status updated to " << (room.availability ? "available" : "unavailable") << ".\n";
                found = true;
                break;
            }
        }
        if (!found)
        {
            std::cerr << "Room with ID " << roomID << " not found.\n";
        }
    }
    saveRoomsToCSV("rooms.csv");
}
