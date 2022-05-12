#include "Accommodation.h"

Accommodation::Accommodation(uint32_t _room_number, uint32_t _number_of_guests, const Time_Period& _period, String _guest_name, String _note)
{
	room_number = _room_number;
	number_of_guests = _number_of_guests;
	period = _period;
	guest_name = _guest_name;
	note = _note;
}

const Time_Period& Accommodation::get_period() const
{
	return period;
}

const Date& Accommodation::get_from() const
{
	return period.get_from();
}

const Date& Accommodation::get_to() const
{
	return period.get_to();
}

uint32_t Accommodation::get_room_number() const
{
	return room_number;
}

const String& Accommodation::get_guest_name() const
{
	return guest_name;
}

uint32_t Accommodation::get_number_of_guests() const
{
	return number_of_guests;
}

void Accommodation::read_accommodation_from_file(std::fstream& file, int position)
{
	file.seekg(position);
	file.read(reinterpret_cast<char*> (&room_number), sizeof(uint32_t));
	file.read(reinterpret_cast<char*>(&number_of_guests), sizeof(uint32_t));
	period.read_period_from_file(file, file.tellg());
	guest_name.read_string_from_file(file, file.tellg());
	note.read_string_from_file(file, file.tellg());
}

void Accommodation::write_accommodation_to_file(std::fstream& file, int position) const
{
	uint8_t accommodation_type = 1;
	file.seekp(position);
	file.write(reinterpret_cast<const char*> (&accommodation_type), sizeof(uint8_t));
	file.write(reinterpret_cast<const char*> (&room_number), sizeof(uint32_t));
	file.write(reinterpret_cast<const char*> (&number_of_guests), sizeof(uint32_t));
	period.write_period_to_file(file, file.tellp());
	guest_name.write_string_to_file(file, file.tellp());
	note.write_string_to_file(file, file.tellp());
}

void Accommodation::change_the_departure_date_in_file(std::fstream& file, int32_t file_pos, const Date& date)
{
	date.write_date_to_file(file, file_pos + position_of_to_date_in_file);
	return;
}

void Accommodation::save(std::fstream& file) const
{
	write_accommodation_to_file(file, file.tellp());
	std::cout << "The reservation for " << get_guest_name() << " from " << get_from() << " to " << get_to() << " has been saved successfully!\n";
	if(note.get_data() != nullptr)std::cout << "There is a note for the reservation: " << note << std::endl;
	return;
}


std::istream& operator>>(std::istream& in, Accommodation& accommodation)
{
	std::cout << "Enter a room number: ";
	in >> accommodation.room_number;
	std::cout << "Enter the number of guests: ";
	in >> accommodation.number_of_guests;
	in >> accommodation.period;
	std::cout << "Enter the guest's name: ";
	in >> accommodation.guest_name;
	std::cout << "Enter a note (Optional): ";
	in >> accommodation.note;
	return in;
}




