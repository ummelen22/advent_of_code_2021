#include <fstream>
#include <istream>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <boost/algorithm/string.hpp>

struct Bingo
{
    std::vector<int> bingo_numbers;
    std::unordered_map<uint32_t, std::vector<std::size_t>> number_positions;
    std::vector<uint32_t> board_sums;
};

std::vector<std::string> readPuzzleInputFromFile(const std::string &fileName)
{
    std::ifstream file(fileName);
    std::string line;
    std::vector<std::string> lines;

    while (getline(file, line))
    {
        lines.push_back(line);
    }

    std::vector<std::string> bingo_numbers_string;
    std::vector<int> bingo_numbers;

    for (const auto &line : lines)
    {
        if (line == lines[0])
        {
            boost::split(bingo_numbers_string, line, boost::is_any_of(","));
            std::transform(bingo_numbers_string.begin(), bingo_numbers_string.end(), std::back_inserter(bingo_numbers),
                           [](const std::string &str)
                           { return std::stoi(str); });
        }
    }
    return lines;
}

int main()
{
    std::vector<std::string> inputs = readPuzzleInputFromFile("../inputs/day4.txt");
    return 0;
}