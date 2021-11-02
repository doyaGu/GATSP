//
// Created by sapai on 2020/11/30.
//

#ifndef GA_CHROMOSOME_H
#define GA_CHROMOSOME_H

#include <iostream>
#include <vector>

namespace ga {
    struct Chromosome;
    using Population = std::vector<Chromosome>;

    struct Chromosome {
        using Gene = std::vector<int>;

        Chromosome &mutate();

        std::pair<Chromosome, Chromosome> crossover(const Chromosome &chr);

        Gene gene;
        double fitness = 0.0;
    };

    inline bool operator==(const Chromosome &lhs, const Chromosome &rhs) {
        return lhs.gene == rhs.gene;
    }

    inline bool operator!=(const Chromosome &lhs, const Chromosome &rhs) {
        return !(lhs == rhs);
    }

    inline bool operator<(const Chromosome &lhs, const Chromosome &rhs) {
        return lhs.fitness < rhs.fitness;
    }

    inline bool operator>(const Chromosome &lhs, const Chromosome &rhs) {
        return rhs < lhs;
    }

    inline bool operator<=(const Chromosome &lhs, const Chromosome &rhs) {
        return !(rhs < lhs);
    }

    inline bool operator>=(const Chromosome &lhs, const Chromosome &rhs) {
        return !(lhs < rhs);
    }

    inline std::ostream &operator<<(std::ostream &os, const Chromosome &chr) {
        os << "Chromosome Gene :";
        for (const auto i : chr.gene) {
            os << ' ' << i;
        }
        os << "\nChromosome Fitness : " << chr.fitness << '\n';
        return os;
    }
}

#endif //GA_CHROMOSOME_H
