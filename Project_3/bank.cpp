// Project identifier: 292F24D17A4455C1B5133EDD8C7CEAA0C9570A98
// Created by fs200 on 2023/11/5.

#include <iostream>
using std::cout, std::cin, std::cerr, std::endl, std::getline;
#include <string>
using std::string, std::stringstream;
#include <cstdint>
#include <queue>
using std::priority_queue;
#include <deque>
using std::deque;
#include <algorithm>
using std::lower_bound, std::upper_bound;
#include <fstream>
using std::ifstream;
#include "Structs.h"
#include "commandLine.h"

inline void printFormattedTime(uint64_t);

int main(int argc, char* argv[]) {
    std::ios_base::sync_with_stdio(false);  // speed up I/O
    Options options;
    getMode(argc, argv, options);
    if (!options.haveFile) {
        cerr << "No file!" << endl;
        exit(1);
    }
    Bank bank;
    ifstream regFile;
    regFile.open(options.fileName);
    string tmpStr;

    while (regFile) {
        regFile >> tmpStr;
        User u(tmpStr);
        bank.users.insert({u.ID, u});
    } // read users
    regFile.close();

    /* -------------------- read commands -------------------- */
    tmpStr.clear();
    while(tmpStr != "$$$") {
        getline(cin, tmpStr);
        stringstream ss(tmpStr);
        if (tmpStr[0] == 'l') {
            /* login and check validity */
            string tempIP, user;
            uint32_t tempPIN;
            ss >> tempIP >> user >> tempPIN >> tempIP;
            bool loginSuccess = bank.login(tempIP, user, tempPIN);
            if (options.verbose) {
                if (loginSuccess) cout << "User " << user << " logged in.\n";
                else cout << "Failed to log in " << user << ".\n";
            }
        } else if (tmpStr[0] == 'o') {
            /* logout */
            string tempID, tempIP;
            ss >> tempID >> tempID >> tempIP;
            bool logoutSuccess = bank.logout(tempID, tempIP);
            if (options.verbose) {
                if (!logoutSuccess)
                    cout << "Failed to log out " << tempID << ".\n";
                else
                    cout << "User " << tempID << " logged out.\n";
            }
        } else if (tmpStr[0] == 'p') {
            /* place and check validity */
            Transaction t(tmpStr);
            bank.checkTransaction(t, options.verbose);
        } else if (tmpStr[0] == '$') { break; }
        else if (tmpStr[0] == '#') {/* comment */}
    }

    /* get rid of all remaining transactions */
    bank.executeAll(options.verbose);

    /* -------------------- query -------------------- */
    while(getline(cin, tmpStr)) {
        if (cin.fail()) break;
        stringstream ss(tmpStr.substr(2));  // ss contains everything but the first two chars
        switch (tmpStr[0]) {
            case 'l': {
                uint64_t start, end;
                string str1, str2;
                ss >> str1 >> str2;
                start = transactionTime(str1);
                end = transactionTime(str2);
                int transCnt = 0;
                Transaction transactionStart(start, -1);
                auto startIT = lower_bound(bank.executedTransactions.begin(),
                                           bank.executedTransactions.end(),
                                           transactionStart, CompareTransactionExe());
                for ( ;startIT != bank.executedTransactions.end(); ++startIT) {
                    if (startIT->exeDate >= start && startIT->exeDate < end) {
                        cout << startIT->ID << ": " << startIT->sender << " sent " << startIT->amount;
                        if (startIT->amount == 1) cout << " dollar ";
                        else cout << " dollars ";
                        cout << "to " << startIT->recipient << " at " << startIT->exeDate << ".\n";
                        ++transCnt;
                    }
                    if (startIT->exeDate >= end) break;
                }
                string be = (transCnt == 1) ? "was" : "were";
                string transactions = (transCnt == 1) ? " transaction " : " transactions ";
                cout << "There " << be << " " << transCnt << transactions << "that " << be
                     << " placed between time " << start << " to " << end << ".\n";
                break;
            }
            case 'r': {
                uint64_t start, end;
                uint32_t revenue = 0;
                string str1, str2;
                ss >> str1 >> str2;
                start = transactionTime(str1);
                end = transactionTime(str2);
                Transaction transactionStart(start, -1);
                auto startIT = lower_bound(bank.executedTransactions.begin(),
                                           bank.executedTransactions.end(),
                                           transactionStart, CompareTransactionExe());
                for ( ; startIT != bank.executedTransactions.end(); ++startIT) {
                    if (startIT->exeDate >= start && startIT->exeDate < end) {
                        revenue += startIT->totalFee;
                    }
                    if (startIT->exeDate >= end) break;
                }
                cout << "281Bank has collected " << revenue << " dollars in fees over";
                printFormattedTime(end - start);
                cout << ".\n";
                break;
            }
            case 'h': {
                string user;
                ss >> user;
                if (bank.users.find(user) == bank.users.end()) {
                    cout << "User " << user << " does not exist.\n";
                    break;
                }
                User &u = bank.users[user];
                cout << "Customer " << user << " account summary:\nBalance: $" << bank.users[user].balance
                        << "\nTotal # of transactions: " << (u.inHistory.size() + u.outHistory.size())
                        << "\nIncoming " << u.inHistory.size() << ":\n";
                size_t inBegin = u.inHistory.size() >= 10 ? u.inHistory.size() - 10: 0;
                size_t outBegin = u.outHistory.size() >= 10 ? u.outHistory.size() - 10: 0;
                for (size_t i = inBegin; i < u.inHistory.size(); ++i) {
                    string dollar = (u.inHistory[i].amount == 1) ? " dollar " : " dollars ";
                    cout << u.inHistory[i].ID << ": " << u.inHistory[i].sender << " sent " << u.inHistory[i].amount
                         << dollar << "to " << u.inHistory[i].recipient << " at "
                         << u.inHistory[i].exeDate << ".\n";
                }
                cout << "Outgoing " << u.outHistory.size() << ":\n";
                for (size_t i = outBegin; i < u.outHistory.size(); ++i) {
                    string dollar = (u.outHistory[i].amount == 1) ? " dollar " : " dollars ";
                    cout << u.outHistory[i].ID << ": " << u.outHistory[i].sender << " sent " << u.outHistory[i].amount
                         << dollar << "to " << u.outHistory[i].recipient << " at "
                         << u.outHistory[i].exeDate << ".\n";
                }
                break;
            }
            case 's': {
                uint64_t time = transactionTime(ss.str());
                time = (time / 1000000ULL) * 1000000ULL;
                cout << "Summary of [" << time << ", " << time + 1000000ULL << "):\n";
                uint32_t revenue = 0;
                int transNum = 0;
                Transaction transactionStart(time, -1);
                auto startIT = lower_bound(bank.executedTransactions.begin(),
                                           bank.executedTransactions.end(),
                                           transactionStart, CompareTransactionExe());
                for (; startIT != bank.executedTransactions.end(); ++startIT) {
                    if (startIT->exeDate >= time && startIT->exeDate < (time + 1000000ULL)) {
                        string dollar = startIT->amount == 1? " dollar ": " dollars ";
                        revenue += startIT->totalFee;
                        cout << startIT->ID << ": " << startIT->sender << " sent " << startIT->amount << dollar
                             << "to " << startIT->recipient << " at " << startIT->exeDate << ".\n";
                        ++transNum;
                    }
                    if (startIT->exeDate >= (time + 1000000ULL)) break;
                }
                string be = (transNum == 1) ? "was" : "were";
                string transactions = (transNum == 1) ? " transaction" : " transactions";
                cout << "There " << be << " a total of " << transNum << transactions
                     << ", 281Bank has collected " << revenue << " dollars in fees.\n";
                break;
            }
            default: {
                break;
            }
        }
    }
    return 0;
}

inline void printFormattedTime(uint64_t time) {
    uint64_t seconds, minutes, hours, days, months, years;
    years = time / 10000000000ULL;
    time -= years * 10000000000ULL;
    months = time / 100000000ULL;
    time -= months * 100000000ULL;
    days = time / 1000000ULL;
    time -= days * 1000000ULL;
    hours = time / 10000ULL;
    time -= hours * 10000ULL;
    minutes = time / 100ULL;
    time -= minutes * 100ULL;
    seconds = time;
    if (years == 1ULL)
        cout << " " << years << " year";
    else if (years != 0ULL)
        cout << " " << years << " years";

    if (months == 1ULL)
        cout << " " << months << " month";
    else if (months != 0ULL)
        cout << " " << months << " months";

    if (days == 1ULL)
        cout << " " << days << " day";
    else if (days != 0ULL)
        cout << " " << days << " days";

    if (hours == 1ULL)
        cout << " " << hours << " hour";
    else if (hours!=0ULL)
        cout << " " << hours << " hours";

    if (minutes == 1ULL)
        cout << " " << minutes << " minute";
    else if (minutes!=0ULL)
        cout << " " << minutes << " minutes";

    if (seconds == 1ULL)
        cout << " " << seconds << " second";
    else if (seconds!=0ULL)
        cout << " " << seconds << " seconds";
}

