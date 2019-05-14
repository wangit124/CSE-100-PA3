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

using namespace std;

int main (int argc, char ** argv) {
	HCTree * myTree = new HCTree();
	
	vector <int> myFreqs;
    myFreqs = vector<int>(ASCII, 0);

	myFreqs[65] = 1;
	myFreqs[66] = 1;
	myFreqs[67] = 4;

	myTree->build(myFreqs);

	ofstream out;

	myTree->encode('A', out);
	
	delete myTree;
}
