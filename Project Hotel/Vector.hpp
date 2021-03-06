#ifndef __VECTOR_HPP
#define __VECTOR_HPP

#include <iostream>
#include <cassert>

template <typename T>
class Vector
{
private:
	T* data = nullptr;
	size_t size = 0;
	size_t capacity = 0;

	void resize(size_t);
	void set_capacity(size_t);
	void set_size(size_t);
	void swap(Vector&);
public:
	Vector() = default;
	~Vector();
	Vector(const Vector&);
	
	Vector& operator=(const Vector&);

	size_t get_capacity() const;
	size_t get_size() const;
	T& operator[](size_t idx);
	const T& operator[](size_t idx) const;
	void push_back(const T&);
	void pop_back();
	void remove_value_at(uint32_t);
	T* begin() const;
	T* end() const;
};

template<typename T>
void Vector<T>::resize(size_t new_capacity)
{
	Vector copy{ *this };
	delete[] data;
	set_capacity(new_capacity);
	data = new T[capacity];
	std::copy(copy.data, copy.data + size, data);
	return;
}

template<typename T>
void Vector<T>::set_capacity(size_t new_capacity)
{
	capacity = new_capacity;
}

template<typename T>
void Vector<T>::set_size(size_t new_size)
{
	size = new_size;
}

template<typename T>
Vector<T>::~Vector()
{
	delete[] data;
}

template<typename T>
Vector<T>::Vector(const Vector& other) : size{ other.size }, capacity{ other.capacity }
{
	data = new T[capacity];
	std::copy(other.data, other.data + size, data);
}

template<typename T>
void Vector<T>::swap(Vector& other)
{
	using std::swap;
	swap(size, other.size);
	swap(capacity, other.capacity);
	swap(data, other.data);
}

template<typename T>
Vector<T>& Vector<T>::operator=(const Vector& other)
{
	Vector copy{ other };
	swap(copy);
	return *this;
}

template<typename T>
size_t Vector<T>::get_capacity() const
{
	return capacity;
}

template<typename T>
size_t Vector<T>::get_size() const
{
	return size;
}

template<typename T>
T& Vector<T>::operator[](size_t idx)
{
	assert(idx < get_size() && "Accessing a valid element of the vector!\n");
	return data[idx];
}

template<typename T>
const T& Vector<T>::operator[](size_t idx) const
{
	assert(idx < get_size() && "Accessing a valid element of the vector!\n");
	return data[idx];
}

template<typename T>
void Vector<T>::push_back(const T& other)
{
	if (get_size() + 1 > get_capacity())resize(get_capacity() * 2 + 1);
	data[get_size()] = other;
	set_size(get_size() + 1);
	return;
}

template<typename T>
void Vector<T>::pop_back()
{
	if(get_size() > 0)set_size(get_size() - 1);
	return;
} 

template<typename T>
void Vector<T>::remove_value_at(uint32_t index)
{
	for (int i = index; i < get_size() - 1; i++)
	{
		data[i] = data[i + 1];
	}
	pop_back();
	return;
}

template<typename T>
inline T* Vector<T>::begin() const
{
	return data;
}

template<typename T>
inline T* Vector<T>::end() const
{
	return begin() + get_size();
}

#endif