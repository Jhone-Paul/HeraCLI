#include "file_reader.hpp"
#include <iostream>
#include <filesystem>

HeraFile::HeraFile(const std::string& path)
    : file(path, H5F_ACC_RDONLY), filename(path) {
}

void HeraFile::listHeaders() {
    H5::Group header = file.openGroup("/Header");

    for (hsize_t i = 0; i < header.getNumObjs(); i++) {
        std::cout << header.getObjnameByIdx(i) << '\n';
    }
}

int HeraFile::getNumBaselines() {
    H5::DataSet dataset = file.openDataSet("/Header/Nbls");

    int value;
    dataset.read(&value, H5::PredType::NATIVE_INT);

    return value;
}

int HeraFile::getNumFrequencies() {
    H5::DataSet dataset = file.openDataSet("/Header/Nfreqs");

    int value;
    dataset.read(&value, H5::PredType::NATIVE_INT);

    return value;
}
 
int HeraFile::getNumTimes() {
    H5::DataSet dataset = file.openDataSet("/Header/Ntimes");

    int value;
    dataset.read(&value, H5::PredType::NATIVE_INT);

    return value;
}

bool HeraFile::fileExists(const std::string& filename) {
    return std::filesystem::exists(filename);
}

double HeraFile::getFileSizeMB(const std::string& filename) {
    return std::filesystem::file_size(filename)
           / (1024.0 * 1024.0);
}