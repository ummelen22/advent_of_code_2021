#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>


struct PuzzleInput
{
    std::string action;
    int value;
};

std::vector<std::string> splitString(std::string line, std::string delimiter)
{
    size_t pos = line.find(delimiter);
    size_t initPos = 0;
    std::vector<std::string> subStrings = {};
    while (pos != std::string::npos)
    {
        subStrings.push_back(line.substr(initPos, pos - initPos));
        initPos = pos + 1;
        pos = line.find(delimiter, initPos);
    }
    subStrings.push_back(line.substr(initPos, std::min(pos, line.size()) - initPos + 1));

    return subStrings;
}


std::vector<PuzzleInput> readPuzzleInputFromFile(const std::string& fileName)
{
    std::ifstream inFile(fileName);
    std::string line;
    std::vector<PuzzleInput> puzzle_input;
    std::vector<std::string> splitted_line;

    while (getline(inFile, line))
    {
        try
        {
            splitted_line = splitString(line, " ");
            puzzle_input.push_back(PuzzleInput{splitted_line[0], stoi(splitted_line[1])});
        }
        catch (const std::invalid_argument& ia)
        {
            std::cerr << "Invalid argument: " << line << " couldn't be converted to an int."
                      << std::endl;
        }
        catch (const std::out_of_range& oor)
        {
            std::cerr << "Invalid argument: " << line
                      << " is out of range of representable values of int." << std::endl;
        }
    }
    return puzzle_input;
}

int solveA(std::vector<PuzzleInput> inputs)
{
    int forward = 0;
    int depth = 0;
    for (auto& input : inputs)
    {
        if (input.action == "forward")
        {
            forward += input.value;
        }
        else if (input.action == "down")
            depth += input.value;
        else if (input.action == "up")
            depth -= input.value;
        else
            throw std::invalid_argument("Action " + input.action + "is not a valid action.");
    }

    return depth * forward;
}

int solveB(std::vector<PuzzleInput> inputs)
{
    int aim = 0;
    int forward = 0;
    int depth = 0;
    for (auto& input : inputs)
    {
        if (input.action == "forward")
        {
            forward += input.value;
            depth += aim * input.value;
        }
        else if (input.action == "down")
            aim += input.value;
        else if (input.action == "up")
            aim -= input.value;
        else
            std::cout << "nope\n";
    }

    return depth * forward;
}

int main()
{
    std::string file_name = "../inputs/day2.txt";
    std::vector<PuzzleInput> inputs = readPuzzleInputFromFile(file_name);

    int sol_a = solveA(inputs);
    std::cout << "Solution part A: " << sol_a << std::endl;

    int sol_b = solveB(inputs);
    std::cout << "Solution part B: " << sol_b << std::endl;
}
