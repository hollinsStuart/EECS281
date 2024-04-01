// Project Identifier: CD7E23DEB13C1B8840F765F9016C084FD5D3F130

/*
 
    Lab 01 is (hopefully) an easy way to get familiar with some of the
    tools used in this class; the autograder, makefile, and get_opt.
    
    get_opt is a function in the C libraries that processes options
    input on the command line at runtime. For example, a program
    might be compiled and run like so:
    
        g++ main.cpp --std=c++17 -o main
        ./main
    
    There was an argument provided to the g++ compiler: '--std=c++17'.
    The program recognizes the '--' string and identifies
    it as an argument.  Get_opt will essentially do this for you,
    all you need to do is make sure it knows what look for, and what to
    do if it finds something.  An example of how you might run a project
    in EECS 281 is as follows (using the makefile that we provide):
    
        make project1
        ./project1 --stack

    This brings the EECS 281 makefile to attention.  There are instructions
    in the makefile and we will go over it in class, but there are a few places
    that you need to edit with your program information.  The makefile will
    save you a lot of time when compiling your programs and submitting to the
    autograder.  In fact, it is required that you include a makefile with your
    autograder submissions.
 
*/

#include <vector>
#include <iostream>
#include <algorithm> // std::sort
#include <getopt.h>
#include <string>    // needed for VS
#include "sorting.h"





// ----------------------------------------------------------------------------
//                    MusicLibrary Declarations
// ----------------------------------------------------------------------------


class MusicLibrary {
    
public:
    
    // Read in the CSV music file through stdin.
    void read_data();

    // Read and process command line arguments.
    void get_options(int argc, char** argv);
    
    // Sort and print the data.
    void run();
    
    
private:
    
    // Holds all the song objects for the program.
    std::vector<Song> music;
    
    // The number of songs to print after sorting.
    int num_print = 2;

    // Signifies what we attribute we are sorting by.
    char policy = '\0';
};




// ----------------------------------------------------------------------------
//                               Driver
// ----------------------------------------------------------------------------




int main(int argc, char** argv) {
 
    try {
        // Instantiate a music library.
        MusicLibrary library;
        
        // Read and process the command line options.
        library.get_options(argc, argv);
        
        // Read in the provided file through stdin.
        library.read_data();
        
        // Sort the data with the provided policy and print
        // the first 'num_print' songs.
        library.run();
    }

    // Catch runtime_errors, print the message, and exit the
    // program with a non-zero status.
    catch (std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    // All done!
    return 0;
}





// ----------------------------------------------------------------------------
//                    MusicLibrary Definitions
// ----------------------------------------------------------------------------


/*

    This program can be run with five different command line options:

        [--print | -p] <num_print>
            Determines how many songs to print.

        [--name | -n]
            Sorts by song title

        [--artist | -a]
            Sorts by song artist

        [--listens | -l]
            Sorts by number of listens that a song has.

        [--help | -h]
            Displays a helpful message!  We wrote one for you,
            so feel free to take a look for additional clarification.

    These are the options you will be incorporating into get_options!
    The program could be run like so:

        ./project0 --print 3 --artist

    Equivallentaly,

        ./project0 -p 3 -a

*/


// Read and process command line options.
void MusicLibrary::get_options(int argc, char** argv) {
    int option_index = 0, option = 0;
    
    // Don't display getopt error messages about options
    opterr = false;

    /*

        TODO: Add the remaining elements into the longOpts array.

    */
    // use getopt to find command line options
    struct option longOpts[] = {{ "print", required_argument, nullptr, 'p' },
                                { "help", no_argument, nullptr, 'h' },
                                {"name", no_argument, nullptr, 'n'},
                                {"artist", no_argument, nullptr, 'a'},
                                {"listens", no_argument, nullptr, 'l'},
                                { nullptr, 0, nullptr, '\0' }};
    
    /*

        TODO: Add the remaining chars to the option string in
                the while loop conditional (currently contains "p:h").
                Options with required_argument (print) need a colon after the
                char, options with no_argument do not (help).

    */
    while ((option = getopt_long(argc, argv, "p:hnal", longOpts, &option_index)) != -1) {
        //std::cout << option << "\n";
        switch (option) {
            case 'p':
                num_print = std::atoi(optarg);
                break;
            case 'n':
                policy = 'n';
                break;
            case 'a':
                policy = 'a';
                break;
            case 'l':
                policy = 'l';
                break;

            /*

                TODO: Add the remaining cases and decide what to do when they occur.

            */               

            case 'h':
                std::cout << "This program reads a CSV file that contains song names,\n"
                          << "the artist who wrote them, and the number of plays each song\n"
                          <<  "has on Spotify.  It then outputs the number of songs specified\n"
                          <<  "in the command line arguments (the print option), which\n"
                          <<  "defaults to 2, sorted by the option specified (one of name,\n"
                          <<  "artist, or listens).\n"
                          <<  "Usage: \'./project0\n\t[--listens | -l]\n"
                          <<                      "\t[--name | -n]\n"
                          <<                      "\t[--artist | -a]\n"
                          <<                      "\t[--print | -p] <# of songs to print>\n"
                          <<                      "\t[--help | -h]\n"
                          <<                      "\t< <CSV Music File>\'" << std::endl;
                exit(0);
        }
    }
    
    // After all the options have been processed,
    // check to make sure a sorting policy has been selected.
    // If one has not been selected, we will default to
    // sorting by song title (name).
    if (!policy)
        policy = 'n';

    
    // If num_print is still 0, then we are just
    // wasting time sorting, so throw an error.
    if (!num_print)
        throw std::runtime_error("No print argument was provided!" 
        " This program will have no tangible results.  Exiting...");
}


/*

    An important concept in efficiency is portrayed in the next function,
    but it can be easy to miss.  std::vector::reserve(size_t new_capacity) 
    is a function that reserves the EXACT amount of memory necessary to 
    fit 'new_capacity' number of elements.  We will go over exactly why
    this is helpful in the first few weeks of class; for now just know
    that it is limiting wasted memory in our program, as well as cutting
    down on a non-trivial amount of time that would normally be lost
    growing the vector.  This is not important with a sample file with 
    six songs, but there are autograder tests with thousands of songs 
    that it will make a difference in.

    std::vector::reserve allocates the memory and increases the CAPACITY
    of the array, but not the SIZE of the array.  This means those objects
    don't actually exist yet, and a call to std::vector::size will portray that.
    To increase the size of the array and insert objects then, we will still
    use std::vector::push_back.  If one was to use std::vector::resize(size_t new_size) 
    instead, they would be increasing both the size as well as the capacity of
    the array, and there would be 'new_size' many default constructed elements
    in the array if the array was initially empty.

*/


// Read data into the program through stdin.
void MusicLibrary::read_data() {
    
    Song song;
    std::string plays;
    int num_songs = 0;


    // Read in the first number to find the number
    // of songs in the file.
    // Also consume the new line after the integer.
    std::cin >> num_songs >> std::ws;
    //std::cout << num_songs << std::endl;    //////////////
    // Reserve the exact amount of memory needed
    // to fit all the songs.
    music.reserve(size_t(num_songs));

    // Read to the end of the CSV file.
    while (std::getline(std::cin, song.name, ',')) {

        // Skip comments.
        if (song.name[0] == '#') {
            size_t pos = 0;

            // If there is a newline, we have consumed
            // part of a song, so adjust the string.
            if ((pos = song.name.find_last_of('\n')) != std::string::npos)
				// Need a +1 here to move past the \n
                song.name = song.name.substr(pos + 1);

            // Otherwise just grab the rest of the line.
            else {
                std::getline(std::cin, song.name);
                continue;
            }
        }
        
        // Get the rest of the line.
        std::getline(std::cin, song.artist, ',');
        std::cin >> song.plays >> std::ws;
        
        // Put the song into the music list.
        music.push_back(song);
    }

    // If we didn't read in any data, throw an error.
    if (!music.size())
        throw std::runtime_error("No data was read in! Refer to the help option to see program usage.");
}


// Sort and print the data.
void MusicLibrary::run() {

    // Determine our sorting policy and sort.
    if (policy == 'n') {
        std::sort(music.begin(), music.end(), Song::NameSort());
    } else if (policy == 'a') {
        std::sort(music.begin(), music.end(), Song::ArtistSort());
    } else if (policy == 'l') {
        std::sort(music.begin(), music.end(), Song::ListensSort());
    }

    /*

        TODO: Add the remaining sorting cases (sorting by artist and listens).

    */

    // Print out the first num_print songs with the
    // overloaded stream insertion operator.   
    for (int i = 0; i < num_print; ++i)
        std::cout << music[size_t(i)] << std::endl;
}




