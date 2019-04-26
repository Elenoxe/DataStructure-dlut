#pragma once
#include "Base.h"
#include <iterator>

namespace eleno
{
	template <class T>
	class ForwardList
	{
	public:
		using value_type = T;
		using reference = value_type&;
		using const_reference = const value_type&;
		using pointer = value_type*;
		using const_pointer = const value_type*;
		using difference_type = ptrdiff_t;
		using size_type = size_t;
	private:
		template <bool _Const>
		class _BaseIterator
			: public std::iterator<std::conditional_t<_Const, std::input_iterator_tag, std::forward_iterator_tag>, T>
		{
			friend class ForwardList;
		public:
			using iterator_category = std::conditional_t<_Const, std::input_iterator_tag, std::forward_iterator_tag>;
			using value_type = typename ForwardList::value_type;
			using difference_type = ptrdiff_t;
			using pointer = std::conditional_t<_Const, const value_type*, value_type*>;
			using reference = std::conditional_t<_Const, const value_type&, value_type&>;
		private:
			LinkNode<value_type>* _pNode;
			explicit _BaseIterator(LinkNode<T>* p = nullptr) { _pNode = p; }
		public:
			_BaseIterator(const _BaseIterator<false>& other) { _pNode = other._pNode; }
			bool operator==(const _BaseIterator<false>& iter) const { return _pNode == iter._pNode; }
			bool operator==(const _BaseIterator<true>& iter) const { return _pNode == iter._pNode; }
			bool operator!=(const _BaseIterator<false>& iter) const { return _pNode != iter._pNode; }
			bool operator!=(const _BaseIterator<true>& iter) const { return _pNode != iter._pNode; }

			_BaseIterator& operator++()
			{
				_pNode = _pNode->next;
				return *this;
			}

			_BaseIterator operator++(int)
			{
				_BaseIterator temp = *this;
				_pNode = _pNode->next;
				return temp;
			}

			_BaseIterator operator+(const size_type& n)
			{
				LinkNode<value_type>* node = _pNode;
				for (size_type i = 0; i != n; ++i)
					node = node->next;
				return _BaseIterator(node);
			}

			reference operator*() { return _pNode->data; }
		};

		size_type _size;
		LinkNode<value_type>* _head;
	public:
		using iterator = _BaseIterator<false>;
		using const_iterator = _BaseIterator<true>;
		ForwardList();
		ForwardList(const ForwardList& other);
		~ForwardList();
		ForwardList& operator=(const ForwardList& other);
		// Iterators
		iterator before_begin() const { return iterator(_head); }
		iterator begin() const { return iterator(_head->next); }
		iterator end() const { return iterator(nullptr); }
		const_iterator cbefore_begin() const { return const_iterator(_head); }
		const_iterator cbegin() const { return const_iterator(_head->next); }
		const_iterator cend() const { return const_iterator(nullptr); }
		// Capacity
		size_type size() const;
		// Element access
		reference front() { return _head->next->data; }
		const_reference front() const { return _head->next->data; }
		// Modifiers
		bool empty() const;
		void push_front(const_reference val);
		void pop_front();
		iterator insert_after(const_iterator iter, const_reference val);
		iterator erase_after(const_iterator iter);
		void clear();
		// Operations
		void reverse();
	};

	template <class T>
	ForwardList<T>::ForwardList()
	{
		_size = 0;
		_head = new LinkNode<value_type>;
		_head->next = nullptr;
	}

	template <class T>
	ForwardList<T>::ForwardList(const ForwardList& other)
	{
		_size = 0;
		_head = new LinkNode<value_type>;
		_head->next = nullptr;
		auto iter = cbefore_begin();
		for (const auto& val : other)
			iter = insert_after(iter, val);
	}

	template <class T>
	ForwardList<T>::~ForwardList()
	{
		clear();
	}

	template <class T>
	ForwardList<T>& ForwardList<T>::operator=(const ForwardList& other)
	{
		clear();
		auto iter = cbefore_begin();
		for (const auto& val : other)
			iter = insert_after(iter, val);
		return *this;
	}

	template <class T>
	bool ForwardList<T>::empty() const
	{
		return _size == 0;
	}

	template <class T>
	void ForwardList<T>::push_front(const_reference val)
	{
		LinkNode<value_type>* node = new LinkNode<T>;
		node->data = val;
		node->next = _head->next;
		_head->next = node;
		++_size;
	}

	template <class T>
	void ForwardList<T>::pop_front()
	{
		if (!empty())
		{
			LinkNode<value_type>* node = _head->next;
			_head->next = node->next;
			delete node;
			--_size;
		}
	}

	template <class T>
	typename ForwardList<T>::iterator ForwardList<T>::insert_after(const_iterator iter, const_reference val)
	{
		LinkNode<value_type>* node = new LinkNode<T>;
		node->data = val;
		node->next = iter._pNode->next;
		iter._pNode->next = node;
		++_size;
		return iterator(node);
	}

	template <class T>
	typename ForwardList<T>::iterator ForwardList<T>::erase_after(const_iterator iter)
	{
		LinkNode<value_type>* node = iter._pNode->next;
		iter._pNode->next = node->next;
		delete node;
		--_size;
		return iterator(iter._pNode->next);
	}

	template <class T>
	size_t ForwardList<T>::size() const
	{
		return _size;
	}

	template <class T>
	void ForwardList<T>::clear()
	{
		while (!empty())
			pop_front();
	}

	template <class T>
	void ForwardList<T>::reverse()
	{
		LinkNode<value_type>* node = _head->next;
		LinkNode<value_type>* current = nullptr;
		while (node)
		{
			LinkNode<value_type>* temp = node->next;
			node->next = current;
			current = node;
			node = temp;
		}
		_head->next = current;
	}
}
