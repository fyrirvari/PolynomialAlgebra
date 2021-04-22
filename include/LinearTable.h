#pragma once
#include "Polynomial.h"
#include "Table.h"

template <class T>
class LinearTable : public Table<std::string, T> //линейна€ таблица на масиве
{
private:
	Entry<std::string, T> *table;
	int current_size;
	int max_size;

	void IncreasingTheSize();
	bool CheckingTheKey(std::string key);
public:
	LinearTable();

	bool empty();
	int size();

	T erase(const std::string& key);
	void insert(const Entry<std::string, T>& entry);
	void insert(const std::string& key, const T& value);

	// Lookup
	int search(const std::string& key) const;
	bool contains_key(const std::string& key) const;
	virtual const Entry<std::string, T> find(const std::string& key) const;

	// Element access
	//virtual T& operator[](const std::string& key);
//	virtual const T& operator[](const std::string& key) const;

	// Member functions
	//virtual ~Table();
//	virtual Table& operator=(const Table& t);


};


template <class T>
LinearTable<T>::LinearTable() : current_size(0), max_size(2)
{
	table = nullptr;
}

/*template <class T>
LinearTable<T>::~Table()
{
	delete[] table;
	table = nullptr;
}*/

template <class T>
bool LinearTable<T>::empty()
{
	if (current_size == 0)
		return true;
	return false;
}

template <class T>
int LinearTable<T>::size()
{
	return current_size;
}

template <class T>
void LinearTable<T>::IncreasingTheSize()
{
	Entry<std::string, T> *tmp = new Entry<std::string, T>[max_size * 2];
	for (int i = 0; i < max_size; i++)
	{
		tmp[i].key = table[i].key;
		tmp[i].value = table[i].value;
	}
	delete[] table;
	max_size *= 2;
	table = new Entry<std::string, T>[max_size];
	for (int i = 0; i < max_size; i++)
	{
		table[i].key = tmp[i].key;
		table[i].value = table[i].value;
	}
	delete[] tmp;
}

template <class T>
bool LinearTable<T>::CheckingTheKey(std::string key)
{
	for (int i = 0; i < current_size; i++)
	{
		if (key == table[i].key)
			return false;
	}
	return true;
}

template <class T>
void LinearTable<T>::insert(const Entry<std::string, T>& entry)
{

	if (empty())
		table = new Entry<std::string, T>[max_size]; //если таблица пуста, выделим пам€ть

	if (!CheckingTheKey(entry.key))
		throw "-1";

	if (current_size == max_size)//если в таблице не хватает места, выделим доп. пам€ть
		IncreasingTheSize();

	table[current_size].key = entry.key;
	table[current_size].value = entry.value;
	current_size++;
}

template <class T>
void LinearTable<T>::insert(const std::string& key, const T& value)
{

	if (empty())
		table = new Entry<std::string, T>[max_size]; //если таблица пуста, выделим пам€ть

	if (!CheckingTheKey(key))
		throw "-1";

	if (current_size == max_size)//если в таблице не хватает места, выделим доп. пам€ть
		IncreasingTheSize();

	table[current_size].key = key;
	table[current_size].value = value;
	current_size++;
}

template <class T>
int LinearTable<T>::search(const std::string& key) const
{
	for (int i = 0; i < current_size; i++)
	{
		if (table[i].key == key)
			return i;
	}
	return -1;
}

template<class T>
bool LinearTable<T>::contains_key(const std::string& key) const
{
	if (search(key) != -1)
		return true;
	return false;
}

template<class T>
const Entry<std::string, T> LinearTable<T>::find(const std::string& key) const
{
	int index = search(key);
	if (index != -1)
		return table[index];
	throw "the entry was not found in the table";

}

template<class T>
T LinearTable<T>::erase(const std::string& key)
{
	int index = search(key);
	if (index != -1)
	{
		table[index].key = table[current_size - 1].key;
		table[index].value = table[current_size - 1].value;
		Entry<std::string, T> *tmp = new Entry<std::string, T>[--current_size];
		for (int i = 0; i < current_size; i++)
		{
			tmp[i].key = table[i].key;
			tmp[i].value = table[i].value;
		}
		delete[] table;
		table = new Entry<std::string, T>[current_size];
		for (int i = 0; i < max_size; i++)
		{
			table[i].key = tmp[i].key;
			table[i].value = tmp[i].value;
		}
		delete[] tmp;
	}
	throw "the entry was not found in the table";
}



