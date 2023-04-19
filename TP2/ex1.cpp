// By: Gonçalo Leão

#include "exercises.h"

bool sum3(unsigned int T, unsigned int nums[3]) {
    for (unsigned int i = 1; i < T; i++) {
        for (unsigned int j = 1; j < i; j++) {
            if (int(T - i - j) > 0){
                nums[0] = i;
                nums[1] = j;
                nums[2] = T - i - j;
                return true;
            }
        }
    }
    return false;
}

/// TESTS ///
#include <gtest/gtest.h>

void compareSums(unsigned int selected[3], unsigned int expectedSum) {
    EXPECT_EQ(selected[0] + selected[1] + selected[2], expectedSum);
}

TEST(TP2_Ex1, 3sumExists) {
    unsigned int selected[3];
    unsigned int T = 10;
    EXPECT_EQ(sum3(T,selected), true);
    compareSums(selected,T);
    T = 18;
    EXPECT_EQ(sum3(T,selected), true);
    compareSums(selected,T);
}

TEST(TP2_Ex1, 3sumNotExists) {
    unsigned int selected[3];
    unsigned int T = 1;
    EXPECT_EQ(sum3(T,selected), false);
}