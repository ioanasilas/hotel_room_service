# Hotel Motel Holiday Inn
## File Structure

### Hotel.h
Header for the Hotel class.

Contains: Declaration and member functions for room management and admin operations.

### Hotel.cpp
Implementation of the Hotel class.

Contains: Functions for loading, displaying, searching, and modifying rooms.

### Room.h
Header for the Room class.

Contains: Declaration and data members for room attributes.

### Room.cpp
Implementation of the Room class.

Contains: Overloaded stream insertion operator for printing room details.

### Utilities.h
Header for utility functions.

Contains: Declarations for reading and writing CSV files.

### Utilities.cpp
Implementation of utility functions.

Contains: Functions for reading and writing room and booking data.

### Booking.h
Header for the Booking class.

Contains: Declaration and data members for booking details.

### Booking.cpp
Implementation of the Booking class.

Contains: Functions for adding, viewing, and canceling bookings.

### user_management.h
Header for user management functions.

Contains: Declaration of the User class and functions for user registration and login.

### user_management.cpp
Implementation of user management functions.

Contains: Functions for reading/writing user data, registering, and logging in users.

### main.cpp
Main entry point for the application.

Contains: Main function to display the menu and handle user input.

### bookings.csv, rooms.csv, users.csv
Each file stores information about bookings, rooms and registered users, respectively.

## How to run the code:
1. Compile the source files into an executable, for example:
`g++ -o hotel_service main.cpp Hotel.cpp Utilities.cpp booking.cpp user_management.cpp room.cpp`
2. Executes the compiled program from the current dir
`./hotel_service`
Then, the menu options should appear in the terminal and the user can navigate through them freely.
