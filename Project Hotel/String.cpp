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
	data = new char[other.size];
	if(other.get_size() != 0)strcpy(data, other.data);
	size = other.size;
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

std::istream& getline(std::istream& in, String& s, const char delim)
{
	char buff;
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
