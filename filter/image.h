#ifndef _IMAGE
#define _IMAGE

#include <iostream>
#include "array2d.h"
#include "imageio.h"
#include "vec3.h"
#include "ppm.h"
#include <string>



using namespace std;

typedef math::Vec3<float> color;

class Image : public math::Array2D<color>, public image::ImageIO {
public:
	Image(int w, int h, color* buffer) : math::Array2D<color>::Array2D(w, h, buffer) {} // constructor 

	// initialising width, height and buffer 


	bool load(const std::string& filename, const std::string& format) {
		int x = this->getWidth(); // x represents the width 
		int y = this->getHeight(); // y represents the height 

		if (format == "ppm" || format == "PPM") {
			cout << "Loading image..." << endl;
			float* b = new float[3 * x * y]; // float array holding the data
			string name = "";
			name += filename;
			name += ".ppm";
			char* cstr = new char[name.size() + 1];
			name.copy(cstr, name.size() + 1);
			cstr[name.size()] = '\0';



			b = image::ReadPPM(cstr, &x, &y); // use the imlemented function to read the image fata 
			;
			if (b == NULL) {
				cout << "Image load is not possible" << endl;
				return false;
			} // if 
			else {
				color* B = new color[x * y]; // the math::Vec3<float> array 

				int t = 0;
				for (int i = 0; i < x * y; i++) {
					B[i] = *new color(b[t], b[t + 1], b[t + 2]);
					t = t + 3;

				} // for loop


				this->setData(B);
				delete[] B;
				delete[] cstr;
				delete[] b;

				return true;

			} // else 


		} // if 

	} // load 


	bool save(const std::string& filename, const std::string& format) {

		if (format == "ppm" || format == "PPM") {
			int x = this->getWidth(); // x represents the width 
			int y = this->getHeight(); // y represents the height 

			bool b = false;
			float* bb = new float[3 * x * y];  // we will store the data to this array 

		   // color* B = new color[x * y];
			color* B;
			B = this->getRawDataPtr();
			int k = 0;
			for (int i = 0; i < x * y; i++) {
				bb[k] = B[i].x;
				bb[k + 1] = B[i].y;
				bb[k + 2] = B[i].z;
				k = k + 3;
			} // for loop 
			string name = "";
			name += filename;
			name += ".ppm";
			char* cstr = new char[name.size() + 1];
			name.copy(cstr, name.size() + 1);
			cstr[name.size()] = '\0';

			b = image::WritePPM(bb, x, y, cstr);
			delete[] cstr;
			//delete[] B; 
		   // delete[] bb; 
			return true;
		} // if 
		else {
			return false;
		} // else 
	} // save




}; // class Image
















#endif // !_IMAGE
