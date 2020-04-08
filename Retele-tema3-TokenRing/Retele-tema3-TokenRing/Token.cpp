#include "Token.h"

Token::Token()
{
	free = true;
	reachedDestination = false;
	ipSource = "";
	ipDestination = "";
	message = "";
}

bool Token::GetFree()
{
	return free;
}

void Token::SetFree(bool free)
{
	this->free = free;
}

std::string Token::GetIpSource()
{
	return ipSource;
}

void Token::SetIpSource(std::string ipSource)
{
	this->ipSource = ipSource;
}

std::string Token::GetIpDestination()
{
	return ipDestination;
}

void Token::SetIpDestination(std::string ipDestination)
{
	this->ipDestination = ipDestination;
}

std::string Token::GetMessage()
{
	return message;
}

void Token::SetMessage(std::string message)
{
	this->message = message;
}

bool Token::GetReachedDestination()
{
	return reachedDestination;
}

void Token::SetReachedDestination(bool reachedDestination)
{
	this->reachedDestination = reachedDestination;
}

std::vector<std::string> Token::GetHistory()
{
	return history;
}

void Token::AddToHistory(std::string element)
{
	history.push_back(element);
}

void Token::ClearHistory()
{
	history.clear();
}
