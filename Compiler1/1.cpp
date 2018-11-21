#include"1.h"
#include<iostream>
using namespace std;
int main(){
//	G A("wenfa.txt");
//	FA a=A.to_FA();
//	a.store("NFA.txt");
//	FA nfa("NFA.txt");
	
//	FA dfa=nfa.to_DFA();

//	dfa.store("DFA.txt");
//	dfa.DFA_simpfy();
//	dfa.store("DFAplus.txt");
    try {
        FA dfa("/home/darker/Documents/compiler/build-Compiler1-Desktop-Default/DFAplus.tx");
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
    }
    return 0;
}
