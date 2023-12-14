#include"Produto.h"
#include<iostream>
#include<string>

using namespace std;

Produto::Produto(int c, string d, float compra, float venda, int qtd, int qmn){
    codigo = c;
    descricao = d;
    valorcompra = compra;
    valorvenda = venda;
    quantidadeestoque = qtd;
    quantidademinima = qmn;
}

//set´s
void Produto::setCodigo(int cod){
    codigo = cod;
}
void Produto::setQuantidadeEstoque(int qtd){
     quantidadeestoque = qtd;
}
void Produto::setQuantidadeMinima(int qmn){
    quantidadeestoque = qmn;
}
void Produto::setValorVenda(float v){
    valorvenda = v;
}
void Produto::setValorCompra(float c){
    valorcompra = c;
}
void Produto::setDescricao(string d){
    descricao = d;
}

//get´s
int Produto::getCodigo(){
    return codigo;
}
int Produto::getQuantidadeEstoque(){
    return quantidadeestoque;
}
int Produto::getQuantidadeMinima(){
    return quantidademinima;
}
float Produto::getValorVenda(){
    return valorvenda;
}
float Produto::getValorCompra(){
    return valorcompra;
}
string Produto::getDescricao(){
    return descricao;
}
