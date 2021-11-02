//
// Created by sapai on 2020/12/6.
//

#include <algorithm>
#include <vector>
#include <stdexcept>

#include "TSP.h"
#include "TSPLIB.h"
#include "DistanceFunctions.h"

namespace tsp {
    TSP::TSP(const TSPLIB &tsplib) :
            dimension_(tsplib.spec.dimension),
            edge_weight_matrix_(dimension_, std::vector<int>(dimension_)) {
        if (tsplib.spec.type != Type::TSP) {
            throw std::runtime_error("Incompatible TSPLIB type.");
        }

        auto distance = getDistanceFunction(tsplib);
        for (const auto &section : tsplib.sections) {
            switch (section.type) {
                case SectionType::NODE_COORD_SECTION: {
                    const auto &nodes = std::get<std::vector<Node>>(section.data);
                    for (auto i = 0; i < dimension_; ++i) {
                        for (auto j = 0; j < dimension_; ++j) {
                            edge_weight_matrix_[i][j] = distance(nodes[i], nodes[j]);
                        }
                    }
                    break;
                }
                default:
                    throw std::runtime_error("Can not handle unsupported section type.");
                    break;
            }
        }

    }

    int TSP::travel(const TSP::Route &route) const {
        int distance = 0;
        int u, v;
        for (int n = 1; n < route.size(); ++n) {
            u = route[n - 1];
            v = route[n];
            distance += edge_weight_matrix_[u][v];
        }
        distance += edge_weight_matrix_[route.back()][route.front()];
        return distance;
    }
}