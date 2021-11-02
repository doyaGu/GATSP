//
// Created by sapai on 2020/12/8.
//

#include <cstdint>

#include <gtest/gtest.h>

#include "TSPLIB.h"
#include "TSP.h"

namespace {
    using namespace tsp;
    TEST(TSP, ulysses16) {
        TSPLIB tsplib;
        EXPECT_NO_THROW(tsplib.load("data/ulysses16.tsp"));
        TSP tsp(tsplib);
        TSP::Route optimal = {0, 13, 12, 11, 6, 5, 14, 4, 10, 8, 9, 15, 2, 1, 3, 7};
//        TSP::Route optimal = {3, 1, 2, 15, 7, 0, 12, 11, 6, 5, 8, 9, 13, 14, 4, 10};
        EXPECT_EQ(tsp.travel(optimal), 6783);
    }
}