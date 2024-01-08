//
// Created by playfulCloud on 12/27/23.
//
#include "Menu.h"
#include <iostream>
#include <algorithm>
#include <filesystem>
#include <fstream>
#include "Menu.h"
#include "../Reader/FileReader.h"
#include "../../Algorithms/GeneticAlgorithmUtils/Population.h"


void Menu::displayMenu() {
    std::cout << "=========================== Effective algorithm design 2 ===========================" << std::endl;
    int gate = 0;

    while (gate != 4) {
        std::cout << "Choose what do you want to do: " << std::endl;
        std::cout << "1 - Read data from ATSP File" << std::endl;
        std::cout << "2 - Choose algorithm with read data" << std::endl;
        std::cout << "3 - Tests" << std::endl;
        std::cout << "4 - Exit" << std::endl;
        std::cin >> gate;
        switch (gate) {
            case 1:
                graph = fileReader->readFromFile();
                break;
            case 2:
                displayAlgorithms(graph);
                break;
            case 3:
                break;
        }
    }
}


void Menu::displayAlgorithms(std::vector<std::vector<int>> graph) {
    std::cout << "=========================== Algorithms menu ===========================" << std::endl;
    int gate = 0;
    while (gate != 5) {
        std::cout << "Choose what do you want to do: " << std::endl;
        std::cout << "1 - Genetic Algorithm - Crossover: Single-point / Mutation: Swap " << std::endl;
        std::cout << "2 - Genetic Algorithm - Crossover: Single-point / Mutation: Scramble " << std::endl;
        std::cout << "3 - Genetic Algorithm - Crossover: OX / Mutation: Swap " << std::endl;
        std::cout << "4 - Genetic Algorithm - Crossover: OX / Mutation: Scramble " << std::endl;
        std::cout << "5 - Choose by yourself with all parameters " << std::endl;
        std::cout << "6 - Exit" << std::endl;
        std::cin >> gate;
        switch (gate) {
            case 1:
                population = new Population(graph,10000,1,1,120,0.8,0.01,false,1,200);
                population->populate();
                population->geneticAlgorithm();
                break;
            case 2:
                population = new Population(graph,1000,1,2,120,0.8,0.01,false,1,200);
                population->populate();
                population->geneticAlgorithm();
                break;
            case 3:
                population = new Population(graph,5000,2,1,120,0.8,0.01,false,1,200);
                population->populate();
                population->geneticAlgorithm();
                break;
            case 4:
                population = new Population(graph,1000,2,2,120,0.8,0.01,false,1,200);
                population->populate();
                population->geneticAlgorithm();
                break;
            case 5:
                population = new Population(graph,1000,2,2,120,0.8,0.01,true,1,200);
                population->populate();
                population->geneticAlgorithm();
                break;
        }
    }
}





//void Menu::doAllGeometricTests(std::vector<std::vector<int>> graph,std::string fileToWrite, int type, int timeLimit) {
//    std::filesystem::path projectPath = std::filesystem::current_path();
//    projectPath = projectPath.parent_path(); // Uzyskanie ścieżki do katalogu nadrzędnego
//    std::string filePath = projectPath.string() + "\\PEA_2\\data\\" + fileToWrite;
//    std::cout << filePath;
//    std::ofstream fileStream(filePath);
//
//    for (int i = 0; i < 10; i++) {
//        if (fileStream.is_open()) {
//            simulatedAnnealing = new SimulatedAnnealing();
//            std::string answer = simulatedAnnealing->simulatedAnnealingForTesting(graph,80,0.99,1000 ,type,timeLimit);
//            fileStream << answer + "\n";
//            std::cout << "skonczony" << std::endl;
//            delete simulatedAnnealing;
//        } else {
//            std::cerr << "Error opening file: " << fileToWrite << std::endl;
//        }
//    }
//}


