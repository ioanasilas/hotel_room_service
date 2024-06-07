#include "Booking.h"
#include "Utilities.h"
#include "Hotel.h"
#include <iostream>
#include <vector>
#include <algorithm>

void addBooking(Hotel &hotel, const std::string &customerName, int roomID, const std::string &checkInDate, const std::string &checkOutDate, int guests)
{
  std::vector<Booking> bookings = Utilities::readBookingsCSV("bookings.csv");

  // to find the last ID used in csv
  int maxID = 0;
  for (const auto &booking : bookings)
  {
    if (booking.bookingID > maxID)
    {
      maxID = booking.bookingID;
    }
  }
  int newBookingID = maxID + 1; // to create a new ID

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

  // check for overlapping bookings
  for (const auto &booking : bookings)
  {
    if (booking.roomID == roomID && booking.status != "cancelled")
    {
      // calculate the number of days since the reference date for existing booking dates
      int existingCheckIn = hotel.dateDifference("2024-01-01", booking.checkInDate);
      int existingCheckOut = hotel.dateDifference("2024-01-01", booking.checkOutDate);

      // calculate the number of days since the reference date for new booking dates
      int newCheckIn = hotel.dateDifference("2024-01-01", checkInDate);
      int newCheckOut = hotel.dateDifference("2024-01-01", checkOutDate);

      // check for overlap
      if ((newCheckIn >= existingCheckIn && newCheckIn < existingCheckOut) ||
          (newCheckOut > existingCheckIn && newCheckOut <= existingCheckOut) ||
          (newCheckIn <= existingCheckIn && newCheckOut >= existingCheckOut))
      {
        std::cerr << "Room ID " << roomID << " is already booked for the selected period.\n";
        return;
      }
    }
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

void displayBookingDetails(int bookingID, const std::string &loggedInUser, bool isAdmin)
{
  std::vector<Booking> bookings = Utilities::readBookingsCSV("bookings.csv");
  auto it = std::find_if(bookings.begin(), bookings.end(), [bookingID](const Booking &b)
                         { return b.bookingID == bookingID; });
  if (it != bookings.end())
  {
    if (isAdmin || it->customerName == loggedInUser)
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
      std::cout << "Access denied. You can only view your own bookings.\n";
    }
  }
  else
  {
    std::cout << "No booking found with ID: " << bookingID << "\n";
  }
}

// for users
void displayUserBookings(const std::string &customerName, bool isAdmin)
{
  std::vector<Booking> bookings = Utilities::readBookingsCSV("bookings.csv");

  std::cout << "Booking Details:\n";
  std::cout << "Booking ID | Customer Name | Room ID | Check-In Date | Check-Out Date | Guests | Total Cost | Status\n";
  std::cout << "------------------------------------------------------------------------------------------------------\n";

  for (const auto &booking : bookings)
  {
    if (isAdmin || booking.customerName == customerName)
    {
      std::cout << booking.bookingID << " | " << booking.customerName << " | " << booking.roomID << " | "
                << booking.checkInDate << " | " << booking.checkOutDate << " | " << booking.guests << " | $"
                << booking.totalCost << " | " << booking.status << "\n";
    }
  }
}