#include<iostream>
#include<cstring>
#include<fstream>
#include"1.h"
using namespace std;	
void G_FA(){
	G A;
	FA a;
	int Sum_Vn=0;
	int Sum_Vt=0;
	ifstream fin("wenfa.txt");
	int check=0;
	while(!fin.eof()){//initialize P[][]
		char c[6];
		fin.getline(c,6);
		cout << c<<endl;
		int* temp;
		temp = new int[3];
		if(c[0]=='\0')break;
		if(check==0){A.s=c[0];check=1;}
		temp[0]=c[0];
		if((c[3]>='A'&&c[3]<='Z')&&c[4]=='\0'){
			temp[1]=c[3];
			temp[2]=0;
		}
		if(!(c[3]>='A'&&c[3]<='Z')&&(c[4]>='A'&&c[4]<='Z')){
			temp[1]=c[4];
			temp[2]=c[3];
		}
		if(!(c[3]>='A'&&c[3]<='Z')&&c[4]=='\0'){
			temp[1]='[';
			temp[2]=c[3];
		}
		A.P.push_back(temp);
	}
	
	for(int i=0;i<A.P.size();i++)//initialize Vn Vt
		for(int j=0;j<3;j++){
			if(A.P[i][j]>'A'&&A.P[i][j]<'Z'){
				if(j==2&&A.P[i][j]=='\0'){
					A.Vn.push_back(A.Vn[Sum_Vn-1]);
					A.Vn[Sum_Vn-1]='[';

				}
				else A.Vn.push_back(A.P[i][j]);
			}
			else A.Vt.push_back(A.P[i][j]);
	}	


	memset(a.Delta,-1,sizeof(int)*27*27);//init FA-Sigma FA-Q FA-Z FA-q0 FA-Delta
	for(int i=0;i<Sum_Vt;i++)
		a.Sigma.push_back(A.Vt[i]);
	for(int i=0;i<Sum_Vn;i++)
		a.Q.push_back(A.Vn[i]);
	a.Q.push_back('[');
	a.q0=A.s;
	
	for(int i=0;i<A.P.size();i++){
		a.Delta[A.P[i][0]-'A'][A.P[i][1]-'A']=A.P[i][2];
	}

	a.Z.push_back('[');
	ofstream fout("NFA.txt");
	fout <<a.q0-'A'<<" ";
	fout << 1<<" "<<a.Z[0]-'A'<<endl;
	for(int i=0;i<27;i++)
		{
			for(int j=0;j<27;j++)
			{
				if (a.Delta[i][j]!=-1){
					// if(a.Delta[i][j]!=0)
					// printf("  %c   \n",a.Delta[i][j]);
					// else
					// 	printf("epsion\n");
					// printf("%c--->%c\n",i+'A',j+'A');
					// printf("\n");
					fout << i<<" "<<j<<" "<< a.Delta[i][j]<<endl;
				}
			}
		}
	// printf("%c\n",a.q0);
}
