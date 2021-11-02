//
// Created by sapai on 2020/12/6.
//

#ifndef TSP_DATA_H
#define TSP_DATA_H

#include <vector>

namespace tsp {
    struct Node {
        int id;
        double x;
        double y;
        double z;
    };

    struct Edge {
        int u;
        int v;
        int weight;
    };

    using NodeList = std::vector<Node>;
    using EdgeList = std::vector<Edge>;
    using EdgeWeightMatrix = std::vector<std::vector<int>>;
}

#endif //TSP_DATA_H
