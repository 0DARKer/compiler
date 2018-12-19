#include"1.h"
#include<iostream>
using namespace std;
int main(){
    try {
        G_3 g("/home/darker/1.txt");
        FA nfa=g.to_FA();
//        nfa.store("/home/darker/nfa.txt");
//        cout << nfa.is_DFA()<<endl;
        FA dfa=nfa.to_DFA();
//        cout << dfa.is_DFA()<<endl;
//        dfa.store("/home/darker/dfa.txt");
        dfa.DFA_simpfy();
//        dfa.store("/home/darker/dfaP.txt");
        dfa.store_Graphviz("/home/darker/1.dot");
        system("dot -Tpng /home/darker/1.dot -o /home/darker/1.png");
        system("gwenview /home/darker/1.png -f &");
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
        if(j==0){
            cout << "exit program...";
            return 0;
        }
    }
    return 0;
}
