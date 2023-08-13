#ifndef _FILTERS
#define _FILTERS


#include <iostream>
#include "image.h"
#include "vec3.h"
using namespace std;

typedef math::Vec3<float> colour;
class Filter {

public:
	Filter() {} // default constructor 

	Filter(Filter& f) { *this = f; } // copy constructor 

	virtual Image operator << (const Image& image) = 0; // pure virtual method - operator which is going to be implemented below

}; // class Filter


class FilterLinear : public Filter {
private:
	colour a;
	colour r;
public:
	FilterLinear(colour a, colour r) {
		this->a = a;
		this->r = r;
	} // constructor 

	FilterLinear() {

	} // default constructor 

	FilterLinear(FilterLinear& b) {
		this->a = b.a;
		this->r = b.r;
	} // copy constructor 

	colour getA() {
		return a;
	} // getter 

	colour getR() {
		return r;
	} // getter

	Image operator << (const Image& image) {
		int width = image.getWidth();
		int height = image.getHeight();

		Image b = image;

		for (unsigned int i = 0; i < height; i++) {
			for (unsigned int j = 0; j < width; j++) {
				b(i, j) = a * b(i, j) + r;
				if (b(i, j).r < 0)
					b(i, j).r = 0;
				if (b(i, j).g < 0)
					b(i, j).g = 0;
				if (b(i, j).b < 0)
					b(i, j).b = 0;

				if (b(i, j).r > 1)
					b(i, j).r = 1;
				if (b(i, j).g > 1)
					b(i, j).g = 1;
				if (b(i, j).b > 1)
					b(i, j).b = 1;
			}
		}
		return b;
	} // operator implementation

}; // class FilterLinear


class FilterGamma : public Filter {
private:
	float y;

public:
	FilterGamma(float v) {
		if (v >= 0.5 && v <= 2.0) {
			this->y = v;
		}
		else {
			// by default lets set it 1
			this->y = 1.0f;
		}
	} // constructor 

	FilterGamma() {
		this->y = 1.0f;
	} // default constructor 

	FilterGamma(FilterGamma& b) {
		this->y = b.y;
	}

	float getParameter() {
		return y;
	} // getter 

	Image operator << (const Image& image) {
		Image b = image;
		int width = image.getWidth();
		int height = image.getHeight();
		for (unsigned int i = 0; i < height; i++) {
			for (unsigned int j = 0; j < width; j++) {
				b(i, j).r = pow(b(i, j).r, y);
				b(i, j).g = pow(b(i, j).g, y);
				b(i, j).b = pow(b(i, j).b, y);
			} // for loop
		} // for loop
		return b;
	} // operator implementation


}; // class FilterGamma



#endif // !_FILTERS

