#include "Poly.h"
void Poly::push(const Term& val)
{
	if (val.coef == 0)
		return;
	if (empty())
	{
		ForwardList<Term>::push_front(val);
		return;
	}
	auto iter = before_begin();
	while (true)
	{
		auto next = iter + 1;
		if (next == end())
		{
			ForwardList<Term>::insert_after(iter, val);
			return;
		}
		if ((*next).exp == val.exp)
		{
			(*next).coef = (*next).coef + val.coef;
			return;
		}
		switch (order())
		{
			case ASCENDING:
				if ((*next).exp > val.exp)
				{
					ForwardList<Term>::insert_after(iter, val);
					return;
				}
				break;
			case DESCENDING:
				if ((*next).exp < val.exp)
				{
					ForwardList<Term>::insert_after(iter, val);
					return;
				}
				break;
		}
		++iter;
	}
}

Poly::term_value_type Poly::subs(const variable_value_type& x) const
{
	if (empty())
		return 0;
	if (size() == 1)
	{
		term_value_type prod = 1;
		const Term& term = front();
		for (Term::exp_type i = 0; i < term.exp; ++i)
			prod *= x;
		return term.coef * prod;
	}
	term_value_type sum;
	if (order() == ASCENDING)
	{
		term_value_type carry = 1;
		const auto multi = [x, &carry](const Term::exp_type& n) -> void
		{
			term_value_type prod = 1;
			for (Term::exp_type i = 0; i < n; ++i)
				prod *= x;
			carry *= prod;
		};
		auto prev = cbegin();
		auto curr = prev + 1;
		multi((*prev).exp);
		sum = (*prev).coef * carry;
		while (curr != cend())
		{
			multi((*curr).exp - (*prev).exp);
			sum += (*curr).coef * carry;
			++prev;
			++curr;
		}
	}
	else
	{
		// Horner's method
		auto prev = cbegin();
		auto curr = prev + 1;
		sum = (*prev).coef;
		while (curr != cend())
		{
			const Term::exp_type time = (*prev).exp - (*curr).exp;
			for (Term::exp_type i = 0; i < time; ++i)
				sum *= x;
			sum += (*curr).coef;
			++prev;
			++curr;
		}
		for (Term::exp_type i = 0; i < (*prev).exp; ++i)
			sum *= x;
	}
	return sum;
}

Poly Poly::operator+(const Poly& rhs) const
{
	Poly temp;
	const auto& addition = order() == rhs.order() ? rhs : (temp = rhs, temp.reverse(), temp);
	const auto cmp = [order = order()](const auto& lhs, const auto& rhs) -> bool
	{
		if (order == ASCENDING)
			return lhs < rhs;
		return lhs > rhs;
	};
	Poly sum;
	auto iter = sum.cbefore_begin();
	auto liter = cbegin();
	auto riter = addition.cbegin();
	while (liter != cend() && riter != addition.cend())
	{
		if ((*liter).exp == (*riter).exp)
		{
			Term::coef_type coef = (*liter).coef + (*riter).coef;
			if (coef != 0)
				iter = sum.ForwardList<Term>::insert_after(iter, Term(coef, (*liter).exp));
			++liter;
			++riter;
			continue;
		}
		auto& choice = cmp((*liter).exp, (*riter).exp) ? liter : riter;
		iter = sum.ForwardList<Term>::insert_after(iter, *choice);
		++choice;
	}
	auto& remain_iter = liter == cend() ? riter : liter;
	auto& remain_poly = liter == cend() ? addition : *this;
	while (remain_iter != remain_poly.cend())
	{
		iter = sum.ForwardList<Term>::insert_after(iter, *remain_iter);
		++remain_iter;
	}
	return sum;
}
