//
// Created by sapai on 2020/12/4.
//

#include <gtest/gtest.h>

#include "TSPLIB.h"

namespace {
    using namespace tsp;
    TEST(TSPLIBTest, Load_a280) {
        TSPLIB tsplib;
        EXPECT_NO_THROW(tsplib.load("data/a280.tsp"));
        EXPECT_EQ(tsplib.spec.name, "a280");
        EXPECT_EQ(tsplib.spec.comment, "drilling problem (Ludwig)");
        EXPECT_EQ(tsplib.spec.type, Type::TSP);
        EXPECT_EQ(tsplib.spec.dimension, 280);
        EXPECT_EQ(tsplib.spec.edge_weight_type, EdgeWeightType::EUC_2D);
        EXPECT_EQ(tsplib.sections[0].type, SectionType::NODE_COORD_SECTION);
    }
}