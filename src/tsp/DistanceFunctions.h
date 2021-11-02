//
// Created by sapai on 2020/12/7.
//

#ifndef GATSP_DISTANCEFUNCTIONS_H
#define GATSP_DISTANCEFUNCTIONS_H

#include <functional>

#include "Type.h"
#include "TSPLIB.h"

namespace tsp {
    using DistanceFunction = std::function<int(const Node &, const Node &)>;

    int distance_1(const Node &a, const Node &b);

    int distance_large(const Node &a, const Node &b);

    int distance_att(const Node &a, const Node &b);

    int distance_ceil_2d(const Node &a, const Node &b);

    int distance_ceil_3d(const Node &a, const Node &b);

    int distance_euc_2d(const Node &a, const Node &b);

    int distance_euc_3d(const Node &a, const Node &b);

    int distance_geo(const Node &a, const Node &b);

    int distance_geom(const Node &a, const Node &b);

    int distance_man_2d(const Node &a, const Node &b);

    int distance_man_3d(const Node &a, const Node &b);

    int distance_max_2d(const Node &a, const Node &b);

    int distance_max_3d(const Node &a, const Node &b);

    int distance_xray1(const Node &a, const Node &b);

    int distance_xray2(const Node &a, const Node &b);

    DistanceFunction getDistanceFunction(const TSPLIB &tsplib);
}

#endif //GATSP_DISTANCEFUNCTIONS_H
