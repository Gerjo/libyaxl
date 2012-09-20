/*
 * File:   main.cpp
 * Author: gerjo
 *
 * Created on September 19, 2012, 7:35 PM
 */

#include <cstdlib>
#include "File.h"
#include <iostream>

using namespace std;


int main(int argc, char** argv) {
    File file("test_file.txt");

	cout << "name? " << file.getName() << endl;
    cout << "isDir? " << file.isDirectory() << endl;
	cout << "isDir? " << file.isFile() << endl;
    cout << "exists? " << file.exists() << endl;

	cout << endl << endl;

	File file2("test_folder");

	cout << "name? " << file2.getName() << endl;
    cout << "isDir? " << file2.isDirectory() << endl;
	cout << "isFile? " << file2.isFile() << endl;
    cout << "exists? " << file2.exists() << endl;

	cout << endl << endl;

	File file3("invalid_file");

	cout << "name? " << file3.getName() << endl;
    cout << "isDir? " << file3.isDirectory() << endl;
	cout << "isDir? " << file3.isFile() << endl;
    cout << "exists? " << file3.exists() << endl;

	cout << endl << endl;
	File file4("fulldir");
	cout << " Scanning /" << file4.getName() << "/ for files... " << endl;
	vector<string> files = file4.list();

	for(vector<string>::iterator it = files.begin(); it != files.end(); ++it) {
		cout << (*it) << endl;
	}

    cout << endl << "All done." << endl;


	#ifdef WIN32
		return cin.get();
	#else
		return 0;
	#endif
}

