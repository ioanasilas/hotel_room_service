#include "Room.h"
#include "Booking.h"
#include "Utilities.h"
#include "Hotel.h"
#include "user_management.h"
#include <iostream>
#include <limits>
#include <cctype> // for std::isdigit

void displayMenu(bool isLoggedIn)
{
    std::cout << "================ Hotel Booking Menu ================\n";
    if (isLoggedIn)
    {
        std::cout << "1. Display Rooms\n";
        std::cout << "2. Search Rooms by Criteria\n";
        std::cout << "3. Book a Room\n";
        std::cout << "4. View Booking Details\n";
        std::cout << "5. Cancel Booking\n";
    }
    else
    {
        std::cout << "6. User Registration\n";
        std::cout << "7. User Login\n";
        std::cout << "8. Staff Entrance\n";
    }
    std::cout << "9. Exit\n";
    std::cout << "=====================================================\n";
    if (!isLoggedIn)
    {
        std::cout << "Please log in to see other available options.\n";
    }
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
    bool isLoggedIn = false;
    bool isAdmin = false;
    std::string loggedInUser;

    int choice;
    do
    {
        displayMenu(isLoggedIn);
        std::cout << "Enter your choice: ";

        if (!getChoice(choice))
        {
            continue; // if invalid input ==> display the menu again
        }

        if (!isLoggedIn && (choice >= 1 && choice <= 5))
        {
            std::cout << "Please log in to access this option.\n";
            continue;
        }

        switch (choice)
        {
        case 1:
            hotel.displayRooms();
            break;
        case 2:
        {
            double maxPrice;
            bool validInput = false;

            do
            {
                std::cout << "Enter maximum price: ";
                std::cin >> maxPrice;

                if (std::cin.fail() || maxPrice <= 0)
                {
                    std::cin.clear();                                                   // clear error flag
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard input buffer
                    std::cout << "Invalid input. Please enter a positive number.\n";
                }
                else
                {
                    validInput = true;
                }

            } while (!validInput);

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
            int roomID;
            std::string checkInDate, checkOutDate;
            int guests;
            std::cout << "Enter room ID: ";
            std::cin >> roomID;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // clear input buffer
            std::cout << "Enter check-in date (YYYY-MM-DD): ";
            std::getline(std::cin, checkInDate);
            std::cout << "Enter check-out date (YYYY-MM-DD): ";
            std::getline(std::cin, checkOutDate);
            std::cout << "Enter number of guests: ";
            std::cin >> guests;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // clear input buffer

            addBooking(hotel, loggedInUser, roomID, checkInDate, checkOutDate, guests);
            break;
        }
        case 4: // view booking details
        {
            int bookingID;
            std::cout << "Enter booking ID: ";
            std::cin >> bookingID;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // clear input buffer
            displayBookingDetails(bookingID, loggedInUser, isAdmin);
            break;
        }
        case 5: // cancel booking
        {
            int bookingID;
            std::cout << "Enter booking ID to modify or cancel: ";
            std::cin >> bookingID;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // clear input buffer
            cancelBooking(bookingID);
            break;
        }
        case 6: // User Registration
        {
            displayUserMenu();
            break;
        }
        case 7: // User Login
        {
            std::string firstName, lastName;
            std::cout << "Enter First Name: ";
            std::cin >> firstName;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // clear input buffer
            std::cout << "Enter Last Name: ";
            std::cin >> lastName;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // clear input buffer

            if (loginUser("users.csv", firstName, lastName))
            {
                isLoggedIn = true;
                loggedInUser = firstName + " " + lastName;
            }
            break;
        }
        case 8: // Staff Entrance
        {
            std::cout << "Staff Entrance:\n";
            std::string password;
            std::cout << "Enter password: ";
            std::cin >> password;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // clear input buffer

            if (hotel.isAdminPasswordCorrect(password))
            {
                isAdmin = true;
                int staffChoice;
                do
                {
                    std::cout << "\nStaff Menu:\n";
                    std::cout << "1. Update Room Status\n";
                    std::cout << "2. Add New Room\n";
                    std::cout << "3. Modify Room Features\n";
                    std::cout << "4. Modify Room Price\n";
                    std::cout << "5. View All Bookings\n";
                    std::cout << "6. Back to Main Menu\n";
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
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // clear input buffer
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
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // clear input buffer
                        hotel.modifyRoomPrice(roomID, newPrice);
                        break;
                    }
                    case 5:
                        displayUserBookings("", true); // Admin views all bookings
                        break;
                    case 6:
                        std::cout << "Returning to Main Menu.\n";
                        break;
                    default:
                        std::cout << "Invalid choice. Please enter a valid option.\n";
                        break;
                    }
                } while (staffChoice != 6);
            }
            else
            {
                std::cout << "Incorrect password. Access denied.\n";
            }
            break;
        }
        case 9: // Exit
            std::cout << "Exiting Hotel Booking Menu. Goodbye!\n";
            return 0; // exit from main function
        default:
            std::cout << "Invalid choice. Please enter a valid option.\n";
            break;
        }
    } while (choice != 9);

    return 0;
}
