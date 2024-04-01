// Project identifier: 9504853406CBAC39EE89AA3AD238AA12CA198043
// Created by fs200 on 2023/9/21.
//

#include "commandLine.h"
#include "Zombie.h"

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
            { "verbose", no_argument, nullptr, 'v' },
            { "statistics", required_argument, nullptr, 's' },
            { "median", no_argument, nullptr, 'm' },
            { "help", no_argument, nullptr, 'h' },
            { nullptr, 0, nullptr, '\0' },
    };  // long_options[]

    while ((choice = getopt_long(argc, argv, "vs:mh", long_options, &index)) != -1) {
        switch (choice) {
            case 'h':
                printHelp();
                exit(0);
            case 'v': {
                // verbose
                options.verbose = true;
                break;
            }  // case 'v'
            case 's':
                options.statistics = true;
                options.statistics_num = atoi(optarg);
                break;
            case 'm': {
                options.median = true;
                break;
            }   // case 'm'
            default:
                cerr << "Error: invalid option!" << std::endl;
                exit(1);
        }  // switch ..choice
    }  // while

}  // getMode()

void printList(const deque<Zombie>& list) {
    cout << "-------------Printlist-------------\n";
    for (const Zombie& z: list) {
        cout << "  Zombie: " << z.name << " (distance: "
             << z.distance << ", speed: "
             << z.speed << ", health: "
             << z.health << ", active: " << z.active << ")\n";
    }
}
