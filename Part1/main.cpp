#include <iostream>
#include <fstream>
#include <regex>
#include <iterator>
#include <vector>
#include <cstdio>

int main() {
    std::ifstream infile;
    infile.open("../input.txt");
    if (!infile.is_open()) {
        std::cout << "Input file opening failed." << std::endl;
        exit(1);
    }

    std::string inputData;
    std::string dataChunk;
    while (!infile.eof()) {
        std::getline(infile, dataChunk);
        inputData += dataChunk;
    }
    infile.close();

    std::regex mulRegex(R"rgx(mul\(\d+,\d+\))rgx");
    auto mulBegin = std::sregex_iterator(inputData.begin(), inputData.end(), mulRegex);

    std::vector<std::string> mulMatches;
    for (auto it = mulBegin; it != std::sregex_iterator(); it++) {
        std::smatch mulMatch = *it;
        mulMatches.push_back(mulMatch.str());
    }

    std::regex numRegex(R"rgx(\d+)rgx");
    std::sregex_iterator numBegin;
    int total = 0;
    for (auto vIt = mulMatches.begin(); vIt != mulMatches.end(); vIt++) {
        std::string mulString = std::data(*vIt);
        numBegin = std::sregex_iterator(mulString.begin(), mulString.end(), numRegex);
        for (auto sIt = numBegin; sIt != std::sregex_iterator(); sIt++) {
            std::smatch num1 = *sIt;
            sIt++;
            std::smatch num2 = *sIt;
            total += stoi(num1.str()) * stoi(num2.str());
        }
    }
    std::cout << "Found " << std::distance(mulBegin, std::sregex_iterator()) << " occurences of mul(x,x)." << std::endl;
    printf("Total: %d\n", total);
}