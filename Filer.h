#ifndef FILE_H_
#define FILE_H_

#include <fstream>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

/*==========================
File_text class

Read/Write data from/to text file
Stores line of text as an element of the string vector
===========================*/
class File_text
{
	vector<string> line_by_line;

public:
	void read_infile(string filename);	// Good
	void print_outfile(string print_file);	// Good
	vector<string> get_vector() const { return line_by_line; };	// Good
};

#endif	//FILE_H_