// Project identifier: 292F24D17A4455C1B5133EDD8C7CEAA0C9570A98
// Created by fs200 on 2023/11/5.

#ifndef P3_PY_STRUCTS_H
#define P3_PY_STRUCTS_H

#include <iostream>
using std::cout, std::cin, std::cerr, std::endl, std::getline;
#include <string>
using std::string;
#include <sstream>
using std::stringstream;
#include <cstdint>
#include <deque>
using std::deque;
#include <vector>
using std::vector;
#include <queue>
using std::priority_queue;
#include <unordered_map>
using std::unordered_map;
#include <algorithm>
using std::find;

/* convert precise time to int */
inline uint64_t transactionTime(const string& s) {
    stringstream ss(s);
    uint64_t ans = 0, temp;
    char c;
    ss >> temp >> c;
    ans += temp;
    ans *= 100ULL;
    ss >> temp >> c;
    ans += temp;
    ans *= 100ULL;
    ss >> temp >> c;
    ans += temp;
    ans *= 100ULL;
    ss >> temp >> c;
    ans += temp;
    ans *= 100ULL;
    ss >> temp >> c;
    ans += temp;
    ans *= 100ULL;
    ss >> temp;
    ans += temp;
    return ans;
}


class Transaction {
public:
    Transaction() = default;
    Transaction(uint64_t time, int ID): exeDate(time), ID(ID) {}
    ~Transaction() = default;

    /* str is the line with place */
    explicit Transaction(const string &str) {
        stringstream ss(str);
        string ts, et;
        char c;
        ss >> et >> ts >> IP >> sender >> recipient >> amount >> et >> c;
        timeStamp = transactionTime(ts);
        exeDate = transactionTime(et);
        if (c == 's') share = true;
        else share = false;
    }

    Transaction(const Transaction& t) = default;

    void print() const;

    uint64_t timeStamp{};
    string IP{};
    string sender;
    string recipient;
    uint32_t amount{};
    uint64_t exeDate{};
    uint32_t totalFee{0};
    int ID{-1};
    bool share{};     // true: share
};


class User {
public:
    User() = default;
    ~User() = default;

    explicit User(const string &str) {
        regTime = transactionTime(str.substr(0, 17));
        string rest = str.substr(18);
        size_t pos = rest.find('|');
        ID = rest.substr(0, pos);
        stringstream ss(rest.substr(pos+1));
        char c;
        ss >> PIN >> c >> balance;
    }

    void print() const;

    uint64_t regTime{};
    string ID;
    uint32_t PIN{};
    uint32_t balance{};
    unordered_map<string, char> validIP;
    vector<Transaction> inHistory;
    vector<Transaction> outHistory;
};


class CompareTransactionExe {
public:
    CompareTransactionExe() = default;
    ~CompareTransactionExe() = default;

    bool operator()(const Transaction& t1, const Transaction& t2) const {
        if (t1.exeDate == t2.exeDate) return t1.ID < t2.ID;
        return t1.exeDate < t2.exeDate;
    }

    bool operator()(const Transaction* t1, const Transaction* t2) const {
        if (t1->exeDate == t2->exeDate) return t1->ID < t2->ID;
        return t1->exeDate < t2->exeDate;
    }
};

class CompareTransactionExePQ {
public:
    CompareTransactionExePQ() = default;
    ~CompareTransactionExePQ() = default;

    bool operator()(const Transaction& t1, const Transaction& t2) const {
        if (t1.exeDate == t2.exeDate) return t1.ID > t2.ID;
        return t1.exeDate > t2.exeDate;
    }

    bool operator()(const Transaction* t1, const Transaction* t2) const {
        if (t1->exeDate == t2->exeDate) return t1->ID > t2->ID;
        return t1->exeDate > t2->exeDate;
    }
};


class Bank {
public:
    Bank() = default;
    ~Bank() = default;

    void printUsers();
    void printExecutedTransactions();
    void printAll();

    inline bool login(const string& ip, const string& id, uint32_t pin) {
        if (users.find(id) == users.end()) return false;    // no such user
        if (pin == users[id].PIN) {
            // add ip to the list
            users[id].validIP.insert({ip,ip[0]});
        } else {
            return false;
        }
        return true;
    }

    inline bool logout(const string& id, const string& ip) {
        if (users.find(id) == users.end()) return false;    // no such user
        if (users[id].validIP.find(ip) != users[id].validIP.end()) {
            // found
            users[id].validIP.erase(ip);
            return true;
        } else {
            // no such IP
            return false;
        }
    }

    inline bool checkTransaction(Transaction& t, bool verbose) {
        if ((t.timeStamp + 3000000ULL) < t.exeDate) {
            if (verbose) cout << "Select a time less than three days in the future.\n";
            return false;
        }
        auto senderIT = this->users.find(t.sender);
        auto recipientIT = this->users.find(t.recipient);
        if (senderIT == this->users.end()) {
            if (verbose) cout << "Sender " << t.sender << " does not exist.\n";
            return false;
        }
        if (recipientIT == this->users.end()) {
            if (verbose) cout << "Recipient " << t.recipient << " does not exist.\n";
            return false;
        }
        if ((users[t.sender].regTime > t.exeDate) || (users[t.recipient].regTime > t.exeDate)) {
            if (verbose) cout << "At the time of execution, sender and/or recipient have not registered.\n";
            return false;
        }
        if (users[t.sender].validIP.empty()) {
            if (verbose) cout << "Sender " << t.sender << " is not logged in.\n";
            return false;
        }
        if (users[t.sender].validIP.find(t.IP) == users[t.sender].validIP.end()) {
            if (verbose) cout << "Fraudulent transaction detected, aborting request.\n";
            return false;
        }
        t.ID = this->transactionID;
        ++this->transactionID;
        executeTransaction(t.timeStamp, verbose);
        this->placedTransactions.push(t);
        if (verbose) {
            cout << "Transaction placed at " << t.timeStamp << ": $" << t.amount << " from "
                 << t.sender << " to " << t.recipient << " at " << t.exeDate << ".\n";
        }
        return true;
    }

    /* Execute transactions until time */
    inline void executeTransaction(uint64_t time, bool verbose) {
        while (!this->placedTransactions.empty() && (this->placedTransactions.top().exeDate <= time)) {
            Transaction t = this->placedTransactions.top();
            this->placedTransactions.pop();
            uint32_t transFee = (t.amount <= 1000)? 10: ((t.amount >= 45000)? 450: t.amount / 100);
            if ((t.exeDate - this->users[t.sender].regTime) >= 50000000000ULL)
                transFee = (transFee * 3) / 4;
            t.totalFee = transFee;
            uint32_t recipientFee = t.share? (transFee/2): 0;
            uint32_t senderFee = transFee - recipientFee;
            if ((this->users[t.sender].balance < (senderFee+t.amount))
                    || this->users[t.recipient].balance < recipientFee) {
                if (verbose) cout << "Insufficient funds to process transaction " << t.ID << ".\n";
                continue;
            } else {
                /* execute successfully */
                this->users[t.sender].balance -= (senderFee + t.amount);
                this->users[t.recipient].balance += (t.amount - recipientFee);
                this->executedTransactions.push_back(t);
                this->users[t.sender].outHistory.push_back(t);
                this->users[t.recipient].inHistory.push_back(t);
                if (verbose)
                    cout << "Transaction executed at " << t.exeDate << ": $" << t.amount << " from "
                         << t.sender << " to " << t.recipient << ".\n";
            } // if executed successfully
        } // while
    } // executeTransaction

    inline void executeAll(bool verbose) {
        while (!this->placedTransactions.empty()) {
            Transaction t = this->placedTransactions.top();
            this->placedTransactions.pop();
            uint32_t transFee = (t.amount <= 1000)? 10: ((t.amount >= 45000)? 450: t.amount / 100);
            if ((t.exeDate - this->users[t.sender].regTime) >= 50000000000ULL)
                transFee = (transFee * 3) / 4;
            t.totalFee = transFee;
            uint32_t recipientFee = t.share? (transFee/2): 0, senderFee = transFee - recipientFee;
            if ((this->users[t.sender].balance < (senderFee+t.amount))
                    || this->users[t.recipient].balance < recipientFee) {
                if (verbose) cout << "Insufficient funds to process transaction " << t.ID << ".\n";
                continue;
            } else {
                /* execute successfully */
                this->users[t.sender].balance -= (senderFee + t.amount);
                this->users[t.recipient].balance += (t.amount - recipientFee);
                this->executedTransactions.push_back(t);
                this->users[t.sender].outHistory.push_back(t);
                this->users[t.recipient].inHistory.push_back(t);
                if (verbose)
                    cout << "Transaction executed at " << t.exeDate << ": $" << t.amount << " from "
                         << t.sender << " to " << t.recipient << ".\n";
            } // if executed successfully
        } // while pq isn't empty
    } // executeAll()

    unordered_map<string, User, std::hash<string>> users;
    priority_queue<Transaction, vector<Transaction>, CompareTransactionExePQ> placedTransactions;
    vector<Transaction> executedTransactions;

    int transactionID{0};

};
#endif //P3_PY_STRUCTS_H
