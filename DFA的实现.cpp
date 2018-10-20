#include<iostream>
#include<fstream>
#include<cstring>
#include<vector>
const int MAX=100;
using namespace std;
int main(){
	ifstream fin("DFAplus.txt");
	int Delta[27][27];
	memset(Delta,-1,sizeof(int)*27*27);
	int q0;
	fin >> q0;
	int N;
	fin >>N;
	vector<int> Z;
	for(int i=0;i<N;i++){
		int c;
		fin >> c;
		Z.push_back(c);
	}
	while(!fin.eof()){
		int i;
		int j;
		int c;
		fin >>i>> j>>c;
		Delta[i][j]=c;
	}

	int chars[MAX];
	int n=0;
	int c;
	while((c=getchar())!='\n'){
		chars[n++]=c;
	}
	int k=0;
	int i;
	for( i=q0;i<27&&k<n;){
		int check=0;
		for(int j=0;j<27;j++)
			if(Delta[i][j]==chars[k]){k++;i=j;check=1;break;}
		if(check==0)i++;
	}
	if(k==n){
		int check=0;
		for(int j=0;j<Z.size();j++){
			if(Z[j]==i){
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