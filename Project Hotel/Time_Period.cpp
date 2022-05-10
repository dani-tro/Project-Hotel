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
	if (get_to() < get_from()) return 0;
	return get_to() - get_from();
}

void Time_Period::read_period_from_file(std::fstream& file, int position)
{
	from.read_date_from_file(file, position);
	to.read_date_from_file(file, file.tellg());
}

void Time_Period::write_period_to_file(std::fstream& file, int position) const
{
	from.write_date_to_file(file, position);
	to.write_date_to_file(file, file.tellp());
}

bool Time_Period::is_valid() const
{
	//TODO
	return duration() > 0;
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

std::istream& operator>>(std::istream& in, Time_Period& time_period)
{
	std::cout << "Enter the first date of the period: ";
	in >> time_period.from;
	std::cout << "Enter the last date of the period: ";
	in >> time_period.to;

	return in;
}
