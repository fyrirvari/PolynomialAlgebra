#pragma once
#include <iostream>

template<class T>
class List
{
private:
	class Node
	{
	public:
		Node(T val, Node* next = nullptr, Node* prev = nullptr) : val(val), next(next), prev(prev) {}
		Node(Node* next, Node* prev) : next(next), prev(prev) {}
		~Node() {}

		T val;
		Node* next;
		Node* prev;
	};
public:
	class iterator
	{
	private:
		Node* node;
	public:
		iterator() : node(nullptr) {}
		iterator(Node* node) : node(node) {}
		iterator(const iterator& it) : node(it.node) {}

		iterator& operator=(const iterator& it)
		{
			node = it.node;
			return *this;
		}

		bool operator==(const iterator& it) const
		{
			return node == it.node;
		}

		bool operator!=(const iterator& it) const
		{
			return !(node == it.node);
		}

		iterator& operator++()
		{
			if (node == nullptr)
				throw "Increment an empty iterator";

			node = node->next;
			return *this;
		}

		iterator& operator--()
		{
			if (node == nullptr)
				throw "Decrement an empty iterator";
			if (node->prev == nullptr)
				throw "Decrement begin iterator";

			node = node->prev;
			return *this;
		}
		
		iterator operator++(int)
		{
			iterator it = *this;
			++(*this);
			return it;
		}

		iterator operator--(int)
		{
			iterator it = *this;
			--(*this);
			return it;
		}

		iterator operator+(int index) const
		{
			iterator it = *this;
			for (int i = 0; i < index; ++i)
				++it;
			return it;
		}
		
		iterator operator-(int index) const
		{
			iterator it = *this;
			for (int i = 0; i < index; ++i)
				--it;
			return it;
		}

		T& operator*() const
		{
			if (node == nullptr)
				throw "Dereference an empty iterator";

			return node->val;
		}

		friend class List;
	};
private:
	iterator _begin;
	iterator _end;
	int _size;
public:
	List() : _size(0) {}
	List(const List& l) : _size(0)
	{
		*this = l;
	}
	~List()
	{
		clear();
	}

	inline iterator begin() const { return _begin; }
	inline iterator end() const { return iterator(); }

	inline T& front() const { return *_begin; }
	inline T& back() const { return *_end; }

	inline bool empty() const { return _size == 0; }
	inline int size() const { return _size; }

	void clear()
	{
		while (!empty())
		{
			T* tmp = pop();
			if (tmp != nullptr)
				delete tmp;
		}
	}

	void push(const T& val)
	{
		if (_begin == nullptr)
		{
			_end = _begin = new Node(val);
		}
		else
		{
			_end.node->next = new Node(val, nullptr, _end.node);
			++_end;
		}
		++_size;
	}

	T* pop()
	{
		T* val = nullptr;
		if (!empty())
		{
			if (_begin == _end)
			{
				val = new T(*_end);
				delete _end.node;
				_end = _begin = nullptr;
			}
			else
			{
				val = new T(*_end);
				--_end;
				delete _end.node->next;
				_end.node->next = nullptr;
			}
			--_size;
		}
		return val;
	}

	void insert(const T& val, int index)
	{
		if (index < 0 || _size < index)
			throw "Illegal index";
		
		if (index == _size)
		{
			push(val);
			--_size;
		}
		else if (index == 0)
		{
			_begin.node->prev = new Node(val, _begin.node, nullptr);
			--_begin;
		}
		else
		{
			iterator it = _begin + index;
			Node* node = new Node(val, it.node, (it - 1).node);
			(it - 1).node->next = node;
			it.node->prev = node;
		}
		++_size;
	}

	void emplace(const T& val, int index)
	{
		if (index < 0 || _size <= index)
			throw "Illegal index";
		
		*(_begin + index) = val;
	}

	T* erase(int index)
	{
		if (index < 0 || _size <= index)
			throw "Illegal index";

		T* val = nullptr;
		if (index == _size - 1)
		{
			val = pop();
			++_size;
		}
		else if (index == 0)
		{
			val = new T(*_begin);
			++_begin;
			delete _begin.node->prev;
			_begin.node->prev = nullptr;
		}
		else
		{
			iterator it = _begin + index;
			(it - 1).node->next = it.node->next;
			(it + 1).node->prev = it.node->prev;
			val = new T(*it);
			delete it.node;
		}
		--_size;
		return val;
	}

	List& operator=(const List& l)
	{
		if (this != &l)
		{
			clear();
			for (T val : l)
				push(val);
		}
		return *this;
	}

	bool operator==(const List& l) const
	{
		if (this != &l)
		{
			if (_size != l._size)
				return false;
			for (iterator it = begin(), it2 = l.begin(); it != end(); ++it, ++it2)
				if (*it != *it2)
					return false;
		}
		return true;
	}

	bool operator!=(const List& l) const
	{
		return !(*this == l);
	}

	T& operator[](int index)
	{
		if (index < 0 || _size <= index)
			throw "Illegal index";

		return *(_begin + index);
	}
	
	const T& operator[](int index) const
	{
		if (index < 0 || _size <= index)
			throw "Illegal index";
		
		return *(_begin + index);
	}

	friend std::ostream& operator<<(std::ostream& out, const List& l)
	{
		for (T val : l)
			out << val;
		return out;
	}
};