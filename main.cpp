#include <iostream>
#include <fstream>
#include <string>
#include <typeinfo>
#include <sstream>



#define SYMBOLS 20

#include "tools.hpp"



void huffman (Dictionary dict){
	Tree MyTree;
	for (int i = 0; i < dict.getSymbolLen(); ++i){
		MyTree.insertNode(dict.getFreq(i) , dict.getSymbol(i));
	}

	cout << dict.getSymbolLen() << endl;

	MyTree.makeMe();

	for (int i = 0; i < dict.getSymbolLen(); ++i)
	{
		MyTree.showme(dict.getSymbol(i));		
	}
}

int main(int argc, char const *argv[])
{

	Dictionary dict;

	// ReadData my_file("files/image.jpg");
	ReadData my_file("files/test.txt");


	string hex_char = my_file.getHexChar();

	cout << "Reading file content...\n";
	
	while (hex_char.length() != 0) {

		for (int i = 0; i < hex_char.length(); ++i){
			dict.insert(hex_char[i]);
		}

		hex_char = my_file.getHexChar();

	}
	
	my_file.closeFile();


	// dict.printme();

	huffman(dict);


	return 0;
}