// Testing file provided for EECS 281 Lab 7

#include "hashtable.h"
#include <string>
#include <iostream>
#include "eecs281-lab07-verifier/ActualVerifier.hpp"
#include <string_view>

static constexpr auto key = typename ActualVerifier<int, int>::Key::NamedParam {};
static constexpr auto value = typename ActualVerifier<int, int>::Value::NamedParam {};
static constexpr auto size = typename ActualVerifier<int, int>::Size::NamedParam {};
static constexpr auto success = typename ActualVerifier<int, int>::Success::NamedParam {};
static constexpr auto probeSequence = typename ActualVerifier<int, int>::ProbeSequence::NamedParam {};

using std::endl, std::cout, std::string;

template<class T>
class MyHash {
public:
    MyHash() = default;
    int operator()(const string& s) {
        return 9;
    };
};

void test1() {
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
    std::cout << "erase: " << midterm.erase("sam") << endl;
    midterm.printAll();
    std::cout << midterm.size() << std::endl;
    midterm.printAll();
    midterm.insert("ffee", 10);
    midterm.insert("mfilo", 43);
    midterm.insert("gggabe", 56);
    std::cout << midterm.insert(s, 50) << " ";
    midterm.printAll();
}

void test2() {
    HashTable<string, int> midterm;
    midterm.printAll();
    midterm.insert("fee", 100);
    midterm.printAll();
    midterm.erase("fee");
    midterm.printAll();
    midterm.insert("fee", 10);
    midterm.printAll();
}

void test3() {
    HashTable<string, int, MyHash<string>> midterm;
    midterm.printAll();
    midterm.insert("fee", 100);
    midterm.printAll();
    midterm["l"];
    midterm.insert("l", 100);
    midterm.printAll();
    midterm.erase("fee");
    midterm["fee"];
    midterm.printAll();
}

void test_insert(){
    HashTable<string, int, MyHash<string>> hashTable;
    hashTable.insert("a", 1);
    cout << hashTable.insert("a", 1) << endl;
    hashTable.insert("b", 2);
    hashTable["c"];
    hashTable["d"];
    cout << "e: " << hashTable["e"] << endl;
    hashTable.erase("e");
    hashTable.insert("e", 5);
    hashTable.printAll();
}

void testSearch() {
    HashTable<string, int, MyHash<string>> hashTable;
    cout << "insert a: " << endl;
    hashTable.insert("a", 1);
    cout << endl;
    hashTable.printAll();
    hashTable.insert("a", 1);

    cout << hashTable["a"] << endl;
    hashTable.erase("a");
    cout << hashTable["c"] << endl;
//    cout << "insert c: " << endl;
//    cout << "c inserted" << endl;
//    hashTable["c"];
//
//    cout << endl;
//    cout << "erase e: " << endl;
//    hashTable.erase("e");
//    cout << endl;
//    hashTable.insert("e", 5);
//    cout << endl;
    hashTable.printAll();
    cout << hashTable["a"] << endl;
    hashTable.erase("a");
    hashTable.insert("a", 1);
    hashTable.insert("a", 11);
    hashTable.insert("c", 2);
    hashTable.printAll();
}

void testErase(){
    HashTable<string, int, MyHash<string>> hashTable;
    hashTable.insert("fa", 1);
    hashTable.insert("fb", 2);
    hashTable.insert("f2e", 12);
    hashTable.insert("f2c", 22);
    hashTable.insert("fad", 21);
    hashTable.insert("fbd", 22);
    hashTable.insert("f2fe", 11);
    hashTable.insert("f2fc", 21);
    hashTable.insert("darr", 1);
    hashTable.insert("dbrr", 2);
    hashTable.insert("d2er", 132);
    hashTable.insert("d2cr", 232);
    hashTable.insert("dadr", 231);
    hashTable.insert("dbdr", 232);
    hashTable.insert("d2fe", 121);
    hashTable.insert("d2fc", 221);
    hashTable.insert("fqa", 1);
    hashTable.insert("fqb", 2);
    hashTable.insert("fq2e", 12);
    hashTable.insert("fq2c", 22);
    hashTable.insert("fqad", 21);
    hashTable.insert("fqbd", 22);
    hashTable.insert("fq2fe", 1187);
    hashTable.insert("fq2fc", 2187);
    hashTable.insert("dqaeg", 156);
    hashTable.insert("dqbeg", 256);
    hashTable.insert("dq2eg", 132);
    hashTable.insert("dq2cg", 232);
    hashTable.insert("dqadg", 231);
    hashTable.insert("dqbdg", 232);
    hashTable.insert("dq2fe", 121);
    hashTable.insert("dq2fc", 221);
    hashTable.insert("fq2fe", 187);
    hashTable.insert("fq2fc", 287);
    hashTable.insert("dqaeg", 16);
    hashTable.insert("dqbeg", 26);
    hashTable.insert("dq2eg", 12);
    hashTable.insert("dq2cg", 22);
    hashTable.insert("dqadg", 21);
    hashTable.insert("dqbdg", 22);
    hashTable.insert("dq2fe", 11);
    hashTable.insert("dq2fc", 21);
    hashTable.printAll();
}

int main() {
    testErase();
    // VERY BASIC EXAMPLE (will likely not compile with default/empty hashtable.h file)

    // ADD MORE TESTS OF YOUR OWN
//    ActualVerifier<int, int, std::hash<int>> {.size= 0};
    return 0;
}
