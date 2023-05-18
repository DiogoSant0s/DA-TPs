// By: Gonçalo Leão

#include "exercises.h"

unsigned int knapsackDP(const unsigned int values[], const unsigned int weights[], unsigned int n, unsigned int maxWeight, bool usedItems[]) {
    unsigned int maxValue[100][101];
    for (unsigned int k = 0; k <= maxWeight; k++) {
        maxValue[0][k] = (k >= weights[0]) ? values[0] : 0;
    }
    for (unsigned int i = 1; i <= n; i++) {
        maxValue[i][0] = 0;
    }
    for (unsigned int i = 1; i < n; i++) {
        for (unsigned int k = 1; k <= maxWeight; k++) {
            if (k < weights[i]) {
                maxValue[i][k] = maxValue[i - 1][k];
            }
            else {
                unsigned int valueUsingItemI = maxValue[i - 1][k - weights[i]] + values[i];
                if (valueUsingItemI > maxValue[i - 1][k]) {
                    maxValue[i][k] = valueUsingItemI;
                }
                else {
                    maxValue[i][k] = maxValue[i - 1][k];
                }
            }
        }
    }
    for (unsigned int i = 0; i < n; i++) {
        usedItems[i] = false;
    }
    unsigned int remainingWeight = maxWeight;
    unsigned int curItem = n - 1;
    for (unsigned int i = n - 1; i > 0; i--) {
        if (remainingWeight == 0)
            break;
        if (maxValue[i][remainingWeight] != maxValue[i-1][remainingWeight]) {
            usedItems[i] = true;
            remainingWeight -= weights[i];
            curItem--;
        }
    }
    if (remainingWeight > 0) {
        usedItems[0] = true;
    }
    return maxValue[n-1][maxWeight];
}

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP5_Ex8, testKnapsack_4items) {
    const unsigned int n = 4;
    {
        unsigned int values[n] = {10, 7, 11, 15};
        unsigned int weights[n] = {1, 2, 1, 3};
        bool usedItems[n];

        EXPECT_EQ(knapsackDP(values, weights, n, 5, usedItems), 36);
        EXPECT_EQ(usedItems[0], true);
        EXPECT_EQ(usedItems[1], false);
        EXPECT_EQ(usedItems[2], true);
        EXPECT_EQ(usedItems[3], true);
    }

    {
        unsigned int values[n] = {3, 4, 5, 6};
        unsigned int weights[n] = {2, 3, 4, 5};
        bool usedItems[n];

        EXPECT_EQ(knapsackDP(values, weights, n, 5, usedItems), 7);
        EXPECT_EQ(usedItems[0], true);
        EXPECT_EQ(usedItems[1], true);
        EXPECT_EQ(usedItems[2], false);
        EXPECT_EQ(usedItems[3], false);
    }
}

TEST(TP5_Ex8, testKnapsack_5items) {
    const unsigned int n = 5;
    {
        unsigned int values[n] = {1, 2, 5, 9, 4};
        unsigned int weights[n] = {2, 3, 3, 4, 6};
        bool usedItems[n];

        EXPECT_EQ(knapsackDP(values, weights, n, 10, usedItems), 16);
        EXPECT_EQ(usedItems[0], false);
        EXPECT_EQ(usedItems[1], true);
        EXPECT_EQ(usedItems[2], true);
        EXPECT_EQ(usedItems[3], true);
        EXPECT_EQ(usedItems[4], false);
    }
}