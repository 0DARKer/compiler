#ifndef oneH
#define oneH 1
#include<iostream>
#include<vector>
const int MAX=30;
struct FA{
    std::vector<int> Delta[MAX][MAX];
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
    void store_Graphviz(std::string);
    bool is_DFA();
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
    void I_epsion(std::vector<int>& );
    void I_epsion(std::vector<int>&, char );
};	 
struct G_3{
	std::vector<int> Vn;
	std::vector<int> Vt;
	std::vector<int*> P;
	int s;
public:
    G_3(const char*);
	FA to_FA();
};
int compare(int * a,int *b ,int N);
int together(int *a,int i,int j);
#endif
