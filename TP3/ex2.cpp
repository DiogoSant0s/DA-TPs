// By: Gonçalo Leão

#include "exercises.h"
#include <algorithm>

bool Activity::operator==(const Activity &a2) const {
    return start == a2.start && finish == a2.finish;
}

bool Activity::operator<(const Activity &a2) const {
    if (start == a2.start) return finish > a2.finish;
    return start < a2.start;
}

// Time: O(N*log(N)), Space: O(N), where N is the number of activities
std::vector<Activity> activitySelectionGR(std::vector<Activity> A) {
    std::vector<Activity> selected;
    std::sort(A.begin(), A.end());
    selected.push_back(*A.begin());
    for (auto it = A.begin(); it != A.end(); it++) {
        if (std::prev(it) -> finish > it -> start) continue;
        else selected.push_back(*it);
    }
    return selected;
}

/// TESTS ///
#include <gtest/gtest.h>
#include <gmock/gmock.h>

TEST(TP3_Ex2, activityScheduling) {
    std::vector<Activity> A = {{10,20}, {30, 35}, {5, 15}, {10, 40}, {40, 50}};
    std::vector<Activity> V = activitySelectionGR(A);
    EXPECT_EQ(V.size(), 3);
    EXPECT_THAT(V, ::testing::UnorderedElementsAre(Activity(5, 15), Activity(30, 35), Activity(40, 50)));
}