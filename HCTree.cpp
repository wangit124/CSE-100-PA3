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

using namespace std;

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
		HCNode * newRoot = new HCNode(newCount, 0);

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

// Destructor for HCTree, deletes all nodes allocated on heap
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
