#pragma once
#include "Base.h"

namespace eleno
{
	template <class T>
	class Queue
	{
	private:
		size_t _size;
		LinkNode<T>* _front;
		LinkNode<T>* _rear;
	public:
		Queue();
		~Queue();
		bool empty() const;
		T& front();
		const T& front() const;
		void push(const T& val);
		void pop();
		size_t size() const;
		void clear();
	};

	template <class T>
	Queue<T>::Queue()
	{
		_size = 0;
		_front = nullptr;
		_rear = nullptr;
	}

	template <class T>
	Queue<T>::~Queue()
	{
		clear();
	}

	template <class T>
	bool Queue<T>::empty() const
	{
		return _size == 0;
	}

	template <class T>
	T& Queue<T>::front()
	{
		return _front->data;
	}

	template <class T>
	const T& Queue<T>::front() const
	{
		return _front->data;
	}

	template <class T>
	void Queue<T>::push(const T& val)
	{
		
		LinkNode<T>* node = new LinkNode<T>;
		node->data = val;
		node->next = nullptr;
		if (empty())
			_front = node;
		else
			_rear->next = node;
		_rear = node;
		++_size;
	}

	template <class T>
	void Queue<T>::pop()
	{
		if (empty())
			return;
		--_size;
		LinkNode<T>* node = _front;
		_front = _front->next;
		delete node;
		if (empty())
			_rear = nullptr;
	}

	template <class T>
	size_t Queue<T>::size() const
	{
		return _size;
	}

	template <class T>
	void Queue<T>::clear()
	{
		while (!empty())
			pop();
	}
}
