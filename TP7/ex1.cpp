#include "exercises.h"

Labyrinth::Labyrinth(int values[10][10]) {
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
            labyrinth[i][j] = values[i][j];
}

#include <iostream>

void Labyrinth::print() const {
    for (const auto& i : labyrinth) {
        for (int j : i) {
            cout << j << " ";
        }
        cout << endl;
    }
}

bool Labyrinth::findGoal(int x, int y) {
    initializeVisited();
    return findGoalRec(x, y);
}

void Labyrinth::initializeVisited() {
    for (auto & i : visited)
        for (bool & j : i)
            j = false;
}

bool Labyrinth::findGoalRec(int x, int y) {
    if (labyrinth[y][x] == MAZE_WALL || visited[y][x]) {
        return false;
    }
    visited[y][x] = true;
    if (labyrinth[y][x] == MAZE_EXIT) {
        cout << ": Reached the goal!" << endl;
        return true;
    }
    return findGoalRec(x - 1, y) || findGoalRec(x + 1, y) || findGoalRec(x, y - 1) || findGoalRec(x, y + 1);
}

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP7_Ex1, testLabyrinthPossible) {
    int lab1[10][10] = {
        {0,0,0,0,0,0,0,0,0,0},
        {0,1,1,1,1,1,0,1,0,0},
        {0,1,0,0,0,1,0,1,0,0},
        {0,1,1,0,1,1,1,1,1,0},
        {0,1,0,0,0,1,0,0,0,0},
        {0,1,0,1,0,1,1,1,1,0},
        {0,1,1,1,0,0,1,0,1,0},
        {0,1,0,0,0,0,1,0,1,0},
        {0,1,1,1,0,0,1,2,0,0},
        {0,0,0,0,0,0,0,0,0,0}
    };
    Labyrinth l1(lab1);
    EXPECT_EQ(l1.findGoal(1,1), true);
}

TEST(TP7_Ex1, testLabyrinthImpossible) {
    int lab1[10][10] = {
            {0,0,0,0,0,0,0,0,0,0},
            {0,1,1,1,1,1,0,1,0,0},
            {0,1,0,0,0,1,0,1,0,0},
            {0,1,1,0,1,1,1,1,1,0},
            {0,1,0,0,0,1,0,0,0,0},
            {0,1,0,1,0,1,1,1,1,0},
            {0,1,1,1,0,0,1,0,1,0},
            {0,1,0,0,0,0,1,0,1,0},
            {0,1,1,1,0,0,0,2,0,0},
            {0,0,0,0,0,0,0,0,0,0}
    };
    Labyrinth l1(lab1);
    EXPECT_EQ(l1.findGoal(1,1), false);
}
