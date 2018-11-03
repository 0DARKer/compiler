#include<iostream>
#include<map>
#include<cstring>
#include<fstream>
#include"1.h"
using namespace std;
void  NFA_DFA(){
	vector<int> temp;
	vector<vector<int>> I0;
	map<char,vector<int>> I1;
	vector<vector<int>>::iterator i0=I0.begin();
	FA nfa;
	// int nfa.Delta[27][27];
	// int q0;//init Delta and q0;
	memset(nfa.Delta,-1,sizeof(int)*27*27);
	ifstream fin("NFA.txt");
	fin>>nfa.q0;
	int N;
	fin >>N;
	// vector<int> Z;
	for(int i=0;i<N;i++){
		int c;
		fin >> c;
		nfa.Z.push_back(c); 
	}
	while(!fin.eof()){
		int i;
		int j;
		int c;
		fin >>i>>j>>c;
		nfa.Delta[i][j]=c;
	}
	
	temp.push_back(nfa.q0);
	I0.push_back(temp);
	temp.clear();

	FA dfa;
	// int dfa.Delta[27][27];
	// int dfa.q0=0;
	// vector<int> N_Z;
	memset(dfa.Delta,-1,sizeof(int)*27*27);

	for( int i0_=0;i0_<I0.size();i0_++){
		I1.clear();
		for(int i0__=0;i0__<I0[i0_].size();i0__++){
			int index;
			index=I0[i0_][i0__];
			for(int j=0;j<27;j++)
				if(nfa.Delta[index][j]!=-1){
					if(nfa.Delta[index][j]!=0){
						I1[nfa.Delta[index][j]].push_back(j);
					}
					else I0[i0_].push_back(j);
				}
		}


		// vector<vector<int>>::iterator i0_1;
		map<char,vector<int>>::iterator i1;
		for(i1=I1.begin();i1!=I1.end();i1++){
			bool check=0;
			int i0_1;
			for(i0_1=0;i0_1<I0.size();i0_1++)
				if(I0[i0_1] == i1->second){check=1;break;}
			if(check==1){dfa.Delta[i0_][i0_1]=i1->first;continue;}
			else {I0.push_back(i1->second);dfa.Delta[i0_][I0.size()-1]=i1->first;}
		}
		bool check=0;
		for(int i=0;i<N;i++)
			for(int j=0;j<I0[i0_].size();j++)
			if(I0[i0_][j]==nfa.Z[i]){
				check=1;
				break;
			}
		if(check==1)dfa.Z.push_back(i0_);

	}
	ofstream fout("DFA.txt");
	fout<<dfa.q0 << " "<<dfa.Z.size()<<" ";
	for(int i=0;i<dfa.Z.size();i++)
		fout << dfa.Z[i]<<" ";
	fout <<endl;
	for(int i=0;i<27;i++)
		for(int j=0;j<27;j++)
			if(dfa.Delta[i][j]!=-1){
				fout << i <<" "<< j <<" "<<dfa.Delta[i][j]<<endl; 
			}
}
