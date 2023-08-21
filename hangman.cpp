#include <fstream>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>

#include <string>
#include <vector>       // std::vector
#include <algorithm>    // std::for_each

#include <locale>
#include <map>
#include "main.h"

using namespace std;

int length;
int num_guesses;
int difficulty;


map<string, int> getWords(char fileName[]) {

	ifstream wordsFile("words.txt");

	vector<string> wordsList;
	string temp;

	while (getline(wordsFile, temp)) {
		wordsList.push_back(temp);
	}

	map<string, int> wordmap;

	for (const auto &i : wordsList) {
		wordmap.insert({i, i.length()});
	}

	return wordmap;
}

map<int, int> getWordsLengthList(map<string, int> wordmap) {
	map<int, int> wordLengthList; // map<lengthOfWord, amountOfWords>

	for (int i = 2; i < 30; i++) {
		wordLengthList.insert({i, 0});
	}

	map<string, int>::iterator wordList_i;

	for (wordList_i = wordmap.begin(); wordList_i != wordmap.end(); wordList_i++) {
		wordLengthList[wordList_i->second]++; 
	}

	return wordLengthList;
}

void printAvailableWordsLength(map<int, int> wordLengths) {
	cout << "BEGIN DEBUGGING" << endl;
	cout << "List of words ordered by length: " << endl;

	map<int, int>::iterator wordLengthList_i;
	for (wordLengthList_i = wordLengths.begin(); wordLengthList_i  != wordLengths.end(); wordLengthList_i++) {
		cout << wordLengthList_i->first << " " << wordLengthList_i->second << endl;
	}

	cout << "END DEBUGGING" << endl;
}

void select_length(map<int, int> wordLengths) {

	int continue_asking = 1;
	do {
		cout << "What length word do you want to use? ";
		cin >> length;

		if (length < 2 || length > 29) {
			cout << "Unavailable word length" << endl;
			cout << "Please re-enter the length between 2 and 29" << endl;
		} else if (wordLengths[length] == 0) {
			cout << "Unavailable word length from the dictionary" << endl;
			cout << "Please re-enter the length" << endl;
		} else {
			continue_asking = 0;
		}
	} while (continue_asking);

	cout << endl;
}

void select_guesses() {
	cout << "How many wrong answers allowed? ";
	cin >> num_guesses;

	while (num_guesses < 10) {
		cout << "Unavailable number of guesses" << endl;
		cout << "Minimum number of guesses is 10" << endl;
		cout << "Please re-enter number greater than 9" << endl;
		cout << "How many wrong answers allowed? ";
		cin >> num_guesses;
	}

	cout << endl;
}

void select_difficulty() {
	cout << "What difficulty level do you want?" << endl;
	cout << "Enter a number between 1 (EASIEST) and 3 (HARDEST): ";
	cin >> difficulty;

	while (difficulty < 1 || difficulty > 3) {
		cout << "Unavailable difficulty level" << endl;
		cout << "Please re-enter the difficulty level between number 1 and 3" << endl;
		cout << "What difficulty level do you want?" << endl;
		cout << "Enter a number between 1 (EASIEST) and 3 (HARDEST): ";
		cin >> difficulty;
	}

	cout << endl;
}

void setup_game(map<int, int> wordLengths) {
	select_length(wordLengths);
	select_guesses();
	select_difficulty();
}

vector<string> getGameWords(map<string, int> wordmap) {
	vector<string> gameWords;

	map<string, int>::iterator wordList_i;

	for (wordList_i = wordmap.begin(); wordList_i != wordmap.end(); wordList_i++) {
		if (wordList_i->second == length) {
			gameWords.push_back(wordList_i->first);
		}
	}
	return gameWords;
}

string generateRepresentation() {
	string word = "";

	for (int i = 0; i < length; i++) {
		word.append("-");
	}

	return word;
}


map<string, int> checkGuess(vector<string> wordArray, char guess, string word_representation) {
	map<string, int> checking_pattern;
	checking_pattern.insert({word_representation, 0});

	for (const auto &word : wordArray) {
		if (word.find(guess) < word.length()) {
			int count = 0;
			string key = "";

			for (int index = 0; index < word.length(); index++) {
				if (word[index] == guess) {
					key += guess;
					count++;
				} else {
					key += word_representation[index];
				}
			}

			if (checking_pattern.find(key) != checking_pattern.end()) {
				checking_pattern[key]++;
			} else {
				checking_pattern.insert({key, 1});
			}
		} else {
			checking_pattern[word_representation]++;
		}
	}

	cout << "BEGIN DEBUGGING: Based on guess, here are the resulting patterns and number of words in each pattern:" << endl;
	map<string, int>::iterator i;
	for (i = checking_pattern.begin(); i != checking_pattern.end(); i++) {
		cout << "pattern: " << i->first << ", number of words: " << i->second << endl;
	}
	cout << "END DEBUGGING" << endl;

	return checking_pattern;
}

string pickLargestFamily(map<string, int> families, string word_representation, char guess, vector<string> wordArray) {
	int largestCount = 0;
	string key;

	map<string, int>::iterator i;
	for (i = families.begin(); i != families.end(); i++) {
		if (i->second > largestCount) {
			largestCount = i->second;
			key = i->first;
		}
	}

	int count = 0;
	for (int j = 0; j < key.length(); j++) {
		if (key[j] == guess) {
			count++;
		}
	}

	if (key.compare(word_representation) == 0) {
		cout << "Sorry, there are no " << guess << "'s" << endl;
	} else if (count == 1) {
		cout << "Yes, there is one " << guess << endl;
	} else {
		cout << "Yes, there are " << count << " " << guess << "'s" << endl;
	}

	return key;
}

vector<string> reduceWordArray(vector<string> wordArray, string word_representation, char guess) {
	
	map<string, string> patterns;
	for (const auto &word : wordArray) {
		string value = "";
		for (int index = 0; index < word.length(); index++) {
			if (word[index] == guess) {
				value += guess;
			} else {
				value += word_representation[index];
			}
		}

		patterns.insert({word, value});
	}

	vector<string> newWordArray;
	map<string, string>::iterator pattern_i;
	for (pattern_i = patterns.begin(); pattern_i != patterns.end(); pattern_i++) {
		if (word_representation.compare(pattern_i->second) == 0) {
			newWordArray.push_back(pattern_i->first);
		}
	}

	return newWordArray;
}

int main(int argc, char *argv[]) {

  if (argc < 2) {
    cout << "ERROR: Please provide the file name" << endl;
    return 1;
    }
  
	int game_continue = 1;

	while (game_continue) {
		map<string, int> wordmap = getWords(argv[1]);

		map<int, int> wordLengths = getWordsLengthList(wordmap);

		printAvailableWordsLength(wordLengths);

		setup_game(wordLengths);

		vector<char> guessed_chars;

		vector<string> wordArray = getGameWords(wordmap);

		string word_representation = generateRepresentation();

		int guess_continue = 1;

		while (guess_continue) {
			check_current_status(wordArray, guessed_chars, word_representation, num_guesses);

			char guess;
			cout << "Your guess? ";
			cin >> guess;

			while (find(guessed_chars.begin(), guessed_chars.end(), guess) != guessed_chars.end()) {
				cout << "You already checked " << guess << endl;
				cout << "Please re-try different letter " << endl;
				cout << endl;
				cout << "Your guess? ";
				cin >> guess;
			} 

			guessed_chars.push_back(guess);
			sort(guessed_chars.begin(), guessed_chars.end());

			cout << "the guess: " << guess << "." << endl;

			cout << endl;
			cout << endl;
			map<string, int> families = checkGuess(wordArray, guess, word_representation);

			word_representation = pickLargestFamily(families, word_representation, guess, wordArray);

			wordArray = reduceWordArray(wordArray, word_representation, guess);

			num_guesses--;

			if (word_representation.find('-') == string::npos) {
			    cout << "You beat me" << endl;
			    cout << endl;

			    char game_again;
			    cout << "Another game? Enter y for another game, anything else to quit: ";

			    cin >> game_again;

			    if (game_again != 'y' && game_again != 'Y') {
			    	game_continue = 0;
			    }

			    guess_continue = 0;

			} else if (num_guesses < 1) {

				cout << "answer: " << wordArray[0] << endl;
				cout << "Sorry, you lose" << endl;
				cout << endl;

				char game_again;
				cout << "Another game? Enter y for another game, anything else to quit: ";

			    cin >> game_again;

			    if (game_again != 'y' && game_again != 'Y') {
			    	game_continue = 0;
			    }

			    guess_continue = 0;
			}
		}
		
	}


	return 0;	
}