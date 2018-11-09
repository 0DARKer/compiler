#include"1.h"
#include<iostream>
using namespace std;
int main(){
	G A("wenfa.txt");
	FA a=A.to_FA();
	a.store("NFA.txt");
	FA nfa("NFA.txt");
	
	FA dfa=nfa.to_DFA();

	dfa.store("DFA.txt");
	dfa.DFA_simpfy();
	dfa.store("DFAplus.txt");
	while(1){
		string a;
		cin >> a;
		const char * b=a.c_str(); 
		dfa.c_match(b);
	}
	// DFA_SDFA();
	// while(1){
	// 	DFA_CO();
 //    }
    return 0;
}