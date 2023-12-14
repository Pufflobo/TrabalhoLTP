#include"Cliente.h"
#include<iostream>
#include<string>

using namespace std;

Cliente::Cliente(int cl, bool inp, string n, string c, string t, string e){
    codCl = cl;
    codInp = inp;
    nome = n;
    cpf = c;
    tel = t;
    endereco = e;
}

void Cliente::verifica(bool inp){
    if(inp == true){
        cout<<"O cliente possui pagamentos pendentes, compra a prazo bloqueada";
    }else{
        cout<<"O cliente não possui dividas, compra a prazo liberada";
    }
}



//set´s modificarão os valores privados
void Cliente::setnome(string n){
    nome = n;
}
void Cliente::setendereco(string e){
    endereco = e;
}
void Cliente::settel(string t){
    tel = t;
}
void Cliente::setcpf(string c){
    cpf = c;
}
void Cliente::setcodigo(int cl){
    codCl = cl;
}
void Cliente::setcodinp(bool inp){
    codInp = inp;
}

//get´s retornarão os valores privados
string Cliente::getnome(){
    return nome;
}
string Cliente::getendereco(){
    return endereco;
}
string Cliente::gettel(){
    return tel;
}
string Cliente::getcpf(){
    return cpf;
}
int Cliente::getcodigo(){
    return codCl;
}
bool Cliente::getcodinp(){
    return codInp;
}
