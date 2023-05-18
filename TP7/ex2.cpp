// By: Gonçalo Leão

#include "exercises.h"

bool subsetSumBTRec(unsigned int A[], unsigned int n, unsigned int curIndex, unsigned int T, unsigned int &subsetSize, unsigned int subset[]) {
    if (curIndex == n) {
        return (T == 0);
    }
    if (T >= A[curIndex]) {
        subset[subsetSize++] = A[curIndex];
        if(subsetSumBTRec(A, n, curIndex + 1, T - A[curIndex], subsetSize, subset)) {
            return true;
        }
        subsetSize--;
    }
    return subsetSumBTRec(A, n, curIndex + 1, T,subsetSize, subset);
}

bool subsetSumBT(unsigned int A[], unsigned int n, unsigned int T, unsigned int subset[], unsigned int &subsetSize) {
    subsetSize = 0;
    return subsetSumBTRec(A,n, 0, T, subsetSize, subset);
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
bool isSubset(const unsigned int A[], unsigned int nA, unsigned int B[], unsigned int nB) {
    for (unsigned int i = 0; i < nA; i++) {
        bool foundNum = false;
        for (unsigned int j = 0; j < nB; j++) {
            if (A[i] == B[j]) {
                foundNum = true;
                break;
            }
        }
        if (!foundNum)
            return false;
    }
    return true;
}

TEST(TP7_Ex2, testSubsetSum) {
    unsigned int A[] = {3, 34, 4, 12, 5, 2};
    unsigned int subset[6];
    unsigned int subsetSize;
    unsigned int T = 9;

    EXPECT_EQ(subsetSumBT(A,6, T, subset,subsetSize), true);
    EXPECT_EQ(sum(subset, subsetSize), T);
    EXPECT_EQ(isSubset(subset, subsetSize, A,6), true);

    T = 20;
    EXPECT_EQ(subsetSumBT(A,6, T, subset,subsetSize), true);
    EXPECT_EQ(sum(subset, subsetSize), T);
    EXPECT_EQ(isSubset(subset, subsetSize, A,6), true);

    T = 30;
    EXPECT_EQ(subsetSumBT(A,6, T, subset,subsetSize), false);
}