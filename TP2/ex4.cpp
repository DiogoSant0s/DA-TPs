// By: Gonçalo Leão

#include "exercises.h"

bool changeMakingBF(const unsigned int C[], const unsigned int Stock[], unsigned int n, unsigned int T, unsigned int usedCoins[]) {
    unsigned int curCandidate[20];
    for (unsigned int i = 0; i < n; i++) {
        curCandidate[i] = 0;
    }
    bool foundSol = false;
    unsigned int minCoins;
    while (true) {
        unsigned int totalValue = 0;
        unsigned int totalCoins = 0;
        for (unsigned int k = 0; k < n; k++) {
            totalValue += C[k]*curCandidate[k];
            totalCoins += curCandidate[k];
        }
        if (totalValue == T) {
            if (!foundSol || totalCoins < minCoins) {
                foundSol = true;
                minCoins = totalCoins;
                for (unsigned int k = 0; k < n; k++) {
                    usedCoins[k] = curCandidate[k];
                }
            }
        }
        unsigned int curIndex = 0;
        while (curCandidate[curIndex] == Stock[curIndex]) {
            curIndex++;
            if (curIndex == n) {
                break;
            }
        }
        if (curIndex == n) {
            break;
        }
        for (unsigned int i = 0; i < curIndex; i++) {
            curCandidate[i] = 0;
        }
        curCandidate[curIndex]++;
    }
    return foundSol;
}

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP2_Ex4, hasBFChangeCanonical) {
    unsigned int C[] = {1,2,5,10};
    unsigned int Stock[] = {1,1,1,1};
    unsigned int n = 4;
    unsigned int usedCoins[4];

    EXPECT_EQ(changeMakingBF(C,Stock, n,13, usedCoins), true);
    EXPECT_EQ(usedCoins[0], 1);
    EXPECT_EQ(usedCoins[1], 1);
    EXPECT_EQ(usedCoins[2], 0);
    EXPECT_EQ(usedCoins[3], 1);

    unsigned int Stock2[] = {1,2,4,2};
    EXPECT_EQ(changeMakingBF(C,Stock2, n,38, usedCoins), true);
    EXPECT_EQ(usedCoins[0], 1);
    EXPECT_EQ(usedCoins[1], 1);
    EXPECT_EQ(usedCoins[2], 3);
    EXPECT_EQ(usedCoins[3], 2);

    unsigned int Stock3[] = {10,2,4,2};
    EXPECT_EQ(changeMakingBF(C,Stock3, n,10, usedCoins), true);
    EXPECT_EQ(usedCoins[0], 0);
    EXPECT_EQ(usedCoins[1], 0);
    EXPECT_EQ(usedCoins[2], 0);
    EXPECT_EQ(usedCoins[3], 1);
}

TEST(TP2_Ex4, hasBFChangeNonCanonical) {
    unsigned int C[] = {1,4,5};
    unsigned int Stock[] = {2,2,1};
    unsigned int n = 3;
    unsigned int usedCoins[3];

    EXPECT_EQ(changeMakingBF(C, Stock, n,6, usedCoins), true);
    EXPECT_EQ(usedCoins[0], 1);
    EXPECT_EQ(usedCoins[1], 0);
    EXPECT_EQ(usedCoins[2], 1);

    EXPECT_EQ(changeMakingBF(C, Stock, n,8, usedCoins), true);
    EXPECT_EQ(usedCoins[0], 0);
    EXPECT_EQ(usedCoins[1], 2);
    EXPECT_EQ(usedCoins[2], 0);

    unsigned int Stock2[] = {8,2,1};
    EXPECT_EQ(changeMakingBF(C,Stock2, n,7, usedCoins), true);
    EXPECT_EQ(usedCoins[0], 2);
    EXPECT_EQ(usedCoins[1], 0);
    EXPECT_EQ(usedCoins[2], 1);

    EXPECT_EQ(changeMakingBF(C,Stock2, n,8, usedCoins), true);
    EXPECT_EQ(usedCoins[0], 0);
    EXPECT_EQ(usedCoins[1], 2);
    EXPECT_EQ(usedCoins[2], 0);
}

TEST(TP2_Ex4, hasNoBFChange) {
    unsigned int C[] = {1,2,5,10};
    unsigned int Stock[] = {0,1,1,1};
    unsigned int n = 4;
    unsigned int usedCoins[4];

    EXPECT_EQ(changeMakingBF(C, Stock, n,18,usedCoins), false);
    EXPECT_EQ(changeMakingBF(C, Stock, n,1,usedCoins), false);
}