// By: Gonçalo Leão

#include "exercises.h"

string hanoiDP(unsigned int n, char src, char dest) {
    // TODO
    return "";
}

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP5_Ex7, testHanoi_height4) {
    string moves = hanoiDP(4, 'A', 'B');
    EXPECT_EQ(count(moves.begin(),moves.end(),','), 14); // there are 15 moves
    EXPECT_EQ(moves,"A->C,A->B,C->B,A->C,B->A,B->C,A->C,A->B,C->B,C->A,B->A,C->B,A->C,A->B,C->B");
}

TEST(TP5_Ex7, testHanoi_height25) {
    string moves = hanoiDP(25, 'A', 'B');
    EXPECT_EQ(count(moves.begin(),moves.end(),','), pow(2,25) - 2); // there are 2^25 - 1 moves
}