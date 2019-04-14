#pragma once
#include "ForwardList.h"
#include "SortedForwardList.h"
using namespace eleno;

struct Term
{
	using coef_type = int;
	using exp_type = unsigned;
	coef_type coef;
	exp_type exp;
	Term() = default;
	Term(const coef_type& c, const exp_type& e) : coef(c), exp(e) { return; }
};

class Poly : public SortedForwardList<Term>
{
	public:
		using variable_value_type = int;
		using term_value_type = long long;
		Poly(const Poly& other) : SortedForwardList<Term>(other) { return; }
		explicit Poly(const Order order = ASCENDING) :SortedForwardList<Term>(order) { return; }
		void push(const Term& val);
		term_value_type subs(const variable_value_type& x) const;
		Poly operator+(const Poly& rhs) const;
};
