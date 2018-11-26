#include "Skup.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

Skup::Skup()
{
    B=0;
    k=0;
}

void Skup::DodajElemenat(char el)
{
    elementi.push_back(el);
}

bool Skup::NadjiElemenat(char el)
{
    for(int i=0; i<elementi.size(); i++){
        if(elementi.at(i)==el) return true;
    }
    return false;
}

void Skup::PostaviDimD(int vs)
{
    duzine[vs][vs];
}

void Skup::PostaviUdaljenosti()
{
    ifstream ucitaj1;
    ucitaj1.open("duzine.txt");
    double duz;
    const int dim=elementi.size();
    PostaviDimD(dim);
    Skup skup1,skup2;
    for(int i=0; i<elementi.size()-1; i++){
        for(int j=i+1; j<elementi.size(); j++){
                ucitaj1>>duz;
                duzine[i][j]=duz;
             if(duz<=B){
                skup1.DodajElemenat(elementi.at(i));
                skup1.DodajElemenat(elementi.at(j));
             }
             else{
                skup1.DodajElemenat(elementi.at(i));
                skup2.DodajElemenat(elementi.at(j));
             }
            Udaljenost *nova=new Udaljenost(elementi.at(i),elementi.at(j),duz);
            DodajUdaljenost(nova);
        }
    }
    cout<<endl<<"Udaljenosti su:"<<endl;
    PrikaziUdaljenosti();
    ucitaj1.close();
    cout<<endl<<"Razvrstane udaljenosti su:"<<endl;

    Razvrstaj();

    cout<<endl;
}

void Skup::DodajUdaljenost(Udaljenost* nova)
{
    udaljenosti.push_back(nova);
}

void Skup::PrikaziUdaljenosti()
{
    for(int i=0; i<udaljenosti.size(); i++)
        {
            Udaljenost* u=udaljenosti[i];
            cout<<"prvi "<<u->dajPrvi()<<'\t'<<"drugi "<<u->dajDrugi()<<'\t'<<"duzina "<<u->dajDuzinu()<<'\t'<<"status "<<u->dajStatus()<<endl;
        }
}


void Skup::IspisiDuzine()
{
    for(int i=0; i<elementi.size()-1; i++){
        for(int j=i+1; j<elementi.size(); j++){
                cout<<duzine[i][j]<<'\t';
        }
        cout<<endl;
    }
}

double Skup::NadjiUdaljenost(char a, char b)
{
    for(int i=0; i<udaljenosti.size(); i++){
        Udaljenost* u=udaljenosti[i];
        if((u->dajPrvi()==a && u->dajDrugi()==b) || (u->dajPrvi()==b && u->dajDrugi()==a)){
                return u->dajDuzinu();
        }
    }
    return (-1.0);
}

bool Skup::NadjiUdaljenost(char b, int s)
{
    char prvi;
    for(int i=0; i<udaljenosti.size(); i++){
        Udaljenost* u=udaljenosti[i];
        if(u->dajStatus()==s){
            prvi=u->dajDrugi();
            double nadji=NadjiUdaljenost(prvi,b);
            if(nadji!=-1 && nadji<=B){
                    u->PostaviStatus(1);
                    return true;
            }
        }
    }
    return false;
}


void Skup::Razvrstaj()
{
    Udaljenost* u=udaljenosti[0];

    if(u->dajDuzinu()<=B){
        u->PostaviStatus(1);
    }
    else u->PostaviStatus(-1);

    for(int i=1; i<udaljenosti.size(); i++)
    {
            Udaljenost* u=udaljenosti[i];
            if(u->dajDuzinu()<=B && (u->dajStatus()!=1 || u->dajStatus()!=-1) && NadjiUdaljenost(u->dajDrugi(),udaljenosti[i-1]->dajStatus())==true){//){ //ako je <=B treba provjeriti ostale koji su vec u skupu 1
                u->PostaviStatus(1);
            }
            else if(u->dajDuzinu()>B) cout<<'\t';
            else{
                    if(NadjiUdaljenost(u->dajDrugi(),udaljenosti[i-1]->dajStatus())==false){
                        PovecajK();
                        u->PostaviStatus(2);
                    }
            }
    }
    cout<<endl;
    PrikaziUdaljenosti();
    if(dajK()==1) PovecajK();
}

int Skup::NadjiStatus(char a, char b)
{
    for(int i=0; i<udaljenosti.size();i++){
        Udaljenost* u=udaljenosti[i];
        if((u->dajPrvi()==a && u->dajDrugi()==b) || (u->dajPrvi()==b && u->dajDrugi()==a)) return u->dajStatus();
    }
    return -1;
}

void Skup::OdrediSkupove()
{
    cout<<endl<<"Dati skup se dijeli na "<<dajK()<<" disjunktnih skupova, čiji elementi se nalaze na udaljenosti koja je manja ili jednaka "<<dajB()<<"."<<endl;
    int k=dajK();
  while(k!=1 && k!=0){
    Skup skup1,skup2;
    for(int i=0; i<udaljenosti.size(); i++){
        Udaljenost* u=udaljenosti[i];
        if(u->dajStatus()==2){
                if(skup1.NadjiElemenat(u->dajPrvi())==false){
                    if(skup1.elementi.size()==0)skup1.DodajElemenat(u->dajPrvi());
                    else{
                    for(int j=0; j<skup1.elementi.size();j++){
                       if(NadjiStatus(skup1.elementi.at(j),u->dajPrvi())==1) skup1.DodajElemenat(u->dajPrvi());
                    }
                    }
                }
                else{
                    if(skup2.NadjiElemenat(u->dajPrvi())==false){
                        if(skup2.elementi.size()==0)skup2.DodajElemenat(u->dajPrvi());
                        else{
                            for(int j=0; j<skup2.elementi.size();j++){
                               if(NadjiStatus(skup2.elementi.at(j),u->dajPrvi())==1) skup2.DodajElemenat(u->dajPrvi());
                            }
                        }
                    }
                }
               if(skup1.NadjiElemenat(u->dajDrugi())==false){
                    if(skup1.elementi.size()==0)skup1.DodajElemenat(u->dajDrugi());
                    else{
                    for(int j=0; j<skup1.elementi.size();j++){
                       if(NadjiStatus(skup1.elementi.at(j),u->dajDrugi())==1) skup1.DodajElemenat(u->dajDrugi());
                    }
                    }
                }
                else{
                    if(skup2.NadjiElemenat(u->dajDrugi())==false){
                        if(skup2.elementi.size()==0)skup2.DodajElemenat(u->dajDrugi());
                        else{
                            for(int j=0; j<skup2.elementi.size();j++){
                               if(NadjiStatus(skup2.elementi.at(j),u->dajPrvi())==1) skup2.DodajElemenat(u->dajDrugi());
                            }
                        }
                    }
                }
                skup2.elementi.push_back(u->dajDrugi());
        }
    }

        cout<<endl<<"------------------"<<endl;
        vector<char>::iterator it;
        it=unique(skup1.elementi.begin(), skup1.elementi.end());
        skup1.elementi.resize(distance(skup1.elementi.begin(),it));
        for(it=skup1.elementi.begin(); it!=skup1.elementi.end();it++) cout<<*it<<'\t';

        cout<<endl<<"------------------"<<endl;
        it=unique(skup2.elementi.begin(), skup2.elementi.end());
        skup2.elementi.resize(distance(skup2.elementi.begin(),it));
        for(it=skup2.elementi.begin(); it!=skup2.elementi.end();it++) cout<<*it<<'\t';
        cout<<endl<<"------------------"<<endl;

    for(int i=0; i<udaljenosti.size(); i++){
        Udaljenost* u=udaljenosti[i];
        if(u->dajStatus()==2){
                cout<<endl<<"Elementi u suprotnim skupovima su: "<<u->dajPrvi()<<'\t'<<u->dajDrugi()<<endl;

                for(int i=0; i<udaljenosti.size(); i++){
                    Udaljenost* d=udaljenosti[i];
                    if(d->dajStatus()==0){
                            if(d->dajPrvi()==u->dajDrugi() && skup1.NadjiElemenat(d->dajDrugi())==false) skup1.DodajElemenat(d->dajDrugi());
                            if(d->dajDrugi()==u->dajDrugi() && skup1.NadjiElemenat(d->dajPrvi())==false) skup1.DodajElemenat(d->dajPrvi());
                    }
                    else if(NadjiUdaljenost(u->dajPrvi(),d->dajPrvi())<=B && u->dajDrugi()!=d->dajPrvi()){
                       if(skup1.NadjiElemenat(d->dajPrvi())==false) skup1.DodajElemenat(d->dajPrvi());
                    }
                    else if(NadjiUdaljenost(u->dajPrvi(),d->dajDrugi())<=B && u->dajDrugi()!=d->dajDrugi()){
                            if(skup1.NadjiElemenat(d->dajDrugi())==false) skup1.DodajElemenat(d->dajDrugi());
                    }
                    else{
                           if(skup2.NadjiElemenat(d->dajPrvi())==false){
                                for(int j=0; j<skup2.elementi.size();j++){
                                    if(NadjiStatus(skup2.elementi.at(j),d->dajPrvi())==1) skup2.DodajElemenat(d->dajPrvi());
                                }
                            }
                            else skup2.DodajElemenat(d->dajPrvi());
                            if(skup2.NadjiElemenat(d->dajDrugi())==false){
                                for(int j=0; j<skup2.elementi.size();j++){
                                    if(NadjiStatus(skup2.elementi.at(j),d->dajPrvi())==1) skup2.DodajElemenat(d->dajDrugi());
                                }
                            }
                            skup1.DodajElemenat('||');

                    }
                }
        }
    }
    k--;
    k--;
        cout<<endl<<endl<<dajK()<<" disjunktnih skupova: "<<endl;
        it=unique(skup1.elementi.begin(), skup1.elementi.end());
        skup1.elementi.resize(distance(skup1.elementi.begin(),it));
        for(it=skup1.elementi.begin(); it!=skup1.elementi.end();it++) cout<<*it<<'\t';

        it=unique(skup2.elementi.begin(), skup2.elementi.end());
        skup2.elementi.resize(distance(skup2.elementi.begin(),it));
        for(it=skup2.elementi.begin(); it!=skup2.elementi.end();it++) cout<<*it<<'\t';
        cout<<endl<<endl;

    }


}

Skup::~Skup()
{
    //dtor
}
