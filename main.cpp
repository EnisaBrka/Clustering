#include <iostream>
#include <fstream>
#include <vector>
#include "Skup.h"

using namespace std;

int main(){

    Skup skup;
    ifstream ucitaj;
    ucitaj.open("podaci.txt");
    char a;
    int b;
    ucitaj>>b;
    skup.PostaviB(b);
    cout<<"B je: "<<b<<endl;
    while(true){
        ucitaj>>a;
        if(ucitaj.eof()) break;
        skup.DodajElemenat(a);
    }
    ucitaj.close();
    skup.PostaviUdaljenosti();
    skup.IspisiDuzine();
    skup.OdrediSkupove();

    return 0;

}
