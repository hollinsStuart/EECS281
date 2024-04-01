#include "String.h"

/*************************************************************\
| DO NOT #INCLUDE ANY OTHER LIBRARIES - YOU WILL LOSE POINTS  |
|                                                             |
\*************************************************************/

// Project Identifier: 5AE7C079A8BF493DDDB6EF76D42136D183D8D7A8

/**************************************************************************************************\
|    EECS 281 Lab 3: String Library                                                                |
|                                                                                                  |
|    During lab, you learned about C++ strings and how they work. In this coding exercise, you     |
|    will be implementing a select few functions from the C++ <string> library. If you do not      |
|    understand everything in this file, do not worry! You will only need to complete the          |
|    functions marked with a TODO, and we will provide you with all the information you need       |
|    to complete this assignment. To locate the portions of this file you need to complete,        |
|    simply find all 8 TODOs in this file (but feel free to explore the rest, if you wish).        |
|                                                                                                  |
\**************************************************************************************************/

int String::number = 0;
int String::total_allocation = 0;
bool String::messages_wanted = false;

// Default initialization is to contain an empty string with no allocation.
// If a non-empty C-string is supplied, this String gets minimum allocation.
String::String(const char* cstr_)
    : cstr{ &a_null_byte }, sz{ 0 }, allocation{ 0 } {
    if (cstr_ && *cstr_ != a_null_byte) {
        cstr = allocate_string(cstr_, 0, strlen(cstr_));
        sz = strlen(cstr);
        allocation = static_cast<int>(sz + 1);
        total_allocation += allocation;
    }
    ++number;
}

// The copy constructor initializes this String with the original's data,
// and gets minimum allocation.
String::String(const String& original)
    : cstr{ allocate_string(original.cstr, 0, original.sz) }, sz{ original.sz },
      allocation{ static_cast<int>(original.sz + 1) } {
    if (!original.sz) {
        allocation = 0;
    }
    total_allocation += allocation;
    ++number;
}

// The move constructor takes original's data and sets the original String
// member variables to the empty state (do not initialize "this" String and swap).
String::String(String&& original) noexcept
    : cstr{ original.cstr }, sz{ original.sz }, allocation{ original.allocation } {
    original.cstr = &a_null_byte;
    original.sz = 0;
    original.allocation = 0;
    ++number;
}

// The destructor deallocates C-string memory.
String::~String() noexcept {
    if (allocation) {
        delete[] cstr;
        cstr = nullptr;
    }
    total_allocation -= allocation;
    sz = 0;
    allocation = 0;
    --number;
}

// The move assignment operator simply swaps the contents of rhs without any copying.
String& String::operator=(String&& rhs) noexcept {
    swap(rhs);
    return *this;
}

// The swap() function swaps the contents of a String with another String.
void String::swap(String& other) noexcept {
    std::swap(cstr, other.cstr);
    std::swap(sz, other.sz);
    std::swap(allocation, other.allocation);
}

// This assignment operator assigns the left-hand side with a copy of the String rhs.
// The implementation uses copy-swap.
String& String::operator=(const String& rhs) {
    String temp{ rhs };
    swap(temp);
    return *this;
}

// This assignment operator creates a temporary String object from the rhs C-string and
// swaps the contents using copy-swap.
String& String::operator=(const char* rhs) {
    String temp{ rhs };
    swap(temp);
    return *this;
}

// The subscript operator for String objects can be used to retrieve a reference to a
// character at index i of the string.
char& String::operator[](size_t i) {
    if (i >= sz) {
        throw String_exception("Subscript out of range");
    }
    return cstr[i];
}

// This implementation is the same as above, but it works on const String objects.
const char& String::operator[](size_t i) const {
    if (i >= sz) {
        throw String_exception("Subscript out of range");
    }
    return cstr[i];
}

// The c_str() function returns a pointer to the internal C-string object that stores
// the current contents of the String object.
const char* String::c_str() const { 
    return cstr; 
}

// The size() function returns the length of the String object.
size_t String::size() const {
    return sz;
}

int String::get_allocation() const {
    return allocation;
}

// front() for String Objects
// This function returns a reference to the first character of the String. You may assume that this
// function will NEVER be called on empty strings.
char& String::front() {
    return *cstr;
}

// back() for String Objects
// This function returns a reference to the last character of the String. You may assume that this
// function will NEVER be called on empty strings.
char& String::back() {
    return *(cstr + sz - 1);
}

// substr() for String Objects
// When substr() is called using two parameters, "pos" and "len", this function returns a newly
// constructed String object with its value initialized to a copy of a substring of the original
// String object, where this substring starts at the character position represented by "pos" and
// spans "len" characters, or until the end of the string, whichever comes first.
//
// This function uses the allocate_string(const char* str, int begin, int len) function
// which returns a char* object that spans a certain length starting from a given position. 
// For example:
//     If char *myCstr represents a C-string with a value {'e', 'e', 'c', 's', '2', '8', '1', '\0'},
//     calling char *newCstr = allocate_string(myCstr, 2, 3) would set newCstr to {'c', 's', '2', '\0'}.
// Then a String object is created by using the constructor defined on line 203.
// allocate_string() uses dynamic memory (calling new), so delete must be called on the C-string
// You may assume that the starting position "pos" < sz, and "len" will be at least 0.
//
// The "len" parameter is optional - if not defined, the "len" is set to a value of String::npos, and the
// substring is built to the very end of the String.
String String::substr(size_t pos, size_t len) const {
    // If the position exceeds the string's size, throw an out of bounds exception.
    if (pos > sz) {
        throw String_exception("Substring bounds invalid");
    }  // if ..pos
    // Allocate a string that starts at position pos and spans len characters.
    char* newCstr = allocate_string(cstr, pos, std::min(len, sz - pos));
    // Use the String constuctor to build a String object from the newCstr.
    String temp(newCstr);
    // Delete the newCstr (since allocate_string uses dynamic memory).
    delete[] newCstr;

    // Return the String object that was created.
    return temp;
}  // substr()

// The clear() function clears the contents of a String object.
void String::clear() {
    String s;
    swap(s);
}  // clear()

// ============================================== TODO #1 ============================================== //

// TODO #1: Implement erase() for String Objects 
// When erase() is called using two parameters, "pos" and "len", this function erases the portion of the
// String object that begins at index "pos" that spans "len" characters (or until the end of the String,
// whichever comes first). If "len" is not defined, the String is erased from "pos" to the end of the String.
// A reference to the modified String object is returned.
//
// You may assume that the starting position "pos" will be valid, and "len" will be >= 0.
//
// HINTS: Start with two pointers or indices, one that begins at the position to begin erasing, and one that 
// begins at the character "len" distance away from "pos" (the first character after "pos" that won't be erased). 
// Make sure to end the new string with the sentinel (null character), which can be assigned using the member 
// variable "a_null_byte" (e.g. *ptr = a_null_byte). Don't forget to update the size of the string, "sz".
String& String::erase(size_t pos, size_t len) {
    // ERROR CHECKING: YOU DO NOT NEED TO WORRY ABOUT THIS FOR THIS LAB
    if (pos > sz)
        throw String_exception("Erase bounds invalid");

    // TODO: Implement erase() below.
    if(len==npos||pos+len>this->sz){
        len=sz-pos;
    }
    char *ptr=&cstr[pos];
    char *end=&cstr[pos+len];

    while(*end!=a_null_byte){
        *ptr++=*end++;
    }

    *ptr=a_null_byte;

    this->sz=ptr - this->cstr;

    return *this;
}  // erase()

// ============================================ END TODO #1 ============================================ //

// ============================================== TODO #2 ============================================== //

// TODO #2: Implement insert() for String Objects
// When insert() is called using two parameters, "pos" and "str", this function inserts the contents of
// "str" BEFORE the character indicated by "pos".
//
// You may assume that the starting position "pos" will be valid.
//
// HINTS: recall how an array works when you try to insert an element - all other elements after the insertion 
// point must be shifted. This is true here as well. First, you must shift all characters after the insertion 
// point by a certain distance. Then, you would insert the contents of the new String into the slots you have 
// freed up for insertion. Make sure you add '\0' to the end of the string after inserting, and "sz" is updated.
String& String::insert(size_t pos, const String& str) {
    // ERROR CHECKING: YOU DO NOT NEED TO WORRY ABOUT THIS FOR THIS LAB
    if (pos > sz)
        throw String_exception("Insertion point out of range");

    // Make sure there is enough space to store the new string - don't worry about this.
    check_allocation(int(sz + str.sz + 1));

    // TODO: Implement insert() below.
    size_t new_size=this->sz+str.sz;
    for(size_t i = new_size; i >= pos + str.sz; i--) {
        cstr[i] = cstr[i - str.sz];
    }
    String tempStr = str;
    for(size_t i = 0; i < tempStr.sz; ++i) {
        cstr[pos + i] = tempStr.cstr[i];
    }
    sz = new_size;
    cstr[new_size] = a_null_byte;
    return *this;
}  // insert()

// ============================================ END TODO #2 ============================================ //

// ============================================== TODO #3 ============================================== //

// TODO #3: Implement replace() for String Objects
// When replace() is called using three parameters, "pos", "len", and "str", this function replaces the
// portion of the String that begins at character "pos" and spans "len" characters with the contents of
// the String object "str".
//
// You may assume that the starting position "pos" will be valid, and "len" will be >= 0.
// If the value of "len" exceeds the end of the String object, replace as many characters as possible.
// A value of String::npos indicates that all characters to the end of the String should be replaced.
//
// HINT: You may make use other functions in this library to write a short solution.
String& String::replace(size_t pos, size_t len, const String& str) {
    // ERROR CHECKING: YOU DO NOT NEED TO WORRY ABOUT THIS FOR THIS LAB
    if (pos > sz)
        throw String_exception("Replace bounds invalid");

    // Make sure there is enough space to store the new string - don't worry about this.
    if ((pos + len) > sz)
        len = sz - pos;
    if (len < str.sz)
        check_allocation(int(sz - len + str.sz + 1));

    // TODO: Implement replace() below.
    if(str.sz==0){
        this->erase(pos,len);
        return *this;
    }
    String tempStr = str;
    this->erase(pos, len);
    this->insert(pos, tempStr);
    return *this;
}  // replace()

// ============================================ END TODO #3 ============================================ //

// The find() function has been provided for you.
// When find() is called using two parameters, "str" and "pos", this function
// searches for the first occurrence of "str" starting at position "pos" of the
// String. Characters before position "pos" are ignored. The entire sequence of
// characters of "str" must match for find() to be successful. If such a
// sequence is found, find() returns a size_t that represents the position of
// the first character of the first match. If "pos" is not specified, the search
// begins at position 0.
//
// If find() fails to find "str" in the String, the function returns npos. If
// "pos" exceeds the length of the string, the function will never find a match.
size_t String::find(const String& str, size_t pos) {
    if (pos + str.sz > sz)
        return npos;
    else {
        // loop through the string
        for (size_t i = pos; i <= sz - str.sz; ++i) {
            // if str matches a substring of cstr, return the index of the match
            if (strncmp(cstr + i, str.cstr, str.sz) == 0) { 
                return i; 
            }  // if
        }  // for ..i
        // otherwise, str was not found, so return npos
        return npos;
    }  // if
}  // find()

// ============================================== TODO #4 ============================================== //

// TODO #4: Implement find_first_of() for String Objects
// When find_first_of() is called using two parameters, "str" and "pos", this function searches the
// String for the first character that matches ANY of the characters in "str", starting at position
// "pos" of the String. Characters before position "pos" are ignored. It is enough for one single
// character of the sequence to match for the search to be successful. If a match is found, the
// function returns a size_t that represents the position of the first character that matches.
// Otherwise, the function returns npos. If "pos" exceeds the length of the string, the function
// will never find a match. If "pos" is not specified, the value of "pos" is assumed to be 0.
//
// HINTS: This is similar to the find() operation, but you will only need ONE character match for
// a search to succeed (and not the entire String "str") - a double for loop is okay here.
size_t String::find_first_of(const String& str, size_t pos) {
    // TODO: Implement find_first_of() below.
    if(pos==npos){
        pos=0;
    }
    if(pos>this->sz){
        return npos;
    }
    for(size_t i=pos;i<this->sz;i++){
        for(size_t j=0;j<str.sz;j++){
            if(cstr[i]==str[j]){
                return i;
            }
        }
    }
    return npos;
}  // find_first_of()

// ============================================ END TODO #4 ============================================ //

// ============================================== TODO #5 ============================================== //

// TODO #5: Implement find_last_of() for String Objects
// When find_last_of() is called using two parameters, "str" and "pos", this function searches the
// String for the last character that matches ANY of the characters in "str", starting at position
// "pos" of the String (and moving toward 0). Characters after position "pos" are ignored. It is
// enough for one single character of the sequence to match for the search to be successful. If a
// match is found, the function returns a size_t that represents the position of the last character
// that matches. Otherwise, the function returns npos. If "pos" exceeds the length of the string,
// the entire String is searched.
//
// HINTS: This is similar to the find_first_of function. Make sure you consider the case where "pos" 
// is larger than the size ("sz") of the String.
size_t String::find_last_of(const String& str, size_t pos) {
    // TODO: Implement find_last_of() below.
    if(pos>this->sz){
        pos=sz;
    }
    for(size_t i=pos;i>0;i--){
        for(size_t j=0;j<str.sz;j++){
            if(cstr[i]==str[j]){
                return i;
            }
        }
    }
    for(size_t j=0;j<str.sz;j++){
        if(cstr[0]==str[j]){
            return 0;
        }
    }
    return npos;
}  // find_last_of()

// ============================================ END TODO #5 ============================================ //

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ YOU MAY IGNORE EVERYTHING BELOW THIS LINE ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// The operator+= for characters appends the character "rhs" to a String and
// returns a reference to the modified String.
String& String::operator+=(char rhs) {
    check_allocation(static_cast<int>(sz + 1 + 1));
    cstr[sz] = rhs;
    cstr[++sz] = a_null_byte;
    return *this;
}

// The operator+= for C-strings appends the C-string "rhs" to a String and
// returns a reference to the modified String.
String& String::operator+=(const char* rhs) {
    if (rhs && *rhs != a_null_byte) {
        char* temp = allocate_string(rhs, 0, sz + 1);
        bool self_assignment = false;
        if (cstr == rhs) self_assignment = true;
        check_allocation(int(sz + 1 + strlen(rhs)));
        if (self_assignment) {
            auto old_size = sz;
            for (size_t i = 0; i < old_size; ++i) {
                operator+=(*(temp + i));
            }
        }
        else {
            while (*rhs) {
                operator+=(*rhs++);
            }
        }
        delete[] temp;
    }
    return *this;
}

// The operator+= for String Objects - used to append another String object
String& String::operator+=(const String& rhs) {
    if (rhs.size() > 0) {
        operator+=(rhs.c_str());
    }
    return *this;
}

// Helper for modifiers; call grow_allocation for the requested amount if need be.
void String::check_allocation(int amount) {
    if (allocation < amount) {
        grow_allocation(amount);
    }
}

// Grow the capacity of this cstr by amount.
void String::grow_allocation(int amount) {
    total_allocation += (2 * amount) - allocation;
    allocation = 2 * amount;
    char* doubled_alloc = new char[static_cast<size_t>(allocation)];
    strcpy(doubled_alloc, cstr);
    if (cstr && *cstr != a_null_byte) {
        delete[] cstr;
        cstr = nullptr;
    }
    std::swap(doubled_alloc, cstr);
}

// Allocates a C-string, constructed on the range from begin to end of C-string str.
char* String::allocate_string(const char* str, size_t begin, size_t len) const {
    char* alloc_str = new char[len + 1];
    memcpy(alloc_str, str + begin, len);
    alloc_str[len] = a_null_byte;
    return alloc_str;
}

// Compare lhs and rhs strings; constructor will convert a C-string literal to a String.
// Comparison is based on std::strcmp result compared to 0
bool operator==(const String& lhs, const String& rhs) {
    return !strcmp(lhs.c_str(), rhs.c_str());
}

bool operator!=(const String& lhs, const String& rhs) {
    return strcmp(lhs.c_str(), rhs.c_str());
}

bool operator<(const String& lhs, const String& rhs) {
    return strcmp(lhs.c_str(), rhs.c_str()) < 0;
}

bool operator>(const String& lhs, const String& rhs) {
    return strcmp(lhs.c_str(), rhs.c_str()) > 0;
}

/* Concatenate a String with another String.
If one of the arguments is a C-string, the String constructor will automatically create
a temporary String for it to match this function (inefficient, but instructive).
This automatic behavior would be disabled if the String constructor was declared "explicit".
This function constructs a copy of the lhs in a local String variable,
then concatenates the rhs to it with operator +=, and returns it. */
String operator+(const String& lhs, const String& rhs) {
    String temp{ lhs };
    temp += rhs;
    return temp;
}
