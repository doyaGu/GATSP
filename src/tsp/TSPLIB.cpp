//
// Created by sapai on 2020/12/2.
//

#include "TSPLIB.h"

#include <sstream>
#include <type_traits>
#include <stdexcept>

#include "Type.h"

namespace tsp {
    template<typename E>
    using StringEnumList = std::vector<std::pair<std::string, E>>;

    template<typename E, typename std::enable_if_t<std::is_enum_v<E>, int> = 0>
    E strtoenum(const std::string &str, const StringEnumList<E> &list) {
        for (const auto &e : list) {
            const auto &s = e.first;
            if (str.size() != s.size()) {
                continue;
            }
            if (str == s) {
                return e.second;
            }
        }
        return E::UNKNOWN;
    }

    bool parseSpecification(const std::string &line, Specification &spec) {
        static const StringEnumList<EntryType> entries = {
                {"NAME",               EntryType::NAME},
                {"TYPE",               EntryType::TYPE},
                {"COMMENT",            EntryType::COMMENT},
                {"DIMENSION",          EntryType::DIMENSION},
                {"CAPACITY",           EntryType::CAPACITY},
                {"EDGE_WEIGHT_TYPE",   EntryType::EDGE_WEIGHT_TYPE},
                {"EDGE_WEIGHT_FORMAT", EntryType::EDGE_WEIGHT_FORMAT},
                {"EDGE_DATA_FORMAT",   EntryType::EDGE_DATA_FORMAT},
                {"NODE_COORD_TYPE",    EntryType::NODE_COORD_TYPE},
                {"DISPLAY_DATA_TYPE",  EntryType::DISPLAY_DATA_TYPE},
        };

        static const StringEnumList<Type> types = {
                {"TSP",  Type::TSP},
                {"ATSP", Type::ATSP},
                {"SOP",  Type::SOP},
                {"HCP",  Type::HCP},
                {"CVRP", Type::CVRP},
                {"TOUR", Type::TOUR},
        };

        static const StringEnumList<EdgeWeightType> edge_weight_types = {
                {"EXPLICIT", EdgeWeightType::EXPLICIT},
                {"EUC_2D",   EdgeWeightType::EUC_2D},
                {"EUC_3D",   EdgeWeightType::EUC_3D},
                {"MAX_2D",   EdgeWeightType::MAX_2D},
                {"MAX_3D",   EdgeWeightType::MAX_3D},
                {"MAN_2D",   EdgeWeightType::MAN_2D},
                {"MAN_3D",   EdgeWeightType::MAN_3D},
                {"CEIL_2D",  EdgeWeightType::CEIL_2D},
                {"GEO",      EdgeWeightType::GEO},
                {"ATT",      EdgeWeightType::ATT},
                {"XRAY1",    EdgeWeightType::XRAY1},
                {"XRAY2",    EdgeWeightType::XRAY2},
                {"SPECIAL",  EdgeWeightType::SPECIAL},
        };

        static const StringEnumList<EdgeWeightFormat> edge_weight_formats = {
                {"FUNCTION",       EdgeWeightFormat::FUNCTION},
                {"FULL_MATRIX",    EdgeWeightFormat::FULL_MATRIX},
                {"UPPER_ROW",      EdgeWeightFormat::UPPER_ROW},
                {"LOWER_ROW",      EdgeWeightFormat::LOWER_ROW},
                {"UPPER_DIAG_ROW", EdgeWeightFormat::UPPER_DIAG_ROW},
                {"LOWER_DIAG_ROW", EdgeWeightFormat::LOWER_DIAG_ROW},
                {"UPPER_COL",      EdgeWeightFormat::UPPER_COL},
                {"LOWER_COL",      EdgeWeightFormat::LOWER_COL},
                {"UPPER_DIAG_COL", EdgeWeightFormat::UPPER_DIAG_COL},
                {"LOWER_DIAG_COL", EdgeWeightFormat::LOWER_DIAG_COL},
        };

        static const StringEnumList<EdgeDataFormat> edge_data_formats = {
                {"EDGE_LIST", EdgeDataFormat::EDGE_LIST},
                {"ADJ_LIST",  EdgeDataFormat::ADJ_LIST},
        };

        static const StringEnumList<NodeCoordType> node_coord_types = {
                {"TWOD_COORDS",   NodeCoordType::TWOD_COORDS},
                {"THREED_COORDS", NodeCoordType::THREED_COORDS},
                {"NO_COORDS",     NodeCoordType::NO_COORDS},
        };

        static const StringEnumList<DisplayDataType> display_data_types = {
                {"COORD_DISPLAY", DisplayDataType::COORD_DISPLAY},
                {"TWOD_DISPLAY",  DisplayDataType::TWOD_DISPLAY},
                {"NO_DISPLAY",    DisplayDataType::NO_DISPLAY},
        };

        auto s = line.find(':');
        if (s == std::string::npos) {
            return false;
        }

        auto k = (line[s - 1] == ' ') ? s - 1 : s;
        auto v = (line[s + 1] == ' ') ? s + 2 : s + 1;
        auto keyword = line.substr(0, k);
        auto value = line.substr(v, line.size() - (v - 1));

        auto type = strtoenum<EntryType>(keyword, entries);
        switch (type) {
            case EntryType::NAME:
                spec.name = value;
                break;
            case EntryType::TYPE:
                spec.type = strtoenum<Type>(value, types);
                break;
            case EntryType::COMMENT:
                spec.comment.append(value);
                spec.comment.push_back('\n');
                break;
            case EntryType::DIMENSION:
                spec.dimension = std::stoi(value);
                break;
            case EntryType::CAPACITY:
                spec.capacity = std::stoi(value);
                break;
            case EntryType::EDGE_WEIGHT_TYPE:
                spec.edge_weight_type = strtoenum<EdgeWeightType>(value, edge_weight_types);
                break;
            case EntryType::EDGE_WEIGHT_FORMAT:
                spec.edge_weight_format = strtoenum<EdgeWeightFormat>(value, edge_weight_formats);
                break;
            case EntryType::EDGE_DATA_FORMAT:
                spec.edge_data_format = strtoenum<EdgeDataFormat>(value, edge_data_formats);
                break;
            case EntryType::NODE_COORD_TYPE: {
                auto node_coord_type = strtoenum<NodeCoordType>(value, node_coord_types);
                if (node_coord_type != NodeCoordType::UNKNOWN) {
                    spec.node_coord_type = node_coord_type;
                }
            }
                break;
            case EntryType::DISPLAY_DATA_TYPE: {
                auto display_data_type = strtoenum<DisplayDataType>(value, display_data_types);
                if (display_data_type != DisplayDataType::UNKNOWN) {
                    spec.display_data_type = display_data_type;
                }
            }
                break;
            case EntryType::END_OF_FILE:
                return true;
            case EntryType::UNKNOWN:
                return false;
        }

        if (!spec.comment.empty() && spec.comment.back() == '\n') {
            spec.comment.pop_back();
        }

        return true;
    }

    bool parseSection(const std::string &line, SectionType &section_type) {
        static const StringEnumList<SectionType> section_types = {
                {"NODE_COORD_SECTION",   SectionType::NODE_COORD_SECTION},
                {"DEPOT_SECTION",        SectionType::DEPOT_SECTION},
                {"DEMAND_SECTION",       SectionType::DEMAND_SECTION},
                {"EDGE_DATA_SECTION",    SectionType::EDGE_DATA_SECTION},
                {"FIXED_EDGES_SECTION",  SectionType::FIXED_EDGES_SECTION},
                {"DISPLAY_DATA_SECTION", SectionType::DISPLAY_DATA_SECTION},
                {"TOUR_SECTION",         SectionType::TOUR_SECTION},
                {"EDGE_WEIGHT_SECTION",  SectionType::EDGE_WEIGHT_SECTION},
        };

        section_type = strtoenum<SectionType>(line, section_types);
        return section_type != SectionType::UNKNOWN;
    }

    void parseNodeList(const std::vector<std::string> &lines, Section &section) {
        auto &data = std::get<NodeList>(section.data);
        data.reserve(lines.size());
        Node node{};
        for (const auto &line : lines) {
            std::stringstream iss(line);
            iss >> node.id >> node.x >> node.y;
            if (!iss.eof()) {
                iss >> node.z;
            }
            data.push_back(node);
        }
    }

    void parseEdgeList(const std::vector<std::string> &lines, Section &section) {
        auto &data = std::get<EdgeList>(section.data);
        data.reserve(lines.size());
        Edge edge{};
        for (const auto &line : lines) {
            std::stringstream iss(line);
            iss >> edge.u >> edge.v;
            data.push_back(edge);
        }
    }

    void parseDepots(const std::vector<std::string> &lines, Section &section) {
        auto &data = std::get<std::vector<int>>(section.data);
        data.reserve(lines.size());
        int id, value;
        for (const auto &line : lines) {
            std::stringstream iss(line);
            iss >> id;
            if (id == -1) { break; }
            iss >> value;
            data.push_back(value);
        }
    }

    void parseInts(const std::vector<std::string> &lines, Section &section) {
        auto &data = std::get<std::vector<int>>(section.data);
        data.reserve(lines.size());
        int value;
        for (const auto &line : lines) {
            std::stringstream iss(line);
            while (iss >> value) {
                if (value == -1) { break; }
                data.push_back(value);
            }
        }
    }

    void parseEdgeWeightMatrix(const std::vector<std::string> &lines, const Specification &spec, Section &section) {
        // TODO: To support to read EDGE_WEIGHT_SECTION.
        throw std::runtime_error("Reading EDGE_WEIGHT_SECTION is not supported.");
    }

    void parseData(const std::vector<std::string> &lines, const Specification &spec, Section &section) {
        switch (section.type) {
            case SectionType::NODE_COORD_SECTION:
                section.data = NodeList();
                parseNodeList(lines, section);
                break;
            case SectionType::DEPOT_SECTION:
                section.data = std::vector<int>();
                parseDepots(lines, section);
                break;
            case SectionType::DEMAND_SECTION:
                section.data = std::vector<int>();
                parseInts(lines, section);
                break;
            case SectionType::EDGE_DATA_SECTION:
                switch (spec.edge_data_format) {
                    case EdgeDataFormat::EDGE_LIST:
                        section.data = EdgeList();
                        parseEdgeList(lines, section);
                        break;
                    case EdgeDataFormat::ADJ_LIST:
                        section.data = std::vector<int>();
                        parseInts(lines, section);
                        break;
                    default:
                        break;
                }
                break;
            case SectionType::FIXED_EDGES_SECTION:
                section.data = EdgeList();
                parseEdgeList(lines, section);
                break;
            case SectionType::DISPLAY_DATA_SECTION:
                section.data = NodeList();
                parseNodeList(lines, section);
                break;
            case SectionType::TOUR_SECTION:
                section.data = std::vector<int>();
                parseInts(lines, section);
                break;
            case SectionType::EDGE_WEIGHT_SECTION:
                section.data = EdgeWeightMatrix();
                parseEdgeWeightMatrix(lines, spec, section);
                break;
            default:
                break;
        }
    }

    void TSPLIB::load(const std::string &name) {
        std::ifstream in(name);
        if (!in) {
            in.exceptions(std::ifstream::failbit);
        }

        std::string line;
        while (std::getline(in, line)) {
            if (line == "EOF") { break; }
            if (!parseSpecification(line, spec)) {
                Section section;
                if (parseSection(line, section.type)) {
                    std::vector<std::string> lines;
                    while (std::getline(in, line)) {
                           if (line.rfind("SECTION") != std::string::npos || line.rfind("EOF") != std::string::npos) {
                               break;
                           }
                        lines.push_back(line);
                    }
                    parseData(lines, spec, section);
                    sections.push_back(section);
                }
            }
        }
    }

    void TSPLIB::load(const char *name) {
        load(std::string(name));
    }
}
