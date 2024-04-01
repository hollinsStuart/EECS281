// Project identifier: 292F24D17A4455C1B5133EDD8C7CEAA0C9570A98
// Created by fs200 on 2023/11/5.

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
            { "verbose", no_argument, nullptr, 'v' },
            { "file", required_argument, nullptr, 'f' },
            { "help", no_argument, nullptr, 'h' },
            { nullptr, 0, nullptr, '\0' },
    };  // long_options[]

    while ((choice = getopt_long(argc, argv, "vf:h", long_options, &index)) != -1) {
        switch (choice) {
            case 'h':
                printHelp();
                exit(0);
            case 'v': {
                // verbose
                options.verbose = true;
                break;
            }  // case 'v'
            case 'f': {
                options.haveFile = true;
                options.fileName = optarg;
                break;
            }
            default:
                cerr << "Error: invalid option!" << std::endl;
                exit(1);
        }  // switch ..choice
    }  // while

}  // getMode()

