#ifndef oneH
#define oneH 1
// #include<iostream>
#include<vector>
struct FA{
	int Delta[27][27];
	int q0;
	std::vector<int> Sigma;
	std::vector<int> Q;
	std::vector<int> Z;
};	
struct G{
	std::vector<int> Vn;
	std::vector<int> Vt;
	std::vector<int*> P;
	int s;
};
void G_FA();
void NFA_DFA();
void DFA_CO();
void DFA_SDFA();
int compare(int * a,int *b ,int N);
int together(int *a,int i,int j);
#endif