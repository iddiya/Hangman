
#include <iostream>
#include <iomanip>

#include <string>
#include <vector>       // std::vector
#include <algorithm>    // std::for_each

#include "main.h"

void check_current_status(vector<string> wordArray, vector<char> guessed_chars, string word, int num_guesses) {
	cout << endl;
	cout << "guesses left: " << num_guesses << endl;
	cout << "DEBUGGING: words left : " << wordArray.size() << endl;
	cout << "guesses so far : [";

	for (const auto &i : guessed_chars) {
		cout << i << " ";
	}
	cout << "]" << endl;

	cout << "current word : " << word << endl;
}
