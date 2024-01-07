//
// Created by Jakub on 06.01.2024.
//

#include <iostream>
#include "Chromosome.h"

Chromosome::Chromosome(std::vector<int>path,int pathValue) {
    this->path = path;
    this->pathValue = pathValue;
}

void Chromosome::displayChromosome() {
    std::cout << "path : ";
    for(int i = 0; i < path.size(); i++){
        if(i == path.size()-1){
            std::cout << path[i];
        }else{
            std::cout << path[i] << "-> ";
        }
    }
    std::cout << std::endl;
    std::cout << "path value: " << pathValue << std::endl;
}
