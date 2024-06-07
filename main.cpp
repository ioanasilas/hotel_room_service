#include "Room.h"
#include "Booking.h"
#include "Utilities.h"
#include "Hotel.h"
#include <iostream>
#include <limits>
#include <cctype> // for std::isdigit
#include "hotel.h"

void displayMenu()
{
    std::cout << "================ Hotel Booking Menu ================\n";
    std::cout << "1. Display Rooms\n";
    std::cout << "2. Search Rooms by Criteria\n";
    std::cout << "3. Book a Room\n";
    std::cout << "4. View Booking Details\n";
    std::cout << "5. Cancel Booking\n";
    std::cout << "6. Exit\n";
    std::cout << "7. Staff Entrance\n";
    std::cout << "=====================================================\n";
}

bool getChoice(int &choice)
{
    std::string input;
    std::getline(std::cin, input);

    // check if input is a single digit
    if (input.size() == 1 && std::isdigit(input[0]))
    {
        choice = input[0] - '0'; // convert char to int
        return true;
    }

    std::cerr << "Invalid choice. Please enter a valid option.\n";
    return false;
}

int main()
{
    Hotel hotel;
    hotel.loadRoomsFromCSV("rooms.csv");

    int choice;
    do
    {
        displayMenu();
        std::cout << "Enter your choice: ";

        if (!getChoice(choice))
        {
            continue; // if invalid input ==> display the menu again
        }

        switch (choice)
        {
        case 1:
            hotel.displayRooms();
            break;
        case 2:
        {
            double maxPrice;
            std::cout << "Enter maximum price: ";
            std::cin >> maxPrice;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // clear input buffer
            bool availableOnly;
            std::cout << "Show only available rooms? (y/n): ";
            char input;
            std::cin >> input;
            availableOnly = (input == 'y' || input == 'Y');
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // clear input buffer

            Room results[MAX_ROOMS];
            int numResults = hotel.searchRoomsByCriteria(maxPrice, availableOnly, results);
            std::cout << "Search Results:\n";
            std::cout << "Room ID | Features        | Price    | Availability for rental\n";
            std::cout << "---------------------------------------------------\n";
            for (int i = 0; i < numResults; ++i)
            {
                hotel.printRoomDetails(results[i]);
            }
            break;
        }
        case 3: // book a room
        {
            std::string customerName;
            int roomID;
            std::string checkInDate, checkOutDate;
            int guests;
            std::cout << "Enter customer name: ";
            std::getline(std::cin, customerName);
            std::cout << "Enter room ID: ";
            std::cin >> roomID;
            std::cin.ignore();
            std::cout << "Enter check-in date (YYYY-MM-DD): ";
            std::getline(std::cin, checkInDate);
            std::cout << "Enter check-out date (YYYY-MM-DD): ";
            std::getline(std::cin, checkOutDate);
            std::cout << "Enter number of guests: ";
            std::cin >> guests;
            std::cin.ignore();

            addBooking(hotel, customerName, roomID, checkInDate, checkOutDate, guests);
            break;
        }
        case 4: // view booking details
        {
            int bookingID;
            std::cout << "Enter booking ID: ";
            std::cin >> bookingID;
            std::cin.ignore();
            displayBookingDetails(bookingID);
            break;
        }
        case 5: // cancel booking
        {
            int bookingID;
            std::cout << "Enter booking ID to modify or cancel: ";
            std::cin >> bookingID;
            std::cin.ignore();
            cancelBooking(bookingID);
            break;
        }
        case 7:
        {
            std::cout << "Staff Entrance:\n";
            std::string password;
            std::cout << "Enter password: ";
            std::cin >> password;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // clear input buffer

            if (hotel.isAdminPasswordCorrect(password))
            {
                int staffChoice;
                do
                {
                    std::cout << "\nStaff Menu:\n";
                    std::cout << "1. Update Room Status\n";
                    std::cout << "2. Add New Room\n";
                    std::cout << "3. Modify Room Features\n";
                    std::cout << "4. Modify Room Price\n";
                    std::cout << "5. Back to Main Menu\n";
                    std::cout << "Enter your choice: ";

                    if (!getChoice(staffChoice))
                    {
                        continue; // if invalid input, display the staff menu again
                    }

                    switch (staffChoice)
                    {
                    case 1:
                    {
                        std::vector<int> roomIDs = hotel.getRoomIDsInput(); // Function to get room IDs
                        hotel.updateRoomStatus(roomIDs);
                        break;
                    }
            
                    case 2:
                    {
                        Room newRoom;
                        std::cout << "Enter Room ID: ";
                        std::cin >> newRoom.roomID;
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // clear input buffer
                        std::cout << "Enter Features: ";
                        std::getline(std::cin, newRoom.features);
                        std::cout << "Enter Price: ";
                        std::cin >> newRoom.price;
                        newRoom.availability = true;
                        hotel.addRoom(newRoom);
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // clear input buffer
                        break;
                    }
                    case 3:
                    {
                        int roomID;
                        std::string newFeatures;
                        std::cout << "Enter Room ID for feature modification: ";
                        std::cin >> roomID;
                        std::cin.ignore();
                        std::cout << "Enter new features: ";
                        std::getline(std::cin, newFeatures);
                        hotel.modifyRoomFeatures(roomID, newFeatures);
                        break;
                    }
                    case 4:
                    {
                        int roomID;
                        double newPrice;
                        std::cout << "Enter Room ID for price modification: ";
                        std::cin >> roomID;
                        std::cout << "Enter new price: ";
                        std::cin >> newPrice;
                        hotel.modifyRoomPrice(roomID, newPrice);
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // clear input buffer
                        break;
                    }
                    case 5:
                        std::cout << "Returning to Main Menu.\n";
                        break;
                    default:
                        std::cout << "Invalid choice. Please enter a valid option.\n";
                        break;
                    }
                } while (staffChoice != 5);
            }
            else
            {
                std::cout << "Incorrect password. Access denied.\n";
            }
            break;
        }
        case 6:
            std::cout << "Exiting Hotel Booking Menu. Goodbye!\n";
            return 0; // exit from main function
        default:
            std::cout << "Invalid choice. Please enter a valid option.\n";
            break;
        }
    } while (choice != 6);

    return 0;
}
