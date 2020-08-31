#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include<sstream>

using namespace std;

/*=====================================================
File_text class

Read/Write data from/to text file
Stores line of text as an element of the string vector
=====================================================*/
class File_text
{
	vector<string> line_by_line;

public:
	void read_infile(string filename);	// Good
	vector<string> get_vector() const { return line_by_line; };	// Good
};

/*=============================================================
void read_infile(string)

Read a text file to store each line as a string vector element

vector<string>line_by_line is a private member of File_text

line_by_line[0] = (143,65),(158,85),(123,55),(112,95),...
line_by_line[last] = ...,(134,45),(132,5),(123,25),(112,95),

This vector will be further split into tokens in Coords class
==============================================================*/
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
				line_by_line.push_back(line);
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
	Coords() {}
	Coords(string degrees)
	{
		convert_deg_to_hex(degrees);
		convert_hex_to_code(get_hex());
	}
	void convert_deg_to_hex(string line_token);	// Good
	void convert_hex_to_code(string hex_code_coords); // Good
	void set_hex(string degs_hex)	{ hex_code = degs_hex; }
	void set_ascii(int hex_ascii)	{ ascii_code = hex_ascii; }
	string get_hex() const	{ return hex_code; }
	int get_ascii() const	{ return ascii_code; }

};

/*==========================
void convert_deg_to_hex(string)

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
void convert_hex_to_code(string)

Converts hex code into ASCII code
Example: (123,42) = 51
51 = 81 <--- This process
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
			else if (count == 1)
				result_number += number_seen;
			result = "";
			number_seen = 0;
		}
	}
	set_ascii(result_number);
}

/*==========+++++++++++++++++++++++++++++++++++++++++++++
char deg_letter(int)
Converts the degree into a letter if value > 9 (a,b,c,d,e,f)
Used in converting from degrees single digit placement
 Used in convert_deg_to_hex(string)
+++++++++++++++++++++++++++============================*/
char deg_letter(int number)
{
	char show_letter;

	switch (number)
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

/*============++++++++++++
int letter_to_number(char)
This will used when converting hex code into ascii (to deal with A-F)
Used in convert_hex_to_code(string)
++++++++++++++===========*/
int letter_to_number(char letter)
{
	int value;

	switch (letter)
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

/*++++++++++++++++++++++++++++++++++++++++++++++++++
Operator class

This class will have translator unit (Coords class)
text reader (File_text class) to read the text file
Final text will be stored in a string
Original data will be stored in vector
ASCII map will be stored in another vector
++++++++++++++++++++++++++++++++++++++++++++++++++*/
class Operator
{
private:
	vector<char> ascii_symbols;
	vector<string> degrees;
	vector<string> errors;
	string final_sentence;
	File_text text;
	Coords translator;
public:
	void setup_symbol(); // Good
	void setup_file();	// Good
	void parse_file();	// Good
	void making_sentence(); // Good
	void run(); // Good
	string get_sentence() const { return final_sentence; }
	void print_sentence() {	cout << "\n" << get_sentence() << endl;	}
	int show_errors(); // Good
	void create_story(); // Good
};

/*+++++++++++++++++++++++++++++++++++++++++++
setup_symbol
This function will populate the ascii vector,
which will be used in converting ascii codes
obtained from Coords class
Ex.
ParseString: (123,32),(32,42),(53,78),
Hex: 51,11,23,
ASCII: 81,17,35,
Letter: Q,DC1,#
+++++++++++++++++++++++++++++++++++++++++++*/
void Operator::setup_symbol()
{
	int starter = 0;
	char placer = ' ';

	for (starter; starter < 128; starter++)
	{
		placer = (char)starter;
		ascii_symbols.push_back(placer);
	}
}

/*++++++++++++++++++++++++++++++++++++++++++++++++++++
setup_file
This function uses read_infile fntn of File_text class
to save the lines into a string vector
++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void Operator::setup_file()
{
	string filer;

	cout << "Welcome to the text file reader Matt Damon!" << endl;
	cout << "Give me the file name please: ";
	getline(cin, filer);
	text.read_infile(filer);
}

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
parse_file()
This will break up the lines from File_text vector
into individual degrees, which are then stored in another vector
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void Operator::parse_file()
{
	bool deg_beg = 0, family = 0;
	bool complete = 0;
	int count;
	int size;

	string stemp;
	vector<string> shower = text.get_vector();

	for (auto a : shower)
	{
		string pstring(a);

		count = 0;
		size = 0;
		if (!deg_beg)
			stemp = "";

		for (unsigned int i = 0; i < pstring.size(); i++)
		{
			if (pstring[i] == '(')
				deg_beg = 1;
			else if (pstring[i] == ')')
			{
				deg_beg = 0;
				if (family && !deg_beg)
				{
					errors.push_back(stemp);
					throw stemp;
				}
				else
				{
					degrees.push_back(stemp);
					count++;
				}
				stemp = "";
			}
			else if ((isdigit(pstring[i]) || pstring[i] == ','))
			{
				if (deg_beg)
				{
					stemp += pstring[i];
					if (pstring[i] != ',')
						size++;
					else
						size = 0;
					if (size > 3)
					{
						errors.push_back(stemp);
						throw 40;
					}
				}
				else if (!deg_beg)
				{
					size = 0;
					continue;
				}
			}
			else if (i == pstring.size() - 1 && deg_beg)
				continue;
			else
			{
				if (deg_beg)
				{ 
					stemp += pstring[i];
					family = 1;
				}
				else
					continue;
			}		
		}
		family = 0;
	}
}

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
making_sentence()
Retrieve from degrees vector then translated through translator
Finally added to a string variable
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void Operator::making_sentence()
{
	char letter;

	for (auto d : degrees)
	{
		translator = Coords(d);
		if (translator.get_ascii() >= 0 && translator.get_ascii() < 128)
			letter = ascii_symbols.at(translator.get_ascii());
		else
			cout << "This is not cool..." << endl;
		final_sentence += letter;
	}
}

/*+++++++++++++++++++++++++++++++
int show_errors()
If there is an error, it will be shown
If no error, this will allow the story
to be printed in the create_story()
+++++++++++++++++++++++++++++++*/
int Operator::show_errors()
{
	int count = 0;

	if (errors.empty())
	{
		cout << "\nThere were no errors to be reported!" << endl;
	}
	else
	{
		for (auto e : errors)
		{
			cout << "Error: "<< e << endl;
			count = 1;
		}
	}
	return count;
}

/*+++++++++++++++++++++++++++++++
void create_story()
final_sentence (string) will be 
added into a text file for easy reading
+++++++++++++++++++++++++++++++*/
void Operator::create_story()
{
	string filename = "Matt_Damon_is_dead.txt";

	cout << "\nSaving this story into a text file called " << filename << " now...\n" << endl;
	
	ofstream file_written("Matt_Damon_is_dead.txt");

	file_written << final_sentence << endl;

	cout << "\tDONE!\n";
}

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ 
run()
Reads from a text file, then fills the degrees vector,
and fills the string which will be printed out at the end
Also creates a text file with translated log entry
To be used in main program
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void Operator::run()
{
	int error = 0;

	this->setup_symbol();
	this->setup_file();
	try {
		this->parse_file();
	}
	catch (string) { cerr << "This is not added\n";  }
	catch (...) { cerr << "This is weird...\n"; }
	this->making_sentence();
	this->print_sentence();
	error = this->show_errors();
	if (!error)
		this->create_story();
	else
		cout << "\nNo story for you..." << endl;
}

/*$$$$$$$$$$$$$$
Main program!!

$$$$$$$$$$$$$$*/
int main()
{
	Operator martian;

	martian.run();

	return 0;
}

/*
Exception Handling:
Case 1 (when degrees are nonsensical, like (103,6&8)

Welcome to the text file reader Matt Damon!
Give me the file name please: test.txt
Reading file now...
This is not added

M The
Error: 50,1@1

No story for you...

---------------------
Case 2 (when there are run-on digits ...,(123,15666666

Welcome to the text file reader Matt Damon!
Give me the file name please: test_run_on.txt
Reading file now...
This is weird...

MThe M
Error: 149,3777

No story for you...

---------------------
Wrong filename or non-existent in same directory

Welcome to the text file reader Matt Damon!
Give me the file name please: test.text
Unable to open file:  test.text
Press any key to continue . . .

---------------------
Text file is not corrupted/missing, so success!!
Log entry is also saved in a text file for easy reading format

Welcome to the text file reader Matt Damon!
Give me the file name please: AsciiDegrees.csv
Reading file now...

The Martian Chapter 1LOG ENTRY: SOL 6I'm pretty much f--ked.That's my considered opinion.F--ked.Six days into what should be the greatest two months of my life, and it's turned into a nightmare.I don't even know who'll read this. I guess someone will find it eventually. Maybe a hundred years from now.For the record ... I didn't die on Sol 6. Certainly the rest of the crew thought I did, and I can't blame them. Maybe there'll be a day of national mourning for me, and my Wikipedia page will say, "Mark Watney is the only human being to have died on Mars."And it'll be right, probably. 'Cause I'll surely die here. Just not on Sol 6 when everyone thinks I did.Let's see ... where do I begin?The Ares Program. Mankind reaching out to Mars to send people to another planet for the very first time and expand the horizons of humanity blah, blah, blah. The Ares 1 crew did their thing and came back heroes. They got the parades and fame and love of the world.Ares 2 did the same thing, in a different location on Mars. They got a firm handshake and a hot cup of coffee when they got home.Ares 3. Well, that was my mission. Okay, not mine per se. Commander Lewis was in charge. I was just one of her crew. Actually, I was the very lowest ranked member of the crew. I would only be "in command" of the mission if I were the only remaining person.What do you know? I'm in command.I wonder if this log will be recovered before the rest of the crew die of old age. I presume they got back to Earth all right. Guys, if you're reading this: It wasn't your fault. You did what you had to do. In your position I would have done the same thing. I don't blame you, and I'm glad you survived.I guess I should explain how Mars missions work, for any layman who may be reading this. We got to Earth orbit the normal way, through an ordinary ship to Hermes. All the Ares missions use Hermes to get to and from Mars. It's really big and cost a lot so NASA built only one.Once we got to Hermes, four additional unmanned missions brought us fuel and supplies while we prepared for our trip. Once everything was a go, we set out for Mars. But not very fast. Gone are the days of heavy chemical fuel burns and trans-Mars injection orbits.Hermes is powered by ion engines. They throw argon out the back of the ship really fast to get a tiny amount of acceleration. The thing is, it doesn't take much reactant mass, so a little argon (and a nuclear reactor to power things) let us accelerate constantly the whole way there. You'd be amazed at how fast you can get going with a tiny acceleration over a long time.I could regale you with tales of how we had great fun on the trip, but I won't. I don't feel like reliving it right now. Suffice it to say we got to Mars 124 days later without strangling each other.From there, we took the MDV (Mars descent vehicle) to the surface. The MDV is basically a big can with some light thrusters and parachutes attached. Its sole purpose is to get six humans from Mars orbit to the surface without killing any of them.And now we come to the real trick of Mars exploration: having all of our shit there in advance.A total of fourteen unmanned missions deposited everything we would need for surface operations. They tried their best to land all the supply vessels in the same general area, and did a reasonably good job. Supplies aren't nearly so fragile as humans and can hit the ground really hard. But they tend to bounce around a lot.Naturally, they didn't send us to Mars until they'd confirmed that all the supplies had made it to the surface and their containers weren't breached. Start to finish, including supply missions, a Mars mission takes about three years. In fact, there were Ares 3 supplies en route to Mars while the Ares 2 crew were on their way home.The most important piece of the advance supplies, of course, was the MAV. The Mars ascent vehicle. That was how we would get back to Hermes after surface operations were complete. The MAV was soft-landed (as opposed to the balloon bounce-fest the other supplies had). Of course, it was in constant communication with Houston, and if there had been any problems with it, we would have passed by Mars and gone home without ever landing.The MAV is pretty cool. Turns out, through a neat set of chemical reactions with the Martian atmosphere, for every kilogram of hydrogen you bring to Mars, you can make thirteen kilograms of fuel. It's a slow process, though. It takes twenty-four months to fill the tank. That's why they sent it long before we got here.You can imagine how disappointed I was when I discovered the MAV was gone.It was a ridiculous sequence of events that led to me almost dying, and an even more ridiculous sequence that led to me surviving.The mission is designed to handle sandstorm gusts up to 150 kph. So Houston got understandably nervous when we got whacked with 175 kph winds. We all got in our flight space suits and huddled in the middle of the Hab, just in case it lost pressure. But the Hab wasn't the problem.The MAV is a spaceship. It has a lot of delicate parts. It can put up with storms to a certain extent, but it can't just get sandblasted forever. After an hour and a half of sustained wind, NASA gave the order to abort. Nobody wanted to stop a monthlong mission after only six days, but if the MAV took any more punishment, we'd all have gotten stranded down there.We had to go out in the storm to get from the Hab to the MAV. That was going to be risky, but what choice did we have?Everyone made it but me.Our main communications dish, which relayed signals from the Hab to Hermes, acted like a parachute, getting torn from its foundation and carried with the torrent. Along the way, it crashed through the reception antenna array. Then one of those long thin antennae slammed into me end-first. It tore through my suit like a bullet through butter, and I felt the worst pain of my life as it ripped open my side. I vaguely remember having the wind knocked out of me (pulled out of me, really) and my ears popping painfully as the pressure of my suit escaped.The last thing I remember was seeing Johanssen hopelessly reaching out toward me.I awoke to the oxygen alarm in my suit. A steady, obnoxious beeping that eventually roused me from a deep and profound desire to just fucking die.The storm had abated; I was facedown, almost totally buried in sand. As I groggily came to, I wondered why I wasn't more dead.The antenna had enough force to punch through the suit and my side, but it had been stopped by my pelvis. So there was only one hole in the suit (and a hole in me, of course).I had been knocked back quite a ways and rolled down a steep hill. Somehow I landed facedown, which forced the antenna to a strongly oblique angle that put a lot of torque on the hole in the suit. It made a weak seal.Then, the copious blood from my wound trickled down toward the hole. As the blood reached the site of the breach, the water in it quickly evaporated from the airflow and low pressure, leaving a gunky residue behind. More blood came in behind it and was also reduced to gunk. Eventually, it sealed the gaps around the hole and reduced the leak to something the suit could counteract.The suit did its job admirably. Sensing the drop in pressure, it constantly flooded itself with air from my nitrogen tank to equalize. Once the leak became manageable, it only had to trickle new air in slowly to relieve the air lost.After a while, the CO2 (carbon dioxide) absorbers in the suit were expended. That's really the limiting factor to life support. Not the amount of oxygen you bring with you, but the amount of CO2 you can remove. In the Hab, I have the oxygenator, a large piece of equipment that breaks apart CO2 to give the oxygen back. But the space suits have to be portable, so they use a simple chemical absorption process with expendable filters. I'd been asleep long enough that my filters were useless.The suit saw this problem and moved into an emergency mode the engineers call "bloodletting." Having no way to separate out the CO2, the suit deliberately vented air to the Martian atmosphere, then backfilled with nitrogen. Between the breach and the bloodletting, it quickly ran out of nitrogen. All it had left was my oxygen tank.So it did the only thing it could to keep me alive. It started backfilling with pure oxygen. I now risked dying from oxygen toxicity, as the excessively high amount of oxygen threatened to burn up my nervous system, lungs, and eyes. An ironic death for someone with a leaky space suit: too much oxygen.Every step of the way would have had beeping alarms, alerts, and warnings. But it was the high-oxygen warning that woke me.The sheer volume of training for a space mission is astounding. I'd spent a week back on Earth practicing emergency space suit drills. I knew what to do.Carefully reaching to the side of my helmet, I got the breach kit. It's nothing more than a funnel with a valve at the small end and an unbelievably sticky resin on the wide end. The idea is you have the valve open and stick the wide end over a hole. The air can escape through the valve, so it doesn't interfere with the resin making a good seal. Then you close the valve, and you've sealed the breach.The tricky part was getting the antenna out of the way. I pulled it out as fast as I could, wincing as the sudden pressure drop dizzied me and made the wound in my side scream in agony.I got the breach kit over the hole and sealed it. It held. The suit backfilled the missing air with yet more oxygen. Checking my arm readouts, I saw the suit was now at 85 percent oxygen. For reference, Earth's atmosphere is about 21 percent. I'd be okay, so long as I didn't spend too much time like that.I stumbled up the hill back toward the Hab. As I crested the rise, I saw something that made me very happy and something that made me very sad: The Hab was intact (yay!) and the MAV was gone (boo!).Right that moment I knew I was screwed. But I didn't want to just die out on the surface. I limped back to the Hab and fumbled my way into an airlock. As soon as it equalized, I threw off my helmet.Once inside the Hab, I doffed the suit and got my first good look at the injury. It would need stitches. Fortunately, all of us had been trained in basic medical procedures, and the Hab had excellent medical supplies. A quick shot of local anesthetic, irrigate the wound, nine stitches, and I was done. I'd be taking antibiotics for a couple of weeks, but other than that I'd be fine.I knew it was hopeless, but I tried firing up the communications array. No signal, of course. The primary satellite dish had broken off, remember? And it took the reception antennae with it. The Hab had secondary and tertiary communications systems, but they were both just for talking to the MAV, which would use its much more powerful systems to relay to Hermes. Thing is, that only works if the MAV is still around.I had no way to talk to Hermes. In time, I could locate the dish out on the surface, but it would take weeks for me to rig up any repairs, and that would be too late. In an abort, Hermes would leave orbit within twenty-four hours. The orbital dynamics made the trip safer and shorter the earlier you left, so why wait?Checking out my suit, I saw the antenna had plowed through my bio-monitor computer. When on an EVA, all the crew's suits are networked so we can see each other's status. The rest of the crew would have seen the pressure in my suit drop to nearly zero, followed immediately by my bio-signs going flat. Add to that watching me tumble down a hill with a spear through me in the middle of a sandstorm .?.?. yeah. They thought I was dead. How could they not?They may have even had a brief discussion about recovering my body, but regulations are clear. In the event a crewman dies on Mars, he stays on Mars. Leaving his body behind reduces weight for the MAV on the trip back. That means more disposable fuel and a larger margin of error for the return thrust. No point in giving that up for sentimentality.So that's the situation. I'm stranded on Mars. I have no way to communicate with Hermes or Earth. Everyone thinks I'm dead. I'm in a Hab designed to last thirty-one days.If the oxygenator breaks down, I'll suffocate. If the water reclaimer breaks down, I'll die of thirst. If the Hab breaches, I'll just kind of explode. If none of those things happen, I'll eventually run out of food and starve to death.So yeah. I'm f--ked.

There were no errors to be reported!

Saving this story into a text file called Matt_Damon_is_dead.txt now...

DONE!

*/
