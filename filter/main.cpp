#include <iostream>
#include <vector>
#include <string>
#include "ppm.h"
#include "vec3.h"
#include "image.h"
#include "array2d.h"
#include "imageio.h"
#include <fstream>
#include "filter.h"
#include "framework.h"
#include <string>
#include <stdlib.h>

using namespace std;

int main(int argc, char* argv[]) {
	cout << "                                                                           CURRENT DATE: " << __DATE__ << endl;
	cout << "                                                                           CURRENT TIME: " << __TIME__ << endl;
	cout << "--------------------------------------------------------------------------" << endl;
	cout << "--------------------------------------------------------------------------" << endl;
	cout << "------------- C++ course 2019-20, Winter Semmester------------------------" << endl;
	cout << "--------------created by: Dimitrios Mamakas (3180102)---------------------" << endl;
	cout << "--------------------------Anastasios Mitsios (3180109)--------------------" << endl;
	cout << "--------------------------------------------------------------------------" << endl;
	cout << "Please give, filters followed by the proper parameters and image name.    " << endl;
	cout << "\n";
	cout << "________________________________________________" << endl;
	cout << "|Filter Name  |  Type  |       Parameters      |" << endl;
	cout << "|FilterLinear |linear  |aR aG aB cR cG cB      |" << endl;
	cout << "|FilterGamma  |gamma   |ã                      |" << endl;
	char buf[256];
	cin.ignore();	// Used to skip the \n (Enter) pressed by the user in the previous input
	cin.getline(buf, 256);
	
	// printing part of code
	vector<string> words;
	int counter = 1;

	while (buf[counter] != *"\0") {
		string s = "";
		int k = counter;
		while (buf[k] != *" " && buf[k] != *"\0") {
			s += buf[k];
			k++;
		} // while 

		words.push_back(s);
		counter = k;
		if (buf[counter] == *" ")
			counter++;

	} // while 
	
	string filename = words[words.size() - 1];

	if (filename[filename.size() - 1] == *"m" && filename[filename.size() - 2] == *"p" && filename[filename.size() - 3] == *"p" && words[0] == "filter") {

		cout << "filename is: " << filename << endl;

		string file = "";
		for (int i = 0; i < filename.size() - 4; i++) {
			file += filename[i];
		}



		fstream file1(filename, ios::in || ios::binary);
		char* buffer = new char[25];
		file1.read((char*)buffer, 25);
		if (!file1) {
			cerr << "Could not load fle, please try again using a valid filename" << endl;
			exit(0);
		}

		int width; int height;
		int counter = 3;
		int spaces = 0;
		string dddd = "";
		vector<string> nums;
		while (spaces < 2) {
			if (buffer[counter] != *" " && buffer[counter] != *"\n") {
				dddd += buffer[counter];
				counter++;
			}
			else {
				spaces++;
				nums.push_back(dddd);
				dddd = "";
				counter++;
			}

		} // while 

		width = stoi(nums[0]);
		height = stoi(nums[1]);
		file1.close();
		delete[] buffer;

		Image m(width, height, NULL);
		m.load(file, "ppm");
		bool ss = false;
		int now = 1;
		while (now < words.size() - 1) {
			if (words[now] == "-f") {
				
				now++;

				if (words[now] == "linear") {
					// expecting to have 6 parameters
					ss = true;
					float a1 = stof(words[now + 1]); // 1st
					float a2 = stof(words[now + 2]); // 2nd
					float a3 = stof(words[now + 3]); // 3d
					float s1 = stof(words[now + 4]); // 4th
					float s2 = stof(words[now + 5]); // 5th
					float s3 = stof(words[now + 6]); // 6th
					
					math::Vec3<float> A(a1, a2, a3);
					math::Vec3<float> B(s1, s2, s3);
					FilterLinear f(A, B);
					Image n = m;
					n = f.operator<<(m);
					m = n;
					now = now + 7;
					
				} // linear filter 
				else if (words[now] == "gamma") {
					// expecting to have just 1 parameter 
					ss = true;
					float y = stof(words[now + 1]); // representing the exponent 
					
					FilterGamma f(y);
					Image n = m;
					n = f.operator<<(m);
					m = n;
					now++;
					now++;
					
				} // gamma filter 
			} // if - if a filter exists
			else {
				cout << "No proper filter name given. Please, retry." << endl;
				break;
				ss = false;
			}
		} // while - here we are going to apply the filters 
		if (ss == true) {
			cout << "Saving.." << endl;
			m.save(file, "ppm");
		}

	} // if 

	else
		cout << "No filename or filter found. Please check again the given format and retry." << endl;


} // main method