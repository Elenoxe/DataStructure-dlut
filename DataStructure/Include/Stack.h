#pragma once
#include "Base.h"

namespace eleno
{
	template <class T>
	class Stack
	{
		private:
		size_t _size;
		LinkNode<T>* _top;
		public:
		Stack();
		~Stack();
		bool empty() const;
		T& top();
		const T& top() const;
		void push(const T& val);
		void pop();
		size_t size() const;
		void clear();
	};

	template <class T>
	Stack<T>::Stack()
	{
		_size = 0;
		_top = nullptr;
	}

	template <class T>
	Stack<T>::~Stack()
	{
		clear();
	}

	template <class T>
	bool Stack<T>::empty() const
	{
		return _size == 0;
	}

	template <class T>
	T& Stack<T>::top()
	{
		if (empty())
			throw "Cannot access the top of an empty stack.";
		return _top->data;
	}

	template <class T>
	const T& Stack<T>::top() const
	{
		if (empty())
			throw "Cannot access the top of an empty stack.";
		return _top->data;
	}

	template <class T>
	void Stack<T>::push(const T& val)
	{
		++_size;
		LinkNode<T>* node = new LinkNode<T>;
		node->data = val;
		node->next = _top;
		_top = node;
	}

	template <class T>
	void Stack<T>::pop()
	{
		if (empty())
			return;
		--_size;
		LinkNode<T>* node = _top;
		_top = _top->next;
		delete node;
	}

	template <class T>
	size_t Stack<T>::size() const
	{
		return _size;
	}

	template <class T>
	void Stack<T>::clear()
	{
		while (!empty())
			pop();
	}
}
