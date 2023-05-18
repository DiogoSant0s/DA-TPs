#include "exercises.h"

#include <iostream>
#include <fstream>

int editDistance(string pattern, string text) {
    int n = (int) text.length();
    std::vector<int> d(n + 1);
    int old, neW;
    for (int j = 0; j <= n; j++)
        d[j] = j;
    int m = (int) pattern.length();
    for (int i = 1; i <= m; i++) {
        old = d[0];
        d[0] = i;
        for (int j = 1; j <= n; j++) {
            if (pattern[i-1] == text[j - 1])
                neW = old;
            else
                neW = 1 + min(min(old, d[j]), d[j - 1]);
            old = d[j];
            d[j] = neW;
        }
    }
    return d[n];
}

float numApproximateStringMatching(const string& filename, const string& toSearch) {
    ifstream is(filename.c_str());
    if (!is) {
        cout << "Error while opening the file." << endl;
        return 0;
    }
    string line1, word1;
    int num = 0, n = 0;
    while (!is.eof()) {
        getline(is, line1);
        stringstream s1(line1);
        while (!s1.eof()) {
            s1 >> word1;
            num += editDistance(toSearch, word1);
            n++;
        }
    }
    is.close();
    float res = (float) num / (float) n;
    return res;
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