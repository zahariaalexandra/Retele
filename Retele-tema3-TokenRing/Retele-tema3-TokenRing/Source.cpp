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

			}
			else
				index++;
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