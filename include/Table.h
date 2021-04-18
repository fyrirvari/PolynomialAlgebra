#pragma once
#include <set>

//		#############################
//		#		TABLE INTERFACE		#
//		#############################

template<class K, class T>
class Entry
{
public:
	Entry(K key, T Value) : key(key), value(value) {}

	K key;
	T value;
};

template<class K, class T>
class Table
{
public:
	// Capacity
	virtual bool empty() = 0;
	virtual int size() = 0;

	// Modifiers
	virtual T erase(const K& key) = 0;
	virtual void insert(const Entry<K, T>& entry) = 0;
	virtual void insert(const K& key, const T& value) = 0;
	virtual void merge(const Table& t) = 0;

	// Lookup
	virtual bool contains_key(const K& key) const = 0;
	virtual const Entry<K,T> find(const K& key) const = 0;

	// Element access
	virtual T& operator[](const K& key) = 0;
	virtual const T& operator[](const K& key) const = 0;

	// Member functions
	virtual ~Table() = 0;
	virtual Table& operator=(const Table& t) = 0;
};