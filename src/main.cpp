//
// Created by sapai on 2020/12/7.
//

#include <iostream>

#include "cxxopts.hpp"
#include "Stopwatch.hpp"

#include "GeneticAlgorithm.h"
#include "TSP.h"
#include "TSPLIB.h"

using ga::GeneticAlgorithm;
using ga::Environment;
using ga::Chromosome;
using tsp::TSPLIB;
using tsp::TSP;

class TSPEnv : public Environment {
public:
    explicit TSPEnv(const TSPLIB &tsplib) : tsp_(tsplib) {}

    Chromosome genChromosome() override {
        return {std::move(randomGene(tsp_.getDimension()))};
    }

    void evalChromosome(Chromosome &chr) override {
        auto distance = tsp_.travel(chr.gene);
        chr.fitness = 1.0 / distance;
    }

    [[nodiscard]] int travel(const TSP::Route &route) const {
        return tsp_.travel(route);
    }

private:
    TSP tsp_;
};

int main(int argc, char *argv[]) {
    cxxopts::Options options("gatsp", "TSP solver using Genetic Algorithms");
    options.add_options()
            ("f,file", "TSPLIB Filename", cxxopts::value<std::string>())
            ("g,generations", "The amount of generation.", cxxopts::value<int>()->default_value("100"))
            ("p,populations", "Population Size", cxxopts::value<int>()->default_value("300"))
            ("m,mutation", "Mutation Probability", cxxopts::value<double>()->default_value("0.1"))
            ("c,crossover", "Crossover Probability", cxxopts::value<double>()->default_value("0.5"))
            ("e,elites", "Elite size", cxxopts::value<int>()->default_value("10"))
            ("v,verbose", "Verbose output", cxxopts::value<bool>()->default_value("false"))
            ("h,help", "Print usage");
    auto result = options.parse(argc, argv);
    if (!result.count("file") || result.count("help")) {
        std::cout << options.help() << std::endl;
        return 0;
    }

    std::string filename = result["file"].as<std::string>();
    int generations = result["generations"].as<int>();
    int populations = result["populations"].as<int>();
    double mutation_probability = result["mutation"].as<double>();
    double crossover_probability = result["crossover"].as<double>();
    int elites = result["elites"].as<int>();
    bool verbose = result["verbose"].as<bool>();

    TSPLIB tsplib;
    tsplib.load(filename);
    TSPEnv tsp_env(tsplib);
    GeneticAlgorithm ga(tsp_env, populations, mutation_probability, crossover_probability, elites);

    Stopwatch timer;
    timer.start();
    auto best = ga(generations, verbose);
    auto time = timer.elapsed();

    std::cout << "The best individual appears in generation " << best.first << ".\n";
    std::cout << best.second;
    std::cout << "The distance: " << tsp_env.travel(best.second.gene) << '\n';
    std::cout << "Time used: " << time << "ms\n";
}
