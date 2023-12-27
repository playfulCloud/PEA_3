//
// Created by playfulCloud on 12/27/23.
//

#ifndef PEA_3_MENU_H
#define PEA_3_MENU_H


#include <vector>
#include "../Reader/FileReader.h"
class Menu {
public:
    void displayAlgorithms(std::vector<std::vector<int>> graph);
    FileReader *fileReader;
    std::vector<std::vector<int>> graph;
    void displayMenu();
};


#endif //PEA_3_MENU_H
