#include <iostream> 
#include "array2d.h"
#include <vector>
using namespace std;



template <typename T>
const unsigned int math::Array2D<T>::getWidth() const {
	return this->width;
} // getWidth 


template <typename T>
const unsigned int math::Array2D<T>::getHeight() const {
	return this->height;
} // getHeight 


template <typename T>
T* math::Array2D<T>::getRawDataPtr() {
	T* p_t_r = &buffer[0];
	return p_t_r;
} // getRawDataPtr 

template <typename T>
void math::Array2D<T>::setData(const T* const& data_ptr) {
	if (width == 0 || height == 0)
		return;
	else {
		for (int i = 0; i < height * width; i++) {
			buffer[i] = data_ptr[i];
		} // for loop
	} // else
} // setData 

template <typename T>
T& math::Array2D<T>::operator () (unsigned int x, unsigned int y) {
	return buffer[x * width + y];
} // operator 

template <typename T>
math::Array2D<T>::Array2D(unsigned int width, unsigned int height, const T* data_ptr) {
	if (width > 0 && height > 0 && data_ptr == NULL) {
		this->width = width;
		this->height = height;
		for (int i = 0; i < width * height; i++)
			buffer.push_back(0);

	} // if 
	else {
		this->width = width;
		this->height = height;
		for (int i = 0; i < width * height; i++)
			buffer.push_back(data_ptr[i]);
	} // else 
} // constructor 


template<typename T>
math::Array2D<T>::Array2D(const Array2D& src) {
	this->width = src.width;
	this->height = src.height;
	this->buffer = src.buffer;
} // copy constructor 

template <typename T>
math::Array2D<T>::~Array2D() {
	//delete[] buffer;
	//cout << "Destructor called" << endl;
} // destructor 

template<typename T>
math::Array2D<T>& math::Array2D<T>:: operator = (const math::Array2D<T>& right) {
	this->height = right.height;
	this->width = right.width;
	this->buffer = right.buffer;
	return *this;
} // copy assigment operator 
