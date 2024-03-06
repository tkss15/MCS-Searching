#pragma once
#ifndef _TREE_

using namespace std;
#include <string>
#include <iostream>
#include <queue>
static const int WORD_SIZE = 27;  // Assuming only lowercase English letters
class TreeNode {
public:
	int data;
	TreeNode* left;
	TreeNode* right;

	TreeNode(int data) : data(data), left(nullptr), right(nullptr) {}
	void printInOrder(TreeNode* node) {
		if (node == nullptr) return;
		std::cout << node->data << " ";
		printInOrder(node->left);
		printInOrder(node->right);
	};
};


class SuffixNode {
public:
	int* position;
	int length;
	SuffixNode** children;

	SuffixNode() {
		length = 0;
		position = nullptr;
		children = new SuffixNode * [WORD_SIZE]();
		for (int i = 0; i < WORD_SIZE; i++)
		{
			children[i] = NULL;
		}
	}

	void updatePosition(int pos) {
		int* newPosition = new int[length + 1];
		for (int i = 0; i < length; i++) {
			newPosition[i] = position[i];
		}
		newPosition[length] = pos;
		delete[] position;
		position = newPosition;
		length++;
	}

	~SuffixNode() {
		delete[] position;
		for (int i = 0; i < WORD_SIZE; ++i) {
			delete children[i];  // Delete each child
		}
		delete[] children;  // Delete the array of children pointers
	}
};
void MCSText(char* text, int textlen, int M, int s, int d, TreeNode* t, SuffixNode*& root);
void insertByMCS(TreeNode*& mcs, SuffixNode*& node, char* t, int len, int pos=-1, int depth = 0);
void updatePos(SuffixNode*& node, const string& word, int pos, int depth = 0);
int* search(SuffixNode* node, std::string word, int index);
void insert(SuffixNode*& node, const string& word, int pos, int depth = 0);
void printTree(SuffixNode* node, std::string path = "", std::string indent = "");
void insertNumber(TreeNode*& root, const string& binaryword, int depth = 0);
void MCSMatchingPosition(SuffixNode*& root, string word, queue<int>& leafQueue);
#endif // !_TREE_
