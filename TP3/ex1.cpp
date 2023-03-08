// By: Gonçalo Leão

#include "exercises.h"

bool changeMakingGR(const unsigned int C[], unsigned int Stock[], unsigned int n, unsigned int T, unsigned int usedCoins[]) {
    for (unsigned int i = 0; i < n; i++) {
        usedCoins[i] = 0;
    }
    unsigned int used = 0;
    while (used < T) {
        unsigned int tmp = used;
        for (unsigned int i = n - 1; true; i--) {
            if (Stock[i] == 0) continue;
            if (C[i] + used <= T) {
                used += C[i];
                Stock[i]--;
                usedCoins[i]++;
            }
            if (tmp != used) break;
        }
        if (tmp == used) return false;
    }
    return true;
}


/// TESTS ///
#include <gtest/gtest.h>

TEST(TP3_Ex1, hasGreedyChange) {
    unsigned int C[] = {1,2,5,10};
    unsigned int Stock[] = {1,1,1,1};
    unsigned int n = 4;
    unsigned int usedCoins[4];

    EXPECT_EQ(changeMakingGR(C, Stock, n, 13, usedCoins), true);
    EXPECT_EQ(usedCoins[0], 1);
    EXPECT_EQ(usedCoins[1], 1);
    EXPECT_EQ(usedCoins[2], 0);
    EXPECT_EQ(usedCoins[3], 1);

    unsigned int Stock2[] = {1,2,4,2};
    EXPECT_EQ(changeMakingGR(C, Stock2, n, 38, usedCoins), true);
    EXPECT_EQ(usedCoins[0], 1);
    EXPECT_EQ(usedCoins[1], 1);
    EXPECT_EQ(usedCoins[2], 3);
    EXPECT_EQ(usedCoins[3], 2);
}

TEST(TP3_Ex1, hasNoGreedyChange) {
    unsigned int C[] = {1,2,5,10};
    unsigned int Stock[] = {0,1,1,1};
    unsigned int n = 4;
    unsigned int usedCoins[4];

    EXPECT_EQ(changeMakingGR(C, Stock, n, 18, usedCoins), false);
    EXPECT_EQ(changeMakingGR(C, Stock, n, 1, usedCoins), false);
}