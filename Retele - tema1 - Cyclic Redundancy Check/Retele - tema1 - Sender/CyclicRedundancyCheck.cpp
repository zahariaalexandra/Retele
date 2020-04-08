#include <iostream>

#include "CyclicRedundancyCheck.h"

void CyclicRedundancyCheck::ReadInput()
{
	
	
	int bit;
	int size;
	bool valid;

	do
	{
		std::cout << "Insert the number of bits you want to send: ";
		std::cin >> size;
		std::cout << "Insert the message you want to send: ";
		valid = true;

		for (int index = 0; index < size; index++)
		{
			std::cin >> bit;
			recievedMessage.push_back(bit);
		}

		if (!ValidateBits(recievedMessage))
		{
			std::cout << "Please insert a valid message!\n";
			recievedMessage.clear();
			valid = false;
		}
	} while (!valid);

	do 
	{
		std::cout << "Insert the number of bits of the polinom: ";
		std::cin >> size;
		std::cout << "Insert the polinom: ";
		valid = true;

		for (int index = 0; index < size; index++)
		{
			std::cin >> bit;
			polinom.push_back(bit);
		}

		if (!ValidatePolinom(polinom))
		{
			std::cout << "You have to insert a valid polinom!\n ";
			polinom.clear();
			valid = false;
		}
	} while (!valid);
}

void CyclicRedundancyCheck::Generate()
{
	GenerateNewMessageAndRank();
	Divide(newMessage);

	sentMessage = newMessage;

	if (rest.empty())
	{
		std::cout << "The message was sent succesfully.\n";
		std::cout << "The sent message: ";

		for (int index = 0; index < sentMessage.size(); index++)
		{
			std::cout << sentMessage[index];
		}

		std::cout << "\n";
	}
	else
	{
		for (int index = 0; index < rest.size(); index++)
		{
			if (sentMessage[sentMessage.size() - index - 1] == rest[rest.size() - index - 1])
				sentMessage[sentMessage.size() - index - 1] = 0;
			else
				sentMessage[sentMessage.size() - index - 1] = 1;
		}

		Divide(sentMessage);

		if (!rest.empty())
		{
			std::cout << "The message was sent succesfully.\n";
			std::cout << "The sent message: ";

			for (int index = 0; index < sentMessage.size(); index++)
			{
				std::cout << sentMessage[index];
			}

			std::cout << "\n";
		}
		else
		{
			std::cout << "The message was sent with errors.\n";
			std::cout << "The sent message: ";

			for (int index = 0; index < sentMessage.size(); index++)
			{
				std::cout << sentMessage[index];
			}

			std::cout << "\n";
		}
	}

}

void CyclicRedundancyCheck::Divide(std::vector<uint8_t> newMessage)
{
	std::vector<uint8_t> auxMessage = newMessage;
	std::vector<uint8_t> tempMessage;

	int indexMessage = 0; 

	while (auxMessage.size() >= rank)
	{
		int indexPolinom = 0;

		while (indexPolinom < polinom.size())
		{
			if (Xor(auxMessage[indexMessage], polinom[indexPolinom]) == 1)
			{
				tempMessage.push_back(Xor(auxMessage[indexMessage], polinom[indexMessage]));
				indexPolinom++;
				indexMessage++;
			}

			if (Xor(auxMessage[indexMessage], polinom[indexPolinom]) == 0 && !tempMessage.empty())
			{
				tempMessage.push_back(Xor(auxMessage[indexMessage], polinom[indexMessage]));
				indexPolinom++;
				indexMessage++;
			}
		}

		for (int index = rank; index < auxMessage.size(); index++)
		{
			tempMessage.push_back(auxMessage[index]);
		}

		auxMessage = tempMessage;
		tempMessage.clear();
	}

	rest = auxMessage;
}

void CyclicRedundancyCheck::GenerateNewMessageAndRank()
{
	rank = 0;

	for (int index = 0; index < polinom.size(); index++)
	{
		if (polinom[index] == 1)
			rank++;
	}

	newMessage = recievedMessage;

	for (int index = 0; index < rank; index++)
	{
		newMessage.emplace_back(0);
	}
}

bool CyclicRedundancyCheck::ValidateBits(std::vector<uint8_t> message)
{
	for (int index = 0; index < message.size(); index++)
	{
		if (message[index] != 0 && message[index] != 1)
			return false;
	}

	return true;
}

bool CyclicRedundancyCheck::ValidatePolinom(std::vector<uint8_t> polinom)
{
	if (!ValidateBits(polinom))
		return false;

	if (polinom[0] == 0 || polinom[polinom.size() - 1] == 0)
		return false;

	return true;
}

uint8_t CyclicRedundancyCheck::Xor(uint8_t x, uint8_t y)
{
	if (x == y)
		return 0;
	return 1;
}
