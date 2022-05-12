#include "Time_Period.h"

Time_Period::Time_Period(const Date& _from, const Date& _to): from{_from}, to{_to}
{
	if (to <= from)throw(2);
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
	if(_from < to)from = _from;
}

void Time_Period::set_to(const Date& _to)
{
	if(from < _to)to = _to;
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

Time_Period intersect(const Time_Period& lhs, const Time_Period& rhs)
{
	Date from, to;
	if (lhs.get_from() < rhs.get_from())from = rhs.get_from();
	else from = lhs.get_from();
	if (lhs.get_to() < rhs.get_to())to = lhs.get_to();
	else to = rhs.get_to();
	Time_Period intersection{ from, to };
	std::cout << intersection.get_from() << " " << intersection.get_to() << " " << rhs.get_from() << " " << rhs.get_to() << std::endl;
	return intersection;
}

std::istream& operator>>(std::istream& in, Time_Period& time_period)
{
	Date from, to;
	std::cout << "Enter the first date of the period: ";
	in >> from;
	std::cout << "Enter the last date of the period: ";
	in >> to;
	try
	{
		time_period = Time_Period(from, to);
	}
	catch (int x)
	{
		std::cout << "The end of the period should be at least one day after the beginning! Please, enter the period again!\n";
		std::cin >> time_period;
	}

	return in;
}
