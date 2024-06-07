#pragma once

#include <string>
#include <vector>

class Hotel; // Forward declaration of Hotel class

class Booking
{
public:
    int bookingID;
    std::string customerName;
    int roomID;
    std::string checkInDate;
    std::string checkOutDate;
    int guests;
    double totalCost;
    std::string status;

    Booking(int id, const std::string &name, int roomId, const std::string &checkIn, const std::string &checkOut, int guestCount, double cost, const std::string &bookingStatus)
        : bookingID(id), customerName(name), roomID(roomId), checkInDate(checkIn), checkOutDate(checkOut), guests(guestCount), totalCost(cost), status(bookingStatus) {}
};

void addBooking(Hotel &hotel, const std::string &customerName, int roomID, const std::string &checkInDate, const std::string &checkOutDate, int guests);
void cancelBooking(int bookingID);
void displayBookingDetails(int bookingID, const std::string &loggedInUser, bool isAdmin);
void displayUserBookings(const std::string &customerName, bool isAdmin);
