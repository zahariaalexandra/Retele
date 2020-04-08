#include <iostream>

#include "Token.h"

void TokenRing(Token& token, std::vector<std::string>& computers)
{
	bool anotherMessage = true;
	int index = 0;

	while (anotherMessage)
	{
		if (index == computers.size() - 1)
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
				std::cout << "Insert the destination IP.\n";
				std::cout << "IP: ";
				std::string ip;
				std::cin >> ip;
				token.SetIpDestination(ip);
				std::cout << "Insert your message.\n";
				std::cout << "Message: ";
				std::string message;
				std::cin >> message;
				token.SetMessage(message);
				token.SetReachedDestination(false);
				token.SetFree(false);
				token.AddToHistory(computers[index]);
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

		}
		
	}
}

int main()
{
	Token token;
	std::vector<std::string> computers;

	return 0;
}