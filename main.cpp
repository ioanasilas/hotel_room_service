#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <limits>

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

    // Admin functionalities
    bool isAdminPasswordCorrect(const std::string& password) const;
    void closeRoomForReservation(int roomID);
    void openRoomForReservation(int roomID);
    void addRoom(const Room& newRoom);
    void saveRoomsToCSV(const std::string& filename) const;
    void modifyRoomFeatures(int roomID, const std::string& newFeatures);
    void modifyRoomPrice(int roomID, double newPrice);
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
        std::cout << "Room ID: " << std::setw(4) << rooms[i].roomID << " | "
                  << "Features: " << std::setw(15) << rooms[i].features << " | "
                  << "Price: $" << std::setw(8) << std::fixed << std::setprecision(2) << rooms[i].price << " | "
                  << "Availability: " << (rooms[i].availability ? "Available" : "Unavailable") << "\n";
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

bool Hotel::isAdminPasswordCorrect(const std::string& password) const {
    // Replace with your actual admin password check logic
    return password == "admin123";
}

void Hotel::closeRoomForReservation(int roomID) {
    for (int i = 0; i < numRooms; ++i) {
        if (rooms[i].roomID == roomID) {
            rooms[i].availability = false; // Set availability to false
            std::cout << "Room " << roomID << " closed for reservations.\n";
            saveRoomsToCSV("rooms.csv"); // Save changes to CSV after modifying room availability
            return;
        }
    }
    std::cout << "Room with ID " << roomID << " not found.\n";
}

void Hotel::openRoomForReservation(int roomID) {
    for (int i = 0; i < numRooms; ++i) {
        if (rooms[i].roomID == roomID) {
            rooms[i].availability = true; // Set availability to true
            std::cout << "Room " << roomID << " opened for reservations.\n";
            saveRoomsToCSV("rooms.csv"); // Save changes to CSV after modifying room availability
            return;
        }
    }
    std::cout << "Room with ID " << roomID << " not found.\n";
}

void Hotel::addRoom(const Room& newRoom) {
    // Check if a room with the same ID already exists
    for (int i = 0; i < numRooms; ++i) {
        if (rooms[i].roomID == newRoom.roomID) {
            std::cout << "Room with ID " << newRoom.roomID << " already exists. Cannot add duplicate room.\n";
            return;
        }
    }

    // Add the new room if there is no duplicate
    if (numRooms < MAX_ROOMS) {
        rooms[numRooms] = newRoom;
        ++numRooms;
        std::cout << "Room added successfully.\n";
        saveRoomsToCSV("rooms.csv"); // Save changes to CSV after adding new room
    } else {
        std::cout << "Cannot add more rooms. Hotel is at full capacity.\n";
    }
}

void Hotel::saveRoomsToCSV(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file for writing: " << filename << "\n";
        return;
    }

    // Write header line
    file << "roomID,features,price,availability\n";

    // Write room data
    for (int i = 0; i < numRooms; ++i) {
        file << rooms[i].roomID << ","
             << rooms[i].features << ","
             << rooms[i].price << ","
             << (rooms[i].availability ? "1" : "0") << "\n";
    }

    file.close();
}

void Hotel::modifyRoomFeatures(int roomID, const std::string& newFeatures) {
    for (int i = 0; i < numRooms; ++i) {
        if (rooms[i].roomID == roomID) {
            rooms[i].features = newFeatures;
            std::cout << "Features for room " << roomID << " updated successfully.\n";
            saveRoomsToCSV("rooms.csv"); // Save changes to CSV after modifying room features
            return;
        }
    }
    std::cout << "Room with ID " << roomID << " not found.\n";
}

void Hotel::modifyRoomPrice(int roomID, double newPrice) {
    for (int i = 0; i < numRooms; ++i) {
        if (rooms[i].roomID == roomID) {
            rooms[i].price = newPrice;
            std::cout << "Price for room " << roomID << " updated successfully.\n";
            saveRoomsToCSV("rooms.csv"); // Save changes to CSV after modifying room price
            return;
        }
    }
    std::cout << "Room with ID " << roomID << " not found.\n";
}

void displayMenu() {
    std::cout << "================ Hotel Booking Menu ================\n";
    std::cout << "1. Display Rooms\n";
    std::cout << "2. Search Rooms by Criteria\n";
    std::cout << "3. Book a Room\n";
    std::cout << "4. View Booking Details\n";
    std::cout << "5. Modify or Cancel Booking\n";
    std::cout << "6. View Hotel Facilities\n";
    std::cout << "7. Contact Information\n";
    std::cout << "8. Exit\n";
    std::cout << "9. Staff Entrance\n";
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
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore newline character left in input buffer

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
            case 9: {
                std::cout << "Staff Entrance:\n";
                std::string password;
                std::cout << "Enter password: ";
                std::cin >> password;

                if (hotel.isAdminPasswordCorrect(password)) {
                    int staffChoice;
                    do {
                        std::cout << "\nStaff Menu:\n";
                        std::cout << "1. Close Room for Reservation\n";
                        std::cout << "2. Open Room for Reservation\n";
                        std::cout << "3. Add New Room\n";
                        std::cout << "4. Modify Room Features\n";
                        std::cout << "5. Modify Room Price\n";
                        std::cout << "6. Back to Main Menu\n";
                        std::cout << "Enter your choice: ";
                        std::cin >> staffChoice;
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore newline character left in input buffer

                        switch (staffChoice) {
                            case 1: {
                                int roomID;
                                std::cout << "Enter Room ID to close for reservation: ";
                                std::cin >> roomID;
                                hotel.closeRoomForReservation(roomID);
                                break;
                            }
                            case 2: {
                                int roomID;
                                std::cout << "Enter Room ID to open for reservation: ";
                                std::cin >> roomID;
                                hotel.openRoomForReservation(roomID);
                                break;
                            }
                            case 3: {
                                Room newRoom;
                                std::cout << "EDGE CASE HERE!! FIX NON-NUMERIC-Enter Room ID: ";
                                std::cin >> newRoom.roomID;
                                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                                std::cout << "Enter Features: ";
                                std::getline(std::cin, newRoom.features);
                                std::cout << "Enter Price: ";
                                std::cin >> newRoom.price;
                                newRoom.availability = true; // New rooms are initially available
                                hotel.addRoom(newRoom);
                                break;
                            }
                            case 4: {
                                int roomID;
                                std::string newFeatures;
                                std::cout << "Enter Room ID to modify: ";
                                std::cin >> roomID;
                                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore newline character left in input buffer
                                std::cout << "Enter new features: ";
                                std::getline(std::cin, newFeatures);
                                hotel.modifyRoomFeatures(roomID, newFeatures);
                                break;
                            }
                            case 5: {
                                int roomID;
                                double newPrice;
                                std::cout << "EDGE CASE- NON NUMERÝC - Enter Room ID to modify: ";
                                std::cin >> roomID;
                                std::cout << "Enter new price: ";
                                std::cin >> newPrice;
                                hotel.modifyRoomPrice(roomID, newPrice);
                                break;
                            }
                            case 6:
                                std::cout << "Returning to Main Menu.\n";
                                break;
                            default:
                                std::cout << "Invalid choice. Please enter a valid option.\n";
                                break;
                        }
                    } while (staffChoice != 6); // Loop until staff chooses to return to main menu
                } else {
                    std::cout << "Incorrect password. Access denied.\n";
                }
                break;
            }
            default:
                std::cout << "Invalid choice. Please enter a valid option.\n";
                break;
        }
    } while (choice != 8); // Loop until user chooses to exit

    return 0;
}
