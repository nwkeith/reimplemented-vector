#pragma once

/*
	Vector.h - common abstraction for arrays in C++
*/

#include <cstring>
#include <stdlib.h>
#include <cstddef>
#include <new>


template <typename T> class Vector {
public:
	int size();
	void push_back(T item);
	T pop_back();
	T pop_front();
	int capacity();
	void reserve(int size);
	void resize(int newSize);
	void cleanUp();
	Vector();
	Vector(Vector&);
	Vector(Vector&&); // move constructor
	~Vector();

	T& operator[](int index);
	T& operator=(int index);
	Vector& operator=(Vector&);
	Vector& operator=(Vector&&);
	T* accessArray(int);


private:
	int m_size;
	int m_capacity;
	std::byte* m_array;
	std::byte* initArray(int);
	
};

template <typename T> 
Vector<T>::Vector()
{
	m_size = 0;
	m_capacity = 1;
	m_array = initArray(m_capacity);
}

template <typename T> 
Vector<T>::~Vector()
{
	cleanUp();
}

template <typename T>
Vector<T>::Vector(Vector& old_vec)
{
	m_size = old_vec.m_size;
	m_capacity = old_vec.m_capacity;
	m_array = initArray(m_capacity);
	for (int i = 0; i < m_capacity; i++) {
		T var = *(old_vec.accessArray(i)); // don't know why I can't use old_vec[i]
		*accessArray(i) = var;
	}
		
}

template<typename T>
Vector<T>::Vector(Vector&& old_vec)
{
	m_size = old_vec.m_size;
	m_capacity = old_vec.m_capacity;
	m_array = old_vec.m_array;
	old_vec.m_size = 0;
	old_vec.m_capacity = 1;
	old_vec.m_array = nullptr;
}

template <typename T> 
T& Vector<T>::operator[](int index)
{
	if (index >= m_size) // out of bounds
		exit(1);
	return *accessArray(index);
}

template <typename T>
T& Vector<T>::operator=(int index)
{
	if (index >= m_size) // out of bounds
		exit(1);
	return *accessArray(index);
}

template <typename T>
Vector<T>& Vector<T>::operator=(Vector<T>& old_vec)
{
	m_size = old_vec.m_size;
	m_capacity = old_vec.m_capacity;
	m_array = initArray(m_capacity);
	for (int i = 0; i < m_capacity; i++)
		*this->accessArray(i) = *old_vec.accessArray(i);
	return *this;
}

template<typename T>
Vector<T>& Vector<T>::operator=(Vector<T>&& old_vec)
{
	m_size = old_vec.m_size;
	m_capacity = old_vec.m_capacity;
	m_array = old_vec.m_array;
	old_vec.m_size = 0;
	old_vec.m_capacity = 1;
	old_vec.m_array = nullptr;
	return *this;
}

template<typename T>
std::byte* Vector<T>::initArray(int capacity)
{
	std::byte* array = reinterpret_cast<std::byte*>(operator new(sizeof(T) * capacity, static_cast<std::align_val_t>(alignof(T))));
	
	return array;
}

template<typename T>
T* Vector<T>::accessArray(int index)
{
	return reinterpret_cast<T*>(&m_array[index * sizeof(T)]); // reinterpret cast may not work
}

template <typename T> 
int Vector<T>::size()
{
	return m_size;
}

template <typename T> 
void Vector<T>::push_back(T item)
{
	if (m_capacity == m_size) { // array is too small
		m_capacity *= 2;
		reserve(m_capacity);
	}
	new (accessArray(m_size)) T(); 
	*accessArray(m_size) = item;
	m_size++;
}

template <typename T> 
T Vector<T>::pop_back()
{
	m_size--;
	return *accessArray(m_size);
}

template <typename T> 
T Vector<T>::pop_front()
{
	m_size--;
	T frontValue = *accessArray(0);
	for (int i = 0; i < m_size; i++) { // do not have to change capacity
		*accessArray(i) = *accessArray(i + 1);
	}
	return frontValue;
}

template <typename T> 
int Vector<T>::capacity()
{
	return m_capacity;
}

template <typename T> 
void Vector<T>::reserve(int size)
{
	std::byte* copyArray = initArray(size);
	std::memcpy(copyArray, m_array, m_size*sizeof(T)); // sizeof(T) varies based on type used
	/*for (int i = 0; i < m_size; i++) {
		T* copyPoint = reinterpret_cast<T*>(&copyArray[i * sizeof(T)]);
		*copyPoint = *accessArray(i);
	}*/
	cleanUp();
	m_capacity = size;
	m_array = copyArray;
}

template <typename T> 
void Vector<T>::resize(int newSize)
{
	if (newSize == m_size) {
		return;
	} else if (newSize < m_size) {
		m_size = newSize;
	} else { // newSize > size
		if (newSize > m_capacity)
			reserve(newSize);
		for (int i = m_size; i < newSize; i++)
			new (accessArray(i)) T();
		m_size = newSize;
	}
}

template <typename T>
void Vector<T>::cleanUp()
{
	for (int i = 0; i < m_size; i++) {
		if (accessArray(i))
			accessArray(i)->~T();
	}
	operator delete (m_array, static_cast<std::align_val_t>(alignof(T)));
}
