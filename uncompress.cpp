/* Description: This is a program that reads in an encoded file,
 * and returns the original message containing ascii characters.
 *
 * Name: Luhao Wang
 * Email: luw055@ucsd.edu
 * Date: May 12, 2019
 * Sources: Piazza
 */

#include "HCTree.hpp"
#include <fstream>

#define ASCII 256
#define ARG1 1
#define ARG2 2

using namespace std;

int main (int argc, char ** argv) {
	// Check valid arguments
	if(argc < 3){
		cout << "Invalid number of arguments." << endl;
		cout << "Usage: ./uncompress <infile filename> <outfile filename>."
			 << endl;
        exit(-1);
    }
	
	// Get input and output files
	char * inputFile = argv[ARG1];
	char * outputFile = argv[ARG2];

	// Create input stream to read from input file
	ifstream in;
    in.open(inputFile, ios::binary);
	
	// Open outstream
	ofstream out;
	out.open(outputFile, ios::binary);
		
	// Check if file exists
	if (!in) {
		cout << "Invalid input file. Please try again." << endl;
		exit(-1);
	}

	// Check if file is empty
	char currSymb = in.get();

	// Create new HCTree and build from array of freqs
	HCTree * myTree = new HCTree();

	// If file is empty, return -1
	if (currSymb == -1) { 
		out.close();
		exit(-1);
	}

	// reopen file
	in.close();
    in.open(inputFile, ios::binary);
	std::string temp ="";

	// Skip to last line
	for (int i=0; i<ASCII; i++) {
		getline(in, temp);
		cout << temp << endl;
	}

	// Decode the input file and write each character to output
	currSymb = in.get();
	while (currSymb != -1) {
		int currChar = myTree->decode(in);
		
		// write to output
		out << currChar;
	}

	// Close input and output
	in.close();
	out.close();

	delete myTree;
}
