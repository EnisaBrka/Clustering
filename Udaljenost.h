#ifndef UDALJENOST_H
#define UDALJENOST_H

class Udaljenost
{
    private:
        char prvi;
        char drugi;
        double duzina;
        int status;
    public:
        Udaljenost();
        Udaljenost(char,char,double);
        char dajPrvi(){return prvi;};
        char dajDrugi(){return drugi;};
        double dajDuzinu(){return duzina;};
        int dajStatus(){return status;};
        void PostaviStatus(int);
        virtual ~Udaljenost();
};

#endif // UDALJENOST_H
