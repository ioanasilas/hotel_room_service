#include <iostream>
#include <fstream>
#include <sstream>

const int MAX_ROOMS = 100; // Maximum number of rooms the hotel can have

struct Room {
    int roomID;
    std::string features;
    double price;
    bool availability;
};

class Hotel {
private:
    Room rooms[MAX_ROOMS];
    int numRooms;

public:
    Hotel() : numRooms(0) {}

    void loadRoomsFromCSV(const std::string& filename);
    void displayRooms() const;
    void displayRoomDetails(int roomID) const;
    int searchRoomsByCriteria(double maxPrice, bool availableOnly, Room* results) const;
    int getNumRooms() const { return numRooms; }
};

void Hotel::loadRoomsFromCSV(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << "\n";
        return;
    }

    std::string line;
    std::getline(file, line); // Read header line (optional)

    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::string token;

        int roomID;
        std::string features;
        double price;
        bool availability;

        // Read room data from CSV
        std::getline(ss, token, ',');
        roomID = std::stoi(token);

        std::getline(ss, features, ',');

        std::getline(ss, token, ',');
        price = std::stod(token);

        std::getline(ss, token, ',');
        availability = token == "1";

        // Add room to hotel if capacity allows
        if (numRooms < MAX_ROOMS) {
            rooms[numRooms].roomID = roomID;
            rooms[numRooms].features = features;
            rooms[numRooms].price = price;
            rooms[numRooms].availability = availability;
            ++numRooms;
        } else {
            std::cout << "Cannot add more rooms. Hotel is at full capacity.\n";
            break; // Exit loop if maximum rooms reached
        }
    }
    file.close();
}

void Hotel::displayRooms() const {
    for (int i = 0; i < numRooms; ++i) {
        std::cout << "Room ID: " << rooms[i].roomID << "\n"
                  << "Features: " << rooms[i].features << "\n"
                  << "Price: $" << rooms[i].price << "\n"
                  << "Availability: " << (rooms[i].availability ? "Available" : "Unavailable") << "\n"
                  << "---------------------------\n";
    }
}

void Hotel::displayRoomDetails(int roomID) const {
    for (int i = 0; i < numRooms; ++i) {
        if (rooms[i].roomID == roomID) {
            std::cout << "Room ID: " << rooms[i].roomID << "\n"
                      << "Features: " << rooms[i].features << "\n"
                      << "Price: $" << rooms[i].price << "\n"
                      << "Availability: " << (rooms[i].availability ? "Available" : "Unavailable") << "\n";
            return;
        }
    }
    std::cout << "Room with ID " << roomID << " not found.\n";
}

int Hotel::searchRoomsByCriteria(double maxPrice, bool availableOnly, Room* results) const {
    int count = 0;

    for (int i = 0; i < numRooms; ++i) {
        if (rooms[i].price <= maxPrice && (!availableOnly || rooms[i].availability)) {
            results[count] = rooms[i];
            ++count;
        }
    }

    return count;
}

void displayMenu() {
    std::cout << "================ Hotel Booking Menu ================\n";
    std::cout << "1. Display Available Rooms\n";
    std::cout << "2. Search Rooms by Criteria\n";
    std::cout << "3. Book a Room\n";
    std::cout << "4. View Booking Details\n";
    std::cout << "5. Modify or Cancel Booking\n";
    std::cout << "6. View Hotel Facilities\n";
    std::cout << "7. Contact Information\n";
    std::cout << "8. Exit\n";
    std::cout << "=====================================================\n";
}

void printRoomDetails(const Room& room) {
    std::cout << "Room ID: " << room.roomID << "\n"
              << "Features: " << room.features << "\n"
              << "Price: $" << room.price << "\n"
              << "Availability: " << (room.availability ? "Available" : "Unavailable") << "\n"
              << "---------------------------\n";
}

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
