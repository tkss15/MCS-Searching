#include "tree.h"


void updatePos(SuffixNode*& node, const string& word, int pos, int depth) {
	if (node == nullptr)
	{
		return;
	}
	cout << '\n' << depth;
 	if (depth == word.size())
	{
		bool flag = true;
		for (int i = 0; i < WORD_SIZE; i++)
		{
			if (node->children != NULL)
			{
				flag = false;
			}
		}
		if(flag)
			node->updatePosition(pos);
		return;
	}
	int index = word[depth] - 'a';
	
	if (node->children[index] != NULL)
	{
		cout << node->children  << endl;
		updatePos(node->children[index], word, pos, depth + 1);
	}
	else
	{
		if (node->children[26] != NULL)
			updatePos(node->children[26], word, pos, depth + 1);
		else
			return;
	}
}
void insert(SuffixNode*& node, const string& word, int pos, int depth) {
	if (node == nullptr) {
		node = new SuffixNode();  // Create a new node if the current node is null
	}

	if (depth == word.size()) {
		if (pos != -1)
			node->updatePosition(pos);  // Update position for the node representing the end of the word
		return;
	}
	int index;
	if (word[depth] == '_')
		index = 26;
	else
		index = word[depth] - 'a';  // Determine the child index based on the current character
	insert(node->children[index], word, pos, depth + 1);  // Recursively insert the rest of the word
}

//         1
//     0       1
//      1    0   1
//       1    1     1

void insertByMCS(TreeNode*& mcs, SuffixNode*& node, char* t, int len, int pos, int depth)
{
	if (mcs == nullptr)
	{
		return;
	}
	if (mcs->left == nullptr && mcs->right == nullptr)
	{
		if (node == nullptr)
		{
			node = new SuffixNode();
			if(pos != -1)
				node->updatePosition(pos);
		}
		if (mcs->data == 0)
		{
			node->children[26] = new SuffixNode();
		}
		else 
		{
			int index = t[depth] - 'a';
			node->children[index] = new SuffixNode();
		}
		return;
	}
	else
	{
		if (node == nullptr)
		{
			node = new SuffixNode();
		}
		if (mcs->data == 0)
		{
			insertByMCS(mcs->left, node->children[26], t, len, pos, depth + 1);
			insertByMCS(mcs->right, node->children[26], t, len, pos, depth + 1);
		}
		else
		{
			int index = t[depth] - 'a';
			insertByMCS(mcs->left, node->children[index], t, len, pos, depth + 1);
			insertByMCS(mcs->right, node->children[index], t, len, pos, depth + 1);
		}
	}
}
//    1
//  0   1
//1    0   1
void insertNumber(TreeNode*& root, const std::string& binaryword, int depth) {
	if (depth > binaryword.size()) {
		// Reached the end of the binary string; stop recursion
		return;
	}

	// Create the root node if it doesn't exist
	if (root == nullptr) {
		root = new TreeNode(binaryword[depth] - '0');
	}

	if (depth + 1 < binaryword.size()) {
		int nextNumber = binaryword[depth + 1] - '0';  // Determine the next number in the string

		// Decide whether to insert in the left or right subtree based on the next number
		if (nextNumber == 0) {
			insertNumber(root->left, binaryword, depth + 1);
		}
		else {
			insertNumber(root->right, binaryword, depth + 1);
		}
	}
}

int* search(SuffixNode* node, std::string word, int index)
{
	if (node == nullptr)
		return nullptr;

	if (index == word.length())
		return node->position;

	char currentChar = word[index];
	int childIndex;
	if (currentChar == '_')
		childIndex = 26;
	else
		childIndex = currentChar - 'a';

	if (node->children[childIndex] == nullptr)
		return nullptr;
	return search(node->children[childIndex], word, index + 1);
}

void printTree(SuffixNode* node, std::string path, std::string indent) {
	if (node == nullptr) return;

	// Print the path leading to this node
	if (!path.empty()) {
		std::cout << indent << path;
		if (node->length > 0) {
			std::cout << " (Positions: ";
			for (int i = 0; i < node->length; ++i) {
				std::cout << node->position[i] << (i < node->length - 1 ? ", " : "");
			}
			std::cout << ")";
		}
		std::cout << std::endl;
	}

	// Recursively print all non-null children
	for (int i = 0; i < WORD_SIZE; ++i) {
		if (node->children[i] != nullptr) {
			// Append the character for this child to the path
			char childChar = 'a' + i; // Assuming lowercase English letters
			printTree(node->children[i], path + childChar, indent + "  ");
		}
	}
}