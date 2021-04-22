#pragma once
#include "Table.h"
#include "List.h"

template<class K, class T>
class HashTable : public Table<K, T>
{
	List<Entry<K, T>>* cells;
	int _size;
	int _c_size;

	void init() const
	{
		_size = 0;
		cells = new List<Entry<K, T>>[_c_size];
	}

	int hash(const K& key) const
	{
		return reinterpret_cast<int>(key) % _c_size;
	}
public:
	HashTable(int _c_size = 20) : _c_size(_c_size) {
		if (_c_size)
			throw "Illegal argument for size";
		init();
	}
	HashTable(const HashTable& ht) : _c_size(ht._c_size)
	{
		init();
		*this = ht;
	}
	~HashTable()
	{
		delete cells;
	}
	bool empty() const
	{
		return _size == 0;
	}
	bool contains_key(const K& key) const
	{
		for (Entry<K, T> entry : cells[hash(key)])
			if (entry.key == key)
				return true;
		return false;
	}

	int size() const
	{
		return _size;
	}

	T erase(const K& key)
	{
		List<Entry<K, T>>& l = cells[hash(key)];
		for (int i = 0; i < l.size(); i++)
		{
			if (l[i].key == key)
				l.erase(i);
		}
		--_size;
	}

	void insert(const Entry<K, T>& entry)
	{
		List<Entry<K, T>>& l = cells[hash(entry.key)];
		for (int i = 0; i < l.size(); i++)
		{
			if (l[i].key == entry.key)
			{
				l[i].value = entry.value;
				return;
			}
		}
		l.push(entry);
		++_size;
	}

	void insert(const K& key, const T& value)
	{
		insert(Entry<K, T>{key, value});
	}

	Entry<K, T>* find(const K& key) const
	{
		List<Entry<K, T>>& l = cells[hash(key)];
		for (int i = 0; i < l.size(); i++)
		{
			if (l[i].key == key)
			{
				return new Entry<K, T>(l[i]);
			}
		}
		return nullptr;
	}

	T* get(const K& key, T* def = nullptr) const
	{
		List<Entry<K, T>>& l = cells[hash(key)];
		for (int i = 0; i < l.size(); i++)
		{
			if (l[i].key == key)
			{
				return &l[i].value;
			}
		}
		return nullptr;
	}

	T& operator[](const K& key)
	{
		T* val = get(key);
		if (val == nullptr)
			throw "Pair \"key-value\" with that key doesn't exist";
		else
			return *val;
	}

	const T& operator[](const K& key) const
	{
		T* val = get(key);
		if (val == nullptr)
			throw "Pair \"key-value\" with that key doesn't exist";
		else
			return *val;
	}

	HashTable& operator=(const HashTable& ht)
	{
		if (this != &ht)
		{
			delete cells;
			_c_size = ht._c_size;
			init();
			for (int i = 0; i < _c_size; ++i)
				cells[i] = ht.cells[i];
		}
		return *this;
	}
};

//#include "List.h"
//
//template<class K, class T>
//class HashTable : public Table<K, T>
//{
//private:
//	class Node
//	{
//	public:
//		Node(const Table<K, T>::Entry& entry, Node *next) : entry(entry), next(next) {}
//
//		Table<K, T>::Entry entry;
//		Node* next;
//	};
//public:
//	class iterator : public Table<K, T>::iterator
//	{
//	private:
//		Node* node;
//		int cell;
//	public:
//		iterator() : node(nullptr), cell(-1) {}
//		iterator(int cell, Node* node) : node(node), cell(cell) {}
//		iterator(const iterator& it) : node(it.node), cell(it.node) {}
//
//		bool empty()
//		{
//			if (cell < 0 || cell >= _c_size)
//				return true;
//			return false;
//		}
//
//		iterator& operator=(const iterator& it)
//		{
//			node = it.node;
//			cell = it.cell;
//			return *this;
//		}
//
//		bool operator==(const iterator& it) const
//		{
//			return node == it.node && cell == it.cell;
//		}
//
//		bool operator!=(const iterator& it) const
//		{
//			return !(node == it.node);
//		}
//
//		iterator& operator++()
//		{
//			if (cell < 0 || cell >=_c_size)
//				throw "Increment an empty iterator";
//			if (*this == _end)
//				throw "Increment end iterator";
//			if (node != nullptr)
//				node = node->next;
//			else
//			{
//				for (; cell != _c_size - 1; ++cell)
//				{
//
//					if (node != nullptr || *this == _end)
//						return *this;
//					{
//						*this = cells[cell + 1];
//					}
//				}
//			}
//
//			/*if (node == nullptr || cell < 0 || cell >= _c_size)
//				throw "Increment an empty iterator";
//			do 
//			{
//				node = node->next;
//				if (node == nullptr && cell == _c_size - 1)
//					throw "Increment end iterator";
//				else if (node == nullptr)
//				{
//					++cell;
//					node = cells[cell].node;
//				}
//			} while (node == nullptr)	*/
//
//			return *this;
//		}
//
//		iterator operator++(int)
//		{
//			iterator it = *this;
//			++(*this);
//			return it;
//		}
//
//		iterator operator+(int index) const
//		{
//			iterator it = *this;
//			for (int i = 0; i < index; ++i)
//				++it;
//			return it;
//		}
//
//		Table<K, T>::Entry& operator*() const
//		{
//			if (node == nullptr || cell < 0 || cell >= _c_size)
//				throw "Dereference an empty iterator";
//
//			return node->entry;
//		}
//
//		friend class HashTable;
//	};
//private:
//	int _size;
//	iterator _begin;
//	iterator _end;
//
//	int _c_size;
//	iterator* cells;
//private:
//	void init()
//	{
//		for (int i = 0; i < _c_size; ++i)
//			cells[i].cell = i;
//		_begin = cells[0];
//		_end = iterator(_c_size -1, nullptr);
//		_size = 0;
//	}
//
//	int hash(const K& key)
//	{
//		return reinterpret_cast<int>(key) % _c_size;
//	}
//public:
//	HashTable(int c_size) : _c_size(c_size), cells(new iterator[_c_size])
//	{ 
//		init();
//	}
//
//	HashTable(const HashTable& ht) : HashTable(), _c_size(ht._c_size)
//	{
//		init();
//		for (auto entry : ht)
//			insert(entry);
//	}
//
//	~HashTable() override
//	{
//		
//	}
//
//	iterator begin()
//	{
//		return _begin;
//	}
//
//	iterator end()
//	{
//		return _end;
//	}
//
//	bool empty()
//	{
//		return _size == 0;
//	}
//
//	int size()
//	{
//		return _size;
//	}
//
//	T erase(iterator& pos)
//	{
//		if (pos.node == nullptr || pos.cell < 0 || pos.cell >= _c_size)
//			throw "incorrect position of element";
//		iterator prev = cells[pos.cell];
//		while (prev.node->next != pos.node)
//			prev.node = prev.node->next;
//		prev.node->next = pos.node->next;
//		delete pos.node;
//	}
//
//	void insert(const Table<K, T>::Entry& entry)
//	{
//		iterator it = cells[hash(entry.key)];
//		if (it.node == nullptr)
//		{
//			it.node = new Node(entry, nullptr);
//			return;
//		}
//		iterator prev;
//		do
//		{
//			prev = it;
//			it.node = it.node->next;
//			if (*prev.key == entry.key)
//			{
//				*prev.value = entry.value;
//				return;
//			}
//		} while (it.node != nullptr);
//		prev.node->next = new Node(entry, nullptr);
//		++_size;
//	}
//
//	void insert(const K& key, const T& value)
//	{
//		insert(Table<K, T>::Entry(key, value));
//	}
//
//	void merge(const Table<K, T>& ht)
//	{
//		for (auto entry : ht)
//			insert(entry);
//	}
//
//	bool contains_key(const K& key) const
//	{
//		for (auto entry : *this)
//			if (entry.key == key)
//				return true;
//		return false;
//	}
//
//	bool contains_value(const T& value) const
//	{
//		for (auto entry : *this)
//			if (entry.value == value)
//				return true;
//		return false;
//	}
//
//	const iterator find(const K& key) const
//	{
//		for (iterator it = cells[hash(key)]; it.node != nullptr; it.node = it.node->next)
//			if (*it.key == key)
//				return it;
//		return iterator();
//	}
//
//	std::set<Table<K, T>::Entry> entry_set() const
//	{
//		std::set<Table<K, T>::Entry> s;
//		for (auto entry : *this)
//			s.insert(entry);
//		return s;
//	}
//
//	std::set<K> key_set() const
//	{
//		std::set<K> s;
//		for (auto entry : *this)
//			s.insert(entry.key);
//		return s;
//	}
//
//	void swap(const HashTable<K, T>& t)
//	{
//	
//	}
//};