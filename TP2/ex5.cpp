#include "exercises.h"

Result nearestPointsBF(vector<Point> &vp) {
    Result res;
    for (unsigned i = 0; i < vp.size(); i++) {
        Point p = vp[i];
        for (unsigned j = i + 1; j < vp.size(); j++) {
            double dist = p.distance(vp[j]);
            if (dist < res.dmin)
                res = Result(dist, p, vp[j]);
        }
    }
    return res;
}

/// TESTS ///
#include "gtest/gtest.h"

TEST(TP2_Ex5, testNPBF) {
    testNearestPoints(nearestPointsBF, "Brute force");
}