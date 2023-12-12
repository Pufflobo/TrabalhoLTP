#ifndef CLIENTE_H_INCLUDED
#define CLIENTE_H_INCLUDED
#include<iostream>
#include<string>
#include <fstream>
#include <limits>
#include <sstream>
#include <locale>

using namespace std;

class ArvoreClientes;

void carregarArquivoParaArvore(ArvoreClientes& arvoreClientes, const string& nomeArquivo);

class Cliente{
    public:
        Cliente(int cl, bool inp, string n, string c, string t, string e);//construtor
        void verifica(bool inp);
        void adicionarNaArvore(ArvoreClientes& arvore);
        //set´s
        void setnome(string n);
        void setendereco(string e);
        void settel(string t);
        void setcpf(string c);
        void setcodigo(int cl);
        void setcodinp(bool inp);
        //get´s
        string getnome();
        string getendereco();
        string gettel();
        string getcpf();
        int getcodigo();
        bool getcodinp();
        void salvarEmArquivo(ofstream& arquivo){
            arquivo << getnome() << ""
                    << getendereco() << ""
                    << gettel() << ""
                    << getcpf() << ""
                    << getcodigo() << ""
                    << getcodinp() << "/n";

        }

    private:
        string tel;
        string endereco;
        string nome;
        string cpf;
        int codCl;
        bool codInp;
};

class ArvoreClientes
{
private:
    struct Nodo{
        Cliente* cliente;
        Nodo* esquerdaPtr;
        Nodo* direitaPtr;

        Nodo(Cliente* cliente) : cliente(cliente), esquerdaPtr(nullptr), direitaPtr(nullptr) {}
    };

    Nodo* raiz;

    Nodo* inserirCliente(Nodo* raiz, Cliente* novoCliente){
        if (raiz == nullptr){
            return new Nodo(novoCliente);
        }

        if (novoCliente->getcodigo() < raiz->cliente->getcodigo())
        {
            raiz->esquerdaPtr = inserirCliente(raiz->esquerdaPtr, novoCliente);
        }else if (novoCliente->getcodigo() > raiz->cliente->getcodigo()){
            raiz->direitaPtr = inserirCliente(raiz->direitaPtr, novoCliente);
        }
        return raiz;
    }

    Nodo* removerCliente(Nodo* raiz, int codigo) {
        if (raiz == nullptr) {
            return raiz;
        }

        if (codigo < raiz->cliente->getcodigo()) {
            raiz->esquerdaPtr = removerCliente(raiz->esquerdaPtr, codigo);
        } else if (codigo > raiz->cliente->getcodigo()) {
            raiz->direitaPtr = removerCliente(raiz->direitaPtr, codigo);
        } else {
            if (raiz->esquerdaPtr == nullptr) {
                Nodo* temp = raiz->direitaPtr;
                delete raiz;
                return temp;
            } else if (raiz->direitaPtr == nullptr) {
                Nodo* temp = raiz->esquerdaPtr;
                delete raiz;
                return temp;
            } else {
                Nodo* temp = raiz->esquerdaPtr;
                while (temp->direitaPtr != nullptr) {
                    temp = temp->direitaPtr;
                }
                raiz->cliente = temp->cliente;
                raiz->esquerdaPtr = removerCliente(raiz->esquerdaPtr, temp->cliente->getcodigo());
            }
        }
            return raiz;
    }


    void salvarRecursivamente(const Nodo* raiz, std::ofstream& arquivo) const{
        if (raiz != nullptr){
            raiz->cliente->salvarEmArquivo(arquivo);
            salvarRecursivamente(raiz->esquerdaPtr, arquivo);
            salvarRecursivamente(raiz->direitaPtr, arquivo);
        }
    }

    Nodo* buscarClientesRecursivamente(Nodo* raiz, int codigo) const{
        if (raiz == nullptr || raiz->cliente->getcodigo() == codigo){
            return raiz;
        }

        if (codigo < raiz->cliente->getcodigo()){
            return buscarClientesRecursivamente(raiz->esquerdaPtr, codigo);
        }else{
            return buscarClientesRecursivamente(raiz->direitaPtr, codigo);
        }
    }

public:
    ArvoreClientes() : raiz(nullptr) {}


    void cadastrarCliente(Cliente* novoCliente){
        raiz = inserirCliente(raiz, novoCliente);
    }

    void salvarEmArquivo(const std::string& nomeArquivo) const{
        std::ofstream arquivo(nomeArquivo);

        if (arquivo.is_open())
        {
            salvarRecursivamente(raiz, arquivo);
            arquivo.close();
        }
        else
        {
            std::cerr << "Erro ao abrir o arquivo para escrita.\n";
        }
    }

    Cliente* buscarCliente(int codigo) const{
        Nodo* resultadoBusca = buscarClientesRecursivamente(raiz, codigo);
        return (resultadoBusca != nullptr) ? resultadoBusca->cliente : nullptr;
    }

    void excluirCliente(ArvoreClientes& arvore, int codigo) {
        Cliente* cliente = arvore.buscarCliente(codigo);
        if (cliente != nullptr) {
            arvore.raiz = arvore.removerCliente(arvore.raiz , codigo);
            std::ofstream arquivo("clientes.txt", std::ios::out | std::ios::trunc);
            if (arquivo.is_open()) {
                arvore.salvarRecursivamente(arvore.raiz, arquivo);
                arquivo.close();
            } else {
                std::cout << "Não foi possível abrir o arquivo para escrita." << std::endl;
            }
        } else {
            std::cout << "Cliente não encontrado." << std::endl;
        }
    }
};

void Cliente::adicionarNaArvore(ArvoreClientes& arvore){
    Cliente* novoCliente = new Cliente(*this);
    arvore.cadastrarCliente(novoCliente);
}

void carregarArquivoParaArvore(ArvoreClientes& arvoreClientes, const std::string& nomeArquivo){
    std::ifstream arquivo(nomeArquivo, ios::binary);

    if (arquivo.is_open()){
       std ::string tel, endereco, nome, cpf;
        int codCl;
        bool codInp;

        while (arquivo >> codCl >> codInp >> nome >>  cpf >> tel >> endereco){
            // Criar um novo produto com as informações lidas do arquivo
            Cliente* novoCliente = new Cliente(codCl, codInp, nome, cpf, tel, endereco);

            // Adicionar o produto à árvore
            arvoreClientes.cadastrarCliente(novoCliente);
        }

        arquivo.close();
    }
    else{
        std::cerr << "Erro ao abrir o arquivo para leitura.\n";
    }
}

void consultarCliente(ArvoreClientes& arvore){
    // Solicitar o código ao usuário
    int codigoConsulta;
    cout << "Digite o código do produto a ser consultado: ";
    while (!(cin >> codigoConsulta) || cin.get() != '\n'){
        cerr << "Entrada inválida. Digite um número válido: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    // Buscar o produto na árvore
    Cliente* clienteEncontrado = arvore.buscarCliente(codigoConsulta);

    // Verificar se o produto foi encontrado
    if (clienteEncontrado != nullptr){
        // Exibir informações do produto
        cout << "Informações do Cliente:\n";
        cout << "Código: " << clienteEncontrado->getcodigo() << "\n";
        cout << "Nome: " << clienteEncontrado->getnome() << "\n";
        cout << "Cpf: " << clienteEncontrado->getcpf() << "\n";
        cout << "Telefone: " << clienteEncontrado->gettel() << "\n";
        cout << "Endereco: " << clienteEncontrado->getendereco() << "\n";

        cout << "Condicao de venda a prazo: ";
        if(clienteEncontrado->getcodinp()!=0)
        cout<<"endividado\n";
        else
        cout<<"nao endividado\n";


    }else{
        cerr << "Cliente não encontrado.\n";
    }
}

#endif // CLIENTE_H_INCLUDED
