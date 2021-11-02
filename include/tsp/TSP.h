//
// Created by sapai on 2020/12/6.
//

#ifndef TSP_TSP_H
#define TSP_TSP_H

#include <array>
#include <string>
#include <vector>

#include "Enums.h"
#include "Type.h"

namespace tsp {
    struct TSPLIB;
    class TSP {
    public:
        using Route = std::vector<int>;

        explicit TSP(const TSPLIB &tsplib);

        [[nodiscard]] int getDimension() const {
            return dimension_;
        }

        [[nodiscard]] int travel(const Route &) const;

    private:
        int dimension_;
        EdgeWeightMatrix edge_weight_matrix_;
    };

}

#endif //TSP_TSP_H
