#pragma once
#include <cstdlib>
#include <exception>

namespace eleno
{
	template <class T>
	class SeqQueue
	{
	private:
		T* _elems;
		size_t _front;
		size_t _rear;
		size_t _size;
		size_t _capacity;
		static const size_t INIT_CAPACITY = 4;
	public:
		SeqQueue();
		~SeqQueue();
		bool empty() const;
		T& front();
		const T& front() const;
		void push(const T& val);
		void pop();
		size_t size() const;
		void clear();
	};

	template <class T>
	SeqQueue<T>::SeqQueue()
	{
		_elems = new T[INIT_CAPACITY];
		_front = 0;
		_rear = 0;
		_size = 0;
		_capacity = INIT_CAPACITY;
	}

	template <class T>
	SeqQueue<T>::~SeqQueue()
	{
		delete _elems;
	}

	template <class T>
	bool SeqQueue<T>::empty() const
	{
		return _size == 0;
	}

	template <class T>
	T& SeqQueue<T>::front()
	{
		return _elems[_front];
	}

	template <class T>
	const T& SeqQueue<T>::front() const
	{
		return _elems[_front];
	}

	template <class T>
	void SeqQueue<T>::push(const T& val)
	{
		if (_size == _capacity)
		{
			T* temp = static_cast<T*>(realloc(_elems, _capacity * 2 * sizeof(T)));
			if (temp)
			{
				_elems = temp;
				if (_front >= _rear)
				{
					memmove(_elems + _size, _elems, _rear);
					_rear = _front + _size;
				}
				_capacity *= 2;
			}
			else
				throw std::bad_alloc();
		}
		_elems[_rear] = val;
		_rear = (_rear + 1) % _capacity;
		++_size;
	}

	template <class T>
	void SeqQueue<T>::pop()
	{
		if (empty())
			return;
		_front = (_front + 1) % _capacity;
		--_size;
	}

	template <class T>
	size_t SeqQueue<T>::size() const
	{
		return _size;
	}

	template <class T>
	void SeqQueue<T>::clear()
	{
		T* temp = static_cast<T*>(realloc(_elems, INIT_CAPACITY * sizeof(T)));
		if (temp)
			_elems = temp;
		else
			throw std::bad_alloc();
		_front = 0;
		_rear = 0;
		_size = 0;
		_capacity = INIT_CAPACITY;
	}
}
