// Project identifier: 9504853406CBAC39EE89AA3AD238AA12CA198043
// Created by fs200 on 2023/9/21.
//
#include <iostream>
using std::cout, std::endl, std::cerr, std::cin, std::endl;
#include <string>
using std::string;
#include <cstdint>
#include <queue>
using std::priority_queue;
#include <deque>
using std::deque;
#include <algorithm>
using std::sort;
using  std::nth_element;
#include "P2random.h"
#include "commandLine.h"    // to proceed command line arguments
#include "Zombie.h"
#include "Functors.h"

int main(int argc, char* argv[]) {
    std::ios_base::sync_with_stdio(false);  // speed up I/O

    Options options;
    getMode(argc, argv, options);

    deque<Zombie> zombieMasterList;
    deque<Zombie*> zombieKilled;
    Zombie killer, loser;       // the last zombie alive/killed
    priority_queue<Zombie*, vector<Zombie*>, zombieCompare> zombiePriorityList;
    priority_queue<Zombie*, vector<Zombie*>, zombieActiveLeft> deadZombiesLeft;
    priority_queue<Zombie*, vector<Zombie*>, zombieActiveRight> deadZombiesRight;
//    priority_queue<uint32_t, vector<uint32_t>, std::less<>> zombieActionLeft;       // for median calculation
//    priority_queue<uint32_t, vector<uint32_t>, std::greater<>> zombieActionRight;       // for median calculation
    uint32_t quiverCapacity, randomSeed, randDistance, randSpeed, randHealth;
    string junk;
    std::getline(cin, junk);    
    cin >> junk >> quiverCapacity >> junk >> randomSeed >> junk >> randDistance >> junk >>
            randSpeed >> junk >> randHealth >> junk;
    P2random::initialize(randomSeed, randDistance, randSpeed, randHealth);

    bool gameEnd = false;
    uint32_t currRound = 1, fileNextRound;
    cin >> junk >> fileNextRound;       // round: 1
    uint32_t thisRoundRand, thisRoundNamed;
    bool endOfFile = false;
    while(!gameEnd) {
        bool readThisRound = (currRound == fileNextRound);
        bool thisRoundKilledZombie = false;
        if (readThisRound) {
            cin >> junk >> thisRoundRand >> junk >> thisRoundNamed; // input line ends
        }
        /* -v output */
        if (options.verbose) {
            cout << "Round: " << currRound << "\n";
        }
        /* for zombie in list */
        for (Zombie &zombie: zombieMasterList) {
            if (zombie.health!=0) {
                /* update position */
                zombie.distance -= zombie.distance < zombie.speed ? zombie.distance : zombie.speed;
                ++zombie.active;
                /* -v output */
                if (options.verbose) {
                    cout << "Moved: " << zombie.name << " (distance: " <<  zombie.distance << ", speed: "
                         << zombie.speed << ", health: " << zombie.health << ")\n";
                }
                /* distance == 0 and output */
                if (zombie.distance == 0) {
                    gameEnd = true;
                    if (killer.name.empty()) killer.name = zombie.name;
                }
            }
        }
        /* player dead ? */
        if (!gameEnd) {
            if (readThisRound) {
                /* New zombies:
                *     1. Random
                *     2. Named
                *     3. -v output
                *  */
                for (uint32_t i = 0; i < thisRoundRand; ++i) {
                    // random zombies
                    string name = P2random::getNextZombieName();
                    uint32_t distance = P2random::getNextZombieDistance();
                    uint32_t speed = P2random::getNextZombieSpeed();
                    uint32_t health = P2random::getNextZombieHealth();
                    zombieMasterList.emplace_back(name, distance, speed, health);
                    zombiePriorityList.push(&zombieMasterList.back());
                    if (options.verbose) {
                        cout << "Created: " << zombieMasterList.back().name << " (distance: "
                             << zombieMasterList.back().distance << ", speed: "
                             << zombieMasterList.back().speed << ", health: "
                             << zombieMasterList.back().health << ")\n";
                    }
                }
                for (uint32_t i = 0; i < thisRoundNamed; ++i) {
                    string name;
                    uint32_t distance, speed, health;
                    cin >> name >> junk >> distance >> junk >> speed >> junk >> health;
                    zombieMasterList.emplace_back(name, distance, speed, health);
                    zombiePriorityList.push(&zombieMasterList.back());
                    if (options.verbose) {
                        cout << "Created: " << zombieMasterList.back().name << " (distance: "
                             << zombieMasterList.back().distance << ", speed: "
                             << zombieMasterList.back().speed << ", health: "
                             << zombieMasterList.back().health << ")\n";
                    }
                }
            } // read
            if (readThisRound) {
                cin >> junk >> junk >> fileNextRound;
                if (!cin ) endOfFile = true;
            }
            /* shoot zombies, by ETA */
            for (uint32_t arrowsUsed = 0; arrowsUsed < quiverCapacity;) {
                if (zombiePriorityList.empty()) {
                    break;
                }
                if (zombiePriorityList.top()->health <= quiverCapacity - arrowsUsed) {
                    // shoot it to death
                    arrowsUsed += zombiePriorityList.top()->health;
                    zombiePriorityList.top()->health = 0;
                    if (zombiePriorityList.size() == 1 && endOfFile) {
                        // last zombie
                        loser.name = zombiePriorityList.top()->name;
                    }
                    thisRoundKilledZombie = true;
                    zombieKilled.push_back(zombiePriorityList.top());
                    /* -v output */
                    if (options.verbose) {
                        cout << "Destroyed: " << zombiePriorityList.top()->name << " (distance: "
                             << zombiePriorityList.top()->distance << ", speed: "
                             << zombiePriorityList.top()->speed << ", health: "
                             << zombiePriorityList.top()->health << ")\n";
                    }
                    pushDeadZombie(zombiePriorityList, deadZombiesLeft, deadZombiesRight);
                } else {
                    // shoot as many as possible
                    zombiePriorityList.top()->health -= (quiverCapacity - arrowsUsed);
                    arrowsUsed = quiverCapacity;
                    break;
                }
            }
        }
        /* median output */
        if ((!deadZombiesLeft.empty()||thisRoundKilledZombie) && options.median && !gameEnd) {
            // At the end of round 1, the median zombie lifetime is 1
            if (deadZombiesLeft.size() == deadZombiesRight.size()) {
                cout << "At the end of round " << currRound << ", the median zombie lifetime is "
                     << (int)(deadZombiesLeft.top()->active + deadZombiesRight.top()->active)/2
                     << "\n";
            } else {
                cout << "At the end of round " << currRound << ", the median zombie lifetime is "
                     << deadZombiesLeft.top()->active
                     << "\n";
            }
        }
        /* endGame? */
        if (!gameEnd) {
            if (endOfFile && zombiePriorityList.empty()) {
                gameEnd = true;
            } else {
                ++currRound;
            }
        }
        if (!cin) endOfFile = true;
    }   // battle loop

    if (zombiePriorityList.empty()) {
        // VICTORY IN ROUND <ROUND_NUMBER>! <NAME_OF_LAST_ZOMBIE_KILLED> was the last zombie.
        cout << "VICTORY IN ROUND " << currRound << "! " << loser.name << " was the last zombie.\n";

    } else {
        // DEFEAT IN ROUND <ROUND_NUMBER>! <NAME_OF_KILLER_ZOMBIE> ate your brains!
        cout << "DEFEAT IN ROUND " << currRound << "! " << killer.name << " ate your brains!\n";
    }
//    printList(zombieMasterList);
    if (options.statistics) {
        // Zombies still active: <NUMBER_OF_ZOMBIES>
        cout << "Zombies still active: " << zombiePriorityList.size() << "\n";
        if (options.statistics_num > (uint32_t)zombieKilled.size()) {
            // not enough dead zombies
            cout << "First zombies killed:\n";
            for (uint32_t i = 0; i < (uint32_t)zombieKilled.size(); ++i) {
                cout << zombieKilled[i]->name << " " << i+1 << "\n";
            }
            cout << "Last zombies killed:\n";
            for (uint32_t i = 0; i < (uint32_t)zombieKilled.size(); ++i) {
                cout << zombieKilled[zombieKilled.size()-i-1]->name << " " << (uint32_t)zombieKilled.size() - i << "\n";
            }
        } else {
            cout << "First zombies killed:\n";
            for (uint32_t i = 0; i < options.statistics_num; ++i) {
                cout << zombieKilled[i]->name << " " << i+1 << "\n";
            }
            cout << "Last zombies killed:\n";
            for (uint32_t i = 0; i < options.statistics_num; ++i) {
                cout << zombieKilled[zombieKilled.size()-i-1]->name << " " << options.statistics_num - i << "\n";
            }
        }
        if (options.statistics_num > (uint32_t)zombieMasterList.size()) {
            // not enough zombies
            sort(zombieMasterList.begin(), zombieMasterList.end(), zombieActiveReversed());
            cout << "Most active zombies:\n";
            for (auto & i : zombieMasterList) {
                cout << i.name << " " << i.active << "\n";
            }
            sort(zombieMasterList.begin(), zombieMasterList.end(), zombieActive());
            cout << "Least active zombies:\n";
            for (auto & i : zombieMasterList) {
                cout << i.name << " " << i.active << "\n";
            }
        } else {
            // enough zombies
            nth_element(zombieMasterList.begin(), zombieMasterList.begin()+options.statistics_num,
                        zombieMasterList.end(), zombieActiveReversed());
            sort(zombieMasterList.begin(), zombieMasterList.begin()+options.statistics_num, zombieActiveReversed());
            cout << "Most active zombies:\n";
            for (uint32_t i = 0; i < (uint32_t)options.statistics_num; ++i) {
                cout << zombieMasterList[i].name << " "
                     << zombieMasterList[i].active << "\n";
            }
            nth_element(zombieMasterList.begin(), zombieMasterList.begin()+options.statistics_num,
                        zombieMasterList.end(), zombieActive());
            sort(zombieMasterList.begin(), zombieMasterList.begin()+options.statistics_num,
                 zombieActive());
            cout << "Least active zombies:\n";
            for (uint32_t i = 0; i < (uint32_t)options.statistics_num; ++i) {
                cout << zombieMasterList[i].name << " "
                     << zombieMasterList[i].active << "\n";
            }
        }

    }
    return 0;
}
