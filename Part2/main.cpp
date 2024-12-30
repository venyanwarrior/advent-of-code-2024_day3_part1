#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>
#include <cstdio>
#include <boost/regex.hpp>

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

    boost::regex mulRegex(R"rgx((mul\(\d+,\d+\)|do\(\)|don't\(\)))rgx");
    auto mulBegin = boost::sregex_iterator(inputData.begin(), inputData.end(), mulRegex);

    bool isMulValid = true;
    std::vector<std::string> mulMatches;
    for (auto it = mulBegin; it != boost::sregex_iterator(); it++) {
        boost::smatch mulMatch = *it;

        if (mulMatch.str() == "don't()") {
            isMulValid = false;
            continue;
        } else if (mulMatch.str() == "do()") {
            isMulValid = true;
            continue;
        }

        if (isMulValid) {
            mulMatches.push_back(mulMatch.str());
        }
    }

    boost::regex numRegex(R"rgx(\d+)rgx");
    boost::sregex_iterator numBegin;
    int total = 0;
    for (auto vIt = mulMatches.begin(); vIt != mulMatches.end(); vIt++) {
        std::string mulString = std::data(*vIt);
        numBegin = boost::sregex_iterator(mulString.begin(), mulString.end(), numRegex);
        for (auto sIt = numBegin; sIt != boost::sregex_iterator(); sIt++) {
            boost::smatch num1 = *sIt;
            sIt++;
            boost::smatch num2 = *sIt;
            total += stoi(num1.str()) * stoi(num2.str());
        }
    }
    std::cout << "Found " << mulMatches.size() << " occurences of mul(x,x)." << std::endl;
    printf("Total: %d\n", total);
}