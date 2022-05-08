#ifndef __DATE_HPP
#define __DATE_HPP

#include <iostream>
#include <fstream>

constexpr uint32_t days_of_month_leap_year[12] = { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
constexpr uint32_t days_of_month_non_leap_year[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

constexpr uint32_t number_of_days_leap_year = 366;
constexpr uint32_t number_of_days_non_leap_year = 365;

class Date
{
private:
	uint32_t day = 1;
	uint32_t month = 1;
	uint32_t year = 1950;

	uint32_t get_days_since_1950() const;
	
public:
	Date() = default;
	Date(uint32_t, uint32_t, uint32_t);
	
	uint32_t get_day() const;
	uint32_t get_month() const;
	uint32_t get_year() const;
	bool operator<(const Date&) const;
	bool operator==(const Date&) const;
	bool operator<=(const Date&) const;
	uint32_t operator-(const Date&) const;

	Date next_day() const;
	friend std::istream& operator>>(std::istream&, Date&);
	void read_date_from_file(std::fstream&);
	void write_date_to_file(std::fstream&);
};

bool is_leap_year(uint32_t);

#endif
