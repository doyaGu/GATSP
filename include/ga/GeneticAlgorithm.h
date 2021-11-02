//
// Created by sapai on 2020/11/30.
//

#ifndef GA_GENETICALGORITHM_H
#define GA_GENETICALGORITHM_H

#include <iostream>
#include <utility>
#include <vector>
#include <stdexcept>

#include "Chromosome.h"
#include "Environment.h"

namespace ga {
    class GeneticAlgorithm {
    public:
        explicit GeneticAlgorithm(Environment &env,
                                  int population_size = 500,
                                  double mutation_probability = 0.5,
                                  double crossover_probability = 0.8,
                                  int elite_size = 12) :
                env_(env),
                population_size_(population_size),
                mutation_probability_(mutation_probability),
                crossover_probability_(crossover_probability),
                elite_size_(elite_size) {
            if (elite_size > population_size) {
                throw std::invalid_argument("Elite size must be smaller than population size.");
            } else if (population_size < 1) {
                throw std::invalid_argument("Population size must be positive.");
            } else if (elite_size < 1) {
                throw std::invalid_argument("Elite size must be positive.");
            }

            population_.reserve(population_size + population_size / 2);
            new_population_.reserve(population_size);
        }

        ~GeneticAlgorithm() = default;

        std::pair<int, Chromosome> operator()(int generations = 100, bool verbose = true);

    private:
        void calcFitness();

        void sort();

        Population::iterator select();

        Population::iterator getBest() {
            return population_.begin();
        }

        void createInitPopulation();

        void printPopulation();

        Population::iterator evolve();

        Environment &env_;
        int population_size_;
        double mutation_probability_;
        double crossover_probability_;
        int elite_size_;
        double fitness_total_ = 0.0;
        Population population_;
        Population new_population_;
    };
}

#endif //GA_GENETICALGORITHM_H
