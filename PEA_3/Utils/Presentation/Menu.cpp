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
                graph = fileReader->readFromFile2("ftv47.atsp");

                writeTittleToFile("times.txt",graph,47,1,1,180,0.8,0.01);
                doTests(graph,47,1,1,180,0.8,0.01);

                writeTittleToFile("times.txt",graph,47,1,2,180,0.8,0.01);
                doTests(graph,47,1,2,180,0.8,0.01);

                writeTittleToFile("times.txt",graph,47,2,1,180,0.8,0.01);
                doTests(graph,47,2,1,180,0.8,0.01);

                writeTittleToFile("times.txt",graph,47,2,2,180,0.8,0.01);
                doTests(graph,47,2,2,180,0.8,0.01);
//

                writeTittleToFile("times.txt",graph,500,1,1,180,0.8,0.01);
                doTests(graph,500,1,1,180,0.8,0.01);

                writeTittleToFile("times.txt",graph,500,1,2,180,0.8,0.01);
                doTests(graph,500,1,2,180,0.8,0.01);

                writeTittleToFile("times.txt",graph,500,2,1,180,0.8,0.01);
                doTests(graph,500,2,1,180,0.8,0.01);

                writeTittleToFile("times.txt",graph,500,2,2,180,0.8,0.01);
                doTests(graph,500,2,2,180,0.8,0.01);


                writeTittleToFile("times.txt",graph,2000,1,1,180,0.8,0.01);
                doTests(graph,2000,1,1,180,0.8,0.01);

                writeTittleToFile("times.txt",graph,2000,1,2,180,0.8,0.01);
                doTests(graph,2000,1,2,180,0.8,0.01);

                writeTittleToFile("times.txt",graph,2000,2,1,180,0.8,0.01);
                doTests(graph,2000,2,1,180,0.8,0.01);

                writeTittleToFile("times.txt",graph,2000,2,2,180,0.8,0.01);
                doTests(graph,2000,2,2,180,0.8,0.01);



                graph = fileReader->readFromFile2("ftv170.atsp");

                writeTittleToFile("times.txt",graph,47,1,1,300,0.8,0.01);
                doTests(graph,47,1,1,300,0.8,0.01);

                writeTittleToFile("times.txt",graph,47,1,2,300,0.8,0.01);
                doTests(graph,47,1,2,300,0.8,0.01);

                writeTittleToFile("times.txt",graph,47,2,1,300,0.8,0.01);
                doTests(graph,47,2,1,300,0.8,0.01);

                writeTittleToFile("times.txt",graph,47,2,2,300,0.8,0.01);
                doTests(graph,47,2,2,300,0.8,0.01);
//

                writeTittleToFile("times.txt",graph,500,1,1,300,0.8,0.01);
                doTests(graph,500,1,1,300,0.8,0.01);

                writeTittleToFile("times.txt",graph,500,1,2,300,0.8,0.01);
                doTests(graph,500,1,2,300,0.8,0.01);

                writeTittleToFile("times.txt",graph,500,2,1,300,0.8,0.01);
                doTests(graph,500,2,1,300,0.8,0.01);

                writeTittleToFile("times.txt",graph,500,2,2,300,0.8,0.01);
                doTests(graph,500,2,2,300,0.8,0.01);


                writeTittleToFile("times.txt",graph,2000,1,1,300,0.8,0.01);
                doTests(graph,2000,1,1,300,0.8,0.01);

                writeTittleToFile("times.txt",graph,2000,1,2,300,0.8,0.01);
                doTests(graph,2000,1,2,300,0.8,0.01);

                writeTittleToFile("times.txt",graph,2000,2,1,300,0.8,0.01);
                doTests(graph,2000,2,1,300,0.8,0.01);

                writeTittleToFile("times.txt",graph,2000,2,2,300,0.8,0.01);
                doTests(graph,2000,2,2,300,0.8,0.01);

                graph = fileReader->readFromFile2("rbg403.atsp");

                writeTittleToFile("times.txt",graph,47,1,1,420,0.8,0.01);
                doTests(graph,47,1,1,420,0.8,0.01);

                writeTittleToFile("times.txt",graph,47,1,2,420,0.8,0.01);
                doTests(graph,47,1,2,420,0.8,0.01);

                writeTittleToFile("times.txt",graph,47,2,1,420,0.8,0.01);
                doTests(graph,47,2,1,420,0.8,0.01);

                writeTittleToFile("times.txt",graph,47,2,2,420,0.8,0.01);
                doTests(graph,47,2,2,420,0.8,0.01);
//

                writeTittleToFile("times.txt",graph,500,1,1,420,0.8,0.01);
                doTests(graph,500,1,1,420,0.8,0.01);

                writeTittleToFile("times.txt",graph,500,1,2,420,0.8,0.01);
                doTests(graph,500,1,2,420,0.8,0.01);

                writeTittleToFile("times.txt",graph,500,2,1,420,0.8,0.01);
                doTests(graph,500,2,1,420,0.8,0.01);

                writeTittleToFile("times.txt",graph,500,2,2,420,0.8,0.01);
                doTests(graph,500,2,2,420,0.8,0.01);


                writeTittleToFile("times.txt",graph,2000,1,1,420,0.8,0.01);
                doTests(graph,2000,1,1,420,0.8,0.01);

                writeTittleToFile("times.txt",graph,2000,1,2,420,0.8,0.01);
                doTests(graph,2000,1,2,420,0.8,0.01);

                writeTittleToFile("times.txt",graph,2000,2,1,420,0.8,0.01);
                doTests(graph,2000,2,1,420,0.8,0.01);

                writeTittleToFile("times.txt",graph,2000,2,2,420,0.8,0.01);
                doTests(graph,2000,2,2,420,0.8,0.01);



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
                population = new Population(graph,1000,1,2,10,0.8,0.01,false,2,200);
                population->populate();
                population->geneticAlgorithm();
                break;
            case 3:
                population = new Population(graph,2000,2,1,120,0.8,0.01,false,1,200);
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





void Menu::doTests(std::vector<std::vector<int>> cites, int sizeOfPopulation, int crossOverType,int mutationType,int time,double crossOverChance,double mutationChance) {
    for (int i = 0; i < 10; i++) {
        population = new Population(cites,sizeOfPopulation,crossOverType,mutationType,time,crossOverChance,mutationChance,false,2,200);
        population->populate();
        population->geneticAlgorithm();
        delete population;
    }
}

void Menu::writeTittleToFile(std::string filename,std::vector<std::vector<int>> cites, int sizeOfPopulation, int crossOverType,int mutationType,int time,double crossOverChance,double mutationChance) {
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
    fileStream << "############## Population: " << sizeOfPopulation <<" with number of cities "<< cites[0].size() <<" ############ Crossover: " << crossover << " with chance: " << crossOverChance << "Mutation: "
               << mutation << " with chance: " << mutationChance << " ############ \n";

}


