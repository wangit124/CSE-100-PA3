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
#include <sstream>

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
		in.close();
		out.close();
		exit(-1);
	}

	// Check if file is empty
	unsigned char nextChar;
	int currSymb = in.get();
	
	// If file is empty, return -1
	if (currSymb == -1) { 
		in.close();
		out.close();
		exit(-1);
	}

	// Create new HCTree and build from array of freqs
	HCTree * myTree = new HCTree();

	// reopen file
	in.close();
    in.open(inputFile, ios::binary);
	
	// Create vector to store frequencies
	vector <int> freqs (ASCII, 0);

	// Build tree from frequencies
	std::string temp = "";
	int tempInt = 0;

	for (int i=0; i<ASCII; i++) {
		// Read line and convert to int
		getline(in, temp);
		stringstream convert(temp);
		convert >> tempInt;

		// Set frequency
		freqs[i] = tempInt;
	}
	
	// Build tree
	myTree->build(freqs);
	
	// Temp variable to store return value
	int currChar;

	// Decode the input file and write each character to output
	while (1) {
		currChar = myTree->decode(in);
		
		// If currChar is EOF, break
		if (currChar == EOF) {
			break;
		}

		// write to output
		out << to_string(currChar);
	}

	// Close input and output
	in.close();
	out.close();

	delete myTree;
}
