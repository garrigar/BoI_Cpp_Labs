
#include <iostream>
#include <string>
using namespace std;

int euler(int n) {

	// ���� a1, a2, a3, ... -- ��� ������� �������� n, �������� ���� �� �����, �� euler(n) = n*(1 - (1 / a1))*(1 - (1 / a2))*(1 - (1 / a3))*...
	// (��� ������� �� �������� ������������������� ������� ������)

	// ������ ������ ���������
	int result = n;

	// ����� ���� ������ [�������] �������� ����� n ��������� �� 1 �� sqrt(n)
	for (int i = 2; i*i <= n; ++i)
		if (n % i == 0) {            // ��� ���������� ������� ������ [��������] �������� i ����� n 							
			while (n % i == 0)       // ����� ������ n �� i �� ������������� ����� ����������� �� n
				n /= i;
			result -= result / i;    // � ��������� result �� (1 - (1 / i))
		}
	// ���� � ����� ������� n > 1, �� ��� n -- ������� �����, � ���� �������� ���������� n
	if (n > 1)
		result -= result / n;
	
	// �������, ��� euler(1) = 1

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