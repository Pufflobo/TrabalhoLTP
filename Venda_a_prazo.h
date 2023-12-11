#ifndef VENDA_A_PRAZO_H_INCLUDED
#define VENDA_A_PRAZO_H_INCLUDED
#include "venda.h"
#include<iostream>
#include<string>
#include <vector>

using namespace std;

class Venda_a_prazo:public Venda{
public:
    Venda_a_prazo(vector<float> l, int c, string d, float t, int p, int cli);
    float calculaValor(vector<float> l);

    int getcliente();
    string getdatav();
    int getparcelas();
    float gettaxa();

private:
    int cliente;
    int parcelas;
    float taxa;
};


#endif // VENDA_A_PRAZO_H_INCLUDED
