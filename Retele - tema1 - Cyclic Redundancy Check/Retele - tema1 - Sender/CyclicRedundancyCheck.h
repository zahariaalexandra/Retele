#pragma once
#include <vector>
#include <cstdint>

class CyclicRedundancyCheck
{
public:
	void ReadInput();
	void Generate();

private:
	uint8_t Xor(uint8_t x, uint8_t y);
	bool ValidateBits(std::vector<uint8_t> message);
	bool ValidatePolinom(std::vector<uint8_t> polinom);
	void GenerateNewMessageAndRank();
	void Divide(std::vector<uint8_t> newMessage);

private:
	std::vector<uint8_t> recievedMessage; // M
	std::vector<uint8_t> polinom; 
	std::vector<uint8_t> newMessage; // M'
	std::vector<uint8_t> sentMessage; // M' - R
	std::vector<uint8_t> rest; // R
	int rank;
};

