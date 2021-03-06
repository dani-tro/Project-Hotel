#include "Room.h"

int32_t Room::is_closed_on(const Date& date, std::fstream& file) const
{
    Closure closure;
    uint8_t closure_type;
    for (size_t i = 0; i < closures_indexes_in_file_list.get_size(); i++)
    {
        file.seekg(closures_indexes_in_file_list[i]);
        file.read(reinterpret_cast<char*>(&closure_type), sizeof(uint8_t));
        closure.read_closure_from_file(file, file.tellg());
        if (closure.get_from() <= date && date <= closure.get_to()) return closures_indexes_in_file_list[i];
    }
    return -1;
}

int32_t Room::is_closed_during(const Time_Period& period, std::fstream& file) const
{
    Closure closure;
    uint8_t closure_type;
    for (size_t i = 0; i < closures_indexes_in_file_list.get_size(); i++)
    {
        file.seekg(closures_indexes_in_file_list[i]);
        file.read(reinterpret_cast<char*>(&closure_type), sizeof(uint8_t));
        closure.read_closure_from_file(file, file.tellg());
        if (intersect(closure.get_period(), period).duration() > 0) return closures_indexes_in_file_list[i];
    }
    return -1;
}

int32_t Room::is_occupied_on(const Date& date, std::fstream& file) const
{
    Accommodation accommodation;
    uint8_t accommodation_type;

    for (size_t i = 0; i < accommodations_indexes_in_file_list.get_size(); i++)
    {
        file.seekg(accommodations_indexes_in_file_list[i]);
        file.read(reinterpret_cast<char*>(&accommodation_type), sizeof(uint8_t));
        accommodation.read_accommodation_from_file(file, file.tellg());
        if (accommodation.get_from() <= date && date <= accommodation.get_to())return accommodations_indexes_in_file_list[i];
    }
    return -1;
}

int32_t Room::is_occupied_during(const Time_Period& period, std::fstream& file) const
{
    Accommodation accommodation;
    uint8_t accommodation_type;
    
    for (size_t i = 0; i < accommodations_indexes_in_file_list.get_size(); i++)
    {
        
        file.seekg(accommodations_indexes_in_file_list[i]);
        file.read(reinterpret_cast<char*>(&accommodation_type), sizeof(uint8_t));
        accommodation.read_accommodation_from_file(file, file.tellg());
        if (intersect(accommodation.get_period(), period).duration() > 0) return accommodations_indexes_in_file_list[i];
    }
    return -1;
}

uint32_t Room::number_of_accommodations_during(const Time_Period& period, std::fstream& file) const
{
    uint32_t counter = 0;
    Accommodation accommodation;
    uint8_t accommodation_type;
    for (size_t i = 0; i < accommodations_indexes_in_file_list.get_size(); i++)
    {
        file.seekg(accommodations_indexes_in_file_list[i]);
        file.read(reinterpret_cast<char*>(&accommodation_type), sizeof(uint8_t));
        accommodation.read_accommodation_from_file(file, file.tellg());
        if (intersect(accommodation.get_period(), period).duration() > 0)counter++;
    }
    return counter;
}

Condition Room::is_available_on(const Date& date, std::fstream& file) const
{
    if (is_closed_on(date, file) != -1)return Condition::Closed;
    if (is_occupied_on(date, file) != -1)return Condition::Occupied;
    return Condition::Available;
}

Condition Room::is_available_during(const Time_Period& period, std::fstream& file) const
{
    if (is_closed_during(period, file) != -1)return Condition::Closed;
    if (is_occupied_during(period, file) != -1)return Condition::Occupied;
    return Condition::Available;
}


uint32_t Room::number_of_days_being_occupied_in_period(const Time_Period& period, std::fstream& file)
{
    uint32_t number_of_days = 0;
    Accommodation accommodation;
    uint8_t accommodation_type;
    for (size_t i = 0; i < accommodations_indexes_in_file_list.get_size(); i++)
    {
        file.seekg(accommodations_indexes_in_file_list[i]);
        file.read(reinterpret_cast<char*>(&accommodation_type), sizeof(uint8_t));
        accommodation.read_accommodation_from_file(file, file.tellg());
        number_of_days += intersect(accommodation.get_period(), period).duration();
    }
    return number_of_days;
}

void Room::read_room_from_file(std::fstream& file, int position)
{
    file.seekg(position);
    file.read(reinterpret_cast<char*>(&room_number), sizeof(uint32_t));
    file.read(reinterpret_cast<char*>(&number_of_beds), sizeof(uint32_t));
    return;
}

uint32_t Room::get_room_number() const
{
    return room_number;
}

uint32_t Room::get_number_of_beds() const
{
    return number_of_beds;
}

void Room::add_accommodation_index_to_the_list(int32_t index)
{
    accommodations_indexes_in_file_list.push_back(index);
}

void Room::remove_accommodation_index_from_the_list(int32_t value)
{
    uint32_t index = 0;
    while (index < accommodations_indexes_in_file_list.get_size() &&
        accommodations_indexes_in_file_list[index] != value)index++;
    accommodations_indexes_in_file_list.remove_value_at(index);
}

void Room::add_closure_index_to_the_list(int32_t index)
{
    closures_indexes_in_file_list.push_back(index);
}

bool Room::operator<(const Room& other) const
{
    if (number_of_beds != other.number_of_beds)return number_of_beds < other.number_of_beds;
    return (room_number < other.room_number);
}

bool Room::operator==(const Room& other) const
{
    return room_number == other.room_number;
}

bool Room::operator<=(const Room& other) const
{
    return (*this < other || *this == other);
}
