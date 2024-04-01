// Testing file provided for EECS 281 Lab 7

#include "badTable.h"
#include <string>
#include <iostream>
#include <string_view>

using std::endl, std::cout, std::string;

int main() {

    // VERY BASIC EXAMPLE (will likely not compile with default/empty hashtable.h file)
    HashTable<string, int> midterm;
    string s = "sam";
    const string & a = s;
    std::cout << midterm.insert(s, 50) << " ";
    std::cout << midterm.insert("fee", 100) << " ";
    std::cout << midterm.insert("milo", 95) << " ";
    std::cout << midterm.insert("gabe", 88) << " \n";
    std::cout << midterm["sam"] << " ";
    std::cout << midterm["fee"] << " ";
    std::cout << midterm["milo"] << " ";
    std::cout << midterm["gabe"] << " \n";
    std::cout << midterm.erase("sam") << " ";
    std::cout << midterm.size() << std::endl;
    std::cout << midterm["sam"] << "\n";

    // ADD MORE TESTS OF YOUR OWN
//    ActualVerifier<int, int, std::hash<int>> {.size= 0};

    return 0;
}
