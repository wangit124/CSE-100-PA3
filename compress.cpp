#include "HCTree.hpp"

using namespace std;

int main (int argc, char ** argv) {
	HCTree * myTree = new HCTree();
	
	vector <int> myFreqs;
    myFreqs = vector<int>(256, 0);

	myFreqs[65] = 1;
	myFreqs[66] = 1;
	myFreqs[67] = 4;

	myTree->build(myFreqs);

	delete myTree;
}
