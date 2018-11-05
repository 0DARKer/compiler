#include<iostream>
#include<cstring>
#include <fstream>
#include"1.h"
using namespace std;
int compare(int * a,int *b ,int N){
	for(int i=0;i<N;i++)
		if(a[i]==b[i])continue;
		else return 0;
	return 1;
}
int together(int *a,int i,int j){
	if(i==j)return j;
	return a[j]=together(a,a[i],i);
}
void DFA_SDFA(){
	//we init dfa here
	FA dfa;
	ifstream fin("DFA.txt");
	fin>>dfa.q0;//nfa.q0
	int N;
	fin >>N;
	for(int i=0;i<N;i++){//nfa.Z
		int c;
		fin >> c;
		dfa.Z.push_back(c); 
	}

	memset(dfa.Delta,-1,sizeof(int)*27*27);//nfa.delta
	while(!fin.eof()){
		int i;
		int j;
		int c;
		fin >>i>>j>>c;
		dfa.Delta[i][j]=c;
	}
	

	// int Delta[27][27];
	// memset(Delta,0,sizeof(int)*27*27);
	// {Delta[1][1]=1;Delta[2][1]=1;Delta[3][2]=1;}
	int a[27];
	for(int i=0;i<27;i++){
		a[i]=i;//we use merge set a[].
	}

	for(int i=0;i<27;i++){
		for(int j=i+1;j<27;j++){
			bool checki =0,checkj=0;
			for(int k=0;k<dfa.Z.size();k++){
				if(dfa.Z[k]==i)checki=1;
				if(dfa.Z[k]==j)checkj=1;
			}
			if(checki==checkj)//end state and normal state never together.
			if(compare(dfa.Delta[i],dfa.Delta[j],27)==1)together(a,i,j);//if dfa.Delta[][] have the same line ,put them together .
		}
	}
	for(int i=0;i<27;i++){
		if(a[i]!=i){
			vector<int>::iterator iter;
			for(iter=dfa.Q.begin();iter<dfa.Q.end();iter++){//rm from Q
				if(*iter==i){
					dfa.Q.erase(iter);
					break;
				}
			}

			for(iter=dfa.Z.begin();iter<dfa.Z.end();iter++){//rm from Z
				if(*iter==i){
					dfa.Z.erase(iter);
					break;
				}
			}
			


			memset(dfa.Delta[i],-1,sizeof(int)*27);//a line that together with other line ,the line will be not needed.
			continue;
		}
		for(int j=0;j<27;j++){
			if(dfa.Delta[i][j]!=0&&a[j]!=j){//the end state replaced by his root state.
				dfa.Delta[i][a[j]]=dfa.Delta[i][j];
				dfa.Delta[i][j]=-1;
			}
		}
	}

	ofstream fout("DFAplus.txt"); //output to file.
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