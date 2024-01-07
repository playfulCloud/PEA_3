//
// Created by Jakub on 06.01.2024.
//

#ifndef PEA_3_CHROMOSOME_H
#define PEA_3_CHROMOSOME_H


#include <vector>

class Chromosome {
public:
    void displayChromosome();
    Chromosome(std::vector<int>path, int pathValue);
    std::vector<int> path;
    int pathValue;
};


#endif //PEA_3_CHROMOSOME_H
