#include <fstream>
#include <iostream>
#include <vector>

std::vector<int> readPuzzleInputFromFile(const std::string& fileName)
{
    std::ifstream inFile(fileName);
    std::string line;
    std::vector<int> numbersInFile;

    while (getline(inFile, line))
    {
        try
        {
            numbersInFile.push_back(stoi(line));
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
    return numbersInFile;
}

int numberOfIncreases(std::vector<int> input, int sliding_window)
{
    int counter = 0;
    int sum = 0;
    int prev_sum = 0;

    // iterate over all inputs and count how often the new sliding window sum increases
    for (size_t i = 0; i <= input.size() - sliding_window; i++)
    {
        prev_sum = sum;
        sum = 0;
        for (size_t k = 0; k < sliding_window; k++)
        {
            sum += input[i + k];
        }

        if (i == 0)
            continue;

        if (sum > prev_sum)
        {
            counter++;
        }
    }
    return counter;
}

int main()
{
    std::string fileName = "../inputs/day1.txt";
    std::vector<int> input = readPuzzleInputFromFile(fileName);

    int sol_a = numberOfIncreases(input, 1);
    int sol_b = numberOfIncreases(input, 3);

    std::cout << "Solution part 1: " << sol_a << std::endl;
    std::cout << "Solution part 2: " << sol_b << std::endl;
}
