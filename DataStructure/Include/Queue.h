#pragma once
#include "Base.h"
namespace eleno
{
	template <class T>
	class Queue
	{
	private:
		size_t _size;
		LinkNode<T> *_front;
		LinkNode<T> *_rear;
	public:
		Queue();
		~Queue();
		bool IsEmpty() const;
		T& Front();
		const T& Front() const;
		void Push(const T& val);
		void Pop();
		size_t Size() const;
		void Clear();
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
		Clear();
	}

	template <class T>
	bool Queue<T>::IsEmpty() const
	{
		return _size == 0;
	}

	template <class T>
	T& Queue<T>::Front()
	{
		if (IsEmpty())
			throw "Cannot access the front of an empty queue.";
		return _front->data;
	}

	template <class T>
	const T& Queue<T>::Front() const
	{
		if (IsEmpty())
			throw "Cannot access the front of an empty queue.";
		return _front->data;
	}

	template <class T>
	void Queue<T>::Push(const T& val)
	{
		++_size;
		LinkNode<T> *node = new LinkNode<T>;
		node->data = val;
		node->next = nullptr;
		if (IsEmpty())
			_front = node;
		else
			_rear->next = node;
		_rear = node;
	}

	template <class T>
	void Queue<T>::Pop()
	{
		if (IsEmpty())
			return;
		--_size;
		LinkNode<T> *node = _front;
		_front = _front->next;
		delete node;
		if (IsEmpty())
			_rear = nullptr;
	}

	template <class T>
	size_t Queue<T>::Size() const
	{
		return _size;
	}

	template <class T>
	void Queue<T>::Clear()
	{
		while (!IsEmpty())
			Pop();
	}
}