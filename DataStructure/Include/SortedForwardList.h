#pragma once
#include "ForwardList.h"
namespace eleno
{
	template <class T>
	class SortedForwardList : public ForwardList<T>
	{
	public:
		enum Order : bool { ASCENDING, DESCENDING };
		using value_type = typename ForwardList<T>::value_type;
		using reference = typename ForwardList<T>::reference ;
		using const_reference = typename ForwardList<T>::const_reference;
		using pointer = typename ForwardList<T>::pointer;
		using const_pointer = typename ForwardList<T>::const_pointer;
		using difference_type = typename ForwardList<T>::difference_type;
		using size_type = typename ForwardList<T>::size_type;
	private:
		Order _order;
	public:
		using iterator = typename ForwardList<T>::iterator;
		using const_iterator = typename ForwardList<T>::const_iterator;
		SortedForwardList(const SortedForwardList& other) :ForwardList<T>(other) { _order = other._order; }
		explicit SortedForwardList(const Order& order = ASCENDING) { _order = order; }
		Order order() const { return _order; }
		void push_front(const value_type& val) = delete;
		iterator insert_after(const_iterator iter, const value_type& val) = delete;
		void push(const value_type& val);
		void reverse();
	};

	template <class T>
	void SortedForwardList<T>::push(const value_type& val)
	{
		if (this->empty())
		{
			ForwardList<T>::push_front(val);
			return;
		}
		auto iter = this->cbefore_begin();
		while (true)
		{
			auto next = iter + 1;
			if (next == this->cend())
			{
				ForwardList<T>::insert_after(iter, val);
				return;
			}
			switch (_order)
			{
			case ASCENDING:
				if ((*next) >= val)
				{
					ForwardList<T>::insert_after(iter, val);
					return;
				}
				break;
			case DESCENDING:
				if ((*next) <= val)
				{
					ForwardList<T>::insert_after(iter, val);
					return;
				}
				break;
			}
			++iter;
		}
	}

	template <class T>
	void SortedForwardList<T>::reverse()
	{
		ForwardList<T>::reverse();
		_order = _order == ASCENDING ? DESCENDING : ASCENDING;
	}
}
