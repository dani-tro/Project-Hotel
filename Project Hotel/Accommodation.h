#ifndef __ACCOMMODATION_HPP
#define __ACCOMMODATION_HPP

#include "Time_Period.h"
#include "String.h"

class Accommodation
{
private:
	uint32_t room_number;
	Time_Period period;
	String guest_name;
	String note;
public:
	Accommodation() = default;
	Accommodation(uint32_t, const Time_Period&, String, String);
	uint32_t get_room_number() const;
	const Time_Period& get_period() const;
	const Date& get_from() const;
	const Date& get_to() const;
	const String& get_guest_name() const;
	void read_accommodation_from_file(std::fstream&, int);
	void write_accommodation_to_file(std::fstream&, int) const;
	friend std::istream& operator>>(std::istream&, Accommodation&);
	void save(std::fstream&) const;
};

#endif