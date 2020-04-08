#include <iostream>
#include <fstream>

#include "Token.h"

void Input(std::vector<std::string>& computers)
{
	std::ifstream fin("InputIpAddresses.txt");
	int size;
	fin >> size;
	std::cout << "There are " << size << " computers connected.\n";

	for (int index = 0; index < size; index++)
	{
		std::string element;
		fin >> element;
		computers.push_back(element);
	}
}

bool SourceDifferentFromDestination(std::string source, std::string destination)
{
	if (source == destination)
		return false;
	
	return true;
}

bool SourceAndDestinationExist(std::string source, std::string destination, std::vector<std::string> computers)
{
	bool exist1 = false;
	bool exist2 = false;

	for (int index = 0; index < computers.size(); index++)
	{
		if (computers[index] == source)
			exist1 = true;
		
		if (computers[index] == destination)
			exist2 = true;
	}

	if (exist1 && exist2)
		return true;
	
	return false;
}

void TokenRing(Token& token, std::vector<std::string> computers)
{

	bool anotherMessage = true;
	int index = 0;

	while (anotherMessage)
	{
		if (index == computers.size())
			index = 0;
		
		if (token.GetFree())
		{
			std::cout << "Computer " << index + 1 << ": Do you want to send a message? (1-yes; 2-no)\n";
			int option;
			std::cout << "Option: ";
			std::cin >> option;
			
			if (option == 1)
			{
				token.SetIpSource(computers[index]);
				std::string ip;

				do
				{
					std::cout << "Insert the destination IP.\n";
					std::cout << "IP: ";					
					std::cin >> ip;
					token.SetIpDestination(ip);
				} while (!SourceAndDestinationExist(computers[index], ip, computers)
					&& !SourceDifferentFromDestination(computers[index], ip));

				std::cout << "Insert your message.\n";
				std::cout << "Message: ";
				std::string message;
				std::cin >> message;
				token.SetMessage(message);
				token.SetReachedDestination(false);
				token.SetFree(false);
				token.AddToHistory(computers[index]);
				std::cout << "Next computer... \n";
				index++;
			}
			else
			{
				std::cout << "Next computer... \n";
				index++;
			}	
		}
		else
		{
			if (!token.GetReachedDestination())
			{
				if (computers[index] == token.GetIpDestination())
				{
					std::cout << "Destination reached!\n";
					std::cout << "Transmited message: \"" << token.GetMessage() << "\"\n";
					token.SetReachedDestination(true);
					token.AddToHistory(computers[index]);
					std::vector<std::string> history = token.GetHistory();
					std::cout << "History: ";
					
					for (int computer = 0; computer < history.size(); computer++)
					{
						std::cout << history[computer] << " ";
					}

					std::cout << "\n";
					std::cout << "Next computer... \n";
					index++;
				}
				else
				{
					token.AddToHistory(computers[index]);
					std::cout << "Destination not reached yet.\n";
					std::cout << "Next computer... \n";
					index++;
				}
			}
			else
			{
				if (computers[index] == token.GetIpSource())
				{
					token.ClearToken();
					std::cout << "The token is free!\n";
				}
				std::cout << "Next computer... \n";
				index++;
			}
		}
	}
}

int main()
{
	Token token;
	std::vector<std::string> computers;

	Input(computers);
	TokenRing(token, computers);

	return 0;
}