
#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <string>
#include <queue>

using namespace std;
vector<string> emptyVecStr;
vector<int> emptyVecInt;
vector< vector<int> > emptyVecVecInt;
unordered_map<string, int> emptyMapStrInt;

// hope it is unnesessary, в точности то же делает и така€ же сложность, как у transform
/*
string to_lower_case(string s) {
	string ans = "";
	for (int i = 0; i < s.size(); ++i)
		if ('A' <= s[i] && s[i] <= 'Z')
			ans += (s[i] - 'A' + 'a');
		else ans += s[i];
		return ans;
}
*/
//

bool is_correct_word(string input) {				// check for correctness

	if (input.length() == 0)
		return false;									//if input is empty, then it's not correct
	for (int i = 0; (i < input.length()); ++i) {
		if (isalpha(input[i]) == 0)
			return false;								//if there's a non-digital char, then not correct
	}
	return true;
}

bool is_correct_filename(string input)
{ 
	string taboo = "\\/:*?\"<>|";
	if (input.length() == 0)
		return false;									//if input is empty, then it's not correct
	for (int i = 0; (i < input.length()); ++i) {
		if (taboo.find(input[i]) != string::npos)
			return false;								//if there's a non-digital char, then not correct
	}
	return true;  
}			

bool get_cont_choice(string msg) {					//to continue or not to continue?

	bool correct = false;					//correctness of a command, this variable is actually useless

	string input;

	while (!correct) {

		cout << msg << " (Y/N) > ";

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

int main()
{
	// TITLE
	cout << "Word Morph" << endl;
	
	do
	{	
		// LISTS INIT
		vector< vector<string> > words_IS;				// splitted by length words: string by number
		vector< unordered_map<string, int> > words_SI;	// splitted by length words: number by string
		words_IS.push_back(emptyVecStr);				// words_IS[0] -- no such words; now we must consider: size = .size() - 1
		words_SI.push_back(emptyMapStrInt);				// words_SI[0] -- no such words; now we must consider: size = .size() - 1

		// DICT FILE OPENING
		string filename;
		cout << "Input a dictionary filename > ";
		getline(cin, filename);
		if (!is_correct_filename(filename))
			cout << "Incorrect filename!" << endl;
		else {

			ifstream fin(filename);

			if (!fin.is_open())
				cout << "No file found!" << endl;
			else {
				
				// --- DICT INIT -----
				string str;
				int curLen;
				while (!fin.eof()) {
					getline(fin, str);							// there're space symbols in some words, like "south korea, south america"  
					transform(str.begin(), str.end(), str.begin(), tolower);		// to lowercase

					curLen = str.size();
					while (curLen > words_IS.size() - 1)		// .size() - 1 нормально, т.к. на данном этапе .size() не меньше 1
						words_IS.push_back(emptyVecStr);
					while (curLen > words_SI.size() - 1)
						words_SI.push_back(emptyMapStrInt);

					words_IS[curLen].push_back(str);
					words_SI[curLen][str] = words_SI[curLen].size();

				}

				fin.close();
				// -------------------
				if (words_IS.size() == 1)
					cout << "No words loaded, file was empty" << endl;
				else 
				{
					// ---- DEFINE GRAFS ----
					vector < vector< vector<int> > > g(words_IS.size(), emptyVecVecInt);	// графы в виде списков смежности by length, по аналогии с листами слов
																							// g[0] is empty, cause no 0-length words exist, now we must consider: size = .size() - 1
					
					vector<int> graph_initialized(words_IS.size(), 0);						// заполнен ли граф by length, по аналогии с листами слов
																							// g_i[0] is empty, cause no 0-length words exist, now we must consider: size = .size() - 1
					// ----------------------

					do {
						// FIRST WORD
						string begin;
						cout << "Input a source word > ";
						getline(cin, begin);
						if (!is_correct_word(begin))
							cout << "Seems like not a word!" << endl;
						else {
							transform(begin.begin(), begin.end(), begin.begin(), tolower);		// to lowercase

							int wl = begin.size();		// word length
							
							if (wl > words_IS.size() - 1)
								cout << "There're no words with this length in dictionary" << endl;
							else 
								if (words_SI[wl].find(begin) == words_SI[wl].end())				// if no begin found
									cout << "The word '" << begin << "' is not in current dictionary, sorry" << endl;
								else {

									// ------- LAZY GRAPH INIT ------------
									if (graph_initialized[wl] == 0) {
										string word;
										int w2index;
										for (size_t i = 0; i < words_IS[wl].size(); ++i) {
											g[wl].push_back(emptyVecInt);	// инициализируем вершины графа пустым списком

											word = words_IS[wl][i];

											for (size_t j = 0; j < word.size(); ++j) {
												char orig = word[j];
												for (word[j] = 'a'; word[j] <= 'z'; word[j]++)
													if (word[j] != orig) {

														if (words_SI[wl].find(word) != words_SI[wl].end()) {	// O(1), amort const
															w2index = words_SI[wl][word];						// O(1), amort const
															g[wl][i].push_back(w2index);

														}

													}
												word[j] = orig;
											}

										}
										graph_initialized[wl] = 1;
									}
									// ---------------------------------
									
									// ---------- BFS ------------
									int n = g[wl].size(); // число вершин
									int s = words_SI[wl][begin]; // номер стартовой вершины

									//ƒл€ разных начальных слов обходы будут разные, поэтому Ќ≈“ смысла хранить все вспомогательные данные обхода, отсортировав по длинам

									queue<int> q;			// ждущие обработки вершины
									q.push(s);					// помещаем первую вершину
									vector<int> used(n);	// вершина уже обработана?				P.S. «аполн€ютс€ значнием конструктора по умолчанию
									vector<int> d(n);		// массив длин путей
									vector<int>	p(n);		// массив предков
									used[s] = 1;				// used[s] := true || перва€ вершина обработана
									p[s] = -1;
									while (!q.empty()) {
										int v = q.front();
										q.pop();
										for (size_t i = 0; i < g[wl][v].size(); ++i) {
											int to = g[wl][v][i];
											if (used[to] == 0) {		// !used[to]
												used[to] = 1;			// used[to] := true
												q.push(to);
												d[to] = d[v] + 1;
												p[to] = v;
											}
										}
									}
									// -------------------------

									do {
										// SECOND WORD
										string end;
										cout << "Input a destination word > ";
										getline(cin, end);
										if (!is_correct_word(end))
											cout << "Seems like not a word!" << endl;
										else {
											transform(end.begin(), end.end(), end.begin(), tolower);		// to lowercase

											int wl2 = end.size();		// word 2 length

											if (wl2 != wl)						// if wl2 != wl
												cout << "Two words differ by length, impossible to solve" << endl;
											else
												
												if (words_SI[wl].find(end) == words_SI[wl].end())				// if no end found
													cout << "The word '" << end << "' is not in current dictionary, sorry" << endl;
												else
													if (end == begin) 
														cout << "Solution obvious: " << begin << " <-> " << end << endl;
													else {

														//“еперь надо восстановить и вывести кратчайший путь до вершины to:

														int to = words_SI[wl][end];

														if (used[to] == 0)				// !used[to]
															cout << "No solution" << endl;
														else {
															vector<int> path;
															for (int v = to; v != -1; v = p[v])
																path.push_back(v);
															cout << "Solution: ";
															for (int i = path.size() - 1; i >= 1; --i)
																cout << words_IS[wl][path[i]] << " -> ";
															cout << words_IS[wl][path[0]] << endl;
														}
													}
												

											
										}


									} while (get_cont_choice("Continue with this source word?"));

								}
							
						}


					} while (get_cont_choice("Continue with this dictionary?"));
				}
			}
		}


	} while (get_cont_choice("Continue?"));


	return 0;
}


/*
ofstream fout("output40.txt");
for (int i = 0; i < g[4].size(); ++i) {
	fout << endl << words_IS[4][i] << ":" << endl;
	for (int j = 0; j < g[4][i].size(); ++j){
		fout << words_IS[4][ g[4][i][j] ] << ' ' << "";
	}
}
fout.close();
*/

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
