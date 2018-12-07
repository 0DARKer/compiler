#include"1.h"
#include<iostream>
using namespace std;
int main(){
    try {
        G_3 g("/home/darker/1.txt");
        FA nfa=g.to_FA();
        FA dfa=nfa.to_DFA();
        dfa.DFA_simpfy();
        while(1){
            string a;
            cin >> a;
            const char * b=a.c_str();
            dfa.c_match(b);
        }
    }
    catch(int j){
        if(j==-1){
            cout << "error to open file"<<endl;
            return 0;
        }
        if(j==-2){
            cout << "not a G_3"<<endl;
            return 0;
        }
    }
    return 0;
}
