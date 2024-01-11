//
// Created by playfulCloud on 12/27/23.
//

#ifndef PEA_3_MENU_H
#define PEA_3_MENU_H


#include <vector>
#include "../Reader/FileReader.h"
#include "../../Algorithms/GeneticAlgorithmUtils/Population.h"

class Menu {
public:
    void displayAlgorithms(std::vector<std::vector<int>> graph);
    FileReader *fileReader;
    Population *population;
    std::vector<std::vector<int>> graph;
    void displayMenu();

    void
    doTests(std::vector<std::vector<int>> cites, int sizeOfPopulation, int crossOverType, int mutationType, int time,
            double crossOverChance, double mutationChance);

    void
    writeTittleToFile(std::string filename, std::vector<std::vector<int>> cites, int sizeOfPopulation,
                      int crossOverType,
                      int mutationType, int time, double crossOverChance, double mutationChance);
};


#endif //PEA_3_MENU_H
