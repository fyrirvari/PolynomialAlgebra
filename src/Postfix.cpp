#include "postfix.h"
#include "stack.h"

vector<string> TPostfix::split(const string& str)
{
	vector<string> separated;
	stringstream ss(str);
	string cur;
	while (ss >> cur)
		separated.push_back(cur);
	return separated;
}

template <class T>
bool TPostfix::contains(const map<string, T>& map, const string& key)
{
	for (pair<const string, T> pair : map)
		if (pair.first == key) return true;
	return false;
}

void TPostfix::ToPostfix(const string& infix)
{
	this->infix = infix;
	vector<string> separated = split(infix);
	postfix = convert(separated, 0, separated.size());
}

size_t TPostfix::findClosingBracket(const vector<string>& separated, size_t openingBracketIndex)
{
	TStack<string> brackets;
	for (size_t i = openingBracketIndex + 1; i < separated.size(); ++i)
	{
		if (separated[i] == "(")
			brackets.push(separated[i]);
		if (separated[i] == ")")
			if (brackets.empty()) return i;
			else brackets.pop();
	}
	throw exception("incorrect expression");
}

string TPostfix::convert(vector<string>& separated, size_t first, size_t last)
{
	string postfix = "";
	TStack<string> operations;
	for (size_t i = first; i < last; ++i)
	{
		{
			bool sub = false;
			while (separated[i][0] == '-')
			{
				sub = !sub;
				separated[i] = separated[i].substr(1, separated[i].length());
			}
			if (sub)
			{
				postfix += "0 ";
				operations.push("-");
			}
		}
		if (!contains(table, separated[i]))	
			postfix += separated[i] + " ";
		else if (separated[i] == "(")
		{
			size_t closingBracket = findClosingBracket(separated, i);
			postfix += convert(separated, i + 1, closingBracket) + " ";
			i = closingBracket;
		}
		else
		{
			while (!operations.empty() && table[operations.peek()].priority >= table[separated[i]].priority)
			{
				postfix += operations.pop() + " ";
			}
			operations.push(separated[i]);
		}
	}
	while (!operations.empty())
	{
		postfix += operations.pop() + " ";
	}
	postfix.erase(postfix.size() - 1);
	return postfix;
}

bool TPostfix::isDigit(char c)
{
	return '0' <= c && c <= '9';
}

bool TPostfix::isNumber(const string& suspect)
{
	bool pointEarlier = false;
	for (char c : suspect)
	{
		if (c == '.')
			if (pointEarlier) return false;
			else pointEarlier = true;
		else if (!isDigit(c))
			return false;
	}
	return true;
}

double TPostfix::Calculate()
{
	return Calculate(HashTable<std::string, Polynomial>(0), 0, 0, 0);
}

double TPostfix::Calculate(const Table<std::string, Polynomial>& poly, double x, double y, double z)
{
	vector<string> separated = split(postfix);
	TStack<double> results;
	map<string, double> variables;
	for (string element : separated)
	{
		if (!contains(table, element))
		{
			if (poly.contains_key(element))
				results.push(poly[element].calculate_value(x, y, z));
			else if (contains(constants, element))
				results.push(constants[element]);
			else if (isNumber(element))
				results.push(strtod(element.c_str(), nullptr));
			else
			{
				if (!contains(variables, element))
				{
					double value;
					cout << "Enter " + element + ": ";
					cin >> value;
					variables.emplace(element, value);
				}
				results.push(variables[element]);
			}
		}
		else
		{
			switch (table[element].operands)
			{
			case 1:
			{
				double variable = results.pop();
				if (element == "ln") results.push(log(variable));
				if (element == "sin") results.push(sin(variable));
				if (element == "cos") results.push(cos(variable));
				if (element == "sqrt") results.push(sqrt(variable));
				break;
			}
			case 2:
			{
				double second = results.pop();
				double first = results.pop();
				if (element == "+") results.push(first + second);
				if (element == "-")	results.push(first - second);
				if (element == "*") results.push(first * second);
				if (element == "/") results.push(first / second);
				if (element == "^") results.push(pow(first, second));
				if (element == "log") results.push(log(second) / log(first));
				break;
			}
			default:
				break;
			}
		}
	}
	return results.pop();
}
