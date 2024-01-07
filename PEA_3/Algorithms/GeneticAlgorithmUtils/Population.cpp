//
// Created by Jakub on 06.01.2024.
//

#include <random>
#include <algorithm>
#include <iostream>
#include "Population.h"

Population::Population(std::vector<std::vector<int>> cites, int sizeOfPopulation) {
    this->cites = cites;
    this->sizeOfPopulation = sizeOfPopulation;
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
    for (int i = 0; i < path.size() - 1; i++) {
        cost += matrix[path[i]][path[i + 1]];
    }
    std::cout << "path cost: " << cost << std::endl;
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
        wholePopulation[i].displayChromosome();
    }
}

void Population::makeCrossOver(Chromosome best, Chromosome chooseToCrossing, int crossOverType) {
    std::vector<int> bestToChoose;
    std::vector<int> chooseToBest;
    if(crossOverType == 1){
        int indexOfSplit = generateRandomNumber(0,cites[0].size()-1);
        std::vector<int>firstPart;
        std::vector<int>secondPart;
        
        for(int i = 1; i < cites[0].size()-1; i++){
            if(i < indexOfSplit){
                firstPart.push_back(best.path[i]);
            }else{
                secondPart.push_back(best.path[i]);
            }
        }

    }else{

    }
}

std::vector<Chromosome> Population::makeCrossOverForPopulation(double crossOverChance) {

    for(int i = 0; i < wholePopulation.size(); i++){
        if(checkPropForChromosome(crossOverChance)){

            if(crossOverChance == 1){

            }else{

            }


        }
    }

    return wholePopulation;
}

std::vector<Chromosome> Population::makeMutationForPopulation(double mutationChance) {
    for(int i = 0; i < wholePopulation.size(); i++){

        if(checkPropForChromosome(mutationChance)){

            if(mutationChance == 1){

            }else{

            }

        }

    }

    return wholePopulation;
}



