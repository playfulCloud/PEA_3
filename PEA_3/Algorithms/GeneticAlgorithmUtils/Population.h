//
// Created by Jakub on 06.01.2024.
//

#ifndef PEA_3_POPULATION_H
#define PEA_3_POPULATION_H


#include <vector>
#include "Chromosome.h"

class Population {
public:
    Population(std::vector<std::vector<int>> cites, int sizeOfPopulation, int crossOverType,int mutationType,int time,double crossOverChance,double mutationChance);
    std::vector<Chromosome> populate();
    std::vector<Chromosome> wholePopulation;
    std::vector<std::vector<int>> cites;
    int sizeOfPopulation;
    int calculatePathCost(std::vector<int> path, std::vector<std::vector<int>> matrix);
    Chromosome generateRandomPath();
    void sortThePopulation();
    void displayPopulation();
    std::vector<Chromosome> makeCrossOverForPopulation();
    std::vector<Chromosome> makeMutationForPopulation();
    bool checkPropForChromosome(double value);
    int generateRandomNumber(int min, int max);
    int crossOverType;
    int mutationType;
    double crossOverChance;
    double mutationChance;
    int time;
    void makeCrossOver(Chromosome best, Chromosome chooseToCrossing);
    void makeMutation(Chromosome toMutate);
    void makeSelection();

    void geneticAlgorithm();

    void displayBestChromosomePath();

    void displayPathOfChromosome(Chromosome chromosome);
};


#endif //PEA_3_POPULATION_H
