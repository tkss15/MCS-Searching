#include "main.h"
#include <iostream>
#include <fstream>

using namespace std;

char* ReadTextFile(string fileName)
{
	ifstream file(fileName, ifstream::ate);// open file at the end.
	char* text;
	char readChar;
	int counter, text_size;



	// Check if the file was opened successfully
	if (!file.is_open()) {
		cerr << "Error opening file" << endl;
		return 0;
	}
	// Get the file size by telling the position of the cursor (which is at the end due to std::ifstream::ate)
	streampos fileSize = file.tellg();
	file.seekg(0, ios::beg);

	counter = 0;
	text = new char[fileSize];
	// Read the file character by character
	while (file.get(readChar) && counter < fileSize) {
		// If the character is not a newline, process it (in this example, print it)
		if (readChar != '\n') {
			text[counter] = readChar;
			counter++;
		}
	}

	// Close the file
	file.close();
	return text;
}

char* CreateRandomText(int text_size, int word_size)
{
	/*
		text_size will define how large the text will be
		word_size will define what will be the chars in everyword ( for example 2 will create words with only a and b )
	*/
	string fileName = "output.txt";
	ofstream file(fileName);
	char* txt;
	txt = new char[text_size];
	for (int i = 0; i < text_size; i++)
	{
		if (i % 10000 == 0)
			cerr << i << "\n";
		txt[i] = 'a' + int(word_size * double(rand()) / double(RAND_MAX));
		file << txt[i];
	}
	file.close();
	return txt;
}

int CalculateW(int word_total_size, int missmatch)
{
	int W = 1;

	long long cnk = CNK_Calculator(word_total_size, missmatch);

	while (check_Test(W, word_total_size, missmatch, cnk))
	{
		W = W + 1;
	}
	return W;
}

long long CNK_Calculator(int n, int k)
{
	if (k > n - k)
	{
		k = n - k;
	}
	long long result = 1;

	for (int i = 1; i < k; ++i)
	{
		result = result * (n - i + 1) / i;
	}
	return result;
}

bool check_Test(int W, int n, int m, long long cnk)
{
	double W_size = pow(W, n - m);
	double P = 2.0 / 100000000.0; // Equivalent to 2/10^8
	double Final_W = 1.0 / W_size;
	return (Final_W * cnk) > P;
}