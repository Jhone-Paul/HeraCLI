#include "file_reader.hpp"
#include "terminal_formatting.hpp"

#include <iostream>
#include <vector>
#include <iomanip>


int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: hera-cli <filename>\n";
        return 1;
    }
    int terminal_width = getTerminalWidth();

    std::cout << std::string(terminal_width, '-') << '\n' <<"Observation information" <<'\n' << std::string(terminal_width, '-') << '\n';

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

            std::cout << std::fixed << std::setprecision(9);

            std::vector<double> times = observation.getJulianDates();
                std::cout << "Start JD: " << times.front() << '\n';
                std::cout << "End JD: " << times.back() << '\n';

            std::cout << "Baselines: "
                    << observation.getNumBaselines() << '\n';

            std::cout << "Frequencies: "
                    << observation.getNumFrequencies() << '\n';

            std::cout << "Times: "
                    << observation.getNumTimes() << '\n';

            std::cout << "Polarizations: "
                    << observation.getNPols() << '\n';
            
            std::cout << "File size: "
                    << observation.getFileSizeMB(argv[1])
                    << " MB\n";
            
        }
    }
    catch (const H5::Exception& error) {
        error.printErrorStack();
        return 1;
    }
    std::cout << std::string(terminal_width, '-') << '\n';


    return 0;
}