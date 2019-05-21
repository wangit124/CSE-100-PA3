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
	
	// Check if file exists
	if (!in) {
		cout << "Invalid input file. Please try again." << endl;
		in.close();
		exit(-1);
	}

	// Read file character by character and calculate frequencies
	unsigned char nextChar;
	int currSymb = in.get();
	int currFreq;

	// If file is empty, return -1
	if (currSymb == -1) { 
		// Open outstream
		in.close();
		exit(-1);
	}
	else {
		nextChar = (unsigned char) currSymb;
		currSymb = (int) nextChar;
		
		// Increment frequency 
		currFreq = freqs[currSymb];
		currFreq = currFreq + 1;
		freqs[currSymb] = currFreq;
	}

	// Keep reading while not EOF
	while ((currSymb = in.get()) != EOF) {
		nextChar = (unsigned char) currSymb;
		currSymb = (int) nextChar;
		
		// Increment frequency 
		currFreq = freqs[currSymb];
		currFreq = currFreq + 1;
		freqs[currSymb] = currFreq;// Increment count of ascii position
	}

	// Close input file and read again
	in.close();
    in.open(inputFile, ios::binary);

	// Open outstream
	ofstream out;
	out.open(outputFile, ios::binary);
	
	// Write header
	for (unsigned int i=0; i<freqs.size(); i++) {
		out << freqs[i] << endl;
	}

	// Create new HCTree and build from array of freqs
	HCTree * myTree = new HCTree();
	myTree->build(freqs);

	// Keep reading while not EOF and encode
	while ((currSymb = in.get()) != EOF) {
		// Convert read to byte
		nextChar = (unsigned char) currSymb;

		// encode
		myTree->encode(currSymb, out);
	}
	
	// Close input and output files
	in.close();
	out.close();
	delete myTree;
}
