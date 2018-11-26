#ifndef SKUP_H
#define SKUP_H
#include <vector>
#include "Udaljenost.h"
using namespace std;

class Skup
{
    private:
        vector<char> elementi;
        double duzine[50][50];
        vector<Udaljenost*> udaljenosti;
        int B;
        int k;
    public:
        Skup();
        int dajB(){return B;};
        int dajK(){return k;};
        void PostaviB(int b){B=b;};
        void PovecajK(){k=k+1;};
        void PostaviDimD(int);

        void DodajElemenat(char);
        bool NadjiElemenat(char);

        void PostaviUdaljenosti(); //kreira udaljenosti ucitane iz fajla
        void DodajUdaljenost(Udaljenost*); //dodaje udaljenosti u vektor
        void PrikaziUdaljenosti(); //ispisuje elemente vektora udaljenosti
        double NadjiUdaljenost(char,char); //traži udaljenost izmedju dva elementa
        bool NadjiUdaljenost(char,int); // traži el sa istim statusom koji je proslijedjen, i onda traži udaljenost, ako postoji <=B, proslijedjenog el i nadjenog el.

        void IspisiDuzine(); //ispisuje ucitane duzine, koje su spremljen u vektor elementi
        void Razvrstaj(); //razvrstava elemente koji su <=B (status 1) i >B (status 0) i el. koji ne mogu biti u istom skupu (status 2)

        int NadjiStatus(char,char);

        void OdrediSkupove();

        virtual ~Skup();
};

#endif // SKUP_H
