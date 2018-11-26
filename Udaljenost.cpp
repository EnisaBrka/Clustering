#include "Udaljenost.h"
#include <iostream>
using namespace std;

Udaljenost::Udaljenost()
{
    //ctor
}

Udaljenost::Udaljenost(char p,char d,double duz)
{
    prvi=p;
    drugi=d;
    duzina=duz;
    status=0;
}


void Udaljenost::PostaviStatus(int s)
{
    this->status=s;
}



Udaljenost::~Udaljenost()
{
    //dtor
}
