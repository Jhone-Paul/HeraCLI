#pragma once

#include <H5Cpp.h>
#include <string>

class HeraFile {
private:
    H5::H5File file;
    std::string filename;

public:
    // Constructor
    HeraFile(const std::string& path);

    // Member functions
    void listHeaders();
    int getNumBaselines();
    int getNumFrequencies();
    int getNumTimes();


    bool fileExists(const std::string& filename);
    double getFileSizeMB(const std::string& filename);
};