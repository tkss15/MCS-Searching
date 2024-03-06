#ifndef _INC_forms2
#define _INC_forms2

#include "mcs.h"

void  Forms::chetv_struct_Generation()
{
	int i, i1, j1, j2, k, n1, Nform, flag1;
	ofstream fout;

	int N = N_glob;
	int N_2 = N_2_glob;
	int Nsovp = Nsovp1_Glob;

	CString qqq1, qqq2;


	int NformMax = 10000; //maximal amount of forms
	int** forms; //array of forms

	forms = new int* [NformMax];
	for (i = 0; i < NformMax; i++)
		forms[i] = new int[N + 1];

	for (i = 0; i < NformMax; i++)
		for (j1 = 0; j1 < N; j1++)
			forms[i][j1] = 0;

	for (i = 0; i < NformMax; i++)
	{
		forms[i][N] = -1;
		forms[i][0] = 1;
	}


	//	the algorithm is described in the presentation Lect2 (p12)


	k = 0;
	Nform = 0;
	for (i = 0; i < NVars_Glob; i++)
	{
		if (i % 100 == 0)
			cerr << "\n " << i;

		//search the created forms in the combination
		flag1 = 1;
		for (i1 = 0; i1 < Nform; i1++)
		{
			for (j1 = 0; j1 <= N - forms[i1][N]; j1++)
			{
				if (Vars_Glob[i][j1] == 0) continue;

				flag1 = 0;
				for (j2 = 1; j2 < forms[i1][N]; j2++)
				{
					if (forms[i1][j2] == 0) continue;

					if (Vars_Glob[i][j1 + j2] != 1)
					{
						flag1 = 1;
						break;
					}
				}

				if (flag1 == 0)	break; //a form is found, goto the next combination

			}

			if (flag1 == 0)	break;
		}

		if (flag1 == 0)	continue;

		//if there is no existing forms - add a new form (can be optimized) 
		for (j1 = 0; j1 < N; j1++)
		{
			if (Vars_Glob[i][j1] == 0) continue;

			n1 = 1;
			for (j2 = 1; j2 < N; j2++)
			{
				forms[Nform][j2] = Vars_Glob[i][j2 + j1];

				if (forms[Nform][j2] == 1)
					n1++;

				if (n1 == Nsovp)
				{
					forms[Nform][N] = j2 + 1; //size of the form
					Nform++;
					break;
				}
			}

			break;
		}

		if (Nform == NformMax)
			break;
	}

	fout.open("forms", ios::out);

	fout << "Nform1 = " << Nform << "\t" << "form1Size = " << N + 1 << " Nsovp1 = " << Nsovp << " N_2 = " << N_2;

	for (i1 = 0; i1 < Nform; i1++)
	{
		fout << "\n>" << i1 << "\t";
		for (j1 = 0; j1 < N + 1; j1++)
			fout << forms[i1][j1] << " ";
	}

	fout.close();

	cerr << "\nk = " << Nform;
	//	cin>>i;

		///////////////////copy to forms_Glob
	Nform1_Glob = Nform;
	form1Size = N + 1;

	forms1Glob = new int* [Nform1_Glob];
	for (i = 0; i < Nform1_Glob; i++)
		forms1Glob[i] = new int[form1Size];

	for (i1 = 0; i1 < Nform1_Glob; i1++)
		for (j1 = 0; j1 < form1Size; j1++)
			forms1Glob[i1][j1] = forms[i1][j1];
	///////////////////////////////////////

}



bool Forms::FindWord(ifstream& fin, std::string aaa)
{
	char a1, a2;
	int i;
	char buf[1000];

	cerr << "\nT_ " << aaa[0];

	while (!fin.eof())
	{
		for (i = 0; i < aaa.length(); i++)
		{
			fin.get(a1);
			if (a1 == aaa[i]) continue;
			else
				break;
		}

		if (i == aaa.length()) return(1);

	}
	return (0);
}

double Forms::degInt(int n, double q)
{
	double a = 1.0;
	for (int i = 0; i < n; i++)
		a = a * q;
	return (a);
}


void  Forms::create_mas1()
{
	int i, j, i1, j1, j2, n, k, n1, Nform, flag1;
	ofstream fout;

	int N = N_glob;
	int N_2 = N_2_glob;

	int* mas1, * mas2;
	mas1 = new int[N];
	mas2 = new int[N];

	for (i = 0; i < N; i++)
		mas1[i] = degInt(i, 2);


	double d1, d2, d3;

	d1 = 1.0;
	n = N - N_2;
	for (i = 0; i < n; i++)
		d1 = d1 * (N - i) / double(n - i);

	int Nmas = int(d1) + 1;


	NVars_Glob = 0;

	Vars_Glob = new bool* [Nmas];
	for (i = 0; i < Nmas; i++)
		Vars_Glob[i] = new bool[N];

	for (i = 0; i < Nmas; i++)
		for (j = 0; j < N; j++)
			Vars_Glob[i][j] = 0;


	for (i = 0; i < degInt(N, 2); i++)
	{
		//generation of all the match/mismatch combinations
		n1 = 0;
		n = i;
		for (i1 = N - 1; i1 >= 0; i1--)
		{
			mas2[i1] = int(n / mas1[i1]); //i1-position in cod binari
			n1 += mas2[i1]; //calculate amount of "1"
			n = n - (mas2[i1] * mas1[i1]);
		}

		if (n1 != N_2) continue;
		if (mas2[0] != 1) continue;

		for (j = 0; j < N; j++)
			Vars_Glob[NVars_Glob][j] = mas2[j];

		NVars_Glob++;

		if (NVars_Glob % 100 == 0)
			cerr << "\n " << NVars_Glob;

		if (NVars_Glob > Nmas)
		{
			cerr << "\n NVars_Glob > Nmas";
			cin >> i;
			return;
		}
	}


	VarsDescr_Glob = new int[NVars_Glob];


	fout.open("tavnits", ios::out);

	fout << "NVars_Glob = " << NVars_Glob << "\t" << "Nmas = " << Nmas;

	for (i = 0; i < NVars_Glob; i++)
	{

		fout << "\n";
		for (j = 0; j < N; j++)
			fout << Vars_Glob[i][j];

	}

	fout.close();

}

void  Forms::Read_Forms1(std::string fname)
{
	int i, n, k;
	char a, buf[1000];

	ofstream fout;
	ifstream fin;

	fin.open(fname.c_str(), ios::in);
	if (!fin.good()) return;

	cerr << "\nT00";

	FindWord(fin, "Nform1 =");

	cerr << "\nT01";
	fin >> Nform1_Glob;



	FindWord(fin, "form1Size =");
	fin >> form1Size;

	FindWord(fin, "Nsovp1 =");
	fin >> Nsovp1_Glob;

	FindWord(fin, "N_2 =");
	fin >> N_2_glob;

	cerr << "\nT01";

	forms1Glob = new int* [Nform1_Glob];
	for (i = 0; i < Nform1_Glob; i++)
		forms1Glob[i] = new int[form1Size];

	cerr << "\n" << Nform1_Glob << " " << form1Size;
	//		cin>>k;

	for (n = 0; n < Nform1_Glob; n++)
		for (i = 0; i < form1Size; i++)
			forms1Glob[n][i] = 0;

	for (n = 0; n < Nform1_Glob; n++)
	{
		fin.getline(buf, sizeof(buf));

		fin >> a;
		fin >> k;

		for (i = 0; i < form1Size; i++)
			fin >> forms1Glob[n][i];

	}

	fin.close();

	cerr << "\nT03";
}




#endif  // _INC_forms2