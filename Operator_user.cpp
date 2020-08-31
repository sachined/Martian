#include "Operator_user.h"


/*
setup_symbol
This function will populate the ascii vector,
which will be used in converting ascii codes
obtained from Coords class
Ex.
ParseString: (123,32),(32,42),(53,78),
 Hex: 51,11,23,
 ASCII: 81,17,35,
 Letter: Q,DC1,# 
*/
void Operator::setup_symbol()
{
	int starter = 0;
	char placer = ' ';
		
	for (starter; starter < 128;starter++) 
	{
		placer = (char)starter;
		ascii_symbols.push_back(placer);
	}
}

/*=========================
setup_file
This function uses read_infile fntn of File_text class
to save the lines into a string vector
*/
void Operator::setup_file()
{
	string filer;

	cout << "Welcome to the text file reader Matt Damon!" << endl;
	cout << "Give me the file name please: ";
	getline(cin, filer);
	text.read_infile(filer);
}


void Operator::parse_file()
{
	bool deg_beg = 0;
	bool complete = 0;
	int count;
	
	string stemp;
	vector<string> shower = text.get_vector();
	
	for (auto a : shower)
	{
		string pstring(a);
		
		count = 0;
		
		if (!deg_beg)
			stemp = "";

		for (unsigned int i = 0; i < pstring.size(); i++)
		{
			if (pstring[i] == '(')
				deg_beg = 1;
			else if (pstring[i] == ')')
			{
				deg_beg = 0;
				degrees.push_back(stemp);
				count++;
				stemp = "";
			}
			else if ((isdigit(pstring[i]) || pstring[i] == ','))
			{
				if (deg_beg)
					stemp += pstring[i];
				else if (!deg_beg)
					continue;
			}
			else if (i == pstring.size() - 1 && deg_beg)
				continue;
			else
			{
				if (deg_beg)
					cout << "This is bad input!" << endl;
				else
					continue;
			}
		}
	}
}

void Operator::making_sentence() 
{
	char letter;

	for (auto d : degrees)
	{
		translator.convert_deg_to_hex(d);
		translator.convert_hex_to_code(translator.get_hex());
		if (translator.get_ascii() >= 0 && translator.get_ascii() < 128)
			letter = ascii_symbols.at(translator.get_ascii());
		else
			cout << "This is not cool..." << endl;
		final_sentence += letter;
	}
}


void Operator::run() 
{
	this->setup_file();
	this->parse_file();
	this->making_sentence();
}