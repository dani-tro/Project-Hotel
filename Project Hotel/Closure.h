#ifndef __CLOSURE_HPP
#define __CLOSURE_HPP

#include "Time_Period.h"
#include "String.h"

class Closure
{
private:
	uint32_t room_number;
	Time_Period period;
	String note;
public:
	Closure() = default;
	void Close(uint32_t, const Time_Period&, String);
	uint32_t get_room_number() const;
	const Time_Period& get_period() const;
	const Date& get_from() const;
	const Date& get_to() const;
	const String& get_note() const;
	void read_closure_from_file(std::fstream&, int);
	void write_closure_to_file(std::fstream&, int) const;
	friend std::istream& operator>>(std::istream&, Closure&);
	void save(std::fstream&) const;
};

#endif