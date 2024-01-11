//
// Created by playfulCloud on 12/27/23.
//

#ifndef PEA_3_FILEREADER_H
#define PEA_3_FILEREADER_H


#include <vector>
#include <string>

class FileReader {

public:
    std::vector<std::vector<int>> readFromFile();

    static void displayReadMatrix(std::vector<std::vector<int>> &adjacencyMatrix) ;

    std::vector<std::vector<int>> readFromFile2(std::__cxx11::basic_string<char> fileName);
};


#endif //PEA_3_FILEREADER_H
