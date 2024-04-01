/*
 * knapsack.h
 * University of Michigan, Ann Arbor
 * EECS 281 Lab 10 Written.
 * DO NOT SUBMIT TO GRADESCOPE.
 * If submitted, this file will be ignored.
 */

#ifndef KNAPSACK_H
#define KNAPSACK_H

#include <vector>

using namespace std;

int knapsack(int C, const std::vector<int>& value, const std::vector<int>& weight);


int KS(int W, vector<int> wt, vector<int> val);


//
//// Returns the value of maximum profit
//int knapSackRec(int W, int wt[], int val[], int index, int** dp)
//{
//    // base condition
//    if (index < 0) return 0;
//
//    if (dp[index][W] != -1)
//        return dp[index][W];
//
//    if (wt[index] > W) {
//
//        // Store the value of function call
//        // stack in table before return
//        dp[index][W] = knapSackRec(W, wt, val, index - 1, dp);
//        return dp[index][W];
//    }
//    else {
//        // Store value in a table before return
//        dp[index][W] = max(val[index]
//                           + knapSackRec(W - wt[index], wt, val,
//                                         index - 1, dp),
//                           knapSackRec(W, wt, val, index - 1, dp));
//
//        // Return value of table after storing
//        return dp[index][W];
//    }
//}
//
//int knapSack(int W, int wt[], int val[], int n)
//{
//    // double pointer to declare the
//    // table dynamically
//    int** dp;
//    dp = new int*[n];
//
//    // loop to create the table dynamically
//    for (int i = 0; i < n; i++)
//        dp[i] = new int[W + 1];
//
//    // loop to initially filled the
//    // table with -1
//    for (int i = 0; i < n; i++)
//        for (int j = 0; j < W + 1; j++)
//            dp[i][j] = -1;
//    return knapSackRec(W, wt, val, n - 1, dp);
//}

// C++ program for the above approach


//// Function to find the maximum profit
//int knapSack(int W, int wt[], int val[], int n)
//{
//    // Making and initializing dp array
//    int dp[W + 1];
//    memset(dp, 0, sizeof(dp));
//
//    for (int i = 1; i < n + 1; i++) {
//        for (int w = W; w >= 0; w--) {
//
//            if (wt[i - 1] <= w)
//
//                // Finding the maximum value
//                dp[w] = max(dp[w],
//                            dp[w - wt[i - 1]] + val[i - 1]);
//        }
//    }
//    // Returning the maximum value of knapsack
//    return dp[W];
//}
//
//// Driver code
//int main()
//{
//    int profit[] = { 60, 100, 120 };
//    int weight[] = { 10, 20, 30 };
//    int W = 50;
//    int n = sizeof(profit) / sizeof(profit[0]);
//    cout << knapSack(W, weight, profit, n);
//    return 0;
//}
//
//
//// Driver Code
//int main()
//{
//    int profit[] = { 60, 100, 120 };
//    int weight[] = { 10, 20, 30 };
//    int W = 50;
//    int n = sizeof(profit) / sizeof(profit[0]);
//    cout << knapSack(W, weight, profit, n);
//    return 0;
//}



#endif