//
// Created by Jakub on 06.01.2024.
//

#include <random>
#include <algorithm>
#include <iostream>
#include <chrono>
#include "Population.h"

Population::Population(std::vector<std::vector<int>> cites, int sizeOfPopulation, int crossOverType,int mutationType,int time,double crossOverChance, double mutationChance) {
    this->cites = cites;
    this->sizeOfPopulation = sizeOfPopulation;
    this->mutationType = mutationType;
    this->crossOverType = crossOverType;
    this->time = time;
    this->crossOverChance = crossOverChance;
    this->mutationChance = mutationChance;
}

Chromosome Population::generateRandomPath() {
    std::vector<int> randomPathForChromosome;
    int pathCost = 0;
    for (int i = 0; i < this->cites[0].size() + 1; i++) {
        if (i == 0) {
            randomPathForChromosome.push_back(0);
        } else if (i == this->cites[0].size()) {
            randomPathForChromosome.push_back(0);
            pathCost += cites[randomPathForChromosome[i - 1]][0];
        } else {
            while (true) {
                int numberCandidate = generateRandomNumber(0, cites[0].size()-1);
                if (std::find(randomPathForChromosome.begin(), randomPathForChromosome.end(), numberCandidate) ==
                    randomPathForChromosome.end()) {
                    pathCost += cites[randomPathForChromosome[i - 1]][numberCandidate];
                    randomPathForChromosome.push_back(numberCandidate);
                    break;
                }
            }

        }
    }

    auto *chromosome = new Chromosome(randomPathForChromosome, pathCost);
    return *chromosome;
}


int Population::generateRandomNumber(int min, int max) {
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<> distr(min, max);

    return distr(gen);
}

bool Population::checkPropForChromosome(double value) {
    std::random_device rd;
    std::mt19937 gen(rd());
    int min = 0;
    int max = 100;
    std::uniform_int_distribution<> distr(min, max);
    int check = distr(gen);
    int bound = value * 100;
    if(check <= bound){
        return true;
    }
    return false;
}

int Population::calculatePathCost(std::vector<int> path, std::vector<std::vector<int>> matrix) {
    int cost = 0;
    for (int i = 0; i < path.size()-1 ; i++) {
        cost += matrix[path[i]][path[i + 1]];
    }
//    std::cout << "path cost: " << cost << std::endl;
    return cost;
}

std::vector<Chromosome> Population::populate() {
    for(int i = 0; i < sizeOfPopulation; i++){
        Chromosome nextChromosome = generateRandomPath();
       wholePopulation.push_back(nextChromosome);
    }
    sortThePopulation();
    return wholePopulation;
}


void Population::sortThePopulation(){
    std::sort(wholePopulation.begin(), wholePopulation.end(), [](const Chromosome &a, const Chromosome &b) {
        return a.pathValue < b.pathValue;
    });
}


void Population::displayPopulation(){
    for(int i = 0; i < wholePopulation.size(); i++){
        std::cout << i+1 << ". with path value: " << wholePopulation[i].pathValue << std::endl;
    }
}

void Population::displayBestChromosomePath(){
    std::cout << "Best chromosome with value: " << wholePopulation[0].pathValue << std::endl;
}

void Population::displayPathOfChromosome(Chromosome chromosome){
    for(int i = 0; i < chromosome.path.size(); i++){
        std::cout << " -> " <<chromosome.path[i];
    }
}

void Population::makeCrossOver(Chromosome best, Chromosome chooseToCrossing) {
    if (crossOverType == 1) {
        int indexOfSplit = generateRandomNumber(1, cites[0].size() - 1);
        std::vector<int> firstPart;
        std::vector<int> secondPart;

        for (int i = 1; i < cites[0].size() - 1; i++) {
            if (i < indexOfSplit) {
                firstPart.push_back(best.path[i]);
            } else {
                secondPart.push_back(best.path[i]);
            }
        }
        for (int i = 1; i < cites[0].size()-1; i++) {
            if (std::find(firstPart.begin(), firstPart.end(), chooseToCrossing.path[i]) ==
                firstPart.end()) {
                firstPart.push_back(chooseToCrossing.path[i]);
            }
            if (std::find(secondPart.begin(), secondPart.end(), chooseToCrossing.path[i]) == secondPart.end()) {
                secondPart.push_back(chooseToCrossing.path[i]);
            }
        }

        secondPart.insert(secondPart.begin(), 0);
        firstPart.insert(firstPart.begin(), 0);
        secondPart.push_back(0);
        firstPart.push_back(0);

        Chromosome chooseToBestChromosome = *new Chromosome(secondPart, calculatePathCost(secondPart, cites));
        Chromosome bestToChooseChromosome = *new Chromosome(firstPart, calculatePathCost(firstPart, cites));

        wholePopulation.push_back(chooseToBestChromosome);
        wholePopulation.push_back(bestToChooseChromosome);
    }else{

    }
}

std::vector<Chromosome> Population::makeCrossOverForPopulation() {
    for(int i = 0; i < sizeOfPopulation; i++){
        if(checkPropForChromosome(this->crossOverChance)){
            if(i == 0){
                makeCrossOver(wholePopulation[1],wholePopulation[0]);
            }else{
                makeCrossOver(wholePopulation[0],wholePopulation[i]);
            }
        }
    }
    return wholePopulation;
}

std::vector<Chromosome> Population::makeMutationForPopulation() {
    int previousSize = wholePopulation.size();
    for(int i = 0; i < previousSize; i++){
        if(checkPropForChromosome(this->mutationChance)){
            makeMutation(wholePopulation[i]);
        }
    }
    return wholePopulation;
}

void Population::makeMutation(Chromosome toMutate) {
    if(mutationType == 1){
        int firstIndexToSwap = generateRandomNumber(1,toMutate.path.size()-2);
        int secondIndexToSwap = generateRandomNumber(1,toMutate.path.size()-2);
        std::vector<int> mutatedPath = toMutate.path;
        std::swap(mutatedPath[firstIndexToSwap], mutatedPath[secondIndexToSwap]);
        int pathLength = calculatePathCost(mutatedPath,cites);
        Chromosome mutated = *new Chromosome(mutatedPath,pathLength);
        wholePopulation.push_back(mutated);
    }else{
        std::vector<int> indexesOfScramble;
        std::vector<int>valuesForScramble;
        std::vector<int> mutatedPath = toMutate.path;

        int howManyNumbersToScramble = generateRandomNumber(1, toMutate.path.size()-2);

        for(int i = 0; i < howManyNumbersToScramble; i++){
            int indexToScrumble =  generateRandomNumber(1, toMutate.path.size()-2);
            while (std::find(indexesOfScramble.begin(), indexesOfScramble.end(), indexToScrumble) !=
                indexesOfScramble.end()) {
                indexToScrumble =  generateRandomNumber(1, toMutate.path.size()-2);
            }
            valuesForScramble.push_back(mutatedPath[indexToScrumble]);
            indexesOfScramble.push_back(indexToScrumble);
        }

        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(valuesForScramble.begin(), valuesForScramble.end(), g);

        for(int i = 0; i < indexesOfScramble.size(); i++){
            mutatedPath[indexesOfScramble[i]] = valuesForScramble[i];
        }

        int pathLength = calculatePathCost(mutatedPath,cites);
        Chromosome mutated = *new Chromosome(mutatedPath,pathLength);
        wholePopulation.push_back(mutated);
    }
}

void Population::makeSelection() {
    sortThePopulation();
    displayBestChromosomePath();
    int length = this->wholePopulation.size();
    if(length > sizeOfPopulation){
        while(wholePopulation.size() != sizeOfPopulation){
            int index = wholePopulation.size()-1;
            wholePopulation.erase(wholePopulation.begin()+index);
        }
    }
}

void Population::geneticAlgorithm(){
    populate();
    auto startTime = std::chrono::high_resolution_clock::now();
    int timeLimitInMs = this->time*1000;
    while(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - startTime).count() < timeLimitInMs){
        makeSelection();
        makeCrossOverForPopulation();
        makeMutationForPopulation();
    }
}

