#include <iostream>
#include <fstream>
#include <vector>

void ReadInput(std::vector<int>& input)
{
	std::ifstream fin("Input.txt");
	int size, bit;

	fin >> size;

	for (int index = 0; index < size; index++)
	{
		fin >> bit;
		input.push_back(bit);
	}
}

bool Validate(std::vector<int> input)
{
	if (input.size() % 7 != 0)
		return false;
	
	for (int index = 0; index < input.size(); index++)
	{
		if (input[index] != 0 && input[index] != 1)
			return false;
	}

	return true;
}

void Partition(std::vector<int> input, int**& matrix, int& lines, int& columns)
{
	lines = (input.size() / 7) + 1;
	columns = 8;

	matrix = new int*[lines];

	for (int index = 0; index < lines; index++)
	{
		matrix[index] = new int[columns];
	}

	int index = 0;

	for (int index1 = 0; index1 < lines - 1; index1++)
	{
		for (int index2 = 0; index2 < columns - 1; index2++)
		{
			matrix[index1][index2] = input[index];
			index++;
		}
	}
}

void Border(int**& matrix, int lines, int columns)
{
	int* parityColumns = new int[columns-1];

	for (int index = 0; index < columns - 1; index++)
	{
		parityColumns[index] = 0;
	}

	for (int index1 = 0; index1 < lines - 1; index1++)
	{
		int parityLine = 0;

		for (int index2 = 0; index2 < columns - 1; index2++)
		{
			if (matrix[index1][index2] == 1)
			{
				parityLine++;
				parityColumns[index2]++;
			}
		}

		matrix[index1][columns - 1] = parityLine % 2;
	}

	for (int index = 0; index < columns - 1; index++)
	{
		matrix[lines - 1][index] = parityColumns[index] % 2;
	}

	matrix[lines - 1][columns - 1] = 1;
}

void ShowMatrix(int** matrix, int lines, int columns)
{
	for (int index1 = 0; index1 < lines; index1++)
	{
		for (int index2 = 0; index2 < columns; index2++)
		{
			std::cout << matrix[index1][index2];
		}

		std::cout << "\n";
	}

	std::cout << "\n";
}

std::vector<int> GenerateMessage(int** matrix, int lines, int columns)
{
	std::vector<int> sentMessage;
	
	for (int index1 = 0; index1 < lines; index1++)
	{
		for (int index2 = 0; index2 < columns; index2++)
		{
			sentMessage.push_back(matrix[index1][index2]);
		}
	}

	return sentMessage;
}

void ShowMessage(std::vector<int> sentMessage)
{
	for (int index = 0; index < sentMessage.size(); index++)
	{
		std::cout << sentMessage[index];
	}

	std::cout << "\n";
}

int main()
{
	std::vector<int> input;

	ReadInput(input);

	if (Validate(input))
	{
		int** matrix;
		int lines = 0;
		int columns = 0;
		std::vector<int> sentMessage;

		Partition(input, matrix, lines, columns);
		Border(matrix, lines, columns);
		std::cout << "The generated matrix is:\n";
		ShowMatrix(matrix, lines, columns);
		sentMessage = GenerateMessage(matrix, lines, columns);
		std::cout << "The message was sent without errors!\n";
		std::cout << "The message is: ";
		ShowMessage(sentMessage);

		std::cout << "Do you want to change a bite in the original message? (1-yes; 2-no)\n";
		std::cout << "Insert 1 or 2: ";
		int option;
		std::cin >> option;
		if (option == 1)
		{
			std::cout << "Which bite do you want to change? ";
			int index;
			std::cin >> index;
			std::cout << "Insert the new bite: ";
			int newBite;
			std::cin >> newBite;
			input[index - 1] = newBite;
			Partition(input, matrix, lines, columns);
			Border(matrix, lines, columns);
			std::vector<int> newMessage = GenerateMessage(matrix, lines, columns);
			bool ok = true;
			
			for (int index = 0; index < sentMessage.size(); index += 7)
			{
				if (sentMessage[index] != newMessage[index])
					ok = false;
			}

			if (ok)
				std::cout << "The message was sent without errors.\n";
			else
				std::cout << "The message was sent with  errors.\n";
				
		}
	}
	else
		std::cout << "Invalid input.\n";

	return 0;
}