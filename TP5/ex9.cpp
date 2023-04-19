#include "exercises.h"

#include <iostream>
#include <fstream>
#include <sstream>

int editDistance(string pattern, string text) {

    return 0;
}

float numApproximateStringMatching(string filename, string toSearch) {
    int wordCounter = 0;
    int res[1000] = {0};

    return 0.0;
}

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP5_Ex9, testEditDistance) {
    EXPECT_EQ(3, editDistance("abcdefghijkl", "bcdeffghixkl"));
    EXPECT_EQ(3, editDistance("bcdeffghixkl", "abcdefghijkl"));

    EXPECT_EQ(1, editDistance("", "b"));
    EXPECT_EQ(1, editDistance("a", ""));
    EXPECT_EQ(1, editDistance("a", "b"));
    EXPECT_EQ(0, editDistance("", ""));
    EXPECT_EQ(0, editDistance("a", "a"));
}

TEST(TP5_Ex9, testNumApproximateStringMatching) {
    const float delta = 0.01;

    const float expected1 = 7.76;
    float dist1 = numApproximateStringMatching("../TP5/text1.txt", "estrutur");
    ASSERT_LE(expected1 - delta, dist1);
    ASSERT_GE(expected1 + delta, dist1);

    const float expected2 = 7.49;
    float dist2 = numApproximateStringMatching("../TP5/text2.txt", "estrutur");
    ASSERT_LE(expected2 - delta, dist2);
    ASSERT_GE(expected2 + delta, dist2);
}