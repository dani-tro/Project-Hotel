#ifndef __ACCOMMODATION_HPP
#define __ACCOMMODATION_HPP

#include "Time_Period.h"
#include "String.h"

constexpr int32_t position_of_to_date_in_file = 21; // sizeof(uint8_t) + 2 * sizeof(uint32_t) + sizeof(Date) 

class Accommodation
{
private:
	uint32_t room_number;
	uint32_t number_of_guests;
	Time_Period period;
	String guest_name;
	String note;
public:
	Accommodation() = default;
	Accommodation(uint32_t, uint32_t, const Time_Period&, String, String);
	uint32_t get_room_number() const;
	uint32_t get_number_of_guests() const;
	const Time_Period& get_period() const;
	const Date& get_from() const;
	const Date& get_to() const;
	const String& get_guest_name() const;
	void read_accommodation_from_file(std::fstream&, int);
	void write_accommodation_to_file(std::fstream&, int) const;
	friend std::istream& operator>>(std::istream&, Accommodation&);
	void change_the_departure_date_in_file(std::fstream&, int32_t, const Date&);
	void save(std::fstream&) const;
};

#endif