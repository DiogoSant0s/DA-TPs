// By: Gonçalo Leão

#include "exercises.h"

bool changeMakingBTRec(unsigned int C[], unsigned int Stock[], unsigned int n, unsigned int curIndex, unsigned int T, unsigned int curNCoins, unsigned int curCoins[], unsigned int &minCoins, unsigned int bestCoins[]) {
    if (curIndex == n) {
        if (T == 0) {
            if (curNCoins < minCoins) {
                minCoins = curNCoins;
                for (unsigned int i = 0; i < n; i++) {
                    bestCoins[i] = curCoins[i];
                }
            }
            return true;
        }
        return false;
    }
    bool foundSolWithCoin = false;
    if (curCoins[curIndex] < Stock[curIndex] && T >= C[curIndex]) {
        curCoins[curIndex]++;
        foundSolWithCoin = changeMakingBTRec(C, Stock, n, curIndex, T - C[curIndex], curNCoins + 1, curCoins,minCoins, bestCoins);
        curCoins[curIndex]--;
    }
    bool foundSolWithoutCoin = changeMakingBTRec(C, Stock, n, curIndex + 1, T, curNCoins, curCoins, minCoins, bestCoins);
    return foundSolWithCoin || foundSolWithoutCoin;
}

bool changeMakingBT(unsigned int C[], unsigned int Stock[], unsigned int n, unsigned int T, unsigned int usedCoins[]) {
    unsigned int minCoins = 0;
    unsigned int curCoins[10000];
    for (unsigned int i = 0; i < n; i++) {
        curCoins[i] = 0;
        minCoins += Stock[i];
    }
    return changeMakingBTRec(C, Stock, n, 0, T, 0, curCoins, minCoins, usedCoins);
}

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP7_Ex3, hasBTChangeCanonical) {
    unsigned int C[] = {1,2,5,10};
    unsigned int Stock[] = {1,1,1,1};
    unsigned int n = 4;
    unsigned int usedCoins[4];

    EXPECT_EQ(changeMakingBT(C, Stock, n, 13, usedCoins), true);
    EXPECT_EQ(usedCoins[0], 1);
    EXPECT_EQ(usedCoins[1], 1);
    EXPECT_EQ(usedCoins[2], 0);
    EXPECT_EQ(usedCoins[3], 1);

    unsigned int Stock2[] = {1,2,4,2};
    EXPECT_EQ(changeMakingBT(C, Stock2, n, 38, usedCoins), true);
    EXPECT_EQ(usedCoins[0], 1);
    EXPECT_EQ(usedCoins[1], 1);
    EXPECT_EQ(usedCoins[2], 3);
    EXPECT_EQ(usedCoins[3], 2);

    unsigned int Stock3[] = {10,2,4,2};
    EXPECT_EQ(changeMakingBT(C, Stock3, n, 10, usedCoins), true);
    EXPECT_EQ(usedCoins[0], 0);
    EXPECT_EQ(usedCoins[1], 0);
    EXPECT_EQ(usedCoins[2], 0);
    EXPECT_EQ(usedCoins[3], 1);
}

TEST(TP7_Ex3, hasBTChangeNonCanonical) {
    unsigned int C[] = {1,4,5};
    unsigned int Stock[] = {2,2,1};
    unsigned int n = 3;
    unsigned int usedCoins[3];

    EXPECT_EQ(changeMakingBT(C, Stock, n, 6, usedCoins), true);
    EXPECT_EQ(usedCoins[0], 1);
    EXPECT_EQ(usedCoins[1], 0);
    EXPECT_EQ(usedCoins[2], 1);

    EXPECT_EQ(changeMakingBT(C, Stock, n, 8, usedCoins), true);
    EXPECT_EQ(usedCoins[0], 0);
    EXPECT_EQ(usedCoins[1], 2);
    EXPECT_EQ(usedCoins[2], 0);

    unsigned int Stock2[] = {8,2,1};
    EXPECT_EQ(changeMakingBT(C, Stock2, n, 7, usedCoins), true);
    EXPECT_EQ(usedCoins[0], 2);
    EXPECT_EQ(usedCoins[1], 0);
    EXPECT_EQ(usedCoins[2], 1);

    EXPECT_EQ(changeMakingBT(C, Stock2, n, 8, usedCoins), true);
    EXPECT_EQ(usedCoins[0], 0);
    EXPECT_EQ(usedCoins[1], 2);
    EXPECT_EQ(usedCoins[2], 0);
}

TEST(TP7_Ex3, hasNoBTChange) {
    unsigned int C[] = {1,2,5,10};
    unsigned int Stock[] = {0,1,1,1};
    unsigned int n = 4;
    unsigned int usedCoins[4];

    EXPECT_EQ(changeMakingBT(C, Stock, n, 18, usedCoins), false);
    EXPECT_EQ(changeMakingBT(C, Stock, n, 1, usedCoins), false);
}