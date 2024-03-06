#pragma once
#ifndef _INC_MCS
#define _INC_MCS

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#pragma warning(disable : 4996)
#pragma warning(disable : 7403)
#include <atlstr.h>
//#include <afxwin.h>         // MFC core and standard components
//#include <afxext.h>         // MFC extensions
#ifndef _AFX_NO_AFXCMN_SUPPORT
//#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT
//#include <AFXTEMPL.H>
#include <fstream>
#include <iostream>
#include <math.h>
//#include <time.h>
#include <iomanip>

using namespace std;


class Forms
{
public:
	int Nform1_Glob;
	int form1Size;
	int Nsovp1_Glob;
	int N_2_glob;
	int N_glob;
	int** forms1Glob;
	bool** Vars_Glob;
	int* VarsDescr_Glob;
	int NVars_Glob;
	int* NForms_pos_Glob;
	int*** forms1_pos_Glob;
	int* SeqPos;

	bool FindWord(ifstream&, std::string);
	void  Read_Forms1(std::string);
	double degInt(int, double);

	void create_mas1(); //creation of the array of all combimnations of the matches
	void chetv_struct_Generation(); //create of the first array of forms

};


// AB_CD 

#endif  //_INC_main