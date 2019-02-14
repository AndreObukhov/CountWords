#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <fstream>

using namespace std;

void StringPrepare(string& str);
void Parentheses(string& str);
void PrintWords(const vector<string>& words, const int& N, int& count);

template <class T>
ostream& operator << (ostream& os, const vector<T>& s) {
    os << "{";
    bool first = true;
    for (const auto& x : s) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << x;
    }
    return os << "}";
}

//переопределенный оператор вывода словаря
template <class K, class V>
ostream& operator << (ostream& os, const map<K, V>& m) {
    os << "{";
    bool first = true;
    for (const auto& kv : m) {
        if (!first) {
            os << "\n";
        }
        first = false;
        os << kv.first << ": " << kv.second;
    }
    return os << "}";
}

void Parentheses(string& str) {     //разбираемся со скобками
    char last_character = str[str.size() - 1];
    if (last_character == ')' || last_character == ']' || last_character == '}'
        || last_character == '"') {
        str.pop_back();
    }

    char first_character = str[0];
    if (first_character == '(' || first_character == '[' || first_character == '{'
            || first_character == '"') {
        str.erase(begin(str));
    }
    if (first_character == '-') {
        str.erase(begin(str));
    }
}

void StringPrepare(string& str) {
    //converting string to lower case
    transform(str.begin(), str.end(), str.begin(), ::tolower);

    //deleting point at the back (all signs needed)
    char last_character = str[str.size() - 1];
    //cout << last_character << endl;
    if (last_character == '.' || last_character == ','
        || last_character == '!' || last_character == '?') {
        str.pop_back();
    }

    Parentheses(str);
}

//чтобы вывести нужное количество слов даже если есть слова "повторяющегося количества"
void PrintWords(const vector<string>& words, const int& N, int& count) {
    for(const auto& str : words) {
        cout << str << endl;
        count ++;
        if(count >= N ) {
            break;
        }
    }
}

int main() {
    string s;
    map<string, int> WordsNumber;

    ifstream input("input.txt");

    for(input >> s; !input.eof(); input >> s) {     //считываем до конца файла
        StringPrepare(s);
        WordsNumber[s]++;
    }

    ofstream output("output.txt");
    output << WordsNumber << endl;
    output << "--- --- --- --- ---" << endl;

    map<int, vector<string>> CountWords;

    for(const auto& thing : WordsNumber) {
        //добавляем слово в вектор строк, соответствующий
        //количеству вхождений этого слова

        CountWords[thing.second].push_back(thing.first);
    }

    output << CountWords << endl;     //вывод вновь составленного словаря в файл
    output.close();

    int N;      //сколько слов нужно вывести
    cin >> N;
    int count = 0;

    auto nd = end(CountWords);      //начинаем с конца словаря, т.к. там наибольшие ключи(количества повторений)
    while (count < N) {
        nd --;
        PrintWords(nd->second, N, count);

        //cout << nd->first << " " << nd->second << endl;
        //count ++;
    }

    return 0;
}