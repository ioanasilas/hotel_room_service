// Utilities.h
#ifndef UTILITIES_H
#define UTILITIES_H

#include <string>

class Utilities {
public:
    static void readCSV(std::string fileName);
    static void writeCSV(std::string fileName, std::string content);
    // Other utility methods
};

#endif
