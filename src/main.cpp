#include "file_reader.hpp"
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: hera-cli <filename>\n";
        return 1;
    }

    bool show_headers = false;
    bool show_summary = false;

    for(int i =0; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "--headers") {
            show_headers = true;
        } else if (arg == "--summary") {
            show_summary = true;
        }
    }

    try {
        HeraFile observation(argv[1]);
        if (show_headers) {
            observation.listHeaders();
        }
        if (show_summary){
            std::cout << "Baselines: "
                    << observation.getNumBaselines() << '\n';

            std::cout << "Frequencies: "
                    << observation.getNumFrequencies() << '\n';
            std::cout << "Times: "
                    << observation.getNumTimes() << '\n';

            std::cout << "File size: "
                << observation.getFileSizeMB(argv[1])
                << " MB\n";
        }
    }
    catch (const H5::Exception& error) {
        error.printErrorStack();
        return 1;
    }



    return 0;
}