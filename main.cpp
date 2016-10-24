#include <iostream>
#include <fstream>
#include <string>
#include <typeinfo>


#define SYMBOLS 260

#include "tools.hpp"



void huffman (Dictionary dict){
	
}

int main(int argc, char const *argv[])
{

	Dictionary dict;

	// ReadData my_file("files/image.jpg");
	ReadData my_file("files/test.txt");

	string line = my_file.readLine();

	while (line.length() != 0) {

		for (int i = 0; i < line.length(); ++i){
			dict.insert(line[i]);
		}

		line = my_file.readLine();

	}
	
	my_file.closeFile();

	// dict.printme();

	huffman(dict);


	return 0;
}