cmake_minimum_required(VERSION 3.27)
project(PEA_3)

set(CMAKE_CXX_STANDARD 17)

add_executable(PEA_3 PEA_3/main.cpp
        PEA_3/Utils/Reader/FileReader.cpp
        PEA_3/Utils/Reader/FileReader.h
        PEA_3/Utils/Presentation/Menu.cpp
        PEA_3/Utils/Presentation/Menu.h
        PEA_3/Algorithms/GeneticAlgorithmUtils/Population.cpp
        PEA_3/Algorithms/GeneticAlgorithmUtils/Population.h
        PEA_3/Algorithms/GeneticAlgorithmUtils/Population.h
        PEA_3/Algorithms/GeneticAlgorithmUtils/Chromosome.cpp
        PEA_3/Algorithms/GeneticAlgorithmUtils/Chromosome.h
        PEA_3/Utils/Answer.cpp
        PEA_3/Utils/Answer.h
        PEA_3/Utils/Answer.h)
