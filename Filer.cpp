#include "Filer.h"

/*==========================
void read_infile(string)

Read a text file to store each line as a element of a string vector
vector<string>line_by_line is a private member of File_text

line_by_line[0] = (143,65),(158,85),(123,55),(112,95),...
line_by_line[last] = ...,(134,45),(132,5),(123,25),(112,95),

This vector will be further split into tokens in Coords class
===========================*/
void File_text::read_infile(string filename)
{
	string line = "";
	ifstream file_read(filename);

	if (file_read.is_open())
	{
		cout << "Reading file now...\n";

		while (!file_read.eof())
		{
			getline(file_read, line);

			if (line.length() > 0)
			{
				line_by_line.push_back(line);  // array notation
				line = "";
			}
		}
	}
	else
	{
		cerr << "Unable to open file:  " << filename << endl;
		system("pause");
		exit(1);
	}
	file_read.close();
}

/*==========================
void print_outfile(string)

Print a text file from a string vector
vector<string>line_by_line is a private member of File_text
===========================*/
void File_text::print_outfile(string print_file)
{
	cout << "Reading out this file now..." << endl;
	int count = 1;

	ofstream file_written(print_file);

	for (auto d : line_by_line)
	{
		file_written << d << endl;
		cout << "Line # " << count << " is as following...\t" << d << endl;
		count++;
	}
}
