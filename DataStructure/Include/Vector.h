#pragma once
#include <iterator>

namespace eleno
{
	template <class T>
	class Vector
	{
	public:
		using value_type = T;
		using reference = value_type &;
		using const_reference = const value_type &;
		using pointer = value_type *;
		using const_pointer = const value_type*;
		using difference_type = ptrdiff_t;
		using size_type = size_t;
	private:
		template <bool _Const>
		class _BaseIterator
			: public std::iterator<std::random_access_iterator_tag, T>
		{
			friend class Vector;
		public:
			using iterator_category = std::conditional_t<_Const, std::input_iterator_tag, std::forward_iterator_tag>;
			using value_type = typename Vector::value_type;
			using difference_type = ptrdiff_t;
			using pointer = std::conditional_t<_Const, const value_type*, value_type*>;
			using reference = std::conditional_t<_Const, const value_type&, value_type&>;
		private:
			pointer _p;
			explicit _BaseIterator(pointer p = nullptr) { _p = p; }
		public:
			_BaseIterator(const _BaseIterator<false>& other) { _p = other._p; }
			bool operator==(const _BaseIterator<false>& iter) const { return _p == iter._p; }
			bool operator==(const _BaseIterator<true>& iter) const { return _p == iter._p; }
			bool operator!=(const _BaseIterator<false>& iter) const { return _p != iter._p; }
			bool operator!=(const _BaseIterator<true>& iter) const { return _p != iter._p; }

			_BaseIterator& operator++()
			{
				++_p;
				return *this;
			}

			_BaseIterator operator++(int)
			{
				_BaseIterator temp = *this;
				++_p;
				return temp;
			}

			_BaseIterator operator+(const size_type& n)
			{
				return _BaseIterator(_p + n);
			}

			_BaseIterator& operator--()
			{
				--_p;
				return *this;
			}

			_BaseIterator operator--(int)
			{
				_BaseIterator temp = *this;
				--_p;
				return temp;
			}

			_BaseIterator operator-(const size_type& n)
			{
				return _BaseIterator(_p - n);
			}

			reference operator*() { return *_p; }
		};

		static const size_type INIT_CAPACITY = 4;

		pointer _elems;
		size_type _size;
		size_type _capacity;
	public:
		using iterator = _BaseIterator<false>;
		using const_iterator = _BaseIterator<true>;
		Vector();
		Vector(const Vector& other);
		~Vector();
		Vector& operator=(const Vector& other);
		// Iterators
		iterator begin() const { return iterator(_elems); }
		iterator end() const { return iterator(nullptr); }
		const_iterator cbegin() const { return const_iterator(_elems); }
		const_iterator cend() const { return const_iterator(nullptr); }
		// Capacity
		size_type size() const;
		size_type capacity() const;
		bool empty() const;
		// Element Access
		reference operator[](const size_type& index);
		const_reference operator[](const size_type& index) const;
		reference front();
		const_reference front() const;
		reference back();
		const_reference back() const;
		// Modifiers
		void push_back(const value_type& val);
		void pop_back();
		iterator insert(iterator iter, const value_type& val);
		iterator erase(iterator iter);
		void clear();
	};

	template <class T>
	Vector<T>::Vector()
	{
		_elems = new T[INIT_CAPACITY];
		_size = 0;
		_capacity = INIT_CAPACITY;
	}

	template <class T>
	Vector<T>::Vector(const Vector& other)
	{
		for (const value_type& elem : other)
			push_back(elem);
	}

	template <class T>
	Vector<T>::~Vector()
	{
		delete[] _elems;
	}

	template <class T>
	Vector<T>& Vector<T>::operator=(const Vector& other)
	{
		_size = other._size;
		_capacity = other._capacity;
		delete[] _elems;
		_elems = new value_type[_capacity];
		for (size_type i = 0; i < other._size; ++i)
			_elems[i] = other[i];
		return *this;
	}

	template <class T>
	typename Vector<T>::size_type Vector<T>::size() const
	{
		return _size;
	}

	template <class T>
	typename Vector<T>::size_type Vector<T>::capacity() const
	{
		return _capacity;
	}

	template <class T>
	bool Vector<T>::empty() const
	{
		return _size == 0;
	}

	template <class T>
	typename Vector<T>::reference Vector<T>::operator[](const size_type& index)
	{
		return _elems[index];
	}

	template <class T>
	typename Vector<T>::const_reference Vector<T>::operator[](const size_type& index) const
	{
		return _elems[index];
	}

	template <class T>
	typename Vector<T>::reference Vector<T>::front()
	{
		return _elems[0];
	}

	template <class T>
	typename Vector<T>::const_reference Vector<T>::front() const
	{
		return _elems[0];
	}

	template <class T>
	typename Vector<T>::reference Vector<T>::back()
	{
		return _elems[_size - 1];
	}

	template <class T>
	typename Vector<T>::const_reference Vector<T>::back() const
	{
		return _elems[_size - 1];
	}

	template <class T>
	void Vector<T>::push_back(const value_type& val)
	{
		if (_size == _capacity)
		{
			pointer temp = _elems;
			_elems = new value_type[_capacity * 2];
			memcpy(_elems, temp, _capacity * sizeof(value_type));
			delete[] temp;
			_capacity *= 2;
		}
		_elems[_size] = val;
		++_size;
	}

	template <class T>
	void Vector<T>::pop_back()
	{
		if (_size > 0)
			--_size;
	}

	template <class T>
	typename Vector<T>::iterator Vector<T>::insert(iterator iter, const value_type& val)
	{
		if (_size == _capacity)
		{
			pointer temp = _elems;
			_elems = new value_type[_capacity * 2];
			memcpy(_elems, temp, _capacity * sizeof(value_type));
			delete[] temp;
		}
		for (pointer p = &_elems[_size - 1]; p >= iter._p; --p)
		{
			*(p + 1) = *p;
		}
		*iter = val;
		++_size;
		return iter;
	}

	template <class T>
	typename Vector<T>::iterator Vector<T>::erase(iterator iter)
	{
		for (pointer p = iter._p; p <= &_elems[_size - 2]; ++p)
		{
			*p = *(p + 1);
		}
		--_size;
		return iter;
	}

	template <class T>
	void Vector<T>::clear()
	{
		delete[] _elems;
		_elems = new T[INIT_CAPACITY];
		_size = 0;
		_capacity = INIT_CAPACITY;
	}
}
