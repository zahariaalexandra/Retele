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

bool AlphabeticKey(std::string key, std::vector<char>& alphabeticKey)
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

int main()
{
    std::string key;
    std::vector<char> text;

    ReadFromFile(key, text);

    system("pause");
    return 0;
}
