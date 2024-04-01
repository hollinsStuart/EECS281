#include "String.h"
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <limits>

/* 
*
*   Lab 3 - String Library Test File
*   Assignment Identifier: 5AE7C079A8BF493DDDB6EF76D42136D183D8D7A8
*
*   Do NOT submit this file to the AG. The test case used here is 
*   identical to the test cases run on the Autograder. The score you
*   see at the bottom of your output will be your score on the lab.
*
*/

#define STRING_BUFFER 32
#define STDIN_REQUEST "%31s"

// Use these to test individual operations all at once:
#define TEST_ERASE 72
#define TEST_INSERT 73
#define TEST_REPLACE 74
#define TEST_FFO 75
#define TEST_FLO 76
#define TEST_ALL 77

size_t npos = std::numeric_limits<size_t>::max();
char a_null_byte = '\0';

bool check_sol(String& act, String& exp) {
    if (strcmp(act.c_str(), exp.c_str())) {
        printf("FAILED - INCORRECT STRING PRODUCED\n");
        if (exp.size() == 0) {
            exp = "<empty string>";
        }
        printf("  EXPECTED STRING: %s\n", exp.c_str());
        printf("  OBTAINED STRING: %s\n", act.c_str());
        return false;
    }
    else if (act.size() != exp.size()) {
        printf("FAILED - INCORRECT STRING SIZE RETURNED\n");
        printf("  CURRENT STRING: %s\n", exp.c_str());
        printf("  EXPECTED SIZE %zu, BUT OBTAINED SIZE %zu\n", exp.size(), act.size());
        return false;
    }
    return true;
}

int main() {
    printf("BEGIN RUNNING LAB 3 TESTS ...\n");
    printf("ENTER A NUMBER BELOW TO BEGIN RUNNING TESTS:\n");
    printf("  -- ENTER 1-71 FOR INDIVIDUAL TESTS\n");
    printf("  -- ENTER 72 TO RUN ONLY ERASE TESTS\n");
    printf("  -- ENTER 73 TO RUN ONLY INSERT TESTS\n");
    printf("  -- ENTER 74 TO RUN ONLY REPLACE TESTS\n");
    printf("  -- ENTER 75 TO RUN ONLY FIND_FIRST_OF TESTS\n");
    printf("  -- ENTER 76 TO RUN ONLY FIND_LAST_OF TESTS\n");
    printf("  -- ENTER 77 TO RUN ALL TESTS\n");
    fflush(stdout);
    int test_number = 0;
    if (scanf("%d", &test_number) == EOF) {
        printf("Failed to read in string - this shouldn't be happening.\n");
        return 1;
    }
    if (test_number < 1 || test_number > 77) {
        printf("Invalid number entered. Please try again.\n");
        return 0;
    }
    int num_correct = 0;
    printf("====================================================================================");
    printf("\nBEGIN RUNNING LAB 3 TEST CASES\n");
    try {
        if (test_number == TEST_ERASE || test_number == TEST_ALL) {
            printf("====================================================================================\n");
            printf(" Running tests for string library erase ...\n");
        }
        // ERASE TEST 1
        if (test_number == 1 || test_number == TEST_ALL || test_number == TEST_ERASE) {
            printf("======================================== 01 ========================================");
            printf("\nRUNNING TEST ERASE 1 ...\n");
            printf("  ORIGINAL STRING: \"root/shared/user/config\"\n");
            printf("  OPERATION: erase(12, 5)\n");
            fflush(stdout);
            String act = "root/shared/user/config";
            act.erase(12, 5);
            String exp = "root/shared/config";
            bool success = check_sol(act, exp);
            if (success) {
                printf("  TEST ERASE 1 - SUCCESS\n");
                ++num_correct;
            }
        }
        // ERASE TEST 2
        if (test_number == 2 || test_number == TEST_ALL || test_number == TEST_ERASE) {
            printf("======================================== 02 ========================================");
            printf("\nRUNNING TEST ERASE 2 ...\n");
            printf("  ORIGINAL STRING: \"potato parrot\"\n");
            printf("  OPERATION: erase(12, 4)\n");
            fflush(stdout);
            String act = "potato parrot";
            act.erase(12, 4);
            String exp = "potato parro";
            bool success = check_sol(act, exp);
            if (success) {
                printf("  TEST ERASE 2 - SUCCESS\n");
                ++num_correct;
            }
        }
        // ERASE TEST 3
        if (test_number == 3 || test_number == TEST_ALL || test_number == TEST_ERASE) {
            printf("======================================== 03 ========================================");
            printf("\nRUNNING TEST ERASE 3 ...\n");
            printf("  ORIGINAL STRING: \"potato parro\"\n");
            printf("  OPERATION: erase(5, 1)\n");
            fflush(stdout);
            String act = "potato parro";
            act.erase(5, 1);
            String exp = "potat parro";
            bool success = check_sol(act, exp);
            if (success) {
                printf("  TEST ERASE 3 - SUCCESS\n");
                ++num_correct;
            }
        }
        // ERASE TEST 4
        if (test_number == 4 || test_number == TEST_ALL || test_number == TEST_ERASE) {
            printf("======================================== 04 ========================================");
            printf("\nRUNNING TEST ERASE 4 ...\n");
            printf("  ORIGINAL STRING: \"potat parro\"\n");
            printf("  OPERATION: erase(0, 1)\n");
            fflush(stdout);
            String act = "potat parro";
            act.erase(0, 1);
            String exp = "otat parro";
            bool success = check_sol(act, exp);
            if (success) {
                printf("  TEST ERASE 4 - SUCCESS\n");
                ++num_correct;
            }
        }
        // ERASE TEST 5
        if (test_number == 5 || test_number == TEST_ALL || test_number == TEST_ERASE) {
            printf("======================================== 05 ========================================");
            printf("\nRUNNING TEST ERASE 5 ...\n");
            printf("  ORIGINAL STRING: \"otat parro\"\n");
            printf("  OPERATION: erase(1, 22)\n");
            fflush(stdout);
            String act = "otat parro";
            act.erase(1, 22);
            String exp = "o";
            bool success = check_sol(act, exp);
            if (success) {
                printf("  TEST ERASE 5 - SUCCESS\n");
                ++num_correct;
            }
        }
        // ERASE TEST 6
        if (test_number == 6 || test_number == TEST_ALL || test_number == TEST_ERASE) {
            printf("======================================== 06 ========================================");
            printf("\nRUNNING TEST ERASE 6 ...\n");
            printf("  ORIGINAL STRING: \"0123456789\"\n");
            printf("  OPERATION: erase(0, 5)\n");
            fflush(stdout);
            String act = "0123456789";
            act.erase(0, 5);
            String exp = "56789";
            bool success = check_sol(act, exp);
            if (success) {
                printf("  TEST ERASE 6 - SUCCESS\n");
                ++num_correct;
            }
        }
        // ERASE TEST 7
        if (test_number == 7 || test_number == TEST_ALL || test_number == TEST_ERASE) {
            printf("======================================== 07 ========================================");
            printf("\nRUNNING TEST ERASE 7 ...\n");
            printf("  ORIGINAL STRING: \"0123456789\"\n");
            printf("  OPERATION: erase(9, 1)\n");
            fflush(stdout);
            String act = "0123456789";
            act.erase(9, 1);
            String exp = "012345678";
            bool success = check_sol(act, exp);
            if (success) {
                printf("  TEST ERASE 7 - SUCCESS\n");
                ++num_correct;
            }
        }
        // ERASE TEST 8
        if (test_number == 8 || test_number == TEST_ALL || test_number == TEST_ERASE) {
            printf("======================================== 08 ========================================");
            printf("\nRUNNING TEST ERASE 8 ...\n");
            printf("  ORIGINAL STRING: \"eecs 281 is fun\"\n");
            printf("  OPERATION: erase(13)\n");
            fflush(stdout);
            String act = "eecs 281 is fun";
            act.erase(13);
            String exp = "eecs 281 is f";
            bool success = check_sol(act, exp);
            if (success) {
                printf("  TEST ERASE 8 - SUCCESS\n");
                ++num_correct;
            }
        }
        // ERASE TEST 9
        if (test_number == 9 || test_number == TEST_ALL || test_number == TEST_ERASE) {
            printf("======================================== 09 ========================================");
            printf("\nRUNNING TEST ERASE 9 ...\n");
            printf("  ORIGINAL STRING: \"thisisalongstring\"\n");
            printf("  OPERATION: erase(7, 4) then erase(12, 2)\n");
            fflush(stdout);
            String act = "thisisalongstring";
            act.erase(7, 4);
            act.erase(12, 2);
            String exp = "thisisastrin";
            bool success = check_sol(act, exp);
            if (success) {
                printf("  TEST ERASE 9 - SUCCESS\n");
                ++num_correct;
            }
        }
        // ERASE TEST 10
        if (test_number == 10 || test_number == TEST_ALL || test_number == TEST_ERASE) {
            printf("======================================== 10 ========================================");
            printf("\nRUNNING TEST ERASE 10 ...\n");
            printf("  ORIGINAL STRING: \"emptystuff\"\n");
            printf("  OPERATION: erase(5, 5) then erase(0, 5)\n");
            fflush(stdout);
            String act = "emptystuff";
            act.erase(5, 5);
            act.erase(0, 5);
            String exp = "";
            bool success = check_sol(act, exp);
            if (success) {
                printf("  TEST ERASE 10 - SUCCESS\n");
                ++num_correct;
            }
        }
        // ERASE TEST 11
        if (test_number == 11 || test_number == TEST_ALL || test_number == TEST_ERASE) {
            printf("======================================== 11 ========================================");
            printf("\nRUNNING TEST ERASE 11 ...\n");
            printf("  ORIGINAL STRING: \"parrot\"\n");
            printf("  OPERATION: erase(0, 281)\n");
            fflush(stdout);
            String act = "parrot";
            act.erase(0, 281);
            String exp = "";
            bool success = check_sol(act, exp);
            if (success) {
                printf("  TEST ERASE 11 - SUCCESS\n");
                ++num_correct;
            }
        }
        if (test_number == TEST_ERASE || test_number == TEST_ALL) {
            printf("====================================================================================\n");
            printf(" %d/11 TESTS PASSED\n", num_correct);
            printf("====================================================================================\n");
        }
        int erase_correct = num_correct;
        num_correct = 0;

        if (test_number == TEST_INSERT || test_number == TEST_ALL) {
            printf("====================================================================================\n");
            printf(" Running tests for string library insert ...\n");
        }
        // INSERT TEST 1
        if (test_number == 12 || test_number == TEST_ALL || test_number == TEST_INSERT) {
            printf("======================================== 12 ========================================");
            printf("\nRUNNING TEST INSERT 1 ...\n");
            printf("  ORIGINAL STRING: \"root/user/config\"\n");
            printf("  OPERATION: insert(4, \"/shared\")\n");
            fflush(stdout);
            String act = "root/user/config";
            act.insert(4, "/shared");
            String exp = "root/shared/user/config";
            bool success = check_sol(act, exp);
            if (success) {
                printf("  TEST INSERT 1 - SUCCESS\n");
                ++num_correct;
            }
        }
        // INSERT TEST 2
        if (test_number == 13 || test_number == TEST_ALL || test_number == TEST_INSERT) {
            printf("======================================== 13 ========================================");
            printf("\nRUNNING TEST INSERT 2 ...\n");
            printf("  ORIGINAL STRING: \" are the best!\"\n");
            printf("  OPERATION: insert(0, \"Parrots\")\n");
            fflush(stdout);
            String act = " are the best!";
            act.insert(0, "Parrots");
            String exp = "Parrots are the best!";
            bool success = check_sol(act, exp);
            if (success) {
                printf("  TEST INSERT 2 - SUCCESS\n");
                ++num_correct;
            }
        }
        // INSERT TEST 3
        if (test_number == 14 || test_number == TEST_ALL || test_number == TEST_INSERT) {
            printf("======================================== 14 ========================================");
            printf("\nRUNNING TEST INSERT 3 ...\n");
            printf("  ORIGINAL STRING: \"My favorite class is \"\n");
            printf("  OPERATION: insert(21, \"EECS 281!\")\n");
            fflush(stdout);
            String act = "My favorite class is ";
            act.insert(21, "EECS 281!");
            String exp = "My favorite class is EECS 281!";
            bool success = check_sol(act, exp);
            if (success) {
                printf("  TEST INSERT 3 - SUCCESS\n");
                ++num_correct;
            }
        }
        // INSERT TEST 4
        if (test_number == 15 || test_number == TEST_ALL || test_number == TEST_INSERT) {
            printf("======================================== 15 ========================================");
            printf("\nRUNNING TEST INSERT 4 ...\n");
            printf("  ORIGINAL STRING: \"0123456789\"\n");
            printf("  OPERATION: insert(2, \"abc\")\n");
            fflush(stdout);
            String act = "0123456789";
            String ins = "abc";
            act.insert(2, ins);
            String exp = "01abc23456789";
            bool success = check_sol(act, exp);
            if (success) {
                printf("  TEST INSERT 4 - SUCCESS\n");
                ++num_correct;
            }
        }
        // INSERT TEST 5
        if (test_number == 16 || test_number == TEST_ALL || test_number == TEST_INSERT) {
            printf("======================================== 16 ========================================");
            printf("\nRUNNING TEST INSERT 5 ...\n");
            printf("  ORIGINAL STRING: \"01abc23456789\"\n");
            printf("  OPERATION: insert(13, \"abc\")\n");
            fflush(stdout);
            String act = "01abc23456789";
            String ins = "abc";
            act.insert(act.size(), ins);
            String exp = "01abc23456789abc";
            bool success = check_sol(act, exp);
            if (success) {
                printf("  TEST INSERT 5 - SUCCESS\n");
                ++num_correct;
            }
        }
        // INSERT TEST 6
        if (test_number == 17 || test_number == TEST_ALL || test_number == TEST_INSERT) {
            printf("======================================== 17 ========================================");
            printf("\nRUNNING TEST INSERT 6 ...\n");
            printf("  ORIGINAL STRING: \"When I start my 281 project, the first thing I think of is FUN\"\n");
            printf("  OPERATION: insert(61, \"NCTIO\")\n");
            fflush(stdout);
            String act = "When I start my 281 project, the first thing I think of is FUN";
            act.insert(61, "NCTIO");
            String exp = "When I start my 281 project, the first thing I think of is FUNCTION";
            bool success = check_sol(act, exp);
            if (success) {
                printf("  TEST INSERT 6 - SUCCESS\n");
                ++num_correct;
            }
        }
        // INSERT TEST 7
        if (test_number == 18 || test_number == TEST_ALL || test_number == TEST_INSERT) {
            printf("======================================== 18 ========================================");
            printf("\nRUNNING TEST INSERT 7 ...\n");
            printf("  ORIGINAL STRING: \"a\"\n");
            printf("  OPERATION: insert(0, \"hahahah\")\n");
            fflush(stdout);
            String act = "a";
            act.insert(0, "hahahah");
            String exp = "hahahaha";
            bool success = check_sol(act, exp);
            if (success) {
                printf("  TEST INSERT 7 - SUCCESS\n");
                ++num_correct;
            }
        }
        // INSERT TEST 8
        if (test_number == 19 || test_number == TEST_ALL || test_number == TEST_INSERT) {
            printf("======================================== 19 ========================================");
            printf("\nRUNNING TEST INSERT 8 ...\n");
            printf("  ORIGINAL STRING: \"\"\n");
            printf("  OPERATION: insert(0, \"parrot\")\n");
            fflush(stdout);
            String act = "";
            act.insert(0, "parrot");
            String exp = "parrot";
            bool success = check_sol(act, exp);
            if (success) {
                printf("  TEST INSERT 8 - SUCCESS\n");
                ++num_correct;
            }
        }
        // INSERT TEST 9
        if (test_number == 20 || test_number == TEST_ALL || test_number == TEST_INSERT) {
            printf("======================================== 20 ========================================");
            printf("\nRUNNING TEST INSERT 9 ...\n");
            printf("  ORIGINAL STRING: \"281\"\n");
            printf("  OPERATION: insert(0, <self>)\n");
            fflush(stdout);
            String act = "281";
            act.insert(0, act);
            String exp = "281281";
            bool success = check_sol(act, exp);
            if (success) {
                printf("  TEST INSERT 9 - SUCCESS\n");
                ++num_correct;
            }
        }
        // INSERT TEST 10
        if (test_number == 21 || test_number == TEST_ALL || test_number == TEST_INSERT) {
            printf("======================================== 21 ========================================");
            printf("\nRUNNING TEST INSERT 10 ...\n");
            printf("  ORIGINAL STRING: \"281\"\n");
            printf("  OPERATION: insert(3, <self>)\n");
            fflush(stdout);
            String act = "281";
            act.insert(act.size(), act);
            String exp = "281281";
            bool success = check_sol(act, exp);
            if (success) {
                printf("  TEST INSERT 10 - SUCCESS\n");
                ++num_correct;
            }
        }
        // INSERT TEST 11
        if (test_number == 22 || test_number == TEST_ALL || test_number == TEST_INSERT) {
            printf("======================================== 22 ========================================");
            printf("\nRUNNING TEST INSERT 11 ...\n");
            printf("  ORIGINAL STRING: \"281\"\n");
            printf("  OPERATION: insert(2, <self>)\n");
            fflush(stdout);
            String act = "281";
            act.insert(2, act);
            String exp = "282811";
            bool success = check_sol(act, exp);
            if (success) {
                printf("  TEST INSERT 11 - SUCCESS\n");
                ++num_correct;
            }
        }

        if (test_number == TEST_INSERT || test_number == TEST_ALL) {
            printf("====================================================================================\n");
            printf(" %d/11 TESTS PASSED\n", num_correct);
            printf("====================================================================================\n");
        }
        int insert_correct = num_correct;
        num_correct = 0;

        if (test_number == TEST_REPLACE || test_number == TEST_ALL) {
            printf("====================================================================================\n");
            printf(" Running tests for string library replace ...\n");
        }
        // REPLACE TEST 1
        if (test_number == 23 || test_number == TEST_ALL || test_number == TEST_REPLACE) {
            printf("======================================== 23 ========================================");
            printf("\nRUNNING TEST REPLACE 1 ...\n");
            printf("  ORIGINAL STRING: \"root/shared/config\"\n");
            printf("  OPERATION: replace(5, 6, \"temp\")\n");
            fflush(stdout);
            String act = "root/shared/config";
            act.replace(5, 6, "temp");
            String exp = "root/temp/config";
            bool success = check_sol(act, exp);
            if (success) {
                printf("  TEST REPLACE 1 - SUCCESS\n");
                ++num_correct;
            }
        }
        // REPLACE TEST 2
        if (test_number == 24 || test_number == TEST_ALL || test_number == TEST_REPLACE) {
            printf("======================================== 24 ========================================");
            printf("\nRUNNING TEST REPLACE 2 ...\n");
            printf("  ORIGINAL STRING: \"Bing is a good instructor.\"\n");
            printf("  OPERATION: replace(15, 19, \"search engine.\")\n");
            fflush(stdout);
            String act = "Bing is a good instructor.";
            act.replace(15, 19, "search engine.");
            String exp = "Bing is a good search engine.";
            bool success = check_sol(act, exp);
            if (success) {
                printf("  TEST REPLACE 2 - SUCCESS\n");
                ++num_correct;
            }
        }
        // REPLACE TEST 3
        if (test_number == 25 || test_number == TEST_ALL || test_number == TEST_REPLACE) {
            printf("======================================== 25 ========================================");
            printf("\nRUNNING TEST REPLACE 3 ...\n");
            printf("  ORIGINAL STRING: \"fun\"\n");
            printf("  OPERATION: replace(0, 1, \"s\")\n");
            fflush(stdout);
            String act = "fun";
            act.replace(0, 1, "s");
            String exp = "sun";
            bool success = check_sol(act, exp);
            if (success) {
                printf("  TEST REPLACE 3 - SUCCESS\n");
                ++num_correct;
            }
        }
        // REPLACE TEST 4
        if (test_number == 26 || test_number == TEST_ALL || test_number == TEST_REPLACE) {
            printf("======================================== 26 ========================================");
            printf("\nRUNNING TEST REPLACE 4 ...\n");
            printf("  ORIGINAL STRING: \"replaceme\"\n");
            printf("  OPERATION: replace(0, 9, \"ok\")\n");
            fflush(stdout);
            String act = "replaceme";
            act.replace(0, 9, "ok");
            String exp = "ok";
            bool success = check_sol(act, exp);
            if (success) {
                printf("  TEST REPLACE 4 - SUCCESS\n");
                ++num_correct;
            }
        }
        // REPLACE TEST 5
        if (test_number == 27 || test_number == TEST_ALL || test_number == TEST_REPLACE) {
            printf("======================================== 27 ========================================");
            printf("\nRUNNING TEST REPLACE 5 ...\n");
            printf("  ORIGINAL STRING: \"potatoparrot\"\n");
            printf("  OPERATION: replace(6, 1, \" p\")\n");
            fflush(stdout);
            String act = "potatoparrot";
            act.replace(6, 1, " p");
            String exp = "potato parrot";
            bool success = check_sol(act, exp);
            if (success) {
                printf("  TEST REPLACE 5 - SUCCESS\n");
                ++num_correct;
            }
        }
        // REPLACE TEST 6
        if (test_number == 28 || test_number == TEST_ALL || test_number == TEST_REPLACE) {
            printf("======================================== 28 ========================================");
            printf("\nRUNNING TEST REPLACE 6 ...\n");
            printf("  ORIGINAL STRING: \"x\"\n");
            printf("  OPERATION: replace(0, 1, \"lab3lab3lab3\")\n");
            fflush(stdout);
            String act = "x";
            act.replace(0, 1, "lab3lab3lab3");
            String exp = "lab3lab3lab3";
            bool success = check_sol(act, exp);
            if (success) {
                printf("  TEST REPLACE 6 - SUCCESS\n");
                ++num_correct;
            }
        }
        // REPLACE TEST 7
        if (test_number == 29 || test_number == TEST_ALL || test_number == TEST_REPLACE) {
            printf("======================================== 29 ========================================");
            printf("\nRUNNING TEST REPLACE 7 ...\n");
            printf("  ORIGINAL STRING: \"apple\"\n");
            printf("  OPERATION: replace(2, 281, \"ex\")\n");
            fflush(stdout);
            String act = "apple";
            act.replace(2, 281, "ex");
            String exp = "apex";
            bool success = check_sol(act, exp);
            if (success) {
                printf("  TEST REPLACE 7 - SUCCESS\n");
                ++num_correct;
            }
        }
        // REPLACE TEST 8
        if (test_number == 30 || test_number == TEST_ALL || test_number == TEST_REPLACE) {
            printf("======================================== 30 ========================================");
            printf("\nRUNNING TEST REPLACE 8 ...\n");
            printf("  ORIGINAL STRING: \"eecs281eecs2811\"\n");
            printf("  OPERATION: replace(11, 4, \"370\")\n");
            fflush(stdout);
            String act = "eecs281eecs2811";
            act.replace(11, 4, "370");
            String exp = "eecs281eecs370";
            bool success = check_sol(act, exp);
            if (success) {
                printf("  TEST REPLACE 8 - SUCCESS\n");
                ++num_correct;
            }
        }
        // REPLACE TEST 9
        if (test_number == 31 || test_number == TEST_ALL || test_number == TEST_REPLACE) {
            printf("======================================== 31 ========================================");
            printf("\nRUNNING TEST REPLACE 9 ...\n");
            printf("  ORIGINAL STRING: \"koala\"\n");
            printf("  OPERATION: replace(0, 1, \"lala\")\n");
            fflush(stdout);
            String act = "koala";
            act.replace(0, 1, "lala");
            String exp = "lalaoala";
            bool success = check_sol(act, exp);
            if (success) {
                printf("  TEST REPLACE 9 - SUCCESS\n");
                ++num_correct;
            }
        }
        // REPLACE TEST 10
        if (test_number == 32 || test_number == TEST_ALL || test_number == TEST_REPLACE) {
            printf("======================================== 32 ========================================");
            printf("\nRUNNING TEST REPLACE 10 ...\n");
            printf("  ORIGINAL STRING: \"eecs281\"\n");
            printf("  OPERATION: replace(0, 10, \"\")\n");
            fflush(stdout);
            String act = "eecs281";
            act.replace(0, 10, "");
            String exp = "";
            bool success = check_sol(act, exp);
            if (success) {
                printf("  TEST REPLACE 10 - SUCCESS\n");
                ++num_correct;
            }
        }
        // REPLACE TEST 11
        if (test_number == 33 || test_number == TEST_ALL || test_number == TEST_REPLACE) {
            printf("======================================== 33 ========================================");
            printf("\nRUNNING TEST REPLACE 11 ...\n");
            printf("  ORIGINAL STRING: \"eecs281\"\n");
            printf("  OPERATION: replace(0, 4, \"\")\n");
            fflush(stdout);
            String act = "eecs281";
            act.replace(0, 4, "");
            String exp = "281";
            bool success = check_sol(act, exp);
            if (success) {
                printf("  TEST REPLACE 11 - SUCCESS\n");
                ++num_correct;
            }
        }
        // REPLACE TEST 12
        if (test_number == 34 || test_number == TEST_ALL || test_number == TEST_REPLACE) {
            printf("======================================== 34 ========================================");
            printf("\nRUNNING TEST REPLACE 12 ...\n");
            printf("  ORIGINAL STRING: \"eecs281\"\n");
            printf("  OPERATION: replace(4, 3, \"\")\n");
            fflush(stdout);
            String act = "eecs281";
            act.replace(4, 3, "");
            String exp = "eecs";
            bool success = check_sol(act, exp);
            if (success) {
                printf("  TEST REPLACE 12 - SUCCESS\n");
                ++num_correct;
            }
        }
        // REPLACE TEST 13
        if (test_number == 35 || test_number == TEST_ALL || test_number == TEST_REPLACE) {
            printf("======================================== 35 ========================================");
            printf("\nRUNNING TEST REPLACE 13 ...\n");
            printf("  ORIGINAL STRING: \"eecs281\"\n");
            printf("  OPERATION: replace(3, 2, <self>)\n");
            fflush(stdout);
            String act = "eecs281";
            act.replace(3, 2, act);
            String exp = "eeceecs28181";
            bool success = check_sol(act, exp);
            if (success) {
                printf("  TEST REPLACE 13 - SUCCESS\n");
                ++num_correct;
            }
        }
        // REPLACE TEST 14
        if (test_number == 36 || test_number == TEST_ALL || test_number == TEST_REPLACE) {
            printf("======================================== 36 ========================================");
            printf("\nRUNNING TEST REPLACE 14 ...\n");
            printf("  ORIGINAL STRING: \"are\"\n");
            printf("  OPERATION: replace(2, 0, \"hur8r3\")\n");
            fflush(stdout);
            String act = "are";
            act.replace(2, 0, "hur8r3");
            String exp = "arhur8r3e";
            bool success = check_sol(act, exp);
            if (success) {
                printf("  TEST REPLACE 14 - SUCCESS\n");
                ++num_correct;
            }
        }
        // REPLACE TEST 15
        if (test_number == 37 || test_number == TEST_ALL || test_number == TEST_REPLACE) {
            printf("======================================== 37 ========================================");
            printf("\nRUNNING TEST REPLACE 15 ...\n");
            printf("  ORIGINAL STRING: \"r\"\n");
            printf("  OPERATION: replace(0, 0, \"live\")\n");
            fflush(stdout);
            String act = "r";
            act.replace(0, 0, "live");
            String exp = "liver";
            bool success = check_sol(act, exp);
            if (success) {
                printf("  TEST REPLACE 15 - SUCCESS\n");
                ++num_correct;
            }
        }
        // REPLACE TEST 16
        if (test_number == 38 || test_number == TEST_ALL || test_number == TEST_REPLACE) {
            printf("======================================== 38 ========================================");
            printf("\nRUNNING TEST REPLACE 16 ...\n");
            printf("  ORIGINAL STRING: \"uqwergniniwiheteoh\"\n");
            printf("  OPERATION: replace(2, 0, \"fuf7t8f7sf7\")\n");
            fflush(stdout);
            String act = "uqwergniniwiheteoh";
            act.replace(2, 0, "fuf7t8f7sf7");
            String exp = "uqfuf7t8f7sf7wergniniwiheteoh";
            bool success = check_sol(act, exp);
            if (success) {
                printf("  TEST REPLACE 16 - SUCCESS\n");
                ++num_correct;
            }
        }
        // REPLACE TEST 17
        if (test_number == 39 || test_number == TEST_ALL || test_number == TEST_REPLACE) {
            printf("======================================== 39 ========================================");
            printf("\nRUNNING TEST REPLACE 17 ...\n");
            printf("  ORIGINAL STRING: \"wants12934875rgywe\"\n");
            printf("  OPERATION: replace(0, 0, \"ufeisiohusopT$*(&YEGUity4irjgoiuij\")\n");
            fflush(stdout);
            String act = "wants12934875rgywe";
            act.replace(0, 0, "ufeisiohusopT$*(&YEGUity4irjgoiuij");
            String exp = "ufeisiohusopT$*(&YEGUity4irjgoiuijwants12934875rgywe";
            bool success = check_sol(act, exp);
            if (success) {
                printf("  TEST REPLACE 17 - SUCCESS\n");
                ++num_correct;
            }
        }
        // REPLACE TEST 18
        if (test_number == 40 || test_number == TEST_ALL || test_number == TEST_REPLACE) {
            printf("======================================== 40 ========================================");
            printf("\nRUNNING TEST REPLACE 18 ...\n");
            printf("  ORIGINAL STRING: \"parrot\"\n");
            printf("  OPERATION: replace(6, 6, \"oy\")\n");
            fflush(stdout);
            String act = "parrot";
            act.replace(6, 6, "oy");
            String exp = "parrotoy";
            bool success = check_sol(act, exp);
            if (success) {
                printf("  TEST REPLACE 18 - SUCCESS\n");
                ++num_correct;
            }
        }
        // REPLACE TEST 19
        if (test_number == 41 || test_number == TEST_ALL || test_number == TEST_REPLACE) {
            printf("======================================== 41 ========================================");
            printf("\nRUNNING TEST REPLACE 19 ...\n");
            printf("  ORIGINAL STRING: \"\"\n");
            printf("  OPERATION: replace(0, 1, \"F\")\n");
            fflush(stdout);
            String act = "";
            act.replace(0, 1, "F");
            String exp = "F";
            bool success = check_sol(act, exp);
            if (success) {
                printf("  TEST REPLACE 19 - SUCCESS\n");
                ++num_correct;
            }
        }
        // REPLACE TEST 20
        if (test_number == 42 || test_number == TEST_ALL || test_number == TEST_REPLACE) {
            printf("======================================== 42 ========================================");
            printf("\nRUNNING TEST REPLACE 20 ...\n");
            printf("  ORIGINAL STRING: \"On$\"\n");
            printf("  OPERATION: replace(0, 2, \"gwu9hwehh08hwhwehggew\")\n");
            fflush(stdout);
            String act = "On$";
            act.replace(0, 2, "gwu9hwehh08hwhwehggew");
            String exp = "gwu9hwehh08hwhwehggew$";
            bool success = check_sol(act, exp);
            if (success) {
                printf("  TEST REPLACE 20 - SUCCESS\n");
                ++num_correct;
            }
        }

        if (test_number == TEST_REPLACE || test_number == TEST_ALL) {
            printf("====================================================================================\n");
            printf(" %d/20 TESTS PASSED\n", num_correct);
            printf("====================================================================================\n");
        }
        int replace_correct = num_correct;
        num_correct = 0;

        if (test_number == TEST_FFO || test_number == TEST_ALL) {
            printf("====================================================================================\n");
            printf(" Running tests for string library find_first_of ...\n");
        }
        // FIND FIRST OF TEST 1
        if (test_number == 43 || test_number == TEST_ALL || test_number == TEST_FFO) {
            printf("======================================== 43 ========================================");
            printf("\nRUNNING TEST FIND_FIRST_OF 1 ...\n");
            printf("  ORIGINAL STRING: \"the quick brown fox jumps over the lazy dog\"\n");
            printf("  OPERATIONS: find_first_of(<all characters from A to Z>)\n");
            fflush(stdout);
            String act = "the quick brown fox jumps over the lazy dog";
            size_t solution[26] = { 36, 10, 7, 40, 2, 16, 42, 1, 6, 20, 8, 35, 22, 14, 12, 23, 4, 11, 24, 0, 5, 27, 13, 18, 38, 37 };
            bool passed = true;
            int counter = 0;
            char* target = new char[2];
            target[1] = '\0';
            for (int i = 0; i < 26; ++i) {
                target[0] = static_cast<char>('a' + i);
                ++counter;
                String next_char = target;
                size_t res = act.find_first_of(next_char);
                if (res != solution[i]) {
                    passed = false;
                    printf("FAILED - INCORRECT INDEX PRODUCED\n");
                    printf("  EXPECTED INDEX %zu FOR CHARACTER \'%c\', BUT GOT INDEX %zu\n", solution[i], *target, res);
                    break;
                }
            }
            if (passed) {
                printf("  TEST FIND_FIRST_OF 1 - SUCCESS\n");
                ++num_correct;
            }
            // clean up memory
            delete[] target;
            (void)counter;
        }
        // Test Find First Of 2
        if (test_number == 44 || test_number == TEST_ALL || test_number == TEST_FFO) {
            printf("======================================== 44 ========================================");
            printf("\nRUNNING TEST FIND_FIRST_OF 2 ...\n");
            printf("  ORIGINAL STRING: \"root/user/config\"\n");
            printf("  OPERATION: find_first_of(\"/\")\n");
            fflush(stdout);
            String act = "root/user/config";
            size_t start = act.find_first_of("/");
            if (start != 4) {
                printf("FAILED - INCORRECT INDEX PRODUCED\n");
                printf("  EXPECTED INDEX 4, BUT GOT INDEX %zu\n", start);
            }
            else {
                printf("  TEST FIND_FIRST_OF 2 - SUCCESS\n");
                ++num_correct;
            }
        }
        // Test Find First Of 3
        if (test_number == 45 || test_number == TEST_ALL || test_number == TEST_FFO) {
            printf("======================================== 45 ========================================");
            printf("\nRUNNING TEST FIND_FIRST_OF 3 ...\n");
            printf("  ORIGINAL STRING: \"the quick brown fox jumps over the lazy dog\"\n");
            printf("  OPERATION: find_first_of(\"jogkuq\")\n");
            fflush(stdout);
            String act = "the quick brown fox jumps over the lazy dog";
            size_t start = act.find_first_of("jogkuq");
            if (start != 4) {
                printf("FAILED - INCORRECT INDEX PRODUCED\n");
                printf("  EXPECTED INDEX 4, BUT GOT INDEX %zu\n", start);
            }
            else {
                printf("  TEST FIND_FIRST_OF 3 - SUCCESS\n");
                ++num_correct;
            }
        }
        // Test Find First Of 4
        if (test_number == 46 || test_number == TEST_ALL || test_number == TEST_FFO) {
            printf("======================================== 46 ========================================");
            printf("\nRUNNING TEST FIND_FIRST_OF 4 ...\n");
            printf("  ORIGINAL STRING: \"This is a question?\"\n");
            printf("  OPERATION: find_first_of(\"?!.)(!\")\n");
            fflush(stdout);
            String act = "This is a question?";
            String target = "?!.)(!";
            size_t start = act.find_first_of(target);
            if (start != 18) {
                printf("FAILED - INCORRECT INDEX PRODUCED\n");
                printf("  EXPECTED INDEX 18, BUT GOT INDEX %zu\n", start);
            }
            else {
                printf("  TEST FIND_FIRST_OF 4 - SUCCESS\n");
                ++num_correct;
            }
        }
        // Test Find First Of 5
        if (test_number == 47 || test_number == TEST_ALL || test_number == TEST_FFO) {
            printf("======================================== 47 ========================================");
            printf("\nRUNNING TEST FIND_FIRST_OF 5 ...\n");
            printf("  ORIGINAL STRING: \"This is an exclamation!\"\n");
            printf("  OPERATION: find_first_of(\"?!.)(!\")\n");
            fflush(stdout);
            String act = "This is an exclamation!";
            String target = "?!.)(!";
            size_t start = act.find_first_of(target);
            if (start != 22) {
                printf("FAILED - INCORRECT INDEX PRODUCED\n");
                printf("  EXPECTED INDEX 22, BUT GOT INDEX %zu\n", start);
            }
            else {
                printf("  TEST FIND_FIRST_OF 5 - SUCCESS\n");
                ++num_correct;
            }
        }
        // Test Find First Of 6
        if (test_number == 48 || test_number == TEST_ALL || test_number == TEST_FFO) {
            printf("======================================== 48 ========================================");
            printf("\nRUNNING TEST FIND_FIRST_OF 6 ...\n");
            printf("  ORIGINAL STRING: \"Words in parentheses can (not) be ignored.\"\n");
            printf("  OPERATION: find_first_of(\"?!.)(!\")\n");
            fflush(stdout);
            String act = "Words in parentheses can (not) be ignored.";
            String target = "?!.)(!";
            size_t start = act.find_first_of(target);
            if (start != 25) {
                printf("FAILED - INCORRECT INDEX PRODUCED\n");
                printf("  EXPECTED INDEX 25, BUT GOT INDEX %zu\n", start);
            }
            else {
                printf("  TEST FIND_FIRST_OF 6 - SUCCESS\n");
                ++num_correct;
            }
        }
        // Test Find First Of 7
        if (test_number == 49 || test_number == TEST_ALL || test_number == TEST_FFO) {
            printf("======================================== 49 ========================================");
            printf("\nRUNNING TEST FIND_FIRST_OF 7 ...\n");
            printf("  ORIGINAL STRING: \"appleappleappleappleorangeappleorange\"\n");
            printf("  OPERATION: find_first_of(\"GgGgGgGgGg\", 27)\n");
            fflush(stdout);
            String act = "appleappleappleappleorangeappleorange";
            size_t start = act.find_first_of("GgGgGgGgGg", 27);
            if (start != 35) {
                printf("FAILED - INCORRECT INDEX PRODUCED\n");
                printf("  EXPECTED INDEX 35, BUT GOT INDEX %zu\n", start);
            }
            else {
                printf("  TEST FIND_FIRST_OF 7 - SUCCESS\n");
                ++num_correct;
            }
        }
        // Test Find First Of 8
        if (test_number == 50 || test_number == TEST_ALL || test_number == TEST_FFO) {
            printf("======================================== 50 ========================================");
            printf("\nRUNNING TEST FIND_FIRST_OF 8 ...\n");
            printf("  ORIGINAL STRING: \"my_eecs281_project\"\n");
            printf("  OPERATION: find_first_of(\"SEGFAULT\")\n");
            fflush(stdout);
            String act = "my_eecs281_project";
            size_t start = act.find_first_of("SEGFAULT");
            if (start != npos) {
                printf("FAILED - INCORRECT INDEX PRODUCED\n");
                printf("  EXPECTED NPOS, BUT GOT INDEX %zu\n", start);
            }
            else {
                printf("  TEST FIND_FIRST_OF 8 - SUCCESS\n");
                ++num_correct;
            }
        }
        // Test Find First Of 9
        if (test_number == 51 || test_number == TEST_ALL || test_number == TEST_FFO) {
            printf("======================================== 51 ========================================");
            printf("\nRUNNING TEST FIND_FIRST_OF 9 ...\n");
            printf("  ORIGINAL STRING: \"my_eecs281_project\"\n");
            printf("  OPERATION: find_first_of(\"SEGFAULT\", 281)\n");
            fflush(stdout);
            String act = "my_eecs281_project";
            size_t start = act.find_first_of("SEGFAULT", 281);
            if (start != npos) {
                printf("FAILED - INCORRECT INDEX PRODUCED\n");
                printf("  EXPECTED NPOS, BUT GOT INDEX %zu\n", start);
            }
            else {
                printf("  TEST FIND_FIRST_OF 9 - SUCCESS\n");
                ++num_correct;
            }
        }
        // Test Find First Of 10
        if (test_number == 52 || test_number == TEST_ALL || test_number == TEST_FFO) {
            printf("======================================== 52 ========================================");
            printf("\nRUNNING TEST FIND_FIRST_OF 10 ...\n");
            printf("  ORIGINAL STRING: \"my_eecs281_project\"\n");
            printf("  OPERATION: find_first_of(\"1234567890\", 9)\n");
            fflush(stdout);
            String act = "my_eecs281_project";
            size_t start = act.find_first_of("1234567890", 9);
            if (start != 9) {
                printf("FAILED - INCORRECT INDEX PRODUCED\n");
                printf("  EXPECTED INDEX 9, BUT GOT INDEX %zu\n", start);
            }
            else {
                printf("  TEST FIND_FIRST_OF 10 - SUCCESS\n");
                ++num_correct;
            }
        }
        // Test Find First Of 11
        if (test_number == 53 || test_number == TEST_ALL || test_number == TEST_FFO) {
            printf("======================================== 53 ========================================");
            printf("\nRUNNING TEST FIND_FIRST_OF 11 ...\n");
            printf("  ORIGINAL STRING: \"Which\"\n");
            printf("  OPERATION: find_first_of(\"xihczu\", 2)\n");
            fflush(stdout);
            String act = "Which";
            size_t start = act.find_first_of("xihczu", 2);
            if (start != 2) {
                printf("FAILED - INCORRECT INDEX PRODUCED\n");
                printf("  EXPECTED INDEX 2, BUT GOT INDEX %zu\n", start);
            }
            else {
                printf("  TEST FIND_FIRST_OF 11 - SUCCESS\n");
                ++num_correct;
            }
        }
        // Test Find First Of 12
        if (test_number == 54 || test_number == TEST_ALL || test_number == TEST_FFO) {
            printf("======================================== 54 ========================================");
            printf("\nRUNNING TEST FIND_FIRST_OF 12 ...\n");
            printf("  ORIGINAL STRING: \"https:w.xyz.com/201e9/09/1$\"\n");
            printf("  OPERATION: find_first_of(\"fehafafafi(@)^(@)\", 16)\n");
            fflush(stdout);
            String act = "https:w.xyz.com/201e9/09/1$";
            size_t start = act.find_first_of("fehafafafi(@)^(@)", 16);
            if (start != 19) {
                printf("FAILED - INCORRECT INDEX PRODUCED\n");
                printf("  EXPECTED INDEX 19, BUT GOT INDEX %zu\n", start);
            }
            else {
                printf("  TEST FIND_FIRST_OF 12 - SUCCESS\n");
                ++num_correct;
            }
        }
        // Test Find First Of 13
        if (test_number == 55 || test_number == TEST_ALL || test_number == TEST_FFO) {
            printf("======================================== 55 ========================================");
            printf("\nRUNNING TEST FIND_FIRST_OF 13 ...\n");
            printf("  ORIGINAL STRING: \"hthe848$$wihniwihethiwti\"\n");
            printf("  OPERATION: find_first_of(\"ihw4thw4htiwh\", 22)\n");
            fflush(stdout);
            String act = "hthe848$$wihniwihethiwti";
            size_t start = act.find_first_of("ihw4thw4htiwh", 22);
            if (start != 22) {
                printf("FAILED - INCORRECT INDEX PRODUCED\n");
                printf("  EXPECTED INDEX 22, BUT GOT INDEX %zu\n", start);
            }
            else {
                printf("  TEST FIND_FIRST_OF 13 - SUCCESS\n");
                ++num_correct;
            }
        }
        // Test Find First Of 14
        if (test_number == 56 || test_number == TEST_ALL || test_number == TEST_FFO) {
            printf("======================================== 56 ========================================");
            printf("\nRUNNING TEST FIND_FIRST_OF 14 ...\n");
            printf("  ORIGINAL STRING: \"https:uwgefw.m\"fxd\"\n");
            printf("  OPERATION: find_first_of(\"ugvhgcfxd\", 3)\n");
            fflush(stdout);
            String act = "https:uwgefw.m\"fxd";
            size_t start = act.find_first_of("ugvhgcfxd", 3);
            if (start != 6) {
                printf("FAILED - INCORRECT INDEX PRODUCED\n");
                printf("  EXPECTED INDEX 6, BUT GOT INDEX %zu\n", start);
            }
            else {
                printf("  TEST FIND_FIRST_OF 14 - SUCCESS\n");
                ++num_correct;
            }
        }

        if (test_number == TEST_FFO || test_number == TEST_ALL) {
            printf("====================================================================================\n");
            printf(" %d/14 TESTS PASSED\n", num_correct);
            printf("====================================================================================\n");
        }
        int ffo_correct = num_correct;
        num_correct = 0;

        if (test_number == TEST_FLO || test_number == TEST_ALL) {
            printf("====================================================================================\n");
            printf(" Running tests for string library find_last_of ...\n");
        }
        // Test Find Last Of 1
        if (test_number == 57 || test_number == TEST_ALL || test_number == TEST_FLO) {
            printf("======================================== 57 ========================================");
            printf("\nRUNNING TEST FIND_LAST_OF 1 ...\n");
            printf("  ORIGINAL STRING: \"the quick brown fox jumps over the lazy dog\"\n");
            printf("  OPERATIONS: find_last_of(<all characters from A to Z>)\n");
            fflush(stdout);
            String str = "the quick brown fox jumps over the lazy dog";
            size_t solution[26] = { 36, 10, 7, 40, 33, 16, 42, 32, 6, 20, 8, 35, 22, 14, 41, 23, 4, 29, 24, 31, 21, 27, 13, 18, 38, 37 };
            bool passed = true;
            int counter = 0;
            char* target = new char[2];
            target[1] = '\0';
            for (int i = 0; i < 26; ++i) {
                target[0] = static_cast<char>('a' + i);
                ++counter;
                String next_char = target;
                size_t res = str.find_last_of(next_char);
                if (res != solution[i]) {
                    passed = false;
                    printf("FAILED - INCORRECT INDEX PRODUCED\n");
                    printf("  EXPECTED INDEX %zu FOR CHARACTER \'%c\', BUT GOT INDEX %zu\n", solution[i], *target, res);
                    break;
                }
            }
            if (passed) {
                printf("  TEST FIND_LAST_OF 1 - SUCCESS\n");
                ++num_correct;
            }
            // clean up memory
            delete[] target;
            (void)counter;
        }
        // Test Find Last Of 2
        if (test_number == 58 || test_number == TEST_ALL || test_number == TEST_FLO) {
            printf("======================================== 58 ========================================");
            printf("\nRUNNING TEST FIND_LAST_OF 2 ...\n");
            printf("  ORIGINAL STRING: \"root/user/config\"\n");
            printf("  OPERATION: find_last_of(\"/\")\n");
            fflush(stdout);
            String act = "root/user/config";
            size_t last = act.find_last_of("/");
            if (last != 9) {
                printf("FAILED - INCORRECT INDEX PRODUCED\n");
                printf("  EXPECTED INDEX 9, BUT GOT INDEX %zu\n", last);
            }
            else {
                printf("  TEST FIND_LAST_OF 2 - SUCCESS\n");
                ++num_correct;
            }
        }
        // Test Find Last Of 3
        if (test_number == 59 || test_number == TEST_ALL || test_number == TEST_FLO) {
            printf("======================================== 59 ========================================");
            printf("\nRUNNING TEST FIND_LAST_OF 3 ...\n");
            printf("  ORIGINAL STRING: \"the quick brown fox jumps over the lazy dog\"\n");
            printf("  OPERATION: find_last_of(\"xicku\")\n");
            fflush(stdout);
            String act = "the quick brown fox jumps over the lazy dog";
            size_t last = act.find_last_of("xicku");
            if (last != 21) {
                printf("FAILED - INCORRECT INDEX PRODUCED\n");
                printf("  EXPECTED INDEX 21, BUT GOT INDEX %zu\n", last);
            }
            else {
                printf("  TEST FIND_LAST_OF 3 - SUCCESS\n");
                ++num_correct;
            }
        }
        // Test Find Last Of 4
        if (test_number == 60 || test_number == TEST_ALL || test_number == TEST_FLO) {
            printf("======================================== 60 ========================================");
            printf("\nRUNNING TEST FIND_LAST_OF 4 ...\n");
            printf("  ORIGINAL STRING: \"EECS 281!!!\"\n");
            printf("  OPERATION: find_last_of(\"EECS 280?!!!\")\n");
            fflush(stdout);
            String act = "EECS 281!!!";
            size_t last = act.find_last_of("EECS 280?!!!");
            if (last != 10) {
                printf("FAILED - INCORRECT INDEX PRODUCED\n");
                printf("  EXPECTED INDEX 10, BUT GOT INDEX %zu\n", last);
            }
            else {
                printf("  TEST FIND_LAST_OF 4 - SUCCESS\n");
                ++num_correct;
            }
        }
        // Test Find Last Of 5
        if (test_number == 61 || test_number == TEST_ALL || test_number == TEST_FLO) {
            printf("======================================== 61 ========================================");
            printf("\nRUNNING TEST FIND_LAST_OF 5 ...\n");
            printf("  ORIGINAL STRING: \"Words in parentheses can (not) be ignored!!!!!\"\n");
            printf("  OPERATIONS: erase(41, 5) then find_last_of(\"?!.)(!\", 65)\n");
            fflush(stdout);
            String act = "Words in parentheses can (not) be ignored!!!!!";
            size_t last = act.erase(41, 5).find_last_of("?!.)(!", 65);
            if (last != 29) {
                printf("FAILED - INCORRECT INDEX PRODUCED\n");
                printf("  EXPECTED INDEX 29, BUT GOT INDEX %zu\n", last);
            }
            else {
                printf("  TEST FIND_LAST_OF 5 - SUCCESS\n");
                ++num_correct;
            }
        }
        // Test Find Last Of 6
        if (test_number == 62 || test_number == TEST_ALL || test_number == TEST_FLO) {
            printf("======================================== 62 ========================================");
            printf("\nRUNNING TEST FIND_LAST_OF 6 ...\n");
            printf("  ORIGINAL STRING: \"Words in parentheses can (not) be ignored!!!!!\"\n");
            printf("  OPERATION: find_last_of(\"?!.)(!\", 24)\n");
            fflush(stdout);
            String act = "Words in parentheses can (not) be ignored!!!!!";
            size_t last = act.find_last_of("?!.)(!", 24);
            if (last != npos) {
                printf("FAILED - INCORRECT INDEX PRODUCED\n");
                printf("  EXPECTED NPOS, BUT GOT INDEX %zu\n", last);
            }
            else {
                printf("  TEST FIND_LAST_OF 6 - SUCCESS\n");
                ++num_correct;
            }
        }
        // Test Find Last Of 7
        if (test_number == 63 || test_number == TEST_ALL || test_number == TEST_FLO) {
            printf("======================================== 63 ========================================");
            printf("\nRUNNING TEST FIND_LAST_OF 7 ...\n");
            printf("  ORIGINAL STRING: \"carrots and parrots\"\n");
            printf("  OPERATION: find_last_of(\"yuck\")\n");
            fflush(stdout);
            String act = "carrots and parrots";
            size_t last = act.find_last_of("yuck");
            if (last != 0) {
                printf("FAILED - INCORRECT INDEX PRODUCED\n");
                printf("  EXPECTED INDEX 0, BUT GOT INDEX %zu\n", last);
            }
            else {
                printf("  TEST FIND_LAST_OF 7 - SUCCESS\n");
                ++num_correct;
            }
        }
        // Test Find Last Of 8
        if (test_number == 64 || test_number == TEST_ALL || test_number == TEST_FLO) {
            printf("======================================== 64 ========================================");
            printf("\nRUNNING TEST FIND_LAST_OF 8 ...\n");
            printf("  ORIGINAL STRING: \"carrots and parrots\"\n");
            printf("  OPERATION: find_last_of(\"yuck\", 0)\n");
            fflush(stdout);
            String act = "carrots and parrots";
            size_t last = act.find_last_of("yuck", 0);
            if (last != 0) {
                printf("FAILED - INCORRECT INDEX PRODUCED\n");
                printf("  EXPECTED INDEX 0, BUT GOT INDEX %zu\n", last);
            }
            else {
                printf("  TEST FIND_LAST_OF 8 - SUCCESS\n");
                ++num_correct;
            }
        }
        // Test Find Last Of 9
        if (test_number == 65 || test_number == TEST_ALL || test_number == TEST_FLO) {
            printf("======================================== 65 ========================================");
            printf("\nRUNNING TEST FIND_LAST_OF 9 ...\n");
            printf("  ORIGINAL STRING: \"thoroughbreds\"\n");
            printf("  OPERATION: find_last_of(\"parrot\", 11)\n");
            fflush(stdout);
            String act = "thoroughbreds";
            size_t last = act.find_last_of("parrot", 11);
            if (last != 9) {
                printf("FAILED - INCORRECT INDEX PRODUCED\n");
                printf("  EXPECTED INDEX 9, BUT GOT INDEX %zu\n", last);
            }
            else {
                printf("  TEST FIND_LAST_OF 9 - SUCCESS\n");
                ++num_correct;
            }
        }
        // Test Find Last Of 10
        if (test_number == 66 || test_number == TEST_ALL || test_number == TEST_FLO) {
            printf("======================================== 66 ========================================");
            printf("\nRUNNING TEST FIND_LAST_OF 10 ...\n");
            printf("  ORIGINAL STRING: \"Which\"\n");
            printf("  OPERATION: find_last_of(\"*A&TFEFIUYG?\")\n");
            fflush(stdout);
            String act = "Which";
            size_t last = act.find_last_of("*A&TFEFIUYG?");
            if (last != npos) {
                printf("FAILED - INCORRECT INDEX PRODUCED\n");
                printf("  EXPECTED NPOS, BUT GOT INDEX %zu\n", last);
            }
            else {
                printf("  TEST FIND_LAST_OF 10 - SUCCESS\n");
                ++num_correct;
            }
        }
        // Test Find Last Of 11
        if (test_number == 67 || test_number == TEST_ALL || test_number == TEST_FLO) {
            printf("======================================== 67 ========================================");
            printf("\nRUNNING TEST FIND_LAST_OF 11 ...\n");
            printf("  ORIGINAL STRING: \"usggAD9345uu3ibeLKE:Ffuf7t8uwgefhsnhgdgtkhm\"\n");
            printf("  OPERATION: find_last_of(\"536788ir4wo874\", 0)\n");
            fflush(stdout);
            String act = "usggAD9345uu3ibeLKE:Ffuf7t8uwgefhsnhgdgtkhm";
            size_t last = act.find_last_of("536788ir4wo874", 0);
            if (last != npos) {
                printf("FAILED - INCORRECT INDEX PRODUCED\n");
                printf("  EXPECTED NPOS, BUT GOT INDEX %zu\n", last);
            }
            else {
                printf("  TEST FIND_LAST_OF 11 - SUCCESS\n");
                ++num_correct;
            }
        }
        // Test Find Last Of 12
        if (test_number == 68 || test_number == TEST_ALL || test_number == TEST_FLO) {
            printf("======================================== 68 ========================================");
            printf("\nRUNNING TEST FIND_LAST_OF 12 ...\n");
            printf("  ORIGINAL STRING: \"https:uwniwihethiwtigefw.m\"fxd\"\n");
            printf("  OPERATION: find_last_of(\"gywe\", 30)\n");
            fflush(stdout);
            String act = "https:uwniwihethiwtigefw.m\"fxd";
            size_t last = act.find_last_of("gywe", 30);
            if (last != 23) {
                printf("FAILED - INCORRECT INDEX PRODUCED\n");
                printf("  EXPECTED INDEX 23, BUT GOT INDEX %zu\n", last);
            }
            else {
                printf("  TEST FIND_LAST_OF 12 - SUCCESS\n");
                ++num_correct;
            }
        }
        // Test Find Last Of 13
        if (test_number == 69 || test_number == TEST_ALL || test_number == TEST_FLO) {
            printf("======================================== 69 ========================================");
            printf("\nRUNNING TEST FIND_LAST_OF 13 ...\n");
            printf("  ORIGINAL STRING: \"yaaaaaaaaaaaaaaaay\"\n");
            printf("  OPERATION: find_last_of(\"happy\", 11)\n");
            fflush(stdout);
            String act = "yaaaaaaaaaaaaaaaay";
            size_t last = act.find_last_of("happy", 11);
            if (last != 11) {
                printf("FAILED - INCORRECT INDEX PRODUCED\n");
                printf("  EXPECTED INDEX 11, BUT GOT INDEX %zu\n", last);
            }
            else {
                printf("  TEST FIND_LAST_OF 13 - SUCCESS\n");
                ++num_correct;
            }
        }
        // Test Find Last Of 14
        if (test_number == 70 || test_number == TEST_ALL || test_number == TEST_FLO) {
            printf("======================================== 70 ========================================");
            printf("\nRUNNING TEST FIND_LAST_OF 14 ...\n");
            printf("  ORIGINAL STRING: \"usgnaoeggAD9MIAD9345u\"\n");
            printf("  OPERATION: find_last_of(\"12934875ruhf\", 9)\n");
            fflush(stdout);
            String act = "usgnaoeggAD9MIAD9345u";
            size_t last = act.find_last_of("12934875ruhf", 9);
            if (last != 0) {
                printf("FAILED - INCORRECT INDEX PRODUCED\n");
                printf("  EXPECTED INDEX 0, BUT GOT INDEX %zu\n", last);
            }
            else {
                printf("  TEST FIND_LAST_OF 14 - SUCCESS\n");
                ++num_correct;
            }
        }
        // Test Find Last Of 15
        if (test_number == 71 || test_number == TEST_ALL || test_number == TEST_FLO) {
            printf("======================================== 71 ========================================");
            printf("\nRUNNING TEST FIND_LAST_OF 15 ...\n");
            printf("  ORIGINAL STRING: \"Which\"\n");
            printf("  OPERATION: find_last_of(\"hi\", 5)\n");
            fflush(stdout);
            String act = "Which";
            size_t last = act.find_last_of("hi", 5);
            if (last != 4) {
                printf("FAILED - INCORRECT INDEX PRODUCED\n");
                printf("  EXPECTED INDEX 4, BUT GOT INDEX %zu\n", last);
            }
            else {
                printf("  TEST FIND_LAST_OF 15 - SUCCESS\n");
                ++num_correct;
            }
        }

        if (test_number == TEST_FLO || test_number == TEST_ALL) {
            printf("====================================================================================\n");
            printf(" %d/15 TESTS PASSED\n", num_correct);
        }
        if (test_number == TEST_ALL) {
            printf("====================================================================================\n");
            printf(" PERFORMANCE SUMMARY:\n");
            printf(" ERASE TESTS PASSED: %d/11 (%.2f%%)\n", erase_correct, ((float)erase_correct / 11) * 100);
            printf(" INSERT TESTS PASSED: %d/11 (%.2f%%)\n", insert_correct, ((float)insert_correct / 11) * 100);
            printf(" REPLACE TESTS PASSED: %d/20 (%.2f%%)\n", replace_correct, ((float)replace_correct / 20) * 100);
            printf(" FIND_FIRST_OF TESTS PASSED: %d/14 (%.2f%%)\n", ffo_correct, ((float)ffo_correct / 14) * 100);
            printf(" FIND_LAST_OF TESTS PASSED: %d/15 (%.2f%%)\n", num_correct, ((float)num_correct / 15) * 100);

            num_correct += ffo_correct += replace_correct += insert_correct += erase_correct;

            printf(" TOTAL TESTS PASSED: %d/71 (%.2f%%)\n", num_correct, ((float)num_correct / 71) * 100);
            printf("====================================================================================\n");
            printf(" FINAL SCORE: %.2f/10\n", ((float)num_correct / 71) * 10);
        }
        return 0;
    }
    catch (const String_exception &s) {
        printf("FAILED\n\n YOUR PROGRAM THREW AN EXCEPTION FOR THIS TEST CASE ...\n");
        printf(" TEST FAILED ... MAKE SURE YOU AREN'T ACCESSING BAD MEMORY\n");
        printf(" PROGRAM EXITING WITH ERROR\n");
        return 1;
    }
    catch (const std::exception &e) {
        printf("FAILED\n\n YOUR PROGRAM THREW AN EXCEPTION FOR THIS TEST CASE ...\n");
        printf(" TEST FAILED ... MAKE SURE YOU AREN'T ACCESSING BAD MEMORY\n");
        printf(" PROGRAM EXITING WITH ERROR\n");
        return 1;
    }
}
