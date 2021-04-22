#ifndef __POSTFIX_H__
#define __POSTFIX_H__

#include <string>
#include "Stack.h"
#include <map>
#include <vector>
#include <iostream>
#include <cmath>
#include <sstream>

#include "Table.h"
#include "HashTable.h"
#include "Polynomial.h"

using namespace std;

class TPostfix
{
	struct data
	{
		int priority;
		int operands;
	};
	string infix;
	string postfix;
	map<string, struct data> table = {
		{"(", {0, 0}},
		{")", {0, 0}},
		{"+", {1, 2}},
		{"-", {1, 2}},
		{"*", {2, 2}},
		{"/", {2, 2}},
		{"^", {2, 2}},
		{"ln", {3, 1}},
		{"sin", {3, 1}},
		{"cos", {3, 1}},
		{"sqrt", {3, 1}},
		{"log", {3, 2}}
	};
	map<string, double> constants = {
		{"pi", 3.14159265358979323846},
		{"e", 2.71828182845904523536},
		{"log2e", 1.44269504088896340736},
		{"log10e", 0.434294481903251827651},
		{"ln2", 0.693147180559945309417},
		{"ln10", 2.30258509299404568402}
	};
	vector<string> split(const string& str);
	template <class T>
	bool contains(const map<string, T>& map, const string& key);
	bool isDigit(char c);
	bool isNumber(const string& suspect);
	string convert(vector<string>& separated, size_t first, size_t last);
	size_t findClosingBracket(const vector<string>& separated, size_t openingBracketIndex);
public:
	TPostfix()
	{
		ToPostfix("a + b");
	}
	TPostfix(const string& infix)
	{
		ToPostfix(infix);
	}
	string GetInfix() { return infix; }
	string GetPostfix() { return postfix; }
	void ToPostfix(const string& infix);
	double Calculate(); // Ввод переменных, вычисление по постфиксной форме
	
	double Calculate(const Table<std::string, Polynomial>& poly, double x, double y, double z); // Для полиномов
};

#endif
