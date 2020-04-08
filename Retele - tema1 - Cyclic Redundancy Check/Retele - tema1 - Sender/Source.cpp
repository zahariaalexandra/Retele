#include <fstream>
#include <iostream>
#include <vector>

//#include "CyclicRedundancyCheck.h"

void ReadInput(std::vector<int>& messageToSend, std::vector<int>& polinom)
{
	std::ifstream fin("Input.txt");
	int size;
	int bit;
	fin >> size;

	for (int index = 0; index < size; index++)
	{
		fin >> bit;
		messageToSend.push_back(bit);
	}

	fin >> size;

	for (int index = 0; index < size; index++)
	{
		fin >> bit;
		polinom.push_back(bit);
	}
}

bool ValidateBits(std::vector<int> message)
{
	for (int index = 0; index < message.size(); index++)
	{
		if (message[index] != 0 && message[index] != 1)
			return false;
	}

	return true;
}

bool ValidatePolinom(std::vector<int> polinom)
{
	if (!ValidateBits(polinom))
		return false;
	if (polinom[0] == 0 || polinom[polinom.size() - 1] == 0)
		return false;
	return true;
}

int Xor(int x, int y)
{
	if (x != y)
		return 1;
	return 0;
}

void Divide(std::vector<int>& message, std::vector<int>& polinom)
{
	std::vector<int> newMessage;
	
	while (message.size() >= polinom.size())
	{
		for (int index = 0; index < polinom.size(); index++)
		{
			newMessage.push_back(Xor(message[index], polinom[index]));
		}

		for (int index = polinom.size(); index < message.size(); index++)
		{
			newMessage.push_back(message[index]);
		}

		bool ok = false;

		while (!ok && newMessage.size() > 0)
		{
			if (newMessage[0] == 0)
				newMessage.erase(newMessage.begin());
			else
				ok = true;
		}

		message = newMessage;
		newMessage.clear();
	}
}

void Show(std::vector<int> rest)
{
	for (int index = 0; index < rest.size(); index++)
	{
		std::cout << rest[index];
	}
	std::cout << "\n";
}

void SendMessage(std::vector<int>& message, std::vector<int>& newMessage, std::vector<int> polinom)
{
	int count = 1;

	for (int index = message.size() - 1; index >= 0; index--)
	{
		newMessage[newMessage.size() - count] = message[index];
		count++;          
	}

	std::cout << "The sent message: ";
	
	for (int index = 0; index < newMessage.size(); index++)
	{
		std::cout << newMessage[index];
	}

	Divide(newMessage, polinom);

	std::cout << "\n";
	if (newMessage.empty())
		std::cout << "Message transmited correctly.\n";
	else
		std::cout << "Message transmited with errors.\n";
}

int main()
{
	std::vector<int> message, tempMessage, newMessage, polinom, tempMessage2;
	bool option;

	ReadInput(message, polinom);
	tempMessage = message;

	if (!ValidateBits(message) || !ValidatePolinom(polinom))
		std::cout << "The input is incorrect!\n";
	else
	{
		int rank = 0;

		for (int index = 0; index < polinom.size(); index++)
		{
			if (polinom[index] == 1)
				rank++;
		}

		for (int contor = 0; contor < rank; contor++)
		{
			message.emplace_back(0);
		}
		
		newMessage = message;
		Divide(message, polinom);
		std::cout << "The rest is: ";
		Show(message);
		SendMessage(message, newMessage,polinom);
	}

	std::cout << "\n";
	std::cout << "Would you like to modify the original message? (1 for yes; 0 for no) ";
	std::cin >> option;
	if (option == 1)
	{
		std::cout << "Which bit would you like to change: ";
		int count;
		std::cin >> count;

		std::cout << "Insert the new bit: ";
		bool newBit;
		std::cin >> newBit;

		tempMessage[count - 1] = newBit;
		std::cout << "The new message: ";
		Show(tempMessage);
		int rank = 0;

		for (int index = 0; index < polinom.size(); index++)
		{
			if (polinom[index] == 1)
				rank++;
		}

		for (int contor = 0; contor < rank; contor++)
		{
			tempMessage.emplace_back(0);
		}

		newMessage = tempMessage;
		Divide(tempMessage, polinom);
		std::cout << "The rest is: ";
		Show(tempMessage);
		SendMessage(tempMessage, newMessage,polinom);
	}
	
	/*CyclicRedundancyCheck crc;
	crc.ReadInput();
	crc.Generate();*/

	return 0;
}