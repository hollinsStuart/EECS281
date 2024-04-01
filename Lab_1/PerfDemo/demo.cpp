#include <iostream>

using namespace std;

const unsigned BIG = 0xFFFF;
const string MSG = "Hello world!";

void call10() {
    for (unsigned i = 0; i < BIG * 1; ++i) {
        cout << MSG << endl;
    }
}

void call20() {
    for (unsigned i = 0; i < BIG * 2; ++i) {
        cout << MSG << endl;
    }
}

void call30() {
    for (unsigned i = 0; i < BIG * 3; ++i) {
        cout << MSG << endl;
    }
}

void call40() {
    for (unsigned i = 0; i < BIG * 4; ++i) {
        cout << MSG << endl;
    }
}

void function1() {
    call20();
    call40();
}

void function2() {
    call10();
    call30();
}

int main() {
    function1();
    function2();
    return 0;
}

