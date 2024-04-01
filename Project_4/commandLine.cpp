// Project identifier: 3E33912F8BAA7542FC4A1585D2DB6FE0312725B9
// Created by fs200 on 2023/11/22.

#include "commandLine.h"

void printHelp() {
    cout << "This message should be helpful enough.\n";
}  // printHelp()

// Process the command line; there is no return value, but the Options
// struct is passed by reference and is modified by this function to send
// information back to the calling function.
void getMode(int argc, char* argv[], Options& options) {
    // These are used with getopt_long()
    opterr = false; // Let us handle all error output for command line options
    int choice;
    int index = 0;
    option long_options[] = {
            { "mode", required_argument, nullptr, 'm' },
            { "help", no_argument, nullptr, 'h' },
            { nullptr, 0, nullptr, '\0' },
    };  // long_options[]

    while ((choice = getopt_long(argc, argv, "hm:", long_options, &index)) != -1) {
        switch (choice) {
            case 'h': {
                printHelp();
                exit(0);
            }
            case 'm': {
                if (options.mode != Mode::NONE) {
                    cerr << "multiple modes detected" << std::endl;
                    exit(1);
                }
                if (string(optarg) == "MST") {
                    options.mode = Mode::MST;
                } else if (string(optarg) == "FASTTSP") {
                    options.mode = Mode::FASTTSP;
                } else if (string(optarg) == "OPTTSP") {
                    options.mode = Mode::OPTTSP;
                } else {
                    cerr << "Unrecognized mode: " << optarg << std::endl;
                    exit(1);
                }
                break;
            }  // case 'm'
            default:
                cerr << "Error: invalid option!" << std::endl;
                exit(1);
        }  // switch ..choice
    }  // while
}  // getMode()

