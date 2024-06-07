#include "Room.h"
#include <iostream>
#include <iomanip>

std::ostream& operator<<(std::ostream& os, const Room& room) 
{
    os << std::setw(7) << room.roomID << " | "
       << std::setw(15) << room.features << " | "
       << std::setw(8) << std::fixed << std::setprecision(2) << room.price << " | "
       << (room.availability ? "Available" : "Unavailable") << "\n";
    return os;
}