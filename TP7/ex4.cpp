// By: Gonçalo Leão

#include "exercises.h"

bool Activity::operator==(const Activity &a2) const {
    return start == a2.start && finish == a2.finish;
}

bool Activity::overlaps(const Activity &a2) const {
    return (start < a2.finish) && (a2.start < finish);
}

void activitySelectionBTRec(vector<Activity> A, const vector<Activity>& curSolution, vector<Activity> &bestSolution) {
    if (A.empty()) {
        if (curSolution.size() > bestSolution.size()) {
            bestSolution = curSolution;
        }
        return;
    }
    Activity nextAct = A.at(A.size() - 1);
    A.pop_back();
    bool overlapsOne = false;
    for (const auto act: curSolution) {
        if (nextAct.overlaps(act)) {
            overlapsOne = true;
            break;
        }
    }
    if (!overlapsOne) {
        vector<Activity> nextSolution = curSolution;
        nextSolution.push_back(nextAct);
        activitySelectionBTRec(A, nextSolution, bestSolution);
    }
    activitySelectionBTRec(A, curSolution, bestSolution);
}

vector<Activity> activitySelectionBT(vector<Activity> A) {
    vector<Activity> curSol;
    vector<Activity> V;
    activitySelectionBTRec(std::move(A), curSol, V);
    return V;
}

/// TESTS ///
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <utility>

bool noOverlaps(const vector<Activity> &acts) {
    for (unsigned int i = 0; i < acts.size(); i++) {
        Activity A1 = acts.at(i);
        for (unsigned int j = i + 1; j < acts.size(); j++) {
            Activity A2 = acts.at(j);
            if (A1.overlaps(A2))
                return false;
        }
    }
    return true;
}

TEST(TP7_Ex4, activityScheduling) {
    vector<Activity> A = {{10,20}, {30, 35}, {5, 15}, {10, 40}, {40, 50}};
    vector<Activity> V = activitySelectionBT(A);
    EXPECT_EQ(V.size(), 3 );
    EXPECT_EQ(noOverlaps(V), true);
}