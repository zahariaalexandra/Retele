#pragma once

#include <string>
#include <vector>

class Token
{
public:
	Token();
	bool GetFree();
	void SetFree(bool free);
	std::string GetIpSource();
	void SetIpSource(std::string ipSource);
	std::string GetIpDestination();
	void SetIpDestination(std::string ipDestination);
	std::string GetMessage();
	void SetMessage(std::string message);
	bool GetReachedDestination();
	void SetReachedDestination(bool reachedDestination);
	std::vector<std::string> GetHistory();
	void AddToHistory(std::string element);
	void ClearHistory();

private:
	std::string ipSource;
	std::string ipDestination;
	std::string message;
	bool reachedDestination;
	bool free;
	std::vector<std::string> history;
};

