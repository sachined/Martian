#include "Coordinates.h"

void Coords::set_hex (string degs_hex) { hex_code = degs_hex; }
void Coords::set_ascii(int hex_ascii) { ascii_code = hex_ascii; }
string Coords::get_hex() const { return hex_code; }
int Coords::get_ascii() const { return ascii_code; }

/*
show_letter()
Used to translate the vector of degrees
into a line of text (final_sentence)
To be used in Coord class to translate ASCII into char/computer responses
*/

char Coords::show_letter()
{
	char letter;
	int number;
	number = ascii_code;
	letter = (char)number;
	return letter;
}

/*==========================
string convert_deg_to_hex(string)

Converts degree coordinates into hex code
Example: (123,42) = 51
===========================*/
void Coords::convert_deg_to_hex(string line_token)
{
	char deg_letter(int);

	string number = "";
	string result;
	string ret;
	string final_result;
	stringstream rr;
	double number_mod;
	int cutter;
	char letter_to_be_added;

	for (unsigned int i = 0; i < line_token.size(); i++)
	{
		if (line_token[i] == ',' || i == (line_token.size() - 1))
		{
			if (i == (line_token.size() - 1))
			{
				number += line_token[i];
			}
			result = number;
			number = "";
			stringstream dd(result);
			dd >> number_mod;
			dd.str("");
			result = "";
			number_mod /= 22.5;
			cutter = (int)number_mod;
			if (cutter > 9 && cutter < 16)
			{	
				letter_to_be_added = deg_letter(cutter);
				ret = letter_to_be_added;
			}
			else
			{
				rr << cutter;
				ret = rr.str();
			}
			final_result += ret;
			rr.str("");
		}
		else
			number += line_token[i];
	}
	set_hex(final_result);
}


/*==========================
string convert_hex_to_code(string)

Converts hex code into ASCII code
Example: (123,42) = 51
51 = 81
===========================*/
void Coords::convert_hex_to_code(string hex_code_coords)
{
	int letter_to_number(char);

	string number;
	string result;
	string final_result;
	int number_seen = 0;
	int result_number = 0;
	unsigned int count;
	unsigned int size;

	number = hex_code_coords;

	size = number.size();

	count = size;
	
	for (unsigned int i = 0; i < size; i++, count--)
	{
		if (isalpha(number[i]))
		{
			number_seen = letter_to_number(number[i]);
			if (count == 2)
				result_number = number_seen * 16;
			else if (count == 1)
				result_number += number_seen;
			result = "";
		}
		else
		{
			int num_number = number[i] - '0';
			number_seen += num_number;
			if (count == 2)
				result_number = number_seen * 16;
			if (count == 1)
				result_number += number_seen;
			result = "";
			number_seen = 0;
		}
	}
	set_ascii(result_number);
}

/*
Converts the degree into a letter if value > 9 (a,b,c,d,e,f)
Used in converting from degrees single digit placement
convert_deg_hex()
*/
char deg_letter(int number)
{
	char show_letter;

	switch(number)
	{
	case 10: show_letter = 'A'; break;
	case 11: show_letter = 'B'; break;
	case 12: show_letter = 'C'; break;
	case 13: show_letter = 'D'; break;
	case 14: show_letter = 'E'; break;
	case 15: show_letter = 'F'; break;
	default: cout << "This is beyond the list" << endl; show_letter = '*'; break;
	}
	return show_letter;
}

/*
letter_to_number(char)
This will used when converting hex code into ascii (to deal with A-F)
convert_hex_ascii
*/
int letter_to_number(char letter)
{
	int value;

	switch(letter)
	{
		case 'A': value = 10; break;
		case 'B': value = 11; break;
		case 'C': value = 12; break;
		case 'D': value = 13; break;
		case 'E': value = 14; break;
		case 'F': value = 15; break;
		default: cout << "This is not hex..." << endl;
	}
	return value;
}