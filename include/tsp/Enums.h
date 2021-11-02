//
// Created by sapai on 2020/12/5.
//

#ifndef TSP_ENUMS_H
#define TSP_ENUMS_H

namespace tsp {
    enum class EntryType {
        NAME,
        TYPE,
        COMMENT,
        DIMENSION,
        CAPACITY,
        EDGE_WEIGHT_TYPE,
        EDGE_WEIGHT_FORMAT,
        EDGE_DATA_FORMAT,
        NODE_COORD_TYPE,
        DISPLAY_DATA_TYPE,
        END_OF_FILE,
        UNKNOWN
    };

    enum class SectionType {
        NODE_COORD_SECTION,
        DEPOT_SECTION,
        DEMAND_SECTION,
        EDGE_DATA_SECTION,
        FIXED_EDGES_SECTION,
        DISPLAY_DATA_SECTION,
        TOUR_SECTION,
        EDGE_WEIGHT_SECTION,
        UNKNOWN
    };

    enum class Type {
        TSP,
        ATSP,
        SOP,
        HCP,
        CVRP,
        TOUR,
        UNKNOWN,
    };

    enum class EdgeWeightType {
        EXPLICIT,
        EUC_2D,
        EUC_3D,
        MAX_2D,
        MAX_3D,
        MAN_2D,
        MAN_3D,
        CEIL_2D,
        GEO,
        ATT,
        XRAY1,
        XRAY2,
        SPECIAL,
        UNKNOWN
    };

    enum class EdgeWeightFormat {
        FUNCTION,
        FULL_MATRIX,
        UPPER_ROW,
        LOWER_ROW,
        UPPER_DIAG_ROW,
        LOWER_DIAG_ROW,
        UPPER_COL,
        LOWER_COL,
        UPPER_DIAG_COL,
        LOWER_DIAG_COL,
        UNKNOWN
    };

    enum class EdgeDataFormat {
        EDGE_LIST,
        ADJ_LIST,
        UNKNOWN
    };

    enum class NodeCoordType {
        TWOD_COORDS,
        THREED_COORDS,
        NO_COORDS,
        UNKNOWN
    };

    enum class DisplayDataType {
        COORD_DISPLAY,
        TWOD_DISPLAY,
        NO_DISPLAY,
        UNKNOWN
    };
}

#endif //TSP_ENUMS_H
