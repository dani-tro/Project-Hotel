#ifndef __VECTOR_HPP
#define __VECTOR_HPP

#include <iostream>

template <typename T>
class Vector
{
private:
	T* data = nullptr;
	size_t size = 0;
	size_t capacity = 0;

	void resize(size_t);
public:
	Vector() = default;
	~Vector();
	Vector(const Vector&);
	void swap(Vector&);
	Vector& operator=(const Vector&);

	size_t get_size() const;
	void push_back(const T&);
};

#endif