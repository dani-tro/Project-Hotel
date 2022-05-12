#include "Date.h"
#include <iostream>

uint32_t Date::get_days_since_1950() const
{
	uint32_t days_since_1950 = day;
	if (is_leap_year(year))
		for (uint32_t i = 1; i < month; i++)days_since_1950 += days_of_month_leap_year[i];
	else for (uint32_t i = 1; i < month; i++)days_since_1950 += days_of_month_non_leap_year[i];
	for (uint32_t i = 1950; i < year; i++)
	{
		if (is_leap_year(i))days_since_1950 += number_of_days_leap_year;
		else days_since_1950 += number_of_days_non_leap_year;
	}
	return days_since_1950;
}

Date::Date(uint32_t _day, uint32_t _month, uint32_t _year) : day{ _day }, month{ _month }, year{ _year }
{
	if (year < 1950 || year >= 10000 || month < 1 || month > 12)
	{
		throw(1);
	}
	if (is_leap_year(year))
	{
		if (day < 1 || day > days_of_month_leap_year[month - 1])throw(1);
	}
	else if (day < 1 || day > days_of_month_non_leap_year[month - 1])throw(1);
}

uint32_t Date::get_day() const
{
	return day;
}

uint32_t Date::get_month() const
{
	return month;
}

uint32_t Date::get_year() const
{
	return year;
}

bool Date::operator<(const Date& other) const
{
	return get_days_since_1950() < other.get_days_since_1950();
}

bool Date::operator==(const Date& other) const
{
	return (get_day() == other.get_day() && get_month() == other.get_month() && get_year() == other.get_year());
}

bool Date::operator<=(const Date& other) const
{
	return (*this < other || *this == other);
}

uint32_t Date::operator-(const Date& other) const
{
	if (*this < other)return 0;
	return get_days_since_1950() - other.get_days_since_1950() + 1;
}

Date Date::next_day() const
{
	Date next_day = *this;
	next_day.day++;
	if (is_leap_year(next_day.year))
	{
		if (next_day.day > days_of_month_leap_year[next_day.month - 1])
		{
			next_day.day = 1;
			next_day.month++;
		}
	}
	else
	{
		if (next_day.day > days_of_month_non_leap_year[next_day.month - 1])
		{
			next_day.day = 1;
			next_day.month++;
		}
	}
	if (next_day.month > 12)
	{
		next_day.month = 1;
		next_day.year++;
	}
	return next_day;
}

void Date::read_date_from_file(std::fstream& file, int position)
{
	file.seekg(position);
	file.read(reinterpret_cast<char*>(&day), sizeof(uint32_t));
	file.read(reinterpret_cast<char*>(&month), sizeof(uint32_t));
	file.read(reinterpret_cast<char*>(&year), sizeof(uint32_t));
}

void Date::write_date_to_file(std::fstream& file, int position) const
{
	file.seekp(position);
	file.write(reinterpret_cast<const char*>(&day), sizeof(uint32_t));
	file.write(reinterpret_cast<const char*>(&month), sizeof(uint32_t));
	file.write(reinterpret_cast<const char*>(&year), sizeof(uint32_t));
}

String Date::to_String() const
{
	char to_char[11];
	to_char[0] = '0' + get_year() / 1000;
	to_char[1] = '0' + (get_year() / 100) % 10;
	to_char[2] = '0' + (get_year() / 10) % 10;
	to_char[3] = '0' + get_year() % 10;
	to_char[4] = '-';
	to_char[5] = '0' + get_month() / 10;
	to_char[6] = '0' + get_month() % 1000;
	to_char[7] = '-';
	to_char[8] = '0' + get_day() / 10;
	to_char[9] = '0' + get_day() % 10;
	to_char[10] = '\0';
	String string = to_char;
	return string;
}

std::istream& operator>>(std::istream& in, Date& date)
{
	uint32_t day, month, year;
	char buff;
	in >> day >> buff >> month >> buff >> year;
	in.get();
	try
	{
		date = Date(day, month, year);
	}
	catch (int x)
	{
		std::cout << "Invalid date entered! Please, try again: ";
		std::cin >> date;
	}
	return in;
}

std::ostream& operator<<(std::ostream& out, const Date& date)
{
	out << date.get_day() << "." << date.get_month() << "." << date.get_year();
	return out;
}



bool is_leap_year(uint32_t year)
{
	return ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0);
}
