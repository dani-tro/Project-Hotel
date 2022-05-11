#include "Closure.h"

void Closure::Close(uint32_t _room_number, const Time_Period& _period, String _note)
{
	room_number = _room_number;
	period = _period;
	note = _note;
	return;
}

const Time_Period& Closure::get_period() const
{
	return period;
}

const Date& Closure::get_from() const
{
	return period.get_from();
}

uint32_t Closure::get_room_number() const
{
	return room_number;
}

const Date& Closure::get_to() const
{
	return period.get_to();
}

void Closure::read_closure_from_file(std::fstream& file, int position)
{
	file.seekg(position);
	file.read(reinterpret_cast<char*> (&room_number), sizeof(uint32_t));
	period.read_period_from_file(file, file.tellg());
	note.read_string_from_file(file, file.tellg());
}

void Closure::write_closure_to_file(std::fstream& file, int position) const
{
	uint8_t closure_type = 2;
	file.seekp(position);
	file.write(reinterpret_cast<const char*> (&closure_type), sizeof(uint8_t));
	file.write(reinterpret_cast<const char*> (&room_number), sizeof(uint32_t));
	period.write_period_to_file(file, file.tellp());
	note.write_string_to_file(file, file.tellp());
}

std::istream& operator>>(std::istream& in, Closure& closure)
{
	std::cout << "Enter a room number: ";
	in >> closure.room_number;
	in >> closure.period;
	std::cout << "Enter a note about the closure: ";
	in >> closure.note;
	return in;
}

void Closure::save(std::fstream& file) const
{
	write_closure_to_file(file, file.std::ios::end);
	std::cout << "The information about closing room #" << get_room_number() << " from " << get_from() << " to " << get_to() << " has been saved successfully!\n";
	if (note.get_data() != nullptr)std::cout << "The reason for the closing is: " << note << std::endl;
	return;
}