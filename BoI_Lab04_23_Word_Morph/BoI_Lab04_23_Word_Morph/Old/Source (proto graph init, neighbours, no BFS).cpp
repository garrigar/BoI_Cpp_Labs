
#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <string>

using namespace std;
vector<string> emptyVecStr;
vector<int> emptyVecInt;
vector< vector<int> > emptyVecVecInt;
unordered_map<string, int> emptyMapStrInt;

void get_neighbours(string s, vector<string>& nb) {
	string ans;
	string left, right;
	int len = s.size();
	for (int i = 0; i < s.size(); ++i) {
		left = s.substr(0, i);
		right = ( (i != (s.size() - 1)) ? s.substr(i + 1) : "" );
		for (char ch = 'a'; ch <= 'z'; ch++)
			if (ch != s[i]) {
				ans = left + ch + right;
				nb.push_back(ans);
			}		
	}


}

int main()
{
	
	vector< vector<string> > words_IS;				// splitted by length words: string by number
	vector< unordered_map<string, int> > words_SI;	// splitted by length words: number by string
	words_IS.push_back(emptyVecStr);				// words_IS[0] -- no such words; now we must consider: size = .size() - 1
	words_SI.push_back(emptyMapStrInt);				// words_SI[0] -- no such words; now we must consider: size = .size() - 1

	ifstream fin("nounlist.txt");
	string str;

	// --- FILE NOT OPEN ---
	if (!fin.is_open()) {
		cout << "Can't open file" << endl;
		system("pause");
		return 1;
	}
	// ---------------------

	// -------- INIT -------
	int curLen;
	while (!fin.eof()) {
		getline(fin, str);		// there're space symbols in some words, like "south korea, south america"  

		curLen = str.size();
		while (curLen > words_IS.size() - 1)
			words_IS.push_back(emptyVecStr);
		while (curLen > words_SI.size() - 1)
			words_SI.push_back(emptyMapStrInt);
		
		words_IS[curLen].push_back(str);
		words_SI[curLen][str] = words_SI[curLen].size();
		
	}

	fin.close();
	// -------------------

	string begin = "bot";
	string end = "duk";

	int wl = begin.size();		// word length
	///TODO
	// if wl != wl
	// if no begin found
	// if no end found


	vector < vector< vector<int> > > g;	// графы в виде списков смежности by length
	g.push_back(emptyVecVecInt);		// g[0] is empty, cause no 0-length words exist, now we must consider: size = .size() - 1
	while (wl > g.size() - 1)
		g.push_back(emptyVecVecInt);

	for (int i = 0; i < words_IS[wl].size(); ++i)
		g[wl].push_back(emptyVecInt);	// инициализируем вершины графа пустым списком
	
	string word1;
	int w2index;
	for (int i = 0; i < words_IS[wl].size(); ++i) {
		word1 = words_IS[wl][i];
		vector<string> neighbours;
		get_neighbours(word1, neighbours);

		for (int j = 0; j < neighbours.size(); ++j) {
			if (words_SI[wl].find(neighbours[j]) != words_SI[wl].end()) {		// O(1), amort const
				w2index = words_SI[wl][ neighbours[j] ];						// O(1), amort const
				g[wl][i].push_back(w2index);
				///g[wl][w2index].push_back(i);
			}

		}
		
	}

	//
	ofstream fout("output1.txt");
	for (int i = 0; i < g[3].size(); ++i) {
		fout << endl << words_IS[3][i] << ":" << endl;
		for (int j = 0; j < g[3][i].size(); ++j){
			fout << words_IS[3][ g[3][i][j] ] << ' ' << "";
		}
	}
	fout.close();
	//

	/*
	vector<string> nei;
	string myword = "";
	get_neighbours(myword, nei);
	for (int i = 0; i < nei.size(); ++i)
		cout << nei[i] << i << endl;
	*/

	/*
	ofstream fout("output.txt");

	for (int i = 1; i <= words.size() - 1; ++i) {
		fout << endl << i << endl;
		for (int j = 0; j < words[i].size(); ++j)
			fout << words[i][j] << ' ';
	}
	
	fout.close();
	*/
	

	system("pause");
	return 0;
}