#ifndef CLIENTE_H_INCLUDED
#define CLIENTE_H_INCLUDED
#include<iostream>
#include<string>
#include <fstream>
#include <limits>
#include <sstream>
#include <locale>

using namespace std;

class Cliente{
    public:
        Cliente(int cl, bool inp, string n, string c, string t, string e);//construtor
        void verifica(bool inp);

        //set´s
        void setnome(string n);
        void setendereco(string e);
        void settel(string t);
        void setcpf(string c);
        void setcod(int cl);
        void setcodinp(bool inp);
        //get´s
        string getnome();
        string getendereco();
        string gettel();
        string getcpf();
        int getcod();
        bool getcodinp();

    private:
        string tel;
        string endereco;
        string nome;
        string cpf;
        int codCl;
        bool codInp;
};

#endif // CLIENTE_H_INCLUDED
