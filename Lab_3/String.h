#ifndef STRING_H
#define STRING_H

#include <cstring> /* strlen, strncmp */
#include <algorithm> /* std::max, std::min, std::swap */
// DO NOT #INCLUDE ANY OTHER LIBRARIES - YOU WILL LOSE POINTS

// Project Identifer: 5AE7C079A8BF493DDDB6EF76D42136D183D8D7A8

/**************************************************************************************************\
|    EECS 281 Lab 3: String Library                                                                |
|                                                                                                  |
|    During lab, you learned about C++ strings and how they work. In this coding exercise, you     |
|    will be implementing a select few functions from the C++ <string> library. If you do not      |
|    understand everything in this file, do not worry! You will only need to complete the          |
|    functions marked with a TODO, and we will provide you with all the information you need       |
|    to complete this assignment. To locate the portions of this file you need to complete,        |
|    simply find all the TODOs in this file (but feel free to explore the rest, if you wish).      |
|                                                                                                  |
\**************************************************************************************************/

// This lab assignment was written by Jake Hage and Andrew Zhou for Winter 2019 and simplified for
// Fall 2019. For instructions on how to implement this lab, please see the lab assignment.

// You should write your code in the "String.cpp" file (this is just the interface).
// You do NOT need to modify this file!

extern size_t npos;
extern char a_null_byte;

// A simple class for error exceptions - msg points to a C-string error message.
struct Error {
    explicit Error(const char* msg_ = "") : msg(msg_) { }
    const char* const msg;
};

// Simple exception class for reporting String errors.
struct String_exception {
    explicit String_exception(const char* msg_) : msg(msg_) { }
    const char* msg;
};

class String {
public:
    // Default initialization is to contain an empty string with no allocation.
    // If a non-empty C-string is supplied, this String gets minimum allocation.
    String(const char* cstr_ = "");
    // The copy constructor initializes this String with the original's data,
    // and gets minimum allocation.
    String(const String& original);
    // Move constructor - take original's data, and set the original String
    // member variables to the empty state (do not initialize "this" String and swap).
    String(String&& original) noexcept;
    // Deallocate C-string memory.
    ~String() noexcept;

    // Move assignment - simply swaps contents with rhs without any copying.
    String& operator=(String&& rhs) noexcept;

    /* Swap the contents of this String with another one.
    The member variable values are interchanged, along with the
    pointers to the allocated C-strings, but the two C-strings
    are neither copied nor modified. No memory allocation/deallocation is done. */
    void swap(String& other) noexcept;

    // Assignment operators
    // Left-hand side gets a copy of rhs data and gets minimum allocation.
    // This operator use the copy-swap idiom for assignment.
    String& operator=(const String& rhs);
    // This operator creates a temporary String object from the rhs C-string, and swaps the contents.
    String& operator=(const char* rhs);

    // Return a reference to character i in the string.
    char& operator[](size_t i);
    const char& operator[](size_t i) const;	// const version for const Strings

    // Accessors
    // Return a pointer to the internal C-string.
    const char* c_str() const;
    // Return size (length) of internal C-string in this String.
    size_t size() const;
    // Return current allocation for this String.
    int get_allocation() const;

    /* These functions find the first and last characters of a String object. */
    char& front();
    char& back();

    // Return a String starting with i and extending for len characters
    // The substring must be contained within the string.
    // If both i = size and len = 0, the input is valid and the result is an empty string.
    // Throw exception if the input is invalid.
    String substr(size_t pos, size_t len = npos) const;

    // Modifiers
    // Set to an empty string with minimum allocation by create/swap with an empty string.
    void clear();

    // Remove the len characters starting at i; allocation is unchanged.
    // The removed characters must be contained within the String.
    // Valid values for i and len are the same as for substring.
    String& erase(size_t pos, size_t len = npos);

    // Insert the supplied source String before character i of this String,
    // pushing the rest of the contents back, reallocating as needed.
    // If i == size, the inserted string is added to the end of this String.
    // This function does not create any temporary String objects.
    // It either directly inserts the new data into this String's space if it is big enough,
    // or allocates new space and copies in the old data with the new data inserted.
    // This String retains the final allocation.
    // The behavior of inserting a String into itself is not specified.
    String& insert(size_t pos, const String& str);

    // Replaces the portion of this string that begins at character i and spans
    // len characters by new contents.
    String& replace(size_t pos, size_t len, const String& str);

    // These functions all find a particular string or character(s) within this String object. */
    size_t find(const String& str, size_t pos = 0);
    size_t find_first_of(const String& str, size_t pos = 0);
    size_t find_last_of(const String& str, size_t pos = npos);

    // These concatenation operators add the rhs string data to the lhs object.
    // They do not create any temporary String objects. They either directly copy the rhs data
    // into the lhs space if it is big enough to hold the rhs, or allocate new space
    // and copy the old lhs data into it followed by the rhs data. The lhs object retains the
    // final memory allocation. If the rhs is a null byte or an empty C-string or String,
    // no change is made to lhs String.
    String& operator+=(char rhs);
    String& operator+=(const char* rhs);
    String& operator+=(const String& rhs);

    // Monitoring functions - not part of a normal implementation
    // used here for demonstration and testing purposes.

    // Returns the total number of Strings in existence.
    static int get_number() { return number; }

    // Returns total bytes allocated for all Strings in existence.
    static int get_total_allocation() { return total_allocation; }

    // Call with true to cause ctor, assignment, and dtor messages to be output.
    // These messages are output from each function before it does anything else.
    static void set_messages_wanted(bool messages_wanted_) { messages_wanted = messages_wanted_; }

private:
    // Variables for monitoring functions, not part of a normal implementation.
    // But used here for demonstration and testing purposes.
    static int number;                   // counts number of String objects in existence
    static int total_allocation;         // counts total amount of memory allocated
    static bool messages_wanted;         // whether to output constructor/destructor/operator= messages, initially false

    // Helper for modifiers; call grow_allocation() for the requested amount if need be.
    void check_allocation(int amount);

    // Grow the capacity of the cstr by amount.
    void grow_allocation(int amount);

    // Allocates a C-string, constructed on the range from begin to end of C-string str.
    char* allocate_string(const char* str, size_t begin, size_t len) const;

    char* cstr;                      // pointer to internal C-string
    size_t sz;                       // size of internal C-string
    int allocation;                  // amount of memory allocated to C-string
};

#endif /* STRING_H */
