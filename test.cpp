void check_current_status(vector<string> wordArray, vector<char> guessed_chars, string word) {
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