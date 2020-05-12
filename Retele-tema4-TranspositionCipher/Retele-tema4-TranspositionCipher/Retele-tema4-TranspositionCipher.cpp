#include <iostream>
#include <fstream>
#include <vector>
#include <string>

void ReadFromFile(std::string& key, std::vector<char>& text)
{
    std::ifstream fin("Input.txt");

    fin >> key;

    for (char letter; fin >> letter; )
    {
        if (!isspace(letter))
            text.push_back(letter);
    }
}

bool Validation(std::string key)
{
    for (int index1 = 0; index1 < key.size() - 1; index1++)
    {
        for (int index2 = index1; index2 < key.size(); index2++)
        {
            if (key[index1] == key[index2])
                return false;
        }
    }

    return true;
}

char FindLowestLetter(std::string key, char lastLetter)
{
    char lowest = 'Z';

    for (int index = 0; index < key.size(); index++)
    {
        if (key[index] >= lastLetter && key[index] < lowest)
            lowest = key[index];
    }

    return lowest;
}

void AlphabeticKey(std::string key, std::vector<char>& alphabeticKey)
{
    alphabeticKey.emplace_back(FindLowestLetter(key, 'a'));

    while (key.length() != alphabeticKey.size())
    {
        char lowest = FindLowestLetter(key, alphabeticKey[alphabeticKey.size() - 1]);
        alphabeticKey.push_back(lowest);
    }
}

int FindLetter(char letter, std::vector<char> alphabeticKey)
{
    for (int index = 0; index < alphabeticKey.size(); index++)
    {
        if (alphabeticKey[index] == letter)
            return index + 1;
    }
}

std::vector<std::vector<char>> GenerateMatrix(std::string key, std::vector<char> alphabeticKey, std::vector<char> text)
{
    std::vector<char> line;
    std::vector<std::vector<char>> matrix;

    //first line
    for (int index = 0; index < key.size(); index++)
    {
        line.push_back(key[index]);
    }
    
    matrix.push_back(line);
    line.clear();
    
    //second line
    for (int index = 0; index < key.size(); index++)
    {
        char digit = (char)FindLetter(key[index], alphabeticKey);
        line.push_back(digit);
    }

    matrix.push_back(line);
    line.clear();
    int index1 = 0; 

    //the rest of the lines
    while (index1 < text.size())
    {
        for (int index2 = 0; index2 < key.size(); index2++)
        {
            line.push_back(text[index1]);
            index1++;
        }

        matrix.push_back(line);
        line.clear();
    }
}

void AddSurplusLetters(std::vector<std::vector<char>>& matrix)
{
    std::vector<char> alphabet = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };
   
    if (matrix[matrix.size() - 1].size() != matrix[matrix.size() - 2].size())
    {
        int index = 0; 

        while (matrix[matrix.size() - 1].size() != matrix[matrix.size() - 2].size())
        {
            matrix[matrix.size() - 1].push_back(alphabet[index]);
            index++;
        }
    }
}

void PrintMatrix(std::vector<std::vector<char>> matrix)
{
    std::ofstream fout("OutputMatrix.txt");

    for (int index1 = 0; index1 < matrix.size(); index1++)
    {
        for (int index2 = 0; index2 < matrix[index1].size(); index2++)
        {
            fout << matrix[index1][index2] << " ";
            std::cout << matrix[index1][index2] << " ";
        }

        fout << "\n";
        std::cout << "\n";
    }
}

void PrintEncryptedMessage(std::vector<std::vector<char>> matrix)
{
    std::ofstream fout("OutputMessage.txt");

    for (int index1 = 2; index1 < matrix.size(); index1++)
    {
        for (int index2 = 0; index2 < matrix[index1].size(); index2++)
        {
            fout << matrix[index1][index2];
            std::cout << matrix[index1][index2];
        }

        fout << " ";
        std::cout << " ";
    }
}

int main()
{
    std::string key;
    std::vector<char> text;

    ReadFromFile(key, text);
    
    if (Validation(key))
    {
        std::vector<char> alphabeticKey;
        AlphabeticKey(key, alphabeticKey);
        std::vector<std::vector<char>> matrix = GenerateMatrix(key, alphabeticKey, text);
        AddSurplusLetters(matrix);
        std::cout << "The generated matrix:\n";
        PrintMatrix(matrix);
        std::cout << "The encrypted message:\n";
        PrintEncryptedMessage(matrix);
    }
    else
        std::cout << "Invalid input!\n";

    system("pause");
    return 0;
}
