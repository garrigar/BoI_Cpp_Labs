
#include <iostream>
#include <string>

using namespace std;

const int MAX_ACCEPTED_LL_LEN = 18;

bool is_correct_unsgn_longint(string input) {				// check for correctness

	if (input.length() == 0)
		return false;									//if input is empty, then it's not correct
	for (int i = 0; (i < input.length()); ++i) {
		if (isdigit(input[i]) == 0)
			return false;								//if there's a non-digital char, then not correct
	}

	if (input.length() > MAX_ACCEPTED_LL_LEN)
		return false;									//if there're 19+ characters, then this couldn't be loaded into long long
	return true;
}

bool get_cont_choice() {					//to continue or not to continue?

	bool correct = false;					//correctness of a command, this variable is actually useless

	string input;

	while (!correct) {

		cout << "Continue? (Y/N) > ";

		getline(cin, input);

		if (input.length() != 1) {
			correct = false;
		}
		else {
			switch (input[0]) {
			case 'Y': {
				correct = true;
				return true;
			}
			case 'y': {
				correct = true;
				return true;
			}
			case 'N': {
				correct = true;
				return false;
			}
			case 'n': {
				correct = true;
				return false;
			}
			default: {correct = false; }
			}
		}
	}

}


long long josephus(long long n, long long k) {
	
	long long res = 0;

	for (long long i = 1; i <= n; ++i)
		res = (res + k) % i;						//joseph(n, k) = (joseph(n-1, k) + k) % n;

	return res + 1;
}


int main() {

	cout << "Josephus problem" << endl;

	long long n;
	long long k;

	string input;			//using a string as an input buffer

	do {

		cout << "Input the number of players: > ";
		getline(cin, input);
		if (!is_correct_unsgn_longint(input)) {
			cout << "Input error" << endl;
		}
		else {

			n = stoll(input);
			
			if (n == 0) {
				cout << "Error, n must be positive" << endl;
			}
			else {

				cout << "Input k: > ";
				getline(cin, input);
				if (!is_correct_unsgn_longint(input)) {
					cout << "Input error" << endl;
				}
				else {

					k = stoll(input);

					if (k == 0) {
						cout << "Error, k must be positive" << endl;
					}
					else {		// Alles in Ordnung

						cout << "Winner: " << josephus(n, k) << endl;

					}

				}

			}

		}

	} while (get_cont_choice());

	return 0;
}
