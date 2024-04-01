// Project Identifier: CD7E23DEB13C1B8840F765F9016C084FD5D3F130

/*

    A utility file containing a few functor declarations,
    the 'Song' data structure, and the overloaded stream insertion
    operator for 'Song'.

*/

// Represents a single song.
struct Song {
    std::string name, artist;
    unsigned int plays;

    class NameSort {
    public:
        bool operator()(const Song& one, const Song& two) {
            return one.name < two.name;
        }
    };

    class ArtistSort {
    public:
        bool operator()(const Song& one, const Song& two) {
            return one.artist < two.artist;
        }
    };

    // We want the most plays to be at the beginning of the vector,
    // so return greater than instead of less than (max heap).
    class ListensSort {
    public:
        bool operator()(const Song& one, const Song& two) {
            return one.plays > two.plays;
        }
    };
};



// Print a song.
std::ostream& operator<<(std::ostream& out, const Song& song) {
    return out << song.name << " by " << song.artist << " has " 
        << std::to_string(song.plays) << " plays.";
}