#pragma once
#include <set>

//		#############################
//		#		TABLE INTERFACE		#
//		#############################

template<class K, class T>
struct Entry
{
	K key;
	T value;
};

template<class K, class T>
class Table
{
public:
	// Capacity
	virtual bool empty() const = 0;
	virtual int size() const = 0;

	// Modifiers
	virtual T erase(const K& key) = 0;
	virtual void insert(const Entry<K, T>& entry) = 0;
	virtual void insert(const K& key, const T& value) = 0;

	// Lookup
	virtual bool contains_key(const K& key) const = 0;
	virtual Entry<K, T>* find(const K& key) const = 0;

	// Element access
	virtual T* get(const K& key, T* def = nullptr) const = 0;
	virtual T& operator[](const K& key) = 0;
	virtual const T& operator[](const K& key) const = 0;

	// Member functions
	virtual ~Table() = 0;
};




//#pragma once
//#include <set>
//
////		#############################
////		#		TABLE INTERFACE		#
////		#############################
//
//template<class K, class T>
//class Table
//{
//public:
//	class Entry
//	{
//	public:
//		Entry(K key, T Value) : key(key), value(value) {}
//
//		K key;
//		T value;
//	};
//public:
//	// Iterators
//	virtual class iterator;
//
//	virtual iterator begin() = 0;
//	virtual iterator end() = 0;
//
//	// Capacity
//	virtual bool empty() = 0;
//	virtual int size() = 0;
//
//	// Modifiers
//	virtual T erase(iterator& pos) = 0;
//	virtual void insert(const Entry& entry) = 0;
//	virtual void insert(const K& key, const T& value) = 0;
//	virtual void merge(const Table& t) = 0;
//
//	// Lookup
//	virtual bool contains_key(const K& key) const = 0;
//	virtual bool contains_value(const T& value) const = 0;
//	virtual const iterator find(const K& key) = 0;
//
//	virtual std::set<Entry> entry_set() = 0;
//	virtual std::set<K> key_set() = 0;
//
//	virtual void swap(const Table& t) = 0;
//	//	──────────── before swap ────────────
//	//	t1: { α : alpha, β : beta, γ : gamma }
//	//	t2: { δ : delta, ε : epsilon }
//	//	──────────── after swap ────────────
//	//	t1: { δ : delta, ε : epsilon }
//	//	t2: { α : alpha, β : beta, γ : gamma }
//
//	// Element access
//	virtual T& operator[](const K& key) = 0;
//
//	// Member functions
//	virtual ~Table() = 0;
//	virtual Table& operator=(const Table& t) = 0
//};