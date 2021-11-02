//
// Created by sapai on 2020/12/8.
//

#include "Environment.h"

#include "random.hpp"

namespace ga {
    using Random = effolkronium::random_static;
    Chromosome::Gene Environment::randomGene(int length) {
        Chromosome::Gene gene;
        gene.reserve(length);
        for (int i = 0; i < length; ++i) {
            gene.push_back(i);
        }
        Random::shuffle(gene);
        return gene;
    }
}