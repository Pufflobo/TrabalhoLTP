#include"Venda.h"
#include <vector>
#include<string>

using namespace std;

Venda::Venda(vector<float> l, int c, string d){
    this->lista = l;
    this->cod = c;
    this->data = d;
}
float Venda::calculaValor(vector<float> l){ //essa lista deve possuir os valores de cada produto comprado
    float soma;
    for(int i=0;i<l.size();i++){
        soma += l[i];
    }
    return soma;
}

vector<float> Venda::getlista(){
    return lista;
}
int Venda::getcod(){
    return cod;
}
string Venda::getdata(){
    return data;
}
