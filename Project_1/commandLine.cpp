// Project Identifier: A8A3A33EF075ACEF9B08F5B9845569ECCB423725
// Created by fs200 on 2023/9/7.
//

#include "commandLine.h"

void printHelp() {
    // substitute with a help message
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
            { "help", no_argument, nullptr, 'h' },
            { "queue", no_argument, nullptr, 'q' },
            { "stack", no_argument, nullptr, 's' },
            { "output", required_argument, nullptr, 'o' },
            { nullptr, 0, nullptr, '\0' },
    };  // long_options[]

    while ((choice = getopt_long(argc, argv, "hqso:", long_options, &index)) != -1) {
        switch (choice) {
            case 'h':
                printHelp();
                exit(0);
            case 'q': {
                if (options.mode == Mode::none) {
                    options.mode = Mode::queue;
                } else {
                    cerr << "Multiple modes!" << std::endl;
                    exit(1);
                }
                break;
            }  // case 'q'
            case 's':
                if (options.mode == Mode::none) {
                    options.mode = Mode::stack;
                } else {
                    cerr << "Multiple modes!" << std::endl;
                    exit(1);
                }
                break;
            case 'o': {
                /* only 'list' or 'map' allowed */
                if (options.output != Output::none) exit(1);
                if (!strcmp(optarg, "map")) {
                    options.output = Output::map;
                } else if (!strcmp(optarg, "list")) {
                    options.output = Output::list;
                } else {
                    cerr << "Not map nor list as output!" << std::endl;
                    exit(1);
                }
                break;
            }   // case 'o'
            default:
                cerr << "Error: invalid option!" << std::endl;
                exit(1);
        }  // switch ..choice
    }  // while

    if (options.mode == Mode::none) {
        std::cerr << "No mode" << std::endl;
        exit(1);
        // options.mode = Mode::stack;  // if ..mode
    }
    if (options.output == Output::none) options.output = Output::map;

}  // getMode()


