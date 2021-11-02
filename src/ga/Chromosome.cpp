//
// Created by sapai on 2020/11/30.
//

#include "Chromosome.h"

#include <algorithm>
#include <random.hpp>

namespace ga {
    using Random = effolkronium::random_static;

    Chromosome &Chromosome::mutate() {
        auto times = Random::get(0, static_cast<int>(gene.size()) - 1);
        for (auto i = 0; i < times; ++i) {
            auto left = Random::get(0, static_cast<int>(gene.size()) - 1);
            auto right = Random::get(0, static_cast<int>(gene.size()) - 1);
            if (left > right) { std::swap(left, right); }

            switch (Random::get(0, 1)) {
                case 0: // 交换操作
                    std::swap(gene[left], gene[right]);
                    break;
                case 1: // 逆转操作
                    std::reverse(gene.begin() + left, gene.begin() + right);
                    break;
                default:
                    break;
            }
        }
        return *this;
    }

    std::pair<Chromosome, Chromosome> Chromosome::crossover(const Chromosome &chr) {
        std::pair<Chromosome, Chromosome> children{*this, chr};
        auto start = Random::get(0, static_cast<int>(gene.size()) - 1);
        for (auto i = start; i < gene.size(); ++i) {
            int first, second;
            for (first = 0; children.first.gene[first] != children.second.gene[i]; ++first);
            for (second = 0; children.second.gene[second] != children.first.gene[i]; ++second);

            std::swap(children.first.gene[i], children.second.gene[i]);

            children.first.gene[first] = children.second.gene[i];
            children.second.gene[second] = children.first.gene[i];
        }
        return children;
    }
}