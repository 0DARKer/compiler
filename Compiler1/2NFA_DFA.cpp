#include<iostream>
#include<map>
#include<cstring>
#include<fstream>
#include"1.h"
using namespace std;
void  NFA_DFA(){
//we init nfa here
	FA nfa;
	ifstream fin("NFA.txt");
	fin>>nfa.q0;//nfa.q0
	int N;
	fin >>N;
	for(int i=0;i<N;i++){//nfa.Z
		int c;
		fin >> c;
		nfa.Z.push_back(c); 
	}

	memset(nfa.Delta,-1,sizeof(int)*27*27);//nfa.delta
	while(!fin.eof()){
		int i;
		int j;
		int c;
		fin >>i>>j>>c;
		nfa.Delta[i][j]=c;
	}
	
//create a table I|Ia|Ib|...|
/*
|I 	 |Ia 	  |Ib  	   |Ic  	 |...|
| I1 |Ialpha1|Ialpa2 |Ialpha3  |...|
|    |
|    |
|    |
I is I ,
I_alpha is Ia,Ib...
*/

	vector<vector<int>> I;{//first I1 have a number q0
		vector<int> temp;
		temp.push_back(nfa.q0);
		I.push_back(temp);
		// temp.clear();			//...init nfa finish 
	}
	map<char,vector<int>> I_alpha;//I-alpha
	// bool chek[27];{
	// 	memset(chek,0,sizeof(bool)*27);
	// }
	
	FA dfa;{
		memset(dfa.Delta,-1,sizeof(int)*27*27);
	}
	// vector<vector<int>>::iterator i0=I.begin();

	for( int Ix=0;Ix<I.size();Ix++){//find I line by line.
		I_alpha.clear();
		for(int Iy=0;Iy<I[Ix].size();Iy++){//in the set I , find each state's path .
			int index;
			index=I[Ix][Iy];
			for(int j=0;j<27;j++){//find every path of this state, get which alpha .
				if(nfa.Delta[index][j]!=-1){ //if not ,we discuss next ,so j++.
					if(nfa.Delta[index][j]!=0){//if alpha is not Epsion 
						bool check=0;			//if check ==0 there is no j in the set.
						for(int i=0;i<I_alpha[nfa.Delta[index][j]].size();i++)
							if(I_alpha[nfa.Delta[index][j]][i]==j)check = 1;
						if(check==0) I_alpha[nfa.Delta[index][j]].push_back(j);//if there is a loop then it is a problem .b
					}
					else{						 //if alpha is Epsion
						bool check=0;
						for(int i=0;i<I[Ix].size();i++)
							if(I[Ix][i]==j)check = 1;
						if(check==0)I[Ix].push_back(j);
					}
				}
			}
		}
		map<char,vector<int>>::iterator Ia;//find set I-alpha
		for(Ia=I_alpha.begin();Ia!=I_alpha.end();Ia++){
			int Iz;
			bool check=0;
			for(Iz=0;Iz<I.size();Iz++)
				if(I[Iz] == Ia->second){check=1;break;}
			if(check==1){dfa.Delta[Ix][Iz]=Ia->first;continue;}//if check==1 ,set Ia is old and will have new path Ix--alpha-->Iz in dfa
			else {I.push_back(Ia->second);dfa.Delta[Ix][I.size()-1]=Ia->first;}//if check ==0 ,set Ia is new and Ia will add to I .
		}

		bool check=0;
		for(int i=0;i<N;i++)
			for(int j=0;j<I[Ix].size();j++)
			if(I[Ix][j]==nfa.Z[i]){
				check=1;
				break;
			}
		if(check==1)dfa.Z.push_back(Ix);//find I? is belong to Z or not ,line by line.

	}
	dfa.q0=0;//we know it was always begin at I=0;
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
