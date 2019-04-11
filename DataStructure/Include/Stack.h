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
		bool IsEmpty() const;
		T& Top();
		const T& Top() const;
		void Push(const T& val);
		void Pop();
		size_t Size() const;
		void Clear();
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
		Clear();
	}

	template <class T>
	bool Stack<T>::IsEmpty() const
	{
		return _size == 0;
	}

	template <class T>
	T& Stack<T>::Top()
	{
		if (IsEmpty())
			throw "Cannot access the top of an empty stack.";
		return _top->data;
	}

	template <class T>
	const T& Stack<T>::Top() const
	{
		if (IsEmpty())
			throw "Cannot access the top of an empty stack.";
		return _top->data;
	}

	template <class T>
	void Stack<T>::Push(const T& val)
	{
		++_size;
		LinkNode<T> *node = new LinkNode<T>;
		node->data = val;
		node->next = _top;
		_top = node;
	}

	template <class T>
	void Stack<T>::Pop()
	{
		if (IsEmpty())
			return;
		--_size;
		LinkNode<T> *node = _top;
		_top = _top->next;
		delete node;
	}

	template <class T>
	size_t Stack<T>::Size() const
	{
		return _size;
	}

	template <class T>
	void Stack<T>::Clear()
	{
		while (!IsEmpty())
			Pop();
	}
}
