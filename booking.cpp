#include "Booking.h"
#include "Utilities.h"
#include "Hotel.h"
#include <iostream>
#include <vector>
#include <algorithm>

void addBooking(Hotel &hotel, const std::string &customerName, int roomID, const std::string &checkInDate, const std::string &checkOutDate, int guests)
{
  std::vector<Booking> bookings = Utilities::readBookingsCSV("bookings.csv");

  // Find the highest booking ID in the current list
  int maxID = 0;
  for (const auto &booking : bookings)
  {
    if (booking.bookingID > maxID)
    {
      maxID = booking.bookingID;
    }
  }
  int newBookingID = maxID + 1; // Increment the highest ID to get a new unique ID

  int days = hotel.dateDifference(checkInDate, checkOutDate);
  if (days < 1 || days > 10)
  {
    std::cerr << "Invalid booking duration: " << days << " days. Must be between 1 and 10 days.\n";
    return;
  }

  double price = hotel.getRoomPrice(roomID);
  if (price == 0)
  {
    std::cerr << "Room not found with ID: " << roomID << "\n";
    return;
  }

  double totalCost = price * days;
  Booking newBooking(newBookingID, customerName, roomID, checkInDate, checkOutDate, guests, totalCost, "confirmed");

  bookings.push_back(newBooking);
  Utilities::writeBookingsCSV("bookings.csv", bookings);
  std::cout << "Booking added successfully.\n";
}

void cancelBooking(int bookingID)
{
  std::vector<Booking> bookings = Utilities::readBookingsCSV("bookings.csv");
  auto it = std::find_if(bookings.begin(), bookings.end(), [bookingID](const Booking &b)
                         { return b.bookingID == bookingID; });

  if (it != bookings.end())
  {
    char confirmation;
    std::cout << "Are you sure you want to cancel the booking with ID " << bookingID << "? This operation is irreversible. (y/n): ";
    std::cin >> confirmation;

    if (confirmation == 'y' || confirmation == 'Y')
    {
      it->status = "cancelled";
      Utilities::writeBookingsCSV("bookings.csv", bookings);
      std::cout << "Booking cancelled successfully. We hope you'll be back!\n";
    }
    else
    {
      std::cout << "Cancellation aborted.\n";
    }
  }
  else
  {
    std::cout << "Booking ID not found.\n";
  }
}

void displayBookingDetails(int bookingID)
{
  std::vector<Booking> bookings = Utilities::readBookingsCSV("bookings.csv");
  auto it = std::find_if(bookings.begin(), bookings.end(), [bookingID](const Booking &b)
                         { return b.bookingID == bookingID; });
  if (it != bookings.end())
  {
    std::cout << "Booking ID: " << it->bookingID << "\n"
              << "Customer Name: " << it->customerName << "\n"
              << "Room ID: " << it->roomID << "\n"
              << "Check-In Date: " << it->checkInDate << "\n"
              << "Check-Out Date: " << it->checkOutDate << "\n"
              << "Guests: " << it->guests << "\n"
              << "Total Cost: $" << it->totalCost << "\n"
              << "Status: " << it->status << "\n";
  }
  else
  {
    std::cout << "No booking found with ID: " << bookingID << "\n";
  }
}
