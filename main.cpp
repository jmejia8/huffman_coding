#include <iostream>
#include <fstream>
#include <string>
#include <typeinfo>
#include <sstream>
#include <stdlib.h>



#define SYMBOLS 300

#include "tools.hpp"

const string KEY_DECODE = "228181";

void huffman_encode (Dictionary dict, string file_name){

	Tree MyTree;

	for (int i = 0; i < dict.getSymbolLen(); ++i){
		MyTree.insertNode(dict.getFreq(i) , dict.getSymbol(i));
	}

	// Create Huffman tree
	MyTree.makeMe();

	// Save codes into dict
	MyTree.saveCodes(&dict);

	// print table of chars, freq and Huffman codes
	dict.printme();

	cout << "\nCompressing..." << endl;

	ReadData input(file_name);
	ofstream output(file_name + ".compressed", ios::binary);

	output << noskipws;

	// header 

	// save the huffman code
	output << KEY_DECODE << endl;

	// decoded file
	output << file_name << endl;


	for (int i = 0; i < dict.getSymbolLen(); ++i)
		output << (int) dict.getSymbol(i) << endl
			   << dict.getCodeIndex(i)    << endl;


	output << endl << "#"  << endl;

	// Read lines of intput file
	string hex_char = input.readLine();
	string code;

	///////////////////////
	///////////////////////
	// char aux for bit saving
	unsigned char* c = (unsigned char*)calloc(1, sizeof(char));
	int shift_count = 0;
	int total = 0;
	///////////////////////
	///////////////////////
	///////////////////////

	while (hex_char.length() != 0) {

		for (int i = 0; i < hex_char.length(); ++i){

			code = dict.getCode(hex_char[i]);

			for (int j = 0; j < code.length(); ++j) {

				if (code[j] == '1'){
					*c |= 1;
				}
				
				*c <<= 1;


				shift_count++;
				total++;

				if (shift_count == 7) {
					output << *c;
					shift_count = 0;
					free(c);
					c = (unsigned char*) calloc(1, sizeof(char));
				}


			}

		}



		hex_char = input.readLine();

	}

	if(shift_count > 0) {
		*c <<= (8 - shift_count);
		output << *c;
		free(c);
		c = (unsigned char*)calloc(1, sizeof(char));
	}


	cout <<  "\nListo " << endl;
	cout << "\nPorcentaje de compresión: " << (float) total / ((float) dict.size() * 8.0)  * 100.0  << "%" << endl;
	cout << "Tamaño de archivo de salida: " << (total/8.0) << "bytes"<< endl;

	input.closeFile();
	output.close();


}


void huffman_decode(string input_name){
	ReadData input(input_name);

	string line = input.readLine();

	if (line != KEY_DECODE) {
		cout << "Error: Formato incorrecto." << endl;
		exit(0);
	}

	cout << "\nDescomprimiendo";

	// file name decoded
	string output_name = input.readLine();

	Dictionary dict;


	// huffman coding
	char symbol;
	do {

		// read char ascii code
		line = input.readLine();

		symbol = (char) atoi(line.c_str());

		if (line == "#")
			break;

		// read huffman coding
		line = input.readLine();

		if (line == "#")
			break;

		dict.insert(symbol);
		dict.setCode(symbol, line);

	} while(1);

	cout << ".";
	line = input.getBinString();
	cout << ".";
	input.closeFile();

	string code;


	ofstream output(output_name);


	string aux;

	for (int i = 0; i < line.length(); ++i) {
		for (int j = 0; j < dict.getSymbolLen(); ++j) {
				
			code = dict.getCodeIndex(j);
			aux = line.substr(0, code.length());

			if (code == aux) {
				output << dict.getSymbolByCode(code);
				line.erase(0, code.length());
				i = 0;

				break;
			}
		}


	}

	cout << ".\n\n";

	output.close();

	cout << "Descompresión exitosa." << endl;

	return;
}


void menu(){
	cout << "=================================" << endl;
	cout << "|\t¿Qué desea hacer?" << endl
		 << "|\t 1. Comprimir." << endl
		 << "|\t 2. descomprimir." << endl
		 << "=================================" << endl
		 << "\nElige: ";
}

int main(int argc, char const *argv[])
{

	menu();

	int option;
	string file_name;
	
	cin >> option;
	
	Dictionary dict;


	if (option == 1){
			cout << "Nombre del archivo: ";
			cin >> file_name;
			ReadData my_file(file_name);

			char letter = my_file.getChar();

			// cout << "Reading file content...\n";

			while (letter != '\0') {

				dict.insert(letter);

				letter = my_file.getChar();

			}
			
			my_file.closeFile();


			huffman_encode(dict, file_name);
			return 0;
	}

	if( option ==  2){

			cout << "Nombre del archivo: ";
			cin >> file_name;
			huffman_decode(file_name);

			return 0;

	}

	cout << "Opción no valída, diculpe." << endl;





	return 0;
}