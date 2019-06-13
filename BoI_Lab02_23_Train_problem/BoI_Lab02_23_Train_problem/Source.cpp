
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

const int MAX_ACCEPTED_D_LEN = 15;

bool is_correct_double(string input) {						// check for correctness
	
	int dotcount = 0;
	bool correct = true;									//suppose is correct
	
	if (input.length() == 0) 
		correct = false;									//if input is empty, then it's not correct
	for (int i = 0; (i < input.length()); ++i) {
		if ( (isdigit(input[i]) == 0) && (input[i] != '.') ) 
			correct = false;								//if there's a non-digital char exept '.' , then not correct
		if (input[i] == '.')
			dotcount++;
	}
	if (dotcount >= 2)
		correct = false;									//if there're more than one dot, than not correct
	if (input.length() > MAX_ACCEPTED_D_LEN) 
		correct = false;									//if there're 15+ characters, then this couldn't be loaded into double
	return correct;
}

bool is_zero(string input) {							//for correct inputs only
	bool iszero = true;
	for (int i = 0; (i < input.length()); ++i) {
		if ( (input[i] != '0') && (input[i] != '.') ) 
			iszero = false;								//if there's a non-zero char exept '.' , then number is not zero 
		
	}
	return iszero;
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

int main() {

	cout << "Train problem" << endl;
	cout << "Please use non-negative real numbers " << MAX_ACCEPTED_D_LEN << " symbols long" << endl;

	double v1 = 0;
	double v2 = 0;
	double s = 0;
	double t = 0;
	double d = 0;

	bool v1_zero = false;
	bool v2_zero = false;
	
	string input;			//using a string as an input buffer
	
	bool choice = false;	//flag for do..while

	do {

		cout << "Input the first velocity: > ";
		getline(cin, input);
		if (!is_correct_double(input)) {
			cout << "Input error" << endl;
		}
		else {
											
			v1 = stod(input);			//string to double
			v1_zero = is_zero(input);

			cout << "Input the second velocity: > ";
			getline(cin, input);
			if (!is_correct_double(input)) {
				cout << "Input error" << endl;
			}
			else {

				v2 = stod(input);
				v2_zero = is_zero(input);

				if (v1_zero && v2_zero) {
					cout << "Both trains are not moving, unpossible to solve" << endl;
				} 
				else {
					cout << "Input a distance between A and B: > ";
					getline(cin, input);
					if (!is_correct_double(input)) {
						cout << "Input error" << endl;
					}
					else {
							
						s = stod(input);
						
						//setprecision
						//cout << /*fixed <<*/ setprecision(10) << "v1: " << v1 << endl << "v2: " << v2 << endl << "s: " << s << endl;
						//cout << setprecision(18) << v1 << endl;
						
						t = s / (v1 + v2);
						d = v1*t;

						cout << setprecision(MAX_ACCEPTED_D_LEN) << "Distance from A to the meeting point: " << d << endl << "Time to meeting: " << t << endl;


					}

				}

			}

		}

		choice = get_cont_choice();

	} while (choice);

	return 0;
}
