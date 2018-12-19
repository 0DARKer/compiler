#include"1.h"
#include<fstream>
#include<iostream>
#include<map>
using namespace std;
FA::FA(){}
FA::FA(const char* filename){
	ifstream fin(filename);
    if(!fin){
        throw -1;
        return ;
    }
	fin>>q0;//nfa.q0
	while(!fin.eof()){
		int c;
		fin >> c;
		if(c!=-1)
			Z.push_back(c); 
		else break;
	}
	while(!fin.eof()){
		int i;
		int j;
		
		fin >>i>>j;
		while(1){
			int c;
			fin >> c;
			if(c!=-1)
				Delta[i][j].push_back(c);
			else break;
		}
	}
}
void FA::store(const char* filename){
	ofstream fout(filename);
	fout <<q0<<endl;
	fout <<Z[0]<<" "<<-1<<endl;
    for(int i=0;i<MAX;i++)
		{
            for(int j=0;j<MAX;j++)
			{
				if (Delta[i][j].size()!=0){
					fout << i<<" "<<j<<" ";
					for(int k=0;k<Delta[i][j].size();k++)
						fout << Delta[i][j][k]<<" ";
					fout<<-1<<endl ;
				}
			}
		}
}
G_3::G_3(const char *filename){
	int Sum_Vn=0;
	int Sum_Vt=0;
	ifstream fin(filename);
	int check=0;
	while(!fin.eof()){//initialize P[][]
        char c[10];
        fin.getline(c,10);
        if(c[5]==0||c[4]==0);
        else {throw -2;}
        cout << c<<endl;
		int* temp;
		temp =  new int[3];
		if(c[0]=='\0')break;
		if(check==0){s=c[0];check=1;}
		temp[0]=c[0];
		if((c[3]>='A'&&c[3]<='Z')&&c[4]=='\0'){
			temp[1]=c[3];
			temp[2]=0;
		}
        else if(!(c[3]>='A'&&c[3]<='Z')&&(c[4]>='A'&&c[4]<='Z')){
			temp[1]=c[4];
			temp[2]=c[3];
		}
        else if(!(c[3]>='A'&&c[3]<='Z')&&c[4]=='\0'){
			temp[1]='[';
			temp[2]=c[3];
        }
        else {throw -2;}
		P.push_back(temp);
	}
	for(int i=0;i<P.size();i++){
		for(int j=0;j<3;j++){
			if(P[i][j]>'A'&&P[i][j]<'Z'){
				if(j==2&&P[i][j]=='\0'){
					Vn.push_back(Vn[Sum_Vn-1]);
					Vn[Sum_Vn-1]='[';
				}
				else Vn.push_back(P[i][j]);
			}
			else Vt.push_back(P[i][j]);
		}	
	}
}
FA G_3::to_FA(){
	FA a;
	vector<int>::iterator j;
	for(j=Vt.begin();j!=Vt.end();j++)
		a.Sigma.push_back(*j-'A');
	for(j=Vn.begin();j!=Vn.end();j++)
		a.Q.push_back(*j-'A');
	a.Q.push_back('['-'A');
	a.q0=s-'A';
	// vector<int *>::iterator i;//if use iterator ,then there is some error happened ,the sigsegv .
	for(int i=0;i<P.size();i++){
		vector<int>::iterator j;
		bool ck=0;
        char temp=P[i][2];
        if(temp=='~')temp=0;
		for(j=a.Delta[P[i][0]-'A'][P[i][1]-'A'].begin();j!=a.Delta[P[i][0]-'A'][P[i][1]-'A'].end();j++){
            if(*j==temp)ck=1;
		}
		if(ck==0)//keep no same.
            a.Delta[P[i][0]-'A'][P[i][1]-'A'].push_back(temp);
		}
	a.Z.push_back('['-'A');
	return a;
}
void FA::I_epsion(vector<int> & a,char i){
    for(int j=0;j<MAX;j++){
        if(Delta[i][j].size())
            for(int &k:Delta[i][j])
                if(k==0){
                    int ck=0;
                    for(int &l:a){
                        if(l==j){
                            ck=1;
                            break;
                        }
                    }
                    if(ck==0){
                        a.push_back(j);
                        I_epsion(a,j);
                    }
                }
    }
//    return a;
}
void FA::I_epsion(vector<int> & a){
	for(int &i:a){
        for(int j=0;j<MAX;j++){
			if(Delta[i][j].size())
				for(int &k:Delta[i][j])
					if(k==0){
						int ck=0;
						for(int &l:a){
							if(l==j){
								ck=1;
								break;
							}
						}
                        if(ck==0){
                            a.push_back(j);
                            I_epsion(a,j);
                        }

					}
		}
	}

//	return a;
}
FA FA::to_DFA(){
	map<int , vector<int>> I_alpha; //(alpha,alpha_set)
	vector<int> tp;
	vector<vector<int>> I;{//I(new_line)
		tp.push_back(q0);
        I_epsion(tp);
		I.push_back(tp);
	} 
	FA dfa;
	for(int line =0;line<I.size();line++){
		I_alpha.clear();
		for(int set=0;set<I[line].size();set++){//find the set path.
			int x = I[line][set];
            for(int y=0;y<MAX;y++){//find a status' path.when get a alpha ,then change to another status.
				if(Delta[x][y].size()){
				// vector<int>::iterator alpha;
				for(int &alpha:Delta[x][y]){
                    if(alpha==0)continue;//error
					bool ck=0;
					// vector<int>::iterator i;
					// for(int &j:alpha)
					for(int &i:I_alpha[alpha])
						if(i==y)ck=1;
					if(ck==0)
						I_alpha[alpha].push_back(y);
				}
			}

			}
		}

        //check new set is in I ; if true put the path in Delta;if false put in I.
		map<int , vector<int>>::iterator alpha_set;//talk about all the alpha_set.and put it in I or not.
		for(alpha_set=I_alpha.begin();alpha_set!=I_alpha.end();alpha_set++){
            tp=alpha_set->second;
            I_epsion(tp);
			int ck=0;//if ck==0 ; then alpha_set put in I ,if ck==1 then put in path ,if ck==-1 path exit ,do nothing.
			for(int new_line=0;new_line<I.size();new_line++){
				if(tp==I[new_line]){//we should define a function here . this is a simple thought.
					ck =1;
					for(int &temp:dfa.Delta[line][new_line]){
						if(&temp==0)break;
						if(temp==alpha_set->first){ck=-1;break;}
					}
					if(ck==1){
						dfa.Delta[line][new_line].push_back(alpha_set->first);
						break;
					}
				}
			} 
			if(ck==0){
				I.push_back(tp);
				ck =1;
				for(int &temp:dfa.Delta[line][I.size()-1]){
					if(&temp==0)break;
					if(temp==alpha_set->first)ck=-1;
				}
				if(ck==1)
					dfa.Delta[line][I.size()-1].push_back(alpha_set->first);
			}
		}
		int ck=1;//find set-Z.
        for(int i=0;i<Z.size();i++){
            for(int set=0;set<I[line].size();set++)
            if(I[line][set]==Z[i]){
                ck=-1;
                break;
            }
            if(ck==-1){dfa.Z.push_back(line);break;}
        }
    }
	dfa.q0=0;
	return dfa;	

}
void FA::DFA_simpfy(){
    int a[MAX];
    for(int i=0;i<MAX;i++)
		a[i]=i;
    for(int i=0;i<MAX;i++){
        for(int j=i+1;j<MAX;j++){
			bool cki=0,ckj=1;
			for(int k=0;k<Z.size();k++){
				if(Z[k]==i)cki=1;
				if(Z[k]==j)ckj=1;
			}
			if(cki==ckj)
                    if(compare(Delta[i],Delta[j],MAX)==1)together(a,i,j);
		}
	}

    for(int i=0;i<MAX;i++){
		if(a[i]!=i){
			vector<int>::iterator iter;
			for(iter=Q.begin();iter!=Q.end();iter++){//rm from Q
				if(*iter==i){
					Q.erase(iter);
					break;
				}
			}
			for(iter=Z.begin();iter<Z.end();iter++){//rm from Z
				if(*iter==i){
					Z.erase(iter);
					break;
				}
			}
            for(int j=0;j<MAX;j++)
				Delta[i][j].clear();
			continue;
		}
        for(int j=0;j<MAX;j++){
			if(Delta[i][j].size()!=0&&a[j]!=j){//the end state replace by root state.
				Delta[i][a[j]]=Delta[i][j];
				Delta[i][j].clear();
			}
		}
	}
}
void FA::c_match(const char* c){
    if(c[0]==0){throw 0;}
	int i=0,j;{//i is the position in c[],and j is the state right now.
        for(j=q0;j<MAX&&c[i]!='\0';){
			int ck=0;
			int k;
            for(k=0;k<MAX;k++){
				for(int &vvi:Delta[j][k])
                    if(vvi==c[i]){ck=-1;break;}
				if(ck==-1)break;
			}
			if(ck==-1){i++;j=k;}
			else {cout << "no ,stack!"<<endl;return; }
		}	
	}
	int ck =1;
	for(int &vi:Z)
		if(vi==j){ck=-1;break;}
	if(ck==-1)cout << "Yes!"<<endl;
	else cout << "no , string is uncompleted."<<endl;
}

void FA::store_Graphviz(string filename){
    ofstream fout(filename);
    string shell_script;
    shell_script="digraph {\n";
    for(int i=0;i<MAX;i++){
        for(int j=0;j<MAX;j++){
            if(Delta[i][j].size()){
                char left=i+'A';
                char right=j+'A';
                for(const char &weight:Delta[i][j]){

                    shell_script=shell_script+"     "+left+" -> "+right+"[label=\""+weight+"\"]\n";
//                    shell_script+=
                }
//                shell_script+=
            }
        }
    }
    shell_script+="}\n";
    fout << shell_script;
}

bool FA::is_DFA(){
    for(int i=0;i<MAX;i++)
        for(int j=0;j<MAX;j++)
            if(Delta[i][j].size())
                for(int k=j+1;k<MAX;k++)
                {
                    for(int  &l:Delta[i][j])
                        for(int  &m:Delta[i][k])
                            if(l==m)return 0;
                }
    return 1;
}
