#ifndef __ROOM_HPP
#define __ROOM_HPP

#include "Vector.hpp"
#include "Accommodation.h"
#include "Closure.h"

#include <iostream>

enum class Condition
{
	Available,
	Occupied, 
	Closed
};

class Room
{
private:
	uint32_t room_number;
	uint32_t number_of_beds;
	Vector<int32_t> accommodations_indexes_in_file_list;
	Vector<int32_t> closures_indexes_in_file_list;

public:
	int32_t is_closed_during(const Time_Period&, std::fstream&) const;
	int32_t is_occupied_during(const Time_Period&, std::fstream&) const;
	Condition is_available_during(const Time_Period&, std::fstream&) const;
	uint32_t number_of_days_being_occupied_in_period(const Time_Period&, std::fstream&);
	void read_room_from_file(std::fstream&, int);
	uint32_t get_room_number() const;
	uint32_t get_number_of_beds() const;
	void add_accommodation_index_to_the_list(int32_t);
	void add_closure_index_to_the_list(int32_t);
	bool operator<(const Room&) const;
	bool operator==(const Room&) const;
	bool operator<=(const Room&) const;
};

#endif