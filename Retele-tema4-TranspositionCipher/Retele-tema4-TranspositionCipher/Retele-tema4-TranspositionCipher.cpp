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

bool AlphabeticKey(std::string key, std::vector<char>& alphabeticKey)
{

}

int main()
{
    std::string key;
    std::vector<char> text;

    ReadFromFile(key, text);

    system("pause");
    return 0;
}
