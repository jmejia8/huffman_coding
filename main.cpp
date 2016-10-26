#include <iostream>
#include <fstream>
#include <string>
#include <typeinfo>
#include <sstream>
#include <stdlib.h>



#define SYMBOLS 300

#include "tools.hpp"


void huffman_encode (Dictionary dict, string file_name){

	Tree MyTree;

	for (int i = 0; i < dict.getSymbolLen(); ++i){
		MyTree.insertNode(dict.getFreq(i) , dict.getSymbol(i));
	}

	MyTree.makeMe();


	MyTree.saveCodes(&dict);

	dict.printme();

	cout << "\nCompressing..." << endl;

	ReadData input(file_name);
	ofstream output(file_name + ".compressed.bin", ios::binary);

	output << noskipws;


	string hex_char = input.readLine();
	int bitt;
	string code;

	///////////////////////
	///////////////////////
	unsigned char* c = (unsigned char*)calloc(1, sizeof(char));
	int shift_count = 0;
	///////////////////////
	///////////////////////
	///////////////////////

	while (hex_char.length() != 0) {

		for (int i = 0; i < hex_char.length(); ++i){

			code = dict.getCode(hex_char[i]);

			for (int j = 0; j < code.length(); ++j) {
				cout << code[j];
				if (code[j] == '1'){
					*c |= 1;
				}

				*c <<= 1;

				shift_count++;

				if (shift_count == 7) {
					output << *c;
					shift_count = 0;
					free(c);
					c = (unsigned char*)calloc(1, sizeof(char));
				}


			}

		}

		if(shift_count > 0) {
			*c <<= (8 - shift_count);
			output << *c;
			free(c);
			c = (unsigned char*)calloc(1, sizeof(char));
		}


		hex_char = input.readLine();

	}

	output << 3;

	input.closeFile();
	output.close();


	cout <<  "Done" << endl;

}

int main(int argc, char const *argv[])
{

	Dictionary dict;
	string file_name = "files/test2.txt";
	// string file_name = "files/image.jpg";

	ReadData my_file(file_name);


	string hex_char = my_file.readLine();

	cout << "Reading file content...\n";

	while (hex_char.length() != 0) {

		for (int i = 0; i < hex_char.length(); ++i){
			dict.insert(hex_char[i]);
		}

		hex_char = my_file.readLine();

	}
	
	my_file.closeFile();


	huffman_encode(dict, file_name);


	return 0;
}