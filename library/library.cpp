#include "library.h"

void sortAndReplace(std::string& input) {
	if (input.empty()) 
		return;

	std::sort(input.rbegin(), input.rend());

	std::string result;

	for (char i : input) {
		if (std::isdigit(static_cast<unsigned char>(i)) && (i - '0') % 2 == 0)
			result += "KB";
		else
			result += i;
	}

	input = result;
}

int getSum(const std::string& input) {
	int sum = 0;

	for (char i : input) {
		if (std::isdigit(static_cast<unsigned char>(i))) {
			sum += i - '0';
		}
	}

	return sum;
}

bool analyseOfSymbols(const std::string& input) {
	for (char i : input) {
		if (!std::isdigit(static_cast<unsigned char>(i)))
			return false;
	}

	return (input.length() > 2) && !(std::stoi(input) % 32);
}