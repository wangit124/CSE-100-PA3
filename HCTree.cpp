/* Description: This is a program that allows one to store
 * characters and their frequencies in a tree structure so 
 * as to make their encoding more efficient later on. This
 * is called a Huffman tree. 
 *
 * Name: Luhao Wang
 * Email: luw055@ucsd.edu
 * Date: May 12, 2019
 * Sources: Piazza
 */

#include "HCTree.hpp"
#include <string>

#define LEFT '0'
#define RIGHT '1'

using namespace std;

/** Use the Huffman algorithm to build a Huffman coding trie.
*  PRECONDITION: freqs is a vector of ints, such that freqs[i] is
*  the frequency of occurrence of byte i in the message.
*  POSTCONDITION:  root points to the root of the trie,
*  and leaves[i] points to the leaf node containing byte i.
*/
void HCTree::build(const vector<int> & freqs)
{
	// Clear huffNodes
	while (!huffNodes.empty()) {
		huffNodes.pop();
	}

	// Create HCNodes for each non-zero frequency and push to queue
	for (unsigned int i=0; i<freqs.size(); i++) {
		if (freqs[i] > 0) {
			leaves[i] = new HCNode(freqs[i], (char)i);
			huffNodes.push(leaves[i]);
		}
	}

	// While queue contains more than 1 node, repeat algorithm
	while (huffNodes.size() > 1) {

		// Get two minimal nodes
		HCNode * min1 = huffNodes.top();
		huffNodes.pop();
		HCNode * min2 = huffNodes.top();
		huffNodes.pop();

		// Create new root
		int newCount = min1->count + min2->count;
		HCNode * newRoot = new HCNode(newCount, min1->symbol);

		// Link nodes
		min1->p = newRoot;
		min2->p = newRoot;
		newRoot->c0 = min1;
		newRoot->c1 = min2;
		
		// Push newRoot into queue
		huffNodes.push(newRoot);
	}

	// Set root to last element
	root = huffNodes.top();
}

/** Write to the given ofstream
*  the sequence of bits (as ASCII) coding the given symbol.
*  PRECONDITION: build() has been called, to create the coding
*  tree, and initialize root pointer and leaves vector.
*  THIS METHOD IS USEFUL FOR THE CHECKPOINT BUT SHOULD NOT
*  BE USED IN THE FINAL SUBMISSION.
*/
void HCTree::encode(byte symbol, ofstream& out) const
{
	// Get the correct leaf
	HCNode * curr = leaves[(int)symbol];

	// If current node is root, write 0 and return
	if (curr == root) {
		out << to_string(0);
		return;
	}

	// If frequency is 0, don't encode
	if (curr->count == 0) {
		return;
	}

	// Store the encoding
	vector<int> encoding;

	// Traverse up the tree and build up bitstring
	while (curr != root) {
		// Check if 0 or 1
		if ((curr->p->c0) && (curr->p->c1)) {
			if ((curr->p->c0) == curr) { 
				encoding.push_back(0);
			}
			else {
				encoding.push_back(1);
			}
		}
		else if (curr->p->c1) {
			encoding.push_back(1);
		}
		else {
			encoding.push_back(0);
		}

		// Traverse up
		curr = curr->p;
	}
	
	// build up output string
	std::string output = "";

	// Get size of encoding
	unsigned int size = encoding.size();

	for (unsigned int i = size-1; i>0; i--) {
		output += to_string(encoding[i]);
	}
	
	// Write last byte
	output += to_string(encoding[0]);

	// Write to output
	out << output;
}

/** Return the symbol coded in the next sequence of bits (represented as
  *  ASCII text) from the ifstream.
  *  PRECONDITION: build() has been called, to create the coding
  *  tree, and initialize root pointer and leaves vector.
  *  THIS METHOD IS USEFUL FOR THE CHECKPOINT BUT SHOULD NOT BE USED
  *  IN THE FINAL SUBMISSION.
*/
int HCTree::decode(ifstream& in) const
{
	// Start from root
	HCNode * curr = root;

	// Get first character from input
	unsigned char nextChar;
	int currSymb;

	// while good, keep reading
	while ((currSymb = in.get()) != EOF && curr != nullptr) {
		// Convert to char
		nextChar = (unsigned char) currSymb;

		// Traverse 0 or 1
		if (nextChar == LEFT) {
			if (curr->c0 != nullptr) {
				curr = curr->c0;
			}
		}
		else if (nextChar == RIGHT) {
			if (curr->c1 != nullptr) {
				curr = curr->c1;
			}
		}
		else {
			continue;
		}

		// Check if reached leaf node
		if (!(curr->c0) && !(curr->c1)) {
			return (int)(curr->symbol);
		}
	}

	// If file empty, return EOF
	return currSymb;
}

/* Destructor for HCTree, deletes all nodes allocated on heap*/
HCTree::~HCTree()
{
	deleteAll(root);
}

/* Helper method to destructor, deletes all nodes*/
void HCTree::deleteAll(HCNode * curr)
{
	// Check if root is null
	if (!curr) {
		return;
	}

	// While there is still memory, delete it
	if (curr->c0) 
		deleteAll(curr->c0);

	// While there is still memory, delete it
	if (curr->c1) 
		deleteAll(curr->c1);

	delete (curr);
}
