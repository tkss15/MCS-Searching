#pragma once
#ifndef _INC_main
#define _INC_main

#include "mcs.h"
#include "tree.h"

// Utils
char* ReadTextFile(string fileName);
char* CreateRandomText(int text_size, int word_size);

int CalculateW(int word_total_size, int missmatch);
long long CNK_Calculator(int n, int k);
bool check_Test(int W, int n, int m, long long cnk);

#endif  //_INC_main