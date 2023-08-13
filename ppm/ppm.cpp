// ppm.cpp : Defines the functions for the static library.
//
#include <iostream>
#include <fstream>
#include <string>
#include "framework.h"
#include "ppm.h" 


using namespace image;
using namespace std;


float* image::ReadPPM(const char* filename, int* w, int* h) {
	fstream file(filename, ios::in || ios::binary);
	char* buffer = new char[25];

	int b = (int)to_string(*w).length();
	int c = (int)to_string(*h).length();
	// there are always going to be 4 chars of tab-'\n' or spacebar placed there
	int fin = 9 + b + c;
	
	file.read((char*)buffer, sizeof(char) * fin);
	string txt; // represents the P6
	txt += buffer[0];
	txt += buffer[1];
	string txt1; // represents the 1st number
	for (int i = 3; i < 3 + b; i++) {
		txt1 += buffer[i];
	}
	string txt2; // represents the 2nd number
	for (int i = 4 + b; i < 4 + b + c; i++) {
		txt2 += buffer[i];
	}
	string txt3;  // represents the 255
	txt3 += buffer[fin - 4];
	txt3 += buffer[fin - 3];
	txt3 += buffer[fin - 2];
	
	cout << "Header part check just started...\n";
	if (txt != "P6") {
		cerr << "You typed a format that does not match P6\n";
		fin = -5;
	}
	else if (txt1 != to_string(*w)) {
		cerr << "Invalid argument width given\n";
		fin = -5;
	}
	else if (txt2 != to_string(*h)) {
		cerr << "Invalid argument height given\n";
		fin = -5;
	}
	else if (txt3 != "255") {
		cerr << "Invalid maximum colour value given. Expected 255\n";
		fin = -5;
	}
	else
		cout << "Header part checks completed succesfully. Ready to procced in file reading..\n";

	delete[]buffer;

	if (fin > 0) {
		fstream file(filename, ios::in | ios::binary);
		if (!file.is_open()) {
			cerr << "Could not open file!\n" << endl;
		}  // if 
		else {
			// binary part of code 
			cout << "File opened succesfully!" << endl;
			cout << "Prepare file for reading" << endl;
			file.seekg(0, ios_base::beg);
			file.seekg(0, file.end);
			int length = file.tellg();
			file.seekg(0, file.beg);
			file.seekg(fin, file.beg); 

			float* buffer = new float[length];

			for (int i = 0; i < length; i++) {
				unsigned char a;
				file.read((char*)&a, sizeof(char));
				buffer[i] = a / 255.0f;
			} // for loop 
			file.close();
			return buffer;
			delete[]buffer;
		} // else 
	} // if start > 0
	else {
		cerr << "Finally, could not read File. Please check again all the properties given.\n";
		return NULL;
	}
} // readPPM


bool image::WritePPM(const float* data, int w, int h, const char* filename) {
	cout << "Writing file.." << endl;
	string a = "filtered_";
	string c = a + filename;
	fstream fl(c, ios::out | ios::binary);
	if (!fl) {
		cout << "Error occured in creating the file with the given properties" << endl;
		return false;
	} // if 

	string text = "P6\n";
	fl.write(text.c_str(), text.size());
	string text1 = to_string(w) + "\n";
	string text2 = to_string(h) + "\n";
	string text3 = "255\n";
	fl.write(text1.c_str(), text1.size());
	fl.write(text2.c_str(), text2.size());
	fl.write(text3.c_str(), text3.size());

	for (int i = 0; i < 3 * w * h; i++) {
		int k = data[i] * 255;
		fl.write((const char*)&k, sizeof(char));
	}
	cout << "File written succesfully\n";
	fl.close();
	delete[]data;
	return true;

} // WritePPM

