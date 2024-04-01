// Project identifier: 292F24D17A4455C1B5133EDD8C7CEAA0C9570A98
// Created by fs200 on 2023/11/5.

#include "Structs.h"

void Bank::printUsers() {
    cout << "Users:\n";
    for (const auto& item: users) {
        item.second.print();
    }
}

void Bank::printExecutedTransactions() {
    cout << "Transactions:\n";
    for (auto &item: this->executedTransactions) {
        item.print();
    }
}

void Bank::printAll() {
    printUsers();
    printExecutedTransactions();
}

void Transaction::print() const {
    cout << "\t" << timeStamp << "\t" << IP << "\t" << sender << "->" << recipient
        << "\t$" << amount << "\tExeDate: "<< exeDate << " ID: " << ID << " " << share << "\n\tfee:"
        << totalFee << endl;
}

void User::print() const {
    cout << "\t" << regTime << "\t" << ID << "\t" << PIN << "\t" << balance << "\t";
    cout << endl;
    cout << "\tIP:\t";
    for (const auto& item: validIP) {
        cout << item.first << "\t";
    }
    cout << endl;
}

