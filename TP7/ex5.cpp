// By: Gonçalo Leão

#include "exercises.h"

void knapsackBTRec(unsigned int values[], unsigned int weights[], unsigned int n, unsigned int curIndex, unsigned int maxWeight, unsigned int curValue, bool curItems[], unsigned int &maxValue, bool usedItems[]) {
    if (curIndex == n) {
        if (curValue > maxValue) {
            maxValue = curValue;
            for (unsigned int i = 0; i < n; i++) {
                usedItems[i] = curItems[i];
            }
        }
    }
    else {
        if (maxWeight >= weights[curIndex]) {
            curItems[curIndex] = true;
            knapsackBTRec(values, weights, n, curIndex + 1, maxWeight - weights[curIndex], curValue + values[curIndex], curItems, maxValue, usedItems);
            curItems[curIndex] = false; // Don't forget to undo the last choice point!
        }
        knapsackBTRec(values, weights, n, curIndex + 1, maxWeight, curValue, curItems, maxValue, usedItems);
    }
}

unsigned int knapsackBT(unsigned int values[], unsigned int weights[], unsigned int n, unsigned int maxWeight, bool usedItems[]) {
    unsigned int maxValue = 0;
    bool curItems[10000];
    for (unsigned int i = 0; i < n; i++) {
        curItems[i] = false;
    }
    knapsackBTRec(values, weights, n, 0, maxWeight, 0, curItems, maxValue, usedItems);
    return maxValue;
}

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP7_Ex5, testKnapsack_4items) {
    const unsigned int n = 4;
    {
        unsigned int values[n] = {10, 7, 11, 15};
        unsigned int weights[n] = {1, 2, 1, 3};
        bool usedItems[n];

        EXPECT_EQ(knapsackBT(values, weights, n, 5, usedItems), 36);
        EXPECT_EQ(usedItems[0], true);
        EXPECT_EQ(usedItems[1], false);
        EXPECT_EQ(usedItems[2], true);
        EXPECT_EQ(usedItems[3], true);
    }

    {
        unsigned int values[n] = {3, 4, 5, 6};
        unsigned int weights[n] = {2, 3, 4, 5};
        bool usedItems[n];

        EXPECT_EQ(knapsackBT(values, weights, n, 5, usedItems), 7);
        EXPECT_EQ(usedItems[0], true);
        EXPECT_EQ(usedItems[1], true);
        EXPECT_EQ(usedItems[2], false);
        EXPECT_EQ(usedItems[3], false);
    }
}

TEST(TP7_Ex5, testKnapsack_5items) {
    const unsigned int n = 5;
    {
        unsigned int values[n] = {1, 2, 5, 9, 4};
        unsigned int weights[n] = {2, 3, 3, 4, 6};
        bool usedItems[n];

        EXPECT_EQ(knapsackBT(values, weights, n, 10, usedItems), 16);
        EXPECT_EQ(usedItems[0], false);
        EXPECT_EQ(usedItems[1], true);
        EXPECT_EQ(usedItems[2], true);
        EXPECT_EQ(usedItems[3], true);
        EXPECT_EQ(usedItems[4], false);
    }
}