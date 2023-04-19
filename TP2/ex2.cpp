// By: Gonçalo Leão

#include "exercises.h"

bool subsetSumBF(const unsigned int A[], unsigned int n, unsigned int T, unsigned int subset[], unsigned int &subsetSize) {
    bool curCandidate[20];
    for (unsigned int i = 0; i < n; i++) {
        curCandidate[i] = false;
    }
    while (true) {
        unsigned int sum = 0;
        for (unsigned int k = 0; k < n; k++) {
            sum += A[k] * (unsigned int) curCandidate[k];
        }
        if (sum == T) {
            subsetSize = 0;
            for (unsigned int k = 0; k < n; k++) {
                if (curCandidate[k]) {
                    subset[subsetSize++] = A[k];
                }
            }
            return true;
        }
        unsigned int curIndex = 0;
        while (curCandidate[curIndex]) {
            curIndex++;
            if (curIndex == n) {
                break;
            }
        }
        if (curIndex == n) {
            break;
        }
        for (unsigned int i = 0; i < curIndex; i++) {
            curCandidate[i] = false;
        }
        curCandidate[curIndex] = true;
    }
    return false;
}

/// TESTS ///
#include <gtest/gtest.h>

unsigned int sum(const unsigned int A[], unsigned int n) {
    unsigned int sum = 0;
    for (unsigned int i = 0; i < n; i++) {
        sum += A[i];
    }
    return sum;
}

// Checks if A is a subset of B
bool isSubset(const unsigned int A[], unsigned int nA, const unsigned int B[], unsigned int nB) {
    for (unsigned int i = 0; i < nA; i++) {
        bool foundNum = false;
        for (unsigned int j = 0; j < nB; j++) {
            if (A[i] == B[j]) {
                foundNum = true;
                break;
            }
        }
        if (!foundNum) return false;
    }
    return true;
}

TEST(TP2_Ex2, testSubsetSum) {
    unsigned int A[] = {3, 34, 4, 12, 5, 2};
    unsigned int subset[6];
    unsigned int subsetSize;
    unsigned int T = 9;
    EXPECT_EQ(subsetSumBF(A,6,T,subset,subsetSize), true);
    EXPECT_EQ(sum(subset, subsetSize), T);
    EXPECT_EQ(isSubset(subset, subsetSize, A,6), true);
    T = 20;
    EXPECT_EQ(subsetSumBF(A,6,T,subset,subsetSize), true);
    EXPECT_EQ(sum(subset, subsetSize), T);
    EXPECT_EQ(isSubset(subset, subsetSize, A,6), true);
    T = 30;
    EXPECT_EQ(subsetSumBF(A,6,T,subset,subsetSize), false);
}