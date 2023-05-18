// By: Gonçalo Leão

#include "exercises.h"

string dpMatrix[25][3][3];

char otherStack(char src, char dest) {
    if (src > dest)
        return otherStack(dest, src);
    else {
        if (src == 'A') {
            if(dest == 'B') return 'C';
            else return 'B';
        }
        else {
            return 'A';
        }
    }
}

string hanoiDP(unsigned int n, char src, char dest) {
    unsigned int srcInt = src - 'A';
    unsigned int destInt = dest - 'A';
    string &dpCell = dpMatrix[n-1][srcInt][destInt];
    if (!dpCell.empty())
        return dpCell;
    else {
        if (n > 1) {
            char aux = otherStack(src, dest);
            auto moves1 = hanoiDP(n - 1, src, aux);
            auto moves2 = hanoiDP(1, src, dest);
            auto moves3 = hanoiDP(n - 1, aux, dest);
            return dpCell = moves1 + "," + moves2 +  "," + moves3;
        }
        else return dpCell = string(1,src) + "->" + string(1,dest);
    }
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