#pragma once
#include <iostream>
#include <map>
#include <vector>
#include <Windows.h>

class Gamble {
public:
	Gamble();
	~Gamble();
	void AddPrediction(std::string userName, int prediction);
	std::pair<std::string, int> GetWinner();
private:
	std::map<std::string, int> predictions;
	int predictedNumber;
	CRITICAL_SECTION critsect;
private:
	int MakePrediction();
};
