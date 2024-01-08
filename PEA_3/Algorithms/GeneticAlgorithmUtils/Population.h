//
// Created by Jakub on 06.01.2024.
//

#ifndef PEA_3_POPULATION_H
#define PEA_3_POPULATION_H


#include <vector>
#include "Chromosome.h"
#include <chrono>

class Population {
public:
    Population(std::vector<std::vector<int>> cites, int sizeOfPopulation, int crossOverType,int mutationType,int time,double crossOverChance,double mutationChance,bool presentation,int condition,int iterations);
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

    void checkOXcorrect(Chromosome &best, Chromosome &chooseToCrossing, int lowerBound, int upperBound,
                        Chromosome &chooseToBestChromosome, Chromosome &bestToChooseChromosome) const;

    std::vector<int> &
    getChild(const Chromosome &best, const Chromosome &chooseToCrossing, std::vector<int> &firstPart, int size,
             int lowerBound, int upperBound, int space) const;

    void inputForPresentation(const std::vector<std::vector<int>> &cites);

    int condition;
    int iterationsWithoutChange;
    int iterationDuringGeneration = 0;

    bool
    conditionOfStop(std::chrono::high_resolution_clock::time_point startTime, int generation,
                    int previousBest,
                    int actualBest);
};


#endif //PEA_3_POPULATION_H
