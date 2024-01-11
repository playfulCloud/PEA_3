//
// Created by Jakub on 06.01.2024.
//

#include <random>
#include <algorithm>
#include <iostream>
#include <chrono>
#include <filesystem>
#include <fstream>
#include "Population.h"
#include "../../Utils/Answer.h"

Population::Population(std::vector<std::vector<int>> cites, int sizeOfPopulation, int crossOverType, int mutationType,
                       int time, double crossOverChance, double mutationChance, bool presentation, int condition,
                       int iterations) {
    if (presentation) {
        inputForPresentation(cites);
    } else {
        this->cites = cites;
        this->sizeOfPopulation = sizeOfPopulation;
        this->mutationType = mutationType;
        this->crossOverType = crossOverType;
        this->time = time;
        this->crossOverChance = crossOverChance;
        this->mutationChance = mutationChance;
        this->condition = condition;
        this->iterationsWithoutChange = iterations;
        this->iterationDuringGeneration = 0;
    }
}

void Population::inputForPresentation(const std::vector<std::vector<int>> &cites) {

    std::cout << "1 - number of iterations without change " << std::endl;
    std::cout << "2 - Time limit " << std::endl;
    std::cout << "Please enter the condition of stop " << std::endl;
    int inputCondition;
    std::cin >> inputCondition;
    this->condition = inputCondition;
    if (inputCondition == 1) {
        std::cout << "Please enter the number of iterations without change " << std::endl;
        int iterations;
        std::cin >> iterations;
        this->iterationsWithoutChange = iterations;
    } else {
        std::cout << "Please enter the time limit in s" << std::endl;
        int timeLimit;
        std::cin >> timeLimit;
        time = timeLimit;
    }


    Population::cites = cites;
    std::cout << "Please enter size of population: " << std::endl;
    int size;
    std::cin >> size;
    sizeOfPopulation = size;

    std::cout << "1 - Single-point " << std::endl;
    std::cout << "2 - OX " << std::endl;
    std::cout << "Please enter crossover type: " << std::endl;
    int crossType;
    std::cin >> crossType;
    crossOverType = crossType;

    std::cout << "Please enter crossover chance: " << std::endl;
    double crossChance;
    std::cin >> crossChance;
    crossOverChance = crossChance;

    std::cout << "1 - Swap " << std::endl;
    std::cout << "2 - Scrumble  " << std::endl;
    std::cout << "Please enter mutation type: " << std::endl;
    int mutType;
    std::cin >> mutType;
    mutationType = mutType;

    std::cout << "Please enter mutation chance: " << std::endl;
    double mutChance;
    std::cin >> mutChance;
    mutationChance = mutChance;
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
                int numberCandidate = generateRandomNumber(0, cites[0].size() - 1);
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
    if (check <= bound) {
        return true;
    }
    return false;
}

int Population::calculatePathCost(std::vector<int> path, std::vector<std::vector<int>> matrix) {
    int cost = 0;
    for (int i = 0; i < path.size() - 1; i++) {
        cost += matrix[path[i]][path[i + 1]];
    }
//    std::cout << "path cost: " << cost << std::endl;
    return cost;
}

std::vector<Chromosome> Population::populate() {
    for (int i = 0; i < sizeOfPopulation; i++) {
        Chromosome nextChromosome = generateRandomPath();
        wholePopulation.push_back(nextChromosome);
    }
    sortThePopulation();
    return wholePopulation;
}


void Population::sortThePopulation() {
    std::sort(wholePopulation.begin(), wholePopulation.end(), [](const Chromosome &a, const Chromosome &b) {
        return a.pathValue < b.pathValue;
    });
}


void Population::displayPopulation() {
    for (int i = 0; i < wholePopulation.size(); i++) {
//        displayPathOfChromosome(wholePopulation[i]);
        std::cout << i + 1 << ". with path value: " << wholePopulation[i].pathValue << std::endl;
    }
}

void Population::displayBestChromosomePath() {
    std::cout << "Best chromosome with value: " << wholePopulation[0].pathValue << std::endl;
}

void Population::displayPathOfChromosome(Chromosome chromosome) {
    for (int i = 0; i < chromosome.path.size(); i++) {
        std::cout << " -> " << chromosome.path[i];
    }
}

void Population::makeCrossOver(Chromosome best, Chromosome chooseToCrossing) {
    std::vector<int> firstPart;
    std::vector<int> secondPart;
    if (crossOverType == 1) {
        int indexOfSplit = generateRandomNumber(1, cites[0].size() - 1);


        for (int i = 1; i < cites[0].size() - 1; i++) {
            if (i < indexOfSplit) {
                firstPart.push_back(best.path[i]);
            } else {
                secondPart.push_back(best.path[i]);
            }
        }

        for (int i = 1; i < cites[0].size() - 1; i++) {
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
    } else {
        int size = best.path.size();
        firstPart = std::vector<int>(size - 2, -1);  // -1 oznacza puste miejsce
        secondPart = std::vector<int>(size - 2, -1);


        int lowerBound = generateRandomNumber(2, cites[0].size() / 2);
        int upperBound = generateRandomNumber((cites[0].size() / 2) + 1, cites[0].size() - 1);

        int space = ((size - 2) - (upperBound - lowerBound));

        firstPart = getChild(best, chooseToCrossing, firstPart, size, lowerBound, upperBound, space);
        secondPart = getChild(chooseToCrossing, best, secondPart, size, lowerBound, upperBound, space);


        Chromosome chooseToBestChromosome = *new Chromosome(secondPart, calculatePathCost(secondPart, cites));
        Chromosome bestToChooseChromosome = *new Chromosome(firstPart, calculatePathCost(firstPart, cites));

        wholePopulation.push_back(chooseToBestChromosome);
        wholePopulation.push_back(bestToChooseChromosome);
    }
}

std::vector<int> &
Population::getChild(const Chromosome &best, const Chromosome &chooseToCrossing, std::vector<int> &firstPart, int size,
                     int lowerBound, int upperBound, int space) const {
    std::vector<int> copyOfBest = best.path;
    copyOfBest.erase(copyOfBest.begin());
    copyOfBest.erase(copyOfBest.end() - 1);

    std::copy(copyOfBest.begin() + lowerBound, copyOfBest.begin() + upperBound, firstPart.begin() + lowerBound);

    int mainIterator = 0;
    int iteratorForParent = upperBound;
    int iteratorForChild = upperBound;
    while (mainIterator < space) {
        if (iteratorForParent == size - 1) {
            iteratorForParent = 1;
        }
        if (iteratorForChild == size - 2) {
            iteratorForChild = 0;
        }
        if (std::find(firstPart.begin(), firstPart.end(), chooseToCrossing.path[iteratorForParent]) ==
            firstPart.end()) {
            firstPart[iteratorForChild] = chooseToCrossing.path[iteratorForParent];
            iteratorForChild++;
            iteratorForParent++;
            mainIterator++;
        } else {
            iteratorForParent++;
        }
    }

    firstPart.insert(firstPart.begin(), 0);
    firstPart.push_back(0);
    return firstPart;
}

void Population::checkOXcorrect(Chromosome &best, Chromosome &chooseToCrossing, int lowerBound, int upperBound,
                                Chromosome &chooseToBestChromosome, Chromosome &bestToChooseChromosome) const {
    std::cout << "##################################" << std::endl;
    std::cout << "Lower bound: " << lowerBound << " UpperBound: " << upperBound << std::endl;
    best.displayChromosome();
    std::cout << "_____________________________________________" << std::endl;
    chooseToCrossing.displayChromosome();
    std::cout << "##################################" << std::endl;
    bestToChooseChromosome.displayChromosome();
    std::cout << "_____________________________________________" << std::endl;
    chooseToBestChromosome.displayChromosome();
    std::cout << "&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&" << std::endl;
}

std::vector<Chromosome> Population::makeCrossOverForPopulation() {
    for (int i = 0; i < sizeOfPopulation; i++) {
        if (checkPropForChromosome(this->crossOverChance)) {
            if (i == 0) {
                makeCrossOver(wholePopulation[1], wholePopulation[0]);
            } else {
                makeCrossOver(wholePopulation[0], wholePopulation[i]);
            }
        }
    }
    return wholePopulation;
}

std::vector<Chromosome> Population::makeMutationForPopulation() {
    int previousSize = wholePopulation.size();
    for (int i = 0; i < previousSize; i++) {
        if (checkPropForChromosome(this->mutationChance)) {
            makeMutation(wholePopulation[i]);
        }
    }
    return wholePopulation;
}

void Population::makeMutation(Chromosome toMutate) {
    if (mutationType == 1) {
        int firstIndexToSwap = generateRandomNumber(1, toMutate.path.size() - 2);
        int secondIndexToSwap = generateRandomNumber(1, toMutate.path.size() - 2);
        std::vector<int> mutatedPath = toMutate.path;
        std::swap(mutatedPath[firstIndexToSwap], mutatedPath[secondIndexToSwap]);
        int pathLength = calculatePathCost(mutatedPath, cites);
        Chromosome mutated = *new Chromosome(mutatedPath, pathLength);
        wholePopulation.push_back(mutated);
    } else {
        std::vector<int> indexesOfScramble;
        std::vector<int> valuesForScramble;
        std::vector<int> mutatedPath = toMutate.path;

        int howManyNumbersToScramble = generateRandomNumber(1, toMutate.path.size() - 2);

        for (int i = 0; i < howManyNumbersToScramble; i++) {
            int indexToScrumble = generateRandomNumber(1, toMutate.path.size() - 2);
            while (std::find(indexesOfScramble.begin(), indexesOfScramble.end(), indexToScrumble) !=
                   indexesOfScramble.end()) {
                indexToScrumble = generateRandomNumber(1, toMutate.path.size() - 2);
            }
            valuesForScramble.push_back(mutatedPath[indexToScrumble]);
            indexesOfScramble.push_back(indexToScrumble);
        }

        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(valuesForScramble.begin(), valuesForScramble.end(), g);

        for (int i = 0; i < indexesOfScramble.size(); i++) {
            mutatedPath[indexesOfScramble[i]] = valuesForScramble[i];
        }

        int pathLength = calculatePathCost(mutatedPath, cites);
        Chromosome mutated = *new Chromosome(mutatedPath, pathLength);
        wholePopulation.push_back(mutated);
    }
}

void Population::makeSelection() {
    sortThePopulation();
//    displayBestChromosomePath();
    int length = this->wholePopulation.size();
    if (length > sizeOfPopulation) {
        while (wholePopulation.size() != sizeOfPopulation) {
            int index = wholePopulation.size() - 1;
            wholePopulation.erase(wholePopulation.begin() + index);
        }
    }
}

bool
Population::conditionOfStop(std::chrono::high_resolution_clock::time_point startTime, int generation, int previousBest,
                            int actualBest) {
    if (condition == 1) {
//        std::cout << "Previous: " << previousBest << "Actual: " << actualBest << std::endl;
//        std::cout << "Iteration without change: " << iterationDuringGeneration << std::endl;
        if (previousBest == actualBest) {
            iterationDuringGeneration++;
            if (iterationDuringGeneration == iterationsWithoutChange) {
                return false;
            } else {
                return true;
            }
        } else {
            iterationDuringGeneration = 0;
            return true;
        }

    } else {
        return std::chrono::duration_cast<std::chrono::milliseconds>(
                std::chrono::high_resolution_clock::now() - startTime).count() < this->time * 1000;
    }

}
void Population::writeAnswerToFile(std::string filename){
    std::filesystem::path projectPath = std::filesystem::current_path();
    projectPath = projectPath.parent_path(); // Uzyskanie ścieżki do katalogu nadrzędnego
    std::string filePath = projectPath.string() + "\\PEA_3\\Data\\" + filename;
    std::ofstream fileStream(filePath, std::ios::app); // Open in append mode

    fileStream << this->answer->pathValue << ";" << this->answer->time << "\n";
}

void Population::writePathAndValueToFile(std::string filename){
    std::filesystem::path projectPath = std::filesystem::current_path();
    projectPath = projectPath.parent_path(); // Uzyskanie ścieżki do katalogu nadrzędnego
    std::string filePath = projectPath.string() + "\\PEA_3\\Data\\" + filename;
    std::ofstream fileStream(filePath, std::ios::app); // Open in append mode

    fileStream <<  "Path value: " << wholePopulation[0].pathValue << " with path: ";
    for(int i = 0; i < wholePopulation[0].path.size(); i++){
        fileStream << wholePopulation[0].path[i] << " ";
    }
    fileStream << "\n";
}



void Population::writeTimeAndBestPathTofile(std::string filename, Chromosome best,
                                            std::chrono::high_resolution_clock::time_point startTime) {

    updateAnswer(best, startTime);

    std::filesystem::path projectPath = std::filesystem::current_path();
    projectPath = projectPath.parent_path(); // Uzyskanie ścieżki do katalogu nadrzędnego
    std::string filePath = projectPath.string() + "\\PEA_3\\Data\\" + filename;
    std::ofstream fileStream(filePath, std::ios::app); // Open in append mode

    fileStream << best.pathValue << ";";
    fileStream << std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::high_resolution_clock::now() - startTime).count();
    fileStream << "\n";
}

void Population::updateAnswer(const Chromosome &best,std::chrono::high_resolution_clock::time_point startTime) {
    if(answer->time != std::chrono::duration_cast<std::chrono::milliseconds>(
                std::chrono::high_resolution_clock::now() - startTime).count() && answer->pathValue != best.pathValue){
        answer->time = std::chrono::duration_cast<std::chrono::milliseconds>(
                std::chrono::high_resolution_clock::now() - startTime).count();
        answer->pathValue = best.pathValue;
    }
}

void Population::writeTittleToFile(std::string filename) {
    std::filesystem::path projectPath = std::filesystem::current_path();
    projectPath = projectPath.parent_path(); // Uzyskanie ścieżki do katalogu nadrzędnego
    std::string filePath = projectPath.string() + "\\PEA_3\\Data\\" + filename;
    std::ofstream fileStream(filePath, std::ios::app); // Open in append mode
    std::string mutation;
    std::string crossover;
    switch (mutationType) {
        case 1:
            mutation = "SWAP";
            break;
        case 2:
            mutation = "SCRUMBLE";
            break;
    }
    switch (crossOverType) {
        case 1:
            crossover = "SINGLE-POINT";
            break;
        case 2:
            crossover = "OX";
            break;
    }
    fileStream << "############## Population: " << sizeOfPopulation <<" with number of cities "<< cites[0].size() <<" ############ Crossover: " << crossover << " with chance: " << crossOverChance << " Mutation: "
               << mutation << " with chance: " << mutationChance << " ############ \n";

}

void Population::writeEndingToFile(std::string filename) {
    std::filesystem::path projectPath = std::filesystem::current_path();
    projectPath = projectPath.parent_path(); // Uzyskanie ścieżki do katalogu nadrzędnego
    std::string filePath = projectPath.string() + "\\PEA_3\\Data\\" + filename;
    std::ofstream fileStream(filePath, std::ios::app); // Open in append mode
    std::string mutation;
    std::string crossover;
    fileStream << "####################################################### \n";
}


void Population::geneticAlgorithm() {
    populate();
    answer = new Answer();
    answer->pathValue = 0;
    answer->time = 69;
    auto startTime = std::chrono::high_resolution_clock::now();
    writeTimeAndBestPathTofile("pathInTime.txt", wholePopulation[0], startTime);

    auto lastSaveTime = std::chrono::high_resolution_clock::now();
    const long long saveInterval = time*100/24;

    int generation = 0;
    int previousBest = wholePopulation[0].pathValue;
    writeTittleToFile("pathInTime.txt");

    while (conditionOfStop(startTime, generation, previousBest, wholePopulation[0].pathValue)) {

        auto currentTime2 = std::chrono::high_resolution_clock::now();
        auto timeSinceLastSave = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime2 - lastSaveTime).count();

        if (timeSinceLastSave >= saveInterval) {
            writeTimeAndBestPathTofile("pathInTime.txt", wholePopulation[0], startTime);
            lastSaveTime = currentTime2;
        }

        previousBest = wholePopulation[0].pathValue;
        updateAnswer(wholePopulation[0],startTime);
        makeSelection();
        makeCrossOverForPopulation();
        makeMutationForPopulation();
    }
    writeAnswerToFile("times.txt");
    writePathAndValueToFile("allPaths.txt");
    wholePopulation[0].displayChromosome();
}

