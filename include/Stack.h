#ifndef __STACK_H__
#define __STACK_H__

const int MAX_STACK_SIZE = 100;

template <class T>
class TStack
{
  T *pMem;
  int capacity;
  int top;
public:
  TStack(int _capacity = 10) : capacity(_capacity), top(-1)
  {
    if ((capacity < 1) || (capacity > MAX_STACK_SIZE))
      throw capacity;
    pMem = new T[capacity];
  }

  TStack(const TStack& st) : capacity(st.capacity), top(st.top)
  {
	  pMem = new T[capacity];
	  for (int i = 0; i <= top; ++i)
		  pMem[i] = st.pMem[i];
  }

  ~TStack()
  {
    delete [] pMem;
  }

  inline int size() const
  {
	  return top + 1;
  }

  inline bool empty() const
  {
	  return top == -1;
  }

  inline bool full() const
  {
	  return top == MAX_STACK_SIZE - 1;
  }

  void push(const T& value)
  {
	  if (full()) throw std::exception("Stack overflow");
	  if (capacity - 1 == top)
	  {
		  int tmpCapacity = capacity * 2 > MAX_STACK_SIZE ? MAX_STACK_SIZE : capacity * 2;
		  T* tmp = new T[tmpCapacity];
		  for (int i = 0; i < capacity; ++i)
			  tmp[i] = pMem[i];
		  delete[] pMem;
		  capacity = tmpCapacity;
		  pMem = tmp;
	  }
	  pMem[++top] = value;
  }

  T pop()
  {
	  if (empty()) throw std::exception("Stack underflow");
	  return pMem[top--];
  }

  T peek() const
  {
	  if (empty()) throw std::exception("Stack underflow");
	  return pMem[top];
  }

  void clear()
  {
	  top = -1;
  }

  int search(const T& value) const
  {
	  int i, qty;
	  for (i = top, qty = 0; i >= 0; --i)
	  {
		  if (pMem[i] == value) break;
		  else ++qty;
	  }
	  return i == -1 ? -1 : qty;
  }

  TStack& operator=(const TStack& st)
  {
	  if (this != &st)
	  {
		  delete[] pMem;
		  capacity = st.capacity;
		  top = st.top;
		  pMem = new T[capacity];
		  for (int i = 0; i <= top; ++i)
			  pMem[i] = st.pMem[i];
	  }
	  return *this;
  }

  bool operator==(const TStack& st) const
  {
	  if (this != &st)
	  {
		  if (top != st.top) return false;
		  for (int i = 0; i <= top; ++i)
			  if (pMem[i] != st.pMem[i]) return false;
	  }
	  return true;
  }

  bool operator!=(const TStack& st) const
  {
	  return !(*this == st);
  }
};

#endif
