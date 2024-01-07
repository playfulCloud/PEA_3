//
// Created by Jakub on 06.01.2024.
//

#ifndef PEA_3_POPULATION_H
#define PEA_3_POPULATION_H


#include <vector>
#include "Chromosome.h"

class Population {
public:
    Population(std::vector<std::vector<int>> cites, int sizeOfPopulation);
    std::vector<Chromosome> populate();
    std::vector<Chromosome> wholePopulation;
    std::vector<std::vector<int>> cites;
    int sizeOfPopulation;
    Chromosome generateRandomPath();
    int calculatePathCost(std::vector<int> path, std::vector<std::vector<int>> matrix);
    void sortThePopulation();
    void displayPopulation();
    std::vector<Chromosome> makeCrossOverForPopulation(double crossOverChance);
    std::vector<Chromosome> makeMutationForPopulation(double mutationChance);
    bool checkPropForChromosome(double value);
    int generateRandomNumber(int min, int max);
    void makeCrossOver(Chromosome best, Chromosome chooseToCrossing,int crossOverType);
};


#endif //PEA_3_POPULATION_H
