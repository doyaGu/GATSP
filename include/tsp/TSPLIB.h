//
// Created by sapai on 2020/12/5.
//

#ifndef TSP_TSPLIB_H
#define TSP_TSPLIB_H

#include <array>
#include <fstream>
#include <cstdint>
#include <utility>
#include <vector>
#include <memory>
#include <variant>

#include "Enums.h"
#include "Type.h"

namespace tsp {
    struct Specification {
        std::string name;
        Type type = Type::UNKNOWN;
        std::string comment;
        int dimension = 0;
        int capacity = 0;
        EdgeWeightType edge_weight_type = EdgeWeightType::UNKNOWN;
        EdgeWeightFormat edge_weight_format = EdgeWeightFormat::UNKNOWN;
        EdgeDataFormat edge_data_format = EdgeDataFormat::UNKNOWN;
        NodeCoordType node_coord_type = NodeCoordType::NO_COORDS;
        DisplayDataType display_data_type = DisplayDataType::NO_DISPLAY;
    };

    struct Section {
        using Data = std::variant<std::vector<int>, NodeList, EdgeList, EdgeWeightMatrix>;
        SectionType type = SectionType::UNKNOWN;
        Data data;
    };
    using Sections = std::vector<Section>;

    struct TSPLIB {
        Specification spec;
        Sections sections;
        void load(const std::string &name);
        void load(const char *name);
    };
}

#endif //TSP_TSPLIB_H
