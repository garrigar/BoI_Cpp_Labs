
#include <iostream>
#include <string>

using namespace std;

long long euler(long long n) {

	// Если a1, a2, a3, ... -- все простые делители n, отличные друг от друга, то euler(n) = n*(1 - (1 / a1))*(1 - (1 / a2))*(1 - (1 / a3))*...
	// (Это следует из свойства мультипликативности функции Эйлера)

	// введем первый множитель
	long long result = n;

	// Далее ищем каждый [простой] делитель числа n перебором от 1 до sqrt(n)
	for (long long i = 2; i*i <= n; ++i)
		if (n % i == 0) {            // При нахождении каждого нового [простого] делителя i числа n 							
			while (n % i == 0)       // будем делить n на i до исчезновнения этого сомножителя из n
				n /= i;
			result -= result / i;    // и домножать result на (1 - (1 / i))
		}
	// Если в конце получим n > 1, то это n -- простое число, и тоже делитель начального n
	if (n > 1)
		result -= result / n;
	
	// Заметим, что euler(1) = 1

	return result;
	
}

int main() {

	const int MAX_ACCEPTED_LL_LEN = 18;
	
	cout << "Euler's totient function" << endl;
	long long n = 0;
	
	string input;	//using a string as an input buffer
	bool correct;	//input correctness statement

	char ctrl = 'N';		//control character
	bool choice = false;	//flag for do..while
	
	do {

		cout << "Input a positive integer [ < 10^18] > ";
		getline(cin, input);
		
		//-- check for correctness
		correct = true;										//suppose is correct
		if (input.length() == 0) correct = false;			//if input is empty, then it's not correct
		for (int i = 0;  (i < input.length()) ; ++i) {
			if (isdigit(input[i]) == 0) correct = false;	//if there's a non-digital char, then not correct
		}
		if (input.length() > MAX_ACCEPTED_LL_LEN) correct = false;			//if there're 19+ characters, then this couldn't be loaded into long long (we need to be < 10^18)
		//--

		if (!correct) {							//error
			cout << "Input error" << endl;
		} else {								//normal
			//n = atoi(input.c_str());
			n = stoll(input);			//string to long long
			
			if (n == 0) {
				cout << "Error, Euler's totient cannot be evaluated at zero" << endl;
			} else {
				cout << "Result: " << euler(n) << endl;
			}
			
		}
		
		//to continue or not to continue?
		correct = false;		//correctness of a command
		while (!correct) {
			
			cout << "Continue? (Y/N) > ";
		
			getline(cin, input);

			if (input.length() != 1) {
				correct = false;
			} else {
				ctrl = input[0];
				switch (ctrl) {
						case 'Y': {
							correct = true; 
							choice = true; 
							break;
						}
						case 'y': {
							correct = true;
							choice = true;
							break;
						}
						case 'N': {
							correct = true; 
							choice = false; 
							break;
						}
						case 'n': {
							correct = true;
							choice = false;
							break;
						}
						default: {correct = false;}
				}
			}
		}
		
		//if ((ctrl == 'Y')||(ctrl == 'y')) choice = true;
		//if ((ctrl == 'N')||(ctrl == 'n')) choice = false;
	
		//cin.ignore();

	} while (choice);

	//cin.clear();
	//cin.get();
	//char c;
	//cin >> c;

	return 0;
}