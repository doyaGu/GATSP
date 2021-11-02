//
// Created by sapai on 2020/12/2.
//

#ifndef GA_ENVIRONMENT_H
#define GA_ENVIRONMENT_H

#include <string>
#include <memory>
#include <utility>
#include <mutex>
#include <forward_list>
#include <functional>
#include <stdexcept>

#include "Chromosome.h"

namespace ga {
    class Environment {
    public:
        Environment() = default;

        virtual ~Environment() = default;

        virtual Chromosome genChromosome() = 0;

        virtual void evalChromosome(Chromosome &chr) = 0;

    protected:
        static Chromosome::Gene randomGene(int length);
    };
}

#endif //GA_ENVIRONMENT_H
