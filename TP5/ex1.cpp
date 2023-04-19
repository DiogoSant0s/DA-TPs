// By: Gonçalo Leão

#include "exercises.h"

unsigned long factorialRecurs(unsigned long n) {
    if (n == 0) {
        return 1;
    }
    return n * factorialRecurs(n - 1);
}

unsigned long factorialDP(unsigned long n) {
    int res[100] = {0};
    res[0] = 1;
    for (int i = 1; i <= n; i++) {
        res[i] = i * res[i - 1];
    }
    return res[n];
}

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP5_Ex1, FactorialTest) {
    EXPECT_EQ(1, factorialRecurs(0));
    EXPECT_EQ(1, factorialRecurs(1));
    EXPECT_EQ(2, factorialRecurs(2));
    EXPECT_EQ(6, factorialRecurs(3));
    EXPECT_EQ(24, factorialRecurs(4));
    EXPECT_EQ(120, factorialRecurs(5));
    EXPECT_EQ(3628800, factorialRecurs(10));
    EXPECT_EQ(39916800, factorialRecurs(11));
    EXPECT_EQ(479001600, factorialRecurs(12));

    EXPECT_EQ(1, factorialDP(0));
    EXPECT_EQ(1, factorialDP(1));
    EXPECT_EQ(2, factorialDP(2));
    EXPECT_EQ(6, factorialDP(3));
    EXPECT_EQ(24, factorialDP(4));
    EXPECT_EQ(120, factorialDP(5));
    EXPECT_EQ(3628800, factorialDP(10));
    EXPECT_EQ(39916800, factorialDP(11));
    EXPECT_EQ(479001600, factorialDP(12));
}