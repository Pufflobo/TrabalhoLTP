#include"Venda_a_prazo.h"
#include"venda.h"
#include<iostream>
#include<string>
#include <vector>
using namespace std;


Venda_a_prazo::Venda_a_prazo(vector<float> l, int c, string d, float t, int p, int cli) : Venda(l, c, d){
    cliente = cli;
    parcelas = p;
    taxa = t;
}

float Venda_a_prazo::calculaValor(vector<float> l){
    float soma;
    for(int i=0;i<l.size();i++){
        soma += l[i];
    }
    soma = soma * taxa;

    return soma;
}

int Venda_a_prazo::getcliente(){
    return cliente;
}
string Venda_a_prazo::getdatav(){
    return data;
}
int Venda_a_prazo::getparcelas(){
    return parcelas;
}
float Venda_a_prazo::gettaxa(){
    return taxa;
}
