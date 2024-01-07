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
    while (gate != 3) {
        std::cout << "Choose what do you want to do: " << std::endl;
        std::cout << "1 - First mutation method" << std::endl;
        std::cout << "2 - Second mutation method" << std::endl;
        std::cout << "3 - First crossbreeding method" << std::endl;
        std::cout << "4 - Second crossbreeding method" << std::endl;
        std::cout << "5 - Exit" << std::endl;
        std::cin >> gate;
        switch (gate) {
            case 1:
                population = new Population(graph,10);
                population->populate();
                population->displayPopulation();
//                population->sortThePopulation();
                break;
            case 2:
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


