#include<iostream>
#include<fstream>
#include<cstring>
#include"1.h"
using namespace std;
void  DFA_CO(){
	ifstream fin("DFA.txt");
	FA dfa;
	// int Delta[27][27];
	memset(dfa.Delta,-1,sizeof(int)*27*27);
	// int q0;
	fin >> dfa.q0;
	int N;
	fin >>N;
	// vector<int> Z;
	for(int i=0;i<N;i++){
		int c;
		fin >> c;
		dfa.Z.push_back(c);
	}
	while(!fin.eof()){
		int i;
		int j;
		int c;
		fin >>i>> j>>c;
		dfa.Delta[i][j]=c;
	}

	// int chars[MAX];
	vector<int> chars;
	// int n=0;
	int c;
	while((c=getchar())!='\n'){
		chars.push_back(c);
	}
	int k=0;
	int i;
	for( i=dfa.q0;i<27&&k<chars.size();){
		int check=0;
		for(int j=0;j<27;j++)
			if(dfa.Delta[i][j]==chars[k]){k++;i=j;check=1;break;}
		if(check==0){
			cout << "Wrong ! state stack"<<endl;
			return ;
		}

	}
	if(k==chars.size()){
		int check=0;
		for(int j=0;j<dfa.Z.size();j++){
			if(dfa.Z[j]==i){
				check=1;
				break;
			}
		}
		if(check==1)
			cout <<"yes"<<endl;
		else
			cout <<"WRONG!"<<endl;
	}
	else cout << "wrong!"<<endl;
}
