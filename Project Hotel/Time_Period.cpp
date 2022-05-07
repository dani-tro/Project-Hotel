#include "Time_Period.h"

Time_Period::Time_Period(const Date& _from, const Date& _to): from{_from}, to{_to}
{
}

const Date& Time_Period::get_from() const
{
	return from;
}

const Date& Time_Period::get_to() const
{
	return to;
}

void Time_Period::set_from(const Date& _from)
{
	from = _from;
}

void Time_Period::set_to(const Date& _to)
{
	to = _to;
}

uint32_t Time_Period::duration() const
{
	std::cout << get_to().get_day() << " " << get_from().get_day() << std::endl;
	return get_to() - get_from();
}

Time_Period intersect(const Time_Period& lhs, const Time_Period& rhs)
{
	Time_Period intersection;
	if (lhs.get_from() < rhs.get_from())intersection.set_from(rhs.get_from());
	else intersection.set_from(lhs.get_from());
	if (lhs.get_to() < rhs.get_to())intersection.set_to(lhs.get_to());
	else intersection.set_to(rhs.get_to());
	return intersection;
}
