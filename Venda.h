#ifndef VENDA_H_INCLUDED
#define VENDA_H_INCLUDED
#include<iostream>
#include<string>
#include <vector>

using namespace std;

class Venda{
public:
    venda();
    Venda(vector<float> l, int c, string d);
    virtual float calculaValor(vector<float> l);

    vector<float> getlista();
    int getcod();
    string getdata();

protected:
    vector<float> lista; //essa lista deve possuir os valores de cada produto comprado
    int cod;
    string data;
};

#endif // VENDA_H_INCLUDED
