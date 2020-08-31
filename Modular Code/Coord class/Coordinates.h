#ifndef COORD_H_
#define COORD_H_

#include <iostream>
#include <vector>
#include <iomanip>
#include<sstream>

using namespace std;

/*==========================
Coords class

Convert degrees into hex code
Then converts into ASCII code
Also handles 
===========================*/

class Coords
{
private:
	int ascii_code;
	string hex_code;
public:
	Coords() 
	{ 
	}
	Coords(string degrees)
	{
		convert_deg_to_hex(degrees); 
		convert_hex_to_code(get_hex());
	}

	void convert_deg_to_hex(string line_token);	// Good
	void convert_hex_to_code(string hex_code_coords);
	void set_hex(string degs_hex); 
	void set_ascii(int hex_ascii);
	string get_hex() const;
	int get_ascii() const;
	char show_letter();

};

#endif // COORD_H