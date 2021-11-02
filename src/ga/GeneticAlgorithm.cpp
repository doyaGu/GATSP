//
// Created by sapai on 2020/12/8.
//

#include "GeneticAlgorithm.h"

#include <iostream>

#include <random.hpp>

namespace ga {
    using Random = effolkronium::random_static;

    // Basic workflow of a genetic algorithm:
    // Produce an initial population of individuals
    // Evaluate the fitness of all individuals
    // while termination condition not met do
    // Select fitter individuals for reproduction and produce new individuals
    // (crossover and mutation)
    // Evaluate fitness of new individuals
    // Generate a new population by inserting some new “good” individuals and
    // by erasing some old “bad” individuals
    // end while
    std::pair<int, Chromosome> GeneticAlgorithm::operator()(int generations, bool verbose) {
        if (verbose) {
            std::cout << "Total generations: " << generations << '\n';
            std::cout << "Population size: " << population_size_ << '\n';
            std::cout << "Elite size: " << elite_size_ << '\n';
            std::cout << "Mutation probability: " << mutation_probability_ << '\n';
        }

        createInitPopulation();
        int generation;
        int best_first_appear_generation = generations;
        for (generation = 0; generation < generations; ++generation) {
            auto last_best_fitness = getBest()->fitness;
            evolve();
            auto best = getBest();
            auto best_fitness = best->fitness;
            if (best_fitness > last_best_fitness) {
                best_first_appear_generation = generation + 1;
            }

            if (verbose) {
                std::cout << "Generation: " << generation + 1 << ", Current Best:\n" << *best << '\n';
            }
        }

        return {best_first_appear_generation, *getBest()};
    }

    void GeneticAlgorithm::calcFitness() {
        fitness_total_ = 0;
        for (auto &chr : population_) {
            env_.evalChromosome(chr);
            fitness_total_ += chr.fitness;
        }
    }

    void GeneticAlgorithm::sort() {
        std::sort(population_.begin(), population_.end(), [](const Chromosome &lhs, const Chromosome &rhs) {
            return lhs > rhs;
        });
    }

    Population::iterator GeneticAlgorithm::select() {
        auto choice = Random::get<double>(0, fitness_total_);
        for (auto chr_iter = population_.begin(); chr_iter != population_.end(); ++chr_iter) {
            if (choice < chr_iter->fitness) {
                return chr_iter;
            }
            choice -= chr_iter->fitness;
        }
        return population_.begin();
    }

    void GeneticAlgorithm::createInitPopulation() {
        for (int i = 0; i < population_size_; ++i) {
            population_.push_back(std::move(env_.genChromosome()));
        }
        calcFitness();
        sort();
    }

    void GeneticAlgorithm::printPopulation() {
        std::cout << "Population Size :" << population_size_ << "\nPopulation :\n";
        int i = 0;
        for (const auto &chr : population_) {
            std::cout << "No." << ++i << " : " << chr << '\n';
        }
    }

    Population::iterator GeneticAlgorithm::evolve() {
        for (int i = 0; i < elite_size_; ++i) {
                new_population_.push_back(population_[i]);
        }

        const auto n = (population_size_ - elite_size_) / 2;
        for (int i = 0; i < n; ++i) {
            auto p1_iter = select();
            auto p2_iter = select();

            std::pair<Chromosome, Chromosome> children;
            if (Random::get<bool>(crossover_probability_)) {
                children = p1_iter->crossover(*p2_iter);
            } else {
                children = {*p1_iter, *p2_iter};
            }

            if (Random::get<bool>(mutation_probability_)) {
                children.first.mutate();
            }

            if (Random::get<bool>(mutation_probability_)) {
                children.second.mutate();
            }

            new_population_.push_back(std::move(children.first));
            new_population_.push_back(std::move(children.second));
        }

        population_ = std::move(new_population_);
        new_population_.clear();
        calcFitness();
        sort();

        return getBest();
    }
}