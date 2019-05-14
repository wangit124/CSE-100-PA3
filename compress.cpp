/* Description: This is a program that uses huffman encoding to
 * encode a file of characters with certain frequencies and write
 * a compressed version of the file.
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
		cout << "Usage: ./compress <infile filename> <outfile filename>."<<endl;
        exit(-1);
    }
	
	// Get input and output files
	char * inputFile = argv[ARG1];
	char * outputFile = argv[ARG2];

	// Create vector to store frequencies
	std::vector<int> freqs (ASCII, 0);

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

	// Read file character by character and calculate frequencies
	char currSymb = in.get();

	// If file is empty, return -1
	if (currSymb == -1) { 
		// Open outstream
		in.close();
		out.close();
		exit(-1);
	}
	
	while (currSymb != -1) {
		// Increment count of ascii position
		int currFreq = freqs[(int)currSymb];
		currFreq++;
		freqs[(int)currSymb] = currFreq;
		
		// Read next character
		currSymb = in.get();
	}
	
	// Create new HCTree and build from array of freqs
	HCTree * myTree = new HCTree();
	myTree->build(freqs);

	// Close input file and read again
	in.close();
    in.open(inputFile, ios::binary);

	// Write header
	for (unsigned int i=0; i<freqs.size(); i++) {
		out << freqs[i] << endl;
	}

	// Read file character by character and encode
	currSymb = in.get();
	while (currSymb != -1) {
		// Encode symbol
		myTree->encode(currSymb, out);

		// Read next character
		currSymb = in.get();
	}
	
	// Close input and output files
	in.close();
	out.close();
	delete myTree;
}
