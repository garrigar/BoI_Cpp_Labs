
#include <iostream>
#include <string>
using namespace std;

int euler(int n) {

	// ≈сли a1, a2, a3, ... -- все простые делители n, отличные друг от друга, то euler(n) = n*(1 - (1 / a1))*(1 - (1 / a2))*(1 - (1 / a3))*...
	// (Ёто следует из свойства мультипликативности функции Ёйлера)

	// введем первый множитель
	int result = n;

	// ƒалее ищем каждый [простой] делитель числа n перебором от 1 до sqrt(n)
	for (int i = 2; i*i <= n; ++i)
		if (n % i == 0) {            // ѕри нахождении каждого нового [простого] делител€ i числа n 							
			while (n % i == 0)       // будем делить n на i до исчезновнени€ этого сомножител€ из n
				n /= i;
			result -= result / i;    // и домножать result на (1 - (1 / i))
		}
	// ≈сли в конце получим n > 1, то это n -- простое число, и тоже делитель начального n
	if (n > 1)
		result -= result / n;
	
	// «аметим, что euler(1) = 1

	return result;
	
}

int main() {

	cout << "Euler's totient function" << endl;
	int n = 0;
	string input;

	char ctrl = 'N';
	bool choice = false;
	//do {

		cout << "Input a positive integer > ";
		getline(cin, input);

		cout << input << endl;
		
		for (int i = 0; ( (isdigit(input[i]) != 0) || (i <= input.length()) ); ++i) {}
		
		
		//cin >> n;

		//cout << "Result: " << euler(n) << endl;
		

		cout << "Continue? (Y/N) > ";
		//cin >> ctrl;
		 
		if ((ctrl == 'Y')||(ctrl == 'y')) choice = true;
		if ((ctrl == 'N')||(ctrl == 'n')) choice = false;

	//} while (choice);

	//cout << euler(3) << endl;
		cin.clear();
		cin.ignore();
		cin.get();
	//char c;
	//cin >> c;
	return 0;

}