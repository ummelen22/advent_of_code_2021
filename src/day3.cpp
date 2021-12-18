#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <bitset>

std::vector<std::string> readPuzzleInputFromFile(const std::string& fileName)
{
    std::ifstream inFile(fileName);
    std::string line;
    std::vector<std::string> lines;

    while (getline(inFile, line))
    {
        try
        {
            lines.push_back(line);
        }
        catch (const std::out_of_range& oor)
        {
            std::cerr << "Invalid argument: " << line
                      << " is out of range of representable values of int." << std::endl;
        }
    }
    return lines;
}

std::bitset<12> getMostCommonBits(std::vector<std::string>& inputs)
{
    std::string binary_number_string;
    for (size_t i = 0; i < inputs[0].size(); i++)
    {
        int ones = 0;
        int zeros = 0;
        for (auto& line : inputs)
        {
            char j = line[i];
            if (j == '0')
                zeros++;
            else if (j == '1')
                ones++;
            else
            {
                throw std::invalid_argument("number must be 1 or 0");
            }

            if (ones >= inputs.size() / 2)
            {
                binary_number_string += "1";
                break;
            }
            else if (zeros > inputs.size() / 2)
            {
                binary_number_string += "0";
                break;
            }
        }
    }
    std::bitset<12> binary_number{binary_number_string};
    return binary_number;
}

int solveA(std::bitset<12>& most_common_bits)
{
    std::bitset<12> least_common_bits(most_common_bits);
    least_common_bits.flip();

    int gamma_rate = (int)(most_common_bits.to_ulong());
    int epsilon_rate = (int)(least_common_bits.to_ulong());
    int power_consumption = gamma_rate * epsilon_rate;

    return power_consumption;
}

std::vector<std::string> filterBitsetsForNthBit(std::vector<std::string>& inputs, std::string& bits_string, std::string keyword, size_t n)
{
    if (inputs.size() == 1)
        return inputs;

    std::vector<std::string> remaining_inputs;
    for (const auto& input : inputs)
    {
        if (input[n] == bits_string[n])
        {
            remaining_inputs.push_back(input);
        }
    }
    n++;

    std::bitset<12> most_common_bits_of_remaining_inputs = getMostCommonBits(remaining_inputs);
    if (keyword == "oxygen")
    {
        bits_string = most_common_bits_of_remaining_inputs.to_string();
    }
    else if (keyword == "co2")
    {
        most_common_bits_of_remaining_inputs.flip();
        bits_string = most_common_bits_of_remaining_inputs.to_string();
    }
    return filterBitsetsForNthBit(remaining_inputs, bits_string, keyword, n);
}

int solveB(std::vector<std::string> inputs, std::bitset<12>& most_common_bits)
{
    std::string most_common_bits_string = most_common_bits.to_string();
    
    std::bitset<12> least_common_bits(most_common_bits);
    least_common_bits.flip();
    std::string least_common_bits_string = least_common_bits.to_string();

    std::bitset<12> oxygen_generator_rating_bitset{filterBitsetsForNthBit(inputs, most_common_bits_string, "oxygen", 0)[0]};
    std::bitset<12> co2_scrubber_rating_bitset{filterBitsetsForNthBit(inputs, least_common_bits_string, "co2", 0)[0]};
    int oxygen_generator_rating = (int)oxygen_generator_rating_bitset.to_ulong();
    int co2_scrubber_rating = (int)co2_scrubber_rating_bitset.to_ulong();
    return oxygen_generator_rating * co2_scrubber_rating;
}

int main()
{
    std::string file_name = "../inputs/day3.txt";
    std::vector<std::string> inputs = readPuzzleInputFromFile(file_name);

    std::bitset<12> most_common_bits = getMostCommonBits(inputs);

    int sol_a = solveA(most_common_bits);
    std::cout << "Solution part A: " << sol_a << std::endl;

    int sol_b = solveB(inputs, most_common_bits);
    std::cout << "Solution part B: " << sol_b << std::endl;
}
