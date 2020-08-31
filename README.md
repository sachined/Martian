# Martian
This will read a series of coordinates that will turn into a post (Binary to String) through number of classes that each serve a unique function
<hr>
Classes
File_text: Reads a binary file, which are then broken into lines, which are then stored in a vector.

Coords: Breaks down the lines into tokens of coordinates, which are then converted into hex code and then into ASCII code.

Operator: This will work in conjuction with Coords class to store vectors of degrees and errors, and ultimately creates a string. This string will be saved into a text file. 
<hr>
Source.cpp has all code along with comments and testing process

The lone text file is the result of succesful binary conversion to string
