#include<iostream>
#include<cstring>
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
int main(){
	int Delta[27][27];
	memset(Delta,0,sizeof(int)*27*27);
	{Delta[1][1]=1;Delta[2][1]=1;Delta[3][2]=1;}
	int a[27];
	for(int i=0;i<27;i++){
		a[i]=i;
	}
	for(int i=0;i<27;i++){
		for(int j=i+1;j<27;j++){
			if(compare(Delta[i],Delta[j],27)==1)together(a,i,j);
		}
	}
	for(int i=0;i<27;i++){
		if(a[i]!=i){
			memset(Delta[i],0,sizeof(int)*27);
			continue;
		}
		for(int j=0;j<27;j++){
			if(Delta[i][j]!=0&&a[j]!=j){
				Delta[i][a[j]]=Delta[i][j];
				Delta[i][j]=0;
			}
		}
	}

}