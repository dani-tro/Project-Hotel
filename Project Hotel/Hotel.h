#ifndef __HOTEL_HPP
#define __HOTEL_HPP

#include "Vector.hpp"
#include "Room.h"

#include <fstream>

class Hotel
{
private:
	Vector<Room> rooms;
	std::fstream file;
public:
	void open_the_file_with_loaded_rooms();
	void read_the_available_rooms_from_file();
	void read_the_loaded_events_in_the_file();
	void run_hotel();
	int32_t find_the_index_of_room_with_given_number(uint32_t) const;
	void process_the_command(String&);
	void register_a_guest();
	void print_the_free_rooms();
	void free_a_room();
	void print_a_report();
	void find_a_room();
	void close_a_room();
	void print_error_message();
	int32_t get_the_room_with_the_fewest_beds(uint32_t, const Time_Period&);
	bool is_valid(Accommodation& );
	bool handle_intersecting_accommodations(uint32_t, Accommodation&);
	void change_room_number_of(Accommodation& accommodation, uint32_t new_room_number, int32_t);
	bool handle_lack_of_rooms_or_closures(uint32_t , Accommodation&);
	bool is_valid(const Closure&);
};

void print_available_commands();
void read_a_command(String&);

#endif