#ifndef oneH
#define oneH 1
#include<iostream>
#include<vector>
struct FA{
	std::vector<int> Delta[27][27];
	int q0;
	std::vector<int> Sigma;
	std::vector<int> Q;
	std::vector<int> Z;
public:
	FA(const char*);
	FA();
	void store(const char*);
	FA to_DFA();
	void DFA_simpfy();
	void c_match(const char*);
private:
	int compare(std::vector<int> * a,std::vector<int> *b ,int N){
		for(int i=0;i<N;i++)
			if(a[i]==b[i])continue;//should define a fun 
			else return 0;
		return 1;
	}
	int together(int *a,int i,int j){ 
		if(i==j)return j;
		return a[j]=together(a,a[i],i);
	}
	std::vector<int> I_epsion(std::vector<int> );
};	 
struct G{
	std::vector<int> Vn;
	std::vector<int> Vt;
	std::vector<int*> P;
	int s;
public:
	G(const char*);
	FA to_FA();
};
void G_FA();
void NFA_DFA();
void DFA_CO();
void DFA_SDFA();
int compare(int * a,int *b ,int N);
int together(int *a,int i,int j);
#endif