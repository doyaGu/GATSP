//
// Created by sapai on 2020/12/7.
//

#include "DistanceFunctions.h"

#include <cstdint>
#include <cmath>

namespace tsp {
    int distance_1(const Node &a, const Node &b) {
        return 1;
    }

    int distance_large(const Node &a, const Node &b) {
        return INT32_MAX;
    }

    int distance_att(const Node &a, const Node &b) {
        double xd = a.x - b.x;
        double yd = a.y - b.y;

        return (int) std::ceil((std::sqrt((xd * xd + yd * yd) / 10.0)));
    }

    int distance_ceil_2d(const Node &a, const Node &b) {
        double xd = a.x - b.x;
        double yd = a.y - b.y;

        return (int) std::ceil(std::sqrt(xd * xd + yd * yd));
    }

    int distance_ceil_3d(const Node &a, const Node &b) {
        double xd = a.x - b.x;
        double yd = a.y - b.y;
        double zd = a.z - b.z;

        return (int) std::ceil(std::sqrt(xd * xd + yd * yd + zd * zd));
    }

    int distance_euc_2d(const Node &a, const Node &b) {
        double xd = a.x - b.x;
        double yd = a.y - b.y;

        return (int) (std::sqrt(xd * xd + yd * yd) + 0.5);
    }

    int distance_euc_3d(const Node &a, const Node &b) {
        double xd = a.x - b.x;
        double yd = a.y - b.y;
        double zd = a.z - b.z;

        return (int) (std::sqrt(xd * xd + yd * yd + zd * zd) + 0.5);
    }


    int distance_geo(const Node &a, const Node &b) {
        constexpr auto PI = 3.141592;
        constexpr auto RRR = 6378.388;

        int deg;
        double min;

        deg = (int) (a.x + 0.5);
        min = a.x - deg;
        double lat_a = PI * (deg + 5.0 * min / 3.0) / 180.0;

        deg = (int) (a.y + 0.5);
        min = a.y - deg;
        double long_a = PI * (deg + 5.0 * min / 3.0) / 180.0;

        deg = (int) (b.x + 0.5);
        min = b.x - deg;
        double lat_b = PI * (deg + 5.0 * min / 3.0) / 180.0;

        deg = (int) (b.y + 0.5);
        min = b.y - deg;
        double long_b = PI * (deg + 5.0 * min / 3.0) / 180.0;

        double q1 = std::cos(long_a - long_b);
        double q2 = std::cos(lat_a - lat_b);
        double q3 = std::cos(lat_a + lat_b);
        return (int) (RRR * std::acos(0.5 * ((1.0 + q1) * q2 - (1.0 - q1) * q3)) + 1.0);
    }


    int distance_geom(const Node &a, const Node &b) {
        const auto M_PI = 3.14159265358979323846264;
        const auto M_RRR = 6378388.0;

        double lat_a = M_PI * (a.x / 180.0);
        double lat_b = M_PI * (b.x / 180.0);
        double long_a = M_PI * (a.y / 180.0);
        double long_b = M_PI * (b.y / 180.0);

        double q1 = std::cos(lat_b) * std::sin(long_a - long_b);
        double q3 = std::sin((long_a - long_b) / 2.0);
        double q4 = std::cos((long_a - long_b) / 2.0);
        double q2 = std::sin(lat_a + lat_b) * q3 * q3 - std::sin(lat_a - lat_b) * q4 * q4;
        double q5 = std::cos(lat_a - lat_b) * q4 * q4 - std::cos(lat_a + lat_b) * q3 * q3;

        return (int) (M_RRR * std::atan2(std::sqrt(q1 * q1 + q2 * q2), q5) + 1.0);
    }

    int distance_man_2d(const Node &a, const Node &b) {
        return (int) (std::fabs(a.x - b.x) + std::fabs(a.y - b.y) + 0.5);
    }

    int distance_man_3d(const Node &a, const Node &b) {
        return (int) ((std::fabs(a.x - b.x) +
                       std::fabs(a.y - b.y) +
                       std::fabs(a.z - b.z)) + 0.5);
    }

    int distance_max_2d(const Node &a, const Node &b) {
        int dx = (int) (std::fabs(a.x - b.x) + 0.5);
        int dy = (int) (std::fabs(a.y - b.y) + 0.5);

        return dx > dy ? dx : dy;
    }

    int distance_max_3d(const Node &a, const Node &b) {
        int dx = (int) (std::fabs(a.x - b.x) + 0.5);
        int dy = (int) (std::fabs(a.y - b.y) + 0.5);
        int dz = (int) (std::fabs(a.z - b.z) + 0.5);

        if (dy > dx) dx = dy;
        return dx > dz ? dx : dz;
    }

    int distance_xray1(const Node &a, const Node &b) {
        double dist_p = std::min(std::fabs(a.x - b.x), std::fabs(std::fabs(a.x - b.x) - 360));
        double dist_c = std::fabs(a.y - b.y);
        double dist_t = std::fabs(a.z - b.z);
        double cost = std::max(dist_p, std::max(dist_c, dist_t));

        return (int) (100 * cost + 0.5);
    }

    int distance_xray2(const Node &a, const Node &b) {
        double dist_p = std::min(std::fabs(a.x - b.x), std::fabs(std::fabs(a.x - b.x) - 360));
        double dist_c = std::fabs(a.y - b.y);
        double dist_t = std::fabs(a.z - b.z);
        double cost = std::max(dist_p / 1.25, std::max(dist_c / 1.5, dist_t / 1.15));

        return (int) (100 * cost + 0.5);
    }

    DistanceFunction getDistanceFunction(const TSPLIB &tsplib) {
        switch (tsplib.spec.edge_weight_type) {
            case EdgeWeightType::EXPLICIT:
                return nullptr;
            case EdgeWeightType::EUC_2D:
                return distance_euc_2d;
            case EdgeWeightType::EUC_3D:
                return distance_euc_3d;
            case EdgeWeightType::MAX_2D:
                return distance_max_2d;
            case EdgeWeightType::MAX_3D:
                return distance_max_3d;
            case EdgeWeightType::MAN_2D:
                return distance_man_2d;
            case EdgeWeightType::MAN_3D:
                return distance_man_3d;
            case EdgeWeightType::CEIL_2D:
                return distance_ceil_2d;
            case EdgeWeightType::GEO:
                return distance_geo;
            case EdgeWeightType::ATT:
                return distance_att;
            case EdgeWeightType::XRAY1:
                return distance_xray1;
            case EdgeWeightType::XRAY2:
                return distance_xray2;
            default:
                return nullptr;
        }
    }
}