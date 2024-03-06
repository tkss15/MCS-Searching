// ConsoleApplication4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "main.h"
#include <map>
#include <set>
#include <vector>

void MCSCheckEquality(char* text, int word_size, int s, int d, queue<int>& leafQueue);
void CalculateMCS(int s, int d, int matches_filter, char* text, int text_len, int word_size, SuffixNode*& root);
void MCSWord(char* text, int textlen, int wordsize, int s, int d, Forms f, SuffixNode*& root, TreeNode* t);
int main()
{/*
	int s = 20;
	int d = 7;
	int WordSize = CalculateW(s, d);

	int word_text_size = 1e3;
	int text_size = 1e5;
	char* txt2 = new char[text_size];
	SuffixNode* root = nullptr;

	txt2 = CreateRandomText(text_size, WordSize);
	CalculateMCS(s, d, 4, txt2, text_size, word_text_size, root);*/
	char* text = new char[4];
	text[0] = 'a';
	text[1] = 'b';
	text[2] = 'b';
	text[3] = 'a';
	int len = 4;
	SuffixNode* root = nullptr;
	TreeNode* tree = nullptr;
	insertNumber(tree, "1111");
	insertNumber(tree, "1011");
	insertNumber(tree, "1101");
	tree->printInOrder(tree);
	insertByMCS(tree, root, text,len);
	updatePos(root, "abax", 3, 0);
	printTree(root);
	delete root;
}
//         1
//     0       1
//      1    0   1
//       1    1     1


void CalculateMCS(int s, int d, int matches_filter, char* text, int text_len, int word_size, SuffixNode*& root)
{
	Forms MCSForms;// Creates a FORM

	MCSForms.N_glob = s; //size of word for search
	MCSForms.N_2_glob = (s - d); //minimal amount of matches
	MCSForms.Nsovp1_Glob = matches_filter; //amount of matches in the filter 

	MCSForms.create_mas1();
	MCSForms.chetv_struct_Generation();// Get MCS 
	/*

	for (i1 = 0; i1 < Nform1_Glob; i1++)
		for (j1 = 0; j1 < form1Size; j1++)
			forms1Glob[i1][j1] = forms[i1][j1];
	*/
	TreeNode* tree = nullptr;
	string mcs_seq = "";
	queue<int> leafQueue;
	for (int i = 0; i < MCSForms.Nform1_Glob; i++)
	{
		int LastValue = MCSForms.forms1Glob[i][MCSForms.form1Size - 1];
		for (int j = 0; j < LastValue; j++)
		{
			cout << (char)('0' + MCSForms.forms1Glob[i][j]);
			mcs_seq = mcs_seq + (char)('0' + MCSForms.forms1Glob[i][j]);
		}
		insertNumber(tree, mcs_seq);
	}
	cout << "\n\n";
	//tree->printInOrder(tree);
	MCSWord(text, text_len, word_size, s, d, MCSForms, root, tree);// searching inside the word for a spesific mcs and then looking for position in the text with the map
	printTree(root);
	MCSText(text, text_len, word_size, s, d, tree, root);
	MCSMatchingPosition(root, "", leafQueue);
	MCSCheckEquality(text, word_size, s, d, leafQueue);
}

void MCSWord(char* text, int textlen, int wordsize, int s, int d, Forms f, SuffixNode*& root, TreeNode* t)
{
	string word;
	for (int i = 0; i < wordsize; i++)
	{
		cerr << i << " _ch\n";
		insertByMCS(t, root, (text + i), textlen);
	}
}
// abcde
//  bcde
void MCSText(char* text, int textlen, int M, int s, int d, TreeNode* t, SuffixNode*& root)
{
	/*
		function creates all combintion of text mcs from given text
	*/
	string word;
	map<string, vector<int>> MCSTextmap;
	for (int i = 0; i < textlen; i++)
	{
		word = "";
		cerr << i << " _ch\n";
		for (int j = 0; j < M; j++)
		{
			word = word + text[i + j];
			//insertByMCS(t, root, (text + i + j), i, textlen);
		}
		cout << word;
		updatePos(root, word, i);
		//Sleep(5000);
	}
}

void MCSMatchingPosition(SuffixNode*& root, string word, queue<int>& leafQueue)
{
	if (root == nullptr)
		return;

	bool flag = true;
	for (int i = 0; i < WORD_SIZE; i++)
	{
		if (root->children[i] != nullptr)
		{
			flag = false;
			if (i == 26)
			{
				MCSMatchingPosition(root->children[i], word + '_', leafQueue);
			}
			else
			{
				MCSMatchingPosition(root->children[i], word + (char)('a' + i), leafQueue);
			}
		}
	}
	if (flag)
	{
		for (int i = 0; i < root->length; i++)
		{
			leafQueue.push(root->position[i]);
		}
	}
}

void MCSCheckEquality(char* text, int word_size, int s, int d, queue<int>& leafQueue)
{
	string fileName = "foundMatches.txt";

	map<string, set<int>> FoundMatches;
	ofstream outfile(fileName);
	string word;
	for (int i = 0; i < word_size; i++)
	{
		while (!leafQueue.empty())
		{
			int address = leafQueue.front();
			string fullword = "";
			int missmatch = 0;
			bool flag = true;
			for (int p = 0; p < s; p++)
			{
				fullword = fullword + text[i + p];
				if (text[i + p] != text[address + p])
				{
					missmatch++;
					if (missmatch > d)
					{
						fullword = "";
						missmatch = 0;
						flag = false;
						break;
					}
				}
			}
			if (flag)
			{
				FoundMatches[fullword].insert(address);
			}
			leafQueue.pop();
		}
	}
	for (const auto& pair : FoundMatches) {
		outfile << pair.first << ": ";
		for (int val : pair.second) {
			outfile << val << " ";
		}
		outfile << "\n";
	}
	outfile.close();
}
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
