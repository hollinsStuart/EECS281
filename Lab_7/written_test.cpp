//
// Created by fs200 on 2023/11/3.
//
#include <iostream>
#include <vector>
#include "replace_words.h"

using namespace std;

int main () {
    vector<string> prefix{"cat", "bat", "rat"};
    vector<string> Sentence{"the", "cattle", "was", "rattled", "by", "the", "battery"};
    vector<string> Output{"the", "cat", "was", "rat", "by", "the", "bat"};
    vector<string> pre2{"cat","cattl", "the", "catt", "th"};
    auto ans = replace_words(prefix, Sentence);
    for (const auto& item: ans) {
        cout << item << " ";
    }
    cout << endl;
    ans = replace_words(pre2, Sentence);
    for (const auto& item: ans) {
        cout << item << " ";
    }
    cout << endl;
    return 0;
}
