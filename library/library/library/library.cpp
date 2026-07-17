#include "library.h"

void sortAndReplace(std::string& input) {
	if (input.empty()) 
		return;

	std::sort(input.rbegin(), input.rend());

	std::string result = input;

	for (char i : input) {
		if (std::isdigit(i) && i % 2 == 0) {
			result.replace(result.find(i), 1, "KB");
		}
	}

	input = result;
}

int getSum(const std::string& input) {
	int sum = 0;

	for (char i : input) {
		if (std::isdigit(i)) {
			sum += i - '0';
		}
	}

	return sum;
}

bool analyseOfSymbols(const std::string& input) {
	for (char c : input) {
		if (!std::isdigit(c)) 
			return false;
	}

	return (input.length() > 2) && !(std::stoi(input) % 32);
}