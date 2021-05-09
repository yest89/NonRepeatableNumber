#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>
#include "Gamble.h"

Gamble::Gamble() {
    InitializeCriticalSection(&critsect);
}

Gamble::~Gamble() {
    DeleteCriticalSection(&critsect);
}

void Gamble::AddPrediction(std::string userName, int prediction) {
    EnterCriticalSection(&critsect);
	this->predictions.insert(std::pair<std::string, int> (userName, prediction));
    LeaveCriticalSection(&critsect);
}

std::pair<std::string, int> Gamble::GetWinner() {
	int guessNumber = this->MakePrediction();

    std::vector<std::pair<std::string, int>> vec;
    // copy key-value pairs from the map to the vector
    std::copy(                                 // here we are working with copy on array
        this->predictions.begin(),             // and there is no need to put it in 
        this->predictions.end(),               // critical section 
        std::back_inserter<std::vector<std::pair<std::string, int>>>(vec));

    int index = abs(vec[0].second - guessNumber);
    int min = vec[0].second;
    std::pair<std::string, int> minPair = vec[0];
    for (std::pair<std::string, int> pair : vec) {
        if (abs(pair.second - guessNumber) < index) {
            index = abs(pair.second - guessNumber);
            min = pair.second;
            minPair = pair;
        }
    }
   
    return minPair;
}

int Gamble::MakePrediction() {
	srand((unsigned)time(0));
	this->predictedNumber = 1 + (rand() % 200); //intentionally put limit range of numbers to 200
	return this->predictedNumber;
}