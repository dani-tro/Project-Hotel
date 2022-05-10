#ifndef __STRING_HPP
#define __STRING_HPP

#include <iostream>
#include <fstream>

class String
{
private:
	char* data = nullptr;
	size_t size = 0;

	void swap(String&);
	void resize(size_t);
	void set_size(size_t);
	void set_data(char*);
public:
	String() = default;
	~String();
	String(const String&);
	String& operator=(const String&);
	String(const char*);

	void tolower();
	void strcat(const String&);
	size_t get_size() const;
	const char* get_data() const;
	friend std::istream& getline(std::istream&, String&, const char);
	void read_string_from_file(std::fstream&, int);
	void write_string_to_file(std::fstream&, int) const;
	friend std::istream& operator>>(std::istream&, String&);
	operator char* () const;
	operator const char*() const;
	bool operator==(const String&) const;
	bool operator==(const char*) const;
	bool operator!=(const char*) const;
};



#endif