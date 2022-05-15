#include "Hotel.h"
#include "String.h"

#include <iostream>
#include <fstream>
#include <algorithm>

void Hotel::open_the_file_with_loaded_rooms()
{
	String name;
	do
	{
		std::cout << "Enter the path to the file with the loaded rooms: ";
		getline(std::cin, name, '\n');
		if(name.get_data() != nullptr)file.open((const char*)name, std::ios::in | std::ios::out | std::ios::binary);
		if (file.is_open() == false)std::cout << "There was an error loading the file! Try again!\n";
		else std::cout << "File loaded successfully!\n";
	} 
	while (file.is_open() == false);
}

void Hotel::read_the_available_rooms_from_file()
{
	Room buff;
	buff.read_room_from_file(file, file.tellg());
	while (buff.get_room_number() != 0)
	{
		rooms.push_back(buff);
		buff.read_room_from_file(file, file.tellg());
	}
	std::sort(rooms.begin(), rooms.end());
	std::cout << "There are " << rooms.get_size() << " rooms in the hotel.\n";
	
}


void Hotel::read_the_loaded_events_in_the_file()
{
	uint8_t type{0};
	int32_t file_position;
	uint32_t room_number{0};
	Accommodation accommodation;
	Closure closure;
	file_position = file.tellg();
	file.read(reinterpret_cast<char*>(&type), sizeof(uint8_t));
	while (!file.eof())
	{
		if (type == 1)
		{
			accommodation.read_accommodation_from_file(file, file.tellg());
			int32_t index = find_the_index_of_room_with_given_number(accommodation.get_room_number());
			rooms[index].add_accommodation_index_to_the_list(file_position);
		}
		else if (type == 2)
		{
			closure.read_closure_from_file(file, file.tellg());
			int32_t index = find_the_index_of_room_with_given_number(closure.get_room_number());
			rooms[index].add_closure_index_to_the_list(file_position);
		}
		file_position = file.tellg();
		file.read(reinterpret_cast<char*>(&type), sizeof(uint8_t));
	}
	file.clear();
	return;
}

void Hotel::run_hotel()
{
	open_the_file_with_loaded_rooms();
	read_the_available_rooms_from_file();
	read_the_loaded_events_in_the_file();
	print_available_commands();
	String command;
	read_a_command(command);
	while (command != "exit the app")
	{
		process_the_command(command);
		read_a_command(command);
	}
	return;
}

int32_t Hotel::find_the_index_of_room_with_given_number(uint32_t room_number) const
{
	for (int i = 0; i < rooms.get_size(); i++)if (rooms[i].get_room_number() == room_number) return i;
	return -1;
}

void Hotel::process_the_command(String& command)
{
	if (command == "register a guest")
	{
		register_a_guest();
	}
	else if (command == "print the free rooms")
	{
		print_the_free_rooms();
	}
	else if (command == "free a room")
	{
		free_a_room();
	}
	else if (command == "print a report")
	{
		print_a_report();
	}
	else if (command == "find a room")
	{
		find_a_room();
	}
	else if (command == "close a room")
	{
		close_a_room();
	}
	else
	{
		print_error_message();
	}
}

void Hotel::register_a_guest()
{
	Accommodation accommodation;
	std::cin >> accommodation;
	if (is_valid(accommodation))
	{
		int index = find_the_index_of_room_with_given_number(accommodation.get_room_number());
		file.seekp(0, file.std::ios::end);
		rooms[index].add_accommodation_index_to_the_list(file.tellp());
		accommodation.save(file);
	}
}

void Hotel::print_the_free_rooms()
{
	Date date;
	std::cout << "Enter a date: ";
	std::cin >> date;
	Vector<uint32_t> free_rooms;
	for (int i = 0; i < rooms.get_size(); i++)
	{
		if (rooms[i].is_available_on(date, file) == Condition::Available)free_rooms.push_back(rooms[i].get_room_number());
	}
	std::cout << "There are " << free_rooms.get_size() << " free rooms on " << date;
	if (free_rooms.get_size() > 0)std::cout << ":";
	std::cout << "\n";
	for (int i = 0; i < free_rooms.get_size(); i++)std::cout << free_rooms[i] << std::endl;
}

void Hotel::free_a_room()
{
	std::cout << "Enter a room number: ";
	uint32_t room_number, room_index;
	Date date;
	std::cin >> room_number;
	std::cout << "Enter the date of departure: ";
	std::cin >> date;
	room_index = find_the_index_of_room_with_given_number(room_number);
	if (room_index == -1)
	{
		std::cout << "There is no room #" << room_number << " in the hotel!\n";
		return;
	}
	int32_t index_of_accommodation_in_file = rooms[room_index].is_occupied_on(date, file);
	if (index_of_accommodation_in_file == -1)
	{
		std::cout << "The room is already empty!\n";
	}
	else
	{
		Accommodation accommodation;
		accommodation.change_the_departure_date_in_file(file, index_of_accommodation_in_file, date);
		std::cout << "The room was vacated successfully!\n";
	}
	return;
}

void Hotel::print_a_report()
{
	Time_Period period;
	std::cin >> period;
	String report_name = "report-";
	report_name.strcat(period.get_from().to_String());
	report_name.strcat(".txt");
	std::fstream report;
	report.open(report_name, std::ios::out);
	for (int i = 0; i < rooms.get_size(); i++)
	{
		uint32_t number_of_days = rooms[i].number_of_days_being_occupied_in_period(period, file);
		if (number_of_days > 0)
		{
			std::cout << "Room #" << rooms[i].get_room_number() << " was occupied " << number_of_days << " days.\n";
			report << "Room #" << rooms[i].get_room_number() << " was occupied " << number_of_days << " days.\n";
		}
	}
	std::cout << "End of the report\n";
	return;
}

void Hotel::find_a_room()
{
	std::cout << "Enter the number of guests: ";
	uint32_t number_of_guests;
	std::cin >> number_of_guests;
	Time_Period period;
	std::cin >> period;
	uint32_t room_number = get_the_room_with_the_fewest_beds(number_of_guests, period);
	if (room_number == -1)std::cout << "There is no appropriate room!\n";
	else std::cout << "The guest can be accommodated in room #" << room_number << std::endl;
	return;
}

void Hotel::close_a_room()
{
	Closure closure;
	std::cin >> closure;
	if (is_valid(closure))
	{
		int index = find_the_index_of_room_with_given_number(closure.get_room_number());
		file.seekp(0, file.std::ios::end);
		rooms[index].add_closure_index_to_the_list(file.tellp());
		closure.save(file);
	}
}

void Hotel::print_error_message()
{
	std::cout << "Invalid command!\n";
}

int32_t Hotel::get_the_room_with_the_fewest_beds(uint32_t number_of_guests, const Time_Period& period)
{
	uint32_t i = 0;
	while(i < rooms.get_size() && (rooms[i].get_number_of_beds() < number_of_guests ||
		rooms[i].is_available_during(period, file) != Condition::Available))
	{
		i++;
	}
	if (i == rooms.get_size())return -1;
	return rooms[i].get_room_number();
}

bool Hotel::is_valid(Accommodation& new_accommodation)
{

	int32_t new_accommodation_room_index = find_the_index_of_room_with_given_number(new_accommodation.get_room_number());
	if (find_the_index_of_room_with_given_number(new_accommodation.get_room_number()) < 0)
	{
		std::cout << "There is no room #" << new_accommodation.get_room_number() << " in the hotel!\n";
		return false;
	}
	int32_t current_accommodation_index_in_file = rooms[new_accommodation_room_index].is_occupied_during(new_accommodation.get_period(), file);
	int32_t closure_index_in_file = rooms[new_accommodation_room_index].is_closed_during(new_accommodation.get_period(), file);
	if (current_accommodation_index_in_file == -1 && closure_index_in_file == -1 &&
		new_accommodation.get_number_of_guests() <= rooms[new_accommodation_room_index].get_number_of_beds()) return true;
	if (closure_index_in_file != -1 || new_accommodation.get_number_of_guests() > rooms[new_accommodation_room_index].get_number_of_beds())
	{
		return handle_lack_of_rooms_or_closures(closure_index_in_file, new_accommodation);
	}
	if (current_accommodation_index_in_file != -1 && new_accommodation.get_number_of_guests() <= rooms[new_accommodation_room_index].get_number_of_beds())
	{
		return handle_intersecting_accommodations(current_accommodation_index_in_file, new_accommodation);
	}
	return false;
}

bool Hotel::handle_intersecting_accommodations(uint32_t current_accommodation_index_in_file, Accommodation& new_accommodation)
{
	Accommodation current_accommodation;
	uint8_t accommodation_type;
	uint32_t option;
	int32_t new_accommodation_room_index = find_the_index_of_room_with_given_number(new_accommodation.get_room_number());
	file.seekg(current_accommodation_index_in_file);
	file.read(reinterpret_cast<char*>(&accommodation_type), sizeof(uint8_t));
	current_accommodation.read_accommodation_from_file(file, file.tellg());
	uint32_t appropriate_room_for_the_new_guests = get_the_room_with_the_fewest_beds(new_accommodation.get_number_of_guests(), new_accommodation.get_period());
	uint32_t appropriate_room_for_the_old_guests = get_the_room_with_the_fewest_beds(current_accommodation.get_number_of_guests(), current_accommodation.get_period());
	uint32_t number_of_accommodations_in_the_period = rooms[new_accommodation_room_index].number_of_accommodations_during(new_accommodation.get_period(), file);

	if (number_of_accommodations_in_the_period <= 1) std::cout << "There is already a reservation for room #" << new_accommodation.get_room_number()
		<< " under the name of " << current_accommodation.get_guest_name() << " from "
		<< current_accommodation.get_from() << " to " << current_accommodation.get_to() << std::endl;
	else std::cout << "There are several reservations for room #" << new_accommodation.get_room_number()
		<< " during this period!\n";
	if (appropriate_room_for_the_new_guests != -1 || (appropriate_room_for_the_old_guests != -1 && number_of_accommodations_in_the_period <= 1))
	{
		std::cout << "Please, choose one of the following:\n";
		if (appropriate_room_for_the_new_guests != -1)std::cout << "1) Accommodate " << new_accommodation.get_guest_name() << " in room #" << appropriate_room_for_the_new_guests << std::endl;
		if (appropriate_room_for_the_old_guests != -1 && number_of_accommodations_in_the_period <= 1)
		{
			if (appropriate_room_for_the_new_guests != -1)std::cout << "2) ";
			if (appropriate_room_for_the_new_guests == -1)std::cout << "1) ";
			std::cout << "Change the accommodation room for the reservation of " << 
				current_accommodation.get_guest_name() << " to room #" << 
				appropriate_room_for_the_old_guests << " and accommodate " << 
				new_accommodation.get_guest_name() << " in room #" << 
				new_accommodation.get_room_number() << std::endl;
		}
		if (appropriate_room_for_the_old_guests != -1 && number_of_accommodations_in_the_period <= 1)
		{
			if (appropriate_room_for_the_new_guests != -1)std::cout << "3) ";
			if (appropriate_room_for_the_new_guests == -1)std::cout << "2) ";
		}
		else std::cout << "2) ";
		std::cout << "Cancel the accommodation of " << new_accommodation.get_guest_name() << std::endl;
		std::cout << "Enter the number of the option you chose: ";
		std::cin >> option;
		std::cin.get();
		switch (option)
		{
		case 3:
			std::cout << "The reservation was rejected!\n";
			return false;
		case 2:
			if (appropriate_room_for_the_new_guests == -1 || appropriate_room_for_the_old_guests == -1 || number_of_accommodations_in_the_period > 1)
			{
				std::cout << "The reservation was rejected!\n";
				return false;
			}
			else
			{
				change_room_number_of(current_accommodation, appropriate_room_for_the_old_guests, current_accommodation_index_in_file);
				return true;
			}
		case 1:
			if (appropriate_room_for_the_new_guests == -1)
			{
				change_room_number_of(current_accommodation, appropriate_room_for_the_old_guests, current_accommodation_index_in_file);
				return true;
			}
			else if (appropriate_room_for_the_new_guests != -1)
			{
				new_accommodation.set_room_number(appropriate_room_for_the_new_guests);
				return true;
			}
		default:std::cout << "Invalid option! The reservation was rejected!\n" << std::endl;
		}
	}
}

void Hotel::change_room_number_of(Accommodation& accommodation, uint32_t new_room_number, int32_t accommodation_index_in_file)
{
	uint32_t current_room_index = find_the_index_of_room_with_given_number(accommodation.get_room_number());
	rooms[current_room_index].remove_accommodation_index_from_the_list(accommodation_index_in_file);
	accommodation.set_room_number(new_room_number);
	accommodation.change_the_room_number_in_file(file, accommodation_index_in_file, new_room_number);
	rooms[find_the_index_of_room_with_given_number(new_room_number)].add_accommodation_index_to_the_list(accommodation_index_in_file);

}

bool Hotel::handle_lack_of_rooms_or_closures(uint32_t closure_index_in_file, Accommodation& new_accommodation)
{
	Closure closure;
	uint8_t closure_type;
	uint32_t option;
	int32_t new_accommodation_room_index = find_the_index_of_room_with_given_number(new_accommodation.get_room_number());
	uint32_t appropriate_room_for_the_new_guests = get_the_room_with_the_fewest_beds(new_accommodation.get_number_of_guests(), new_accommodation.get_period());
	if (closure_index_in_file != -1)
	{
		file.seekg(closure_index_in_file);
		file.read(reinterpret_cast<char*>(&closure_type), sizeof(uint8_t));
		closure.read_closure_from_file(file, file.tellg());
		std::cout << "Room #" << new_accommodation.get_room_number() << " will be closed from " <<
			closure.get_from() << " to " << closure.get_to() << " because of " << closure.get_note() << std::endl;

	}
	else if (new_accommodation.get_number_of_guests() > rooms[new_accommodation_room_index].get_number_of_beds())
		std::cout << "There are no enough beds in the room!\n";

	if (appropriate_room_for_the_new_guests != -1)
	{
		std::cout << "Please, choose one of the following:\n";
		std::cout << "1) Accommodate " << new_accommodation.get_guest_name() << " in room #" << appropriate_room_for_the_new_guests << std::endl;
		std::cout << "2) Cancel the accommodation of " << new_accommodation.get_guest_name() << std::endl;
		std::cout << "Enter the number of the option you chose: ";
		std::cin >> option;
		std::cin.get();
		switch (option)
		{
		case 2:
			std::cout << "The reservation was rejected!\n";
			return false;
		case 1:
			new_accommodation.set_room_number(appropriate_room_for_the_new_guests);
			return true;
		default:
			return false;
		}
	}
	return false;
}

bool Hotel::is_valid(const Closure& closure)
{
	int32_t index = find_the_index_of_room_with_given_number(closure.get_room_number());
	if (index < 0)
	{
		std::cout << "There is no room #" << closure.get_room_number() << " in the hotel!\n";
		return false;
	}
	int32_t accommodation_index = rooms[index].is_occupied_during(closure.get_period(), file);
	int32_t closure_index = rooms[index].is_closed_during(closure.get_period(), file);

	if (accommodation_index != -1)
	{
		Accommodation accommodation;
		uint8_t accommodation_type;
		file.seekg(accommodation_index);
		file.read(reinterpret_cast<char*>(&accommodation_type), sizeof(uint8_t));
		accommodation.read_accommodation_from_file(file, file.tellg());
		std::cout << "Cannot close the room because there is already a reservation for room #" 
			<< accommodation.get_room_number() << " under the name of " 
			<< accommodation.get_guest_name() << " from " << accommodation.get_from() 
			<< " to " << accommodation.get_to() << std::endl;
		return false;
	}
	else if (closure_index != -1)
	{
		Closure closure;
		uint8_t closure_type;
		file.seekg(closure_index);
		file.read(reinterpret_cast<char*>(&closure_type), sizeof(uint8_t));
		closure.read_closure_from_file(file, file.tellg());
		std::cout << "There is already planned closing of Room #" << closure.get_room_number() << " from " <<
		closure.get_from() << " to " << closure.get_to() << " because of " << closure.get_note() << std::endl;
		return false;
	}
	return true;
}

void print_available_commands()
{
	std::cout << "------------------------------------------------------------------------------------------------------------------------\n";
	std::cout << "TO PERFORM OPERATIONS, ENTER SOME OF THE FOLLOWING COMMANDS: (CASE-INSENSITIVE)\n";
	std::cout << "REGISTER A GUEST\n";
	std::cout << "PRINT THE FREE ROOMS\n";
	std::cout << "FREE A ROOM\n";
	std::cout << "PRINT A REPORT\n";
	std::cout << "FIND A ROOM\n";
	std::cout << "CLOSE A ROOM\n";
	std::cout << "EXIT THE APP\n";
	std::cout << "------------------------------------------------------------------------------------------------------------------------\n";
}

void read_a_command(String& command)
{
	std::cout << "Command: ";
	getline(std::cin, command, '\n');
	command.tolower();
	return;
}
