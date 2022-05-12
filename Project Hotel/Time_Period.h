#ifndef __TIME_PERIOD_HPP
#define __TIME_PERIOD_HPP

#include "Date.h"

class Time_Period
{
private:
	Date from{01, 01, 1950};
	Date to{02, 01, 1950};
public:
	Time_Period() = default;
	Time_Period(const Date&, const Date&);
	const Date& get_from() const;
	const Date& get_to() const;
	void set_from(const Date&);
	void set_to(const Date&);
	uint32_t duration() const;
	void read_period_from_file(std::fstream&, int);
	void write_period_to_file(std::fstream&, int) const;
	friend std::istream& operator>>(std::istream&, Time_Period&);
};

Time_Period intersect(const Time_Period&, const Time_Period&);

#endif