#include "String.h"

#include <iostream>

void String::swap(String& other)
{
	using std::swap;
	swap(size, other.size);
	swap(data, other.data);
}

void String::resize(size_t increment)
{
	char* copy = new char[get_size() + increment + 1];
	if (get_size() != 0)strcpy(copy, data);
	copy[get_size()] = '\0';
	delete[] data;
	set_data(copy);
	set_size(get_size() + increment);
}

String::~String()
{
	delete[] data;
}

String::String(const String& other)
{
	data = new char[other.get_size()];
	if(other.get_size() != 0)strcpy(data, other.get_data());
	set_size(other.get_size());
}

String& String::operator=(const String& other)
{
	String copy{ other };
	swap(copy);
	return *this;
}

String::String(const char* str)
{
	size = strlen(str);
	data = new char[size + 1];
	strcpy(data, str);
	data[size] = '\0';
}

void String::set_size(size_t _size)
{
	size = _size;
}

void String::set_data(char* _data)
{
	data = _data;
}

void String::tolower()
{
	for (int i = 0; i < get_size(); i++)
	{
		if('A' <= data[i] && data[i] <= 'Z')data[i] = (data[i] - 'A' + 'a');
	}
	return;
}

size_t String::get_size() const
{
	return size;
}

const char* String::get_data() const
{
	return data;
}

void String::read_string_from_file(std::fstream& file)
{
	file.read(reinterpret_cast<char*>(&size), sizeof(size_t));
	char* buff = new char[get_size() + 1];
	file.read(buff, get_size());
	buff[get_size()] = '\0';
	set_data(buff);
}

void String::write_string_to_file(std::fstream& file)
{
	file.write(reinterpret_cast<const char*>(&size), sizeof(size_t));
	file.write(*this, get_size());
}

String::operator char* () const
{
	return data;
}

String::operator const char*() const
{
	return data;
}

bool String::operator==(const char* other)
{
	if (get_size() == 0 && strlen(other) == 0)return true;
	if(get_size() - 1 != strlen(other))return false;
	for (int i = 0; i < get_size(); i++)if (data[i] != other[i])return false;
	return true;
}

std::istream& getline(std::istream& in, String& s, const char delim)
{
	char buff;
	s = String();
	s.resize(1);
	while (in.peek() != delim)
	{
		buff = in.get();
		s.resize(1);
		strncat(s.data, &buff, 1);
	}
	in.get();
	return in;
}

std::istream& operator>>(std::istream& in, String& s)
{
	getline(in, s, ' ');
	return in;
}
