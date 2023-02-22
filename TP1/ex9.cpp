// By: Gonçalo Leão

#include "exercises.h"
#include "../data_structures/Heap.h"

int kthSmallest(unsigned int k, std::vector<int> v) {
    int res;
    Heap heap(std::move(v));
    for(unsigned int i = 1; i <= k; i++) {
        if (heap.empty()) {
            return -1;
        }
        res = heap.extractMin();
    }
    return res;
}

/// TESTS ///
#include <gtest/gtest.h>
#include <utility>

TEST(TP1_Ex9, test_kthSmallest) {
    auto A = {1, 2, 3, 4};
    EXPECT_EQ(kthSmallest(1,A), 1);
    EXPECT_EQ(kthSmallest(2,A), 2);
    EXPECT_EQ(kthSmallest(3,A), 3);
    EXPECT_EQ(kthSmallest(4,A), 4);

    auto a = {2, -1, -3, 4};
    EXPECT_EQ(kthSmallest(1,a), -3);
    EXPECT_EQ(kthSmallest(2,a), -1);
    EXPECT_EQ(kthSmallest(3,a), 2);
    EXPECT_EQ(kthSmallest(4,a), 4);

    auto B = {2, -1, 3, 4};
    EXPECT_EQ(kthSmallest(1,B), -1);
    EXPECT_EQ(kthSmallest(2,B), 2);
    EXPECT_EQ(kthSmallest(3,B), 3);
    EXPECT_EQ(kthSmallest(4,B), 4);

    auto b = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    EXPECT_EQ(kthSmallest(1,b), -5);
    EXPECT_EQ(kthSmallest(2,b), -3);
    EXPECT_EQ(kthSmallest(3,b), -2);
    EXPECT_EQ(kthSmallest(4,b), -1);
    EXPECT_EQ(kthSmallest(5,b),  1);
    EXPECT_EQ(kthSmallest(6,b),  1);
    EXPECT_EQ(kthSmallest(7,b),  2);
    EXPECT_EQ(kthSmallest(8,b),  4);
    EXPECT_EQ(kthSmallest(9,b),  4);
}