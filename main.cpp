// main.cpp
#include "hotel.h"
#include <iostream>
int main() {
    Hotel hotel;
    hotel.loadRoomsFromCSV("rooms.csv");

    int choice;
    do {
        displayMenu();
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        std::cin.ignore(); // Ignore newline character left in input buffer

        switch (choice) {
            case 1:
                hotel.displayRooms();
                break;
            case 2: {
                double maxPrice;
                std::cout << "Enter maximum price: ";
                std::cin >> maxPrice;

                bool availableOnly;
                char input;
                std::cout << "Show only available rooms? (y/n): ";
                std::cin >> input;
                availableOnly = (input == 'y' || input == 'Y');

                Room results[MAX_ROOMS]; // Assuming max possible matches is MAX_ROOMS

                int numResults = hotel.searchRoomsByCriteria(maxPrice, availableOnly, results);

                std::cout << "Search Results:\n";
                for (int i = 0; i < numResults; ++i) {
                    printRoomDetails(results[i]);
                }
                break;
            }
            case 3:
                // Implement room booking functionality
                break;
            case 4:
                // Implement view booking details functionality
                break;
            case 5:
                // Implement modify or cancel booking functionality
                break;
            case 6:
                // Display hotel facilities
                break;
            case 7:
                // Display contact information
                break;
            case 8:
                std::cout << "Exiting Hotel Booking Menu. Goodbye!\n";
                break;
            default:
                std::cout << "Invalid choice. Please enter a valid option.\n";
                break;
        }

        std::cout << "\n";
    } while (choice != 8);

    return 0;
}
