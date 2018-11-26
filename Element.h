#ifndef ELEMENT_H
#define ELEMENT_H


class Element
{
    private:
        char x;
    public:
        Element();
        Element(char);
        char dajX(){return x;};
        virtual ~Element();
};

#endif // ELEMENT_H
