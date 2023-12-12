#ifndef PRODUTO_H_INCLUDED
#define PRODUTO_H_INCLUDED
#include<iostream>
#include<string>
#include <fstream>
#include <limits>
#include <sstream>
#include <locale>

using namespace std;

class ArvoreProdutos;
void carregarArquivoParaArvore(ArvoreProdutos& arvoreProdutos, const std::string& nomeArquivo);


class Produto{
public:
    Produto(int cod, string d,float compra, float venda, int qtd, int qmn);

    void adicionarNaArvore(ArvoreProdutos& arvore);

    void setCodigo(int cod);
    void setQuantidadeEstoque(int qtd);
    void setQuantidadeMinima(int qmn);
    void setValorVenda(float v);
    void setValorCompra(float c);
    void setDescricao(string d);

    int getCodigo();
    int getQuantidadeEstoque();
    int getQuantidadeMinima();
    float getValorVenda();
    float getValorCompra();
    string getDescricao();

     void salvarEmArquivo(std::ofstream& arquivo)
    {
        arquivo << getCodigo() << " "
                << getDescricao() << " "
                << getValorCompra() << " "
                << getValorVenda() << " "
                << getQuantidadeMinima() << " "
                << getQuantidadeEstoque() << "\n";
    }

private:
    int codigo;
    float valorcompra;
    float valorvenda;
    string descricao;
    int quantidademinima;
    int quantidadeestoque;
};

class ArvoreProdutos
{
private:
    struct Nodo{
        Produto* produto;
        Nodo* esquerdaPtr;
        Nodo* direitaPtr;

        Nodo(Produto* produto) : produto(produto), esquerdaPtr(nullptr), direitaPtr(nullptr) {}
    };

    Nodo* raiz;

    Nodo* inserirProduto(Nodo* raiz, Produto* novoProduto){
        if (raiz == nullptr){
            return new Nodo(novoProduto);
        }

        if (novoProduto->getCodigo() < raiz->produto->getCodigo())
        {
            raiz->esquerdaPtr = inserirProduto(raiz->esquerdaPtr, novoProduto);
        }else if (novoProduto->getCodigo() > raiz->produto->getCodigo()){
            raiz->direitaPtr = inserirProduto(raiz->direitaPtr, novoProduto);
        }
        return raiz;
    }




    void salvarRecursivamente(const Nodo* raiz, std::ofstream& arquivo) const{
        if (raiz != nullptr){
            raiz->produto->salvarEmArquivo(arquivo);
            salvarRecursivamente(raiz->esquerdaPtr, arquivo);
            salvarRecursivamente(raiz->direitaPtr, arquivo);
        }
    }

    Nodo* buscarProdutoRecursivamente(Nodo* raiz, int codigo) const{
        if (raiz == nullptr || raiz->produto->getCodigo() == codigo){
            return raiz;
        }

        if (codigo < raiz->produto->getCodigo()){
            return buscarProdutoRecursivamente(raiz->esquerdaPtr, codigo);
        }else{
            return buscarProdutoRecursivamente(raiz->direitaPtr, codigo);
        }
    }

     Nodo* removerProduto(Nodo* raiz, int codigo) {
        if (raiz == nullptr) {
            return raiz;
        }

        if (codigo < raiz->produto->getCodigo()) {
            raiz->esquerdaPtr = removerProduto(raiz->esquerdaPtr, codigo);
        } else if (codigo > raiz->produto->getCodigo()) {
            raiz->direitaPtr = removerProduto(raiz->direitaPtr, codigo);
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
                Nodo* temp = buscarProdutoRecursivamente(raiz->esquerdaPtr, codigo);
                while (temp != nullptr && temp->direitaPtr != nullptr) {
                    temp = temp->direitaPtr;
                }
                raiz->produto = temp->produto;
                raiz->esquerdaPtr = removerProduto(raiz->esquerdaPtr, temp->produto->getCodigo());
            }
        }
        return raiz;
    }

public:
    ArvoreProdutos() : raiz(nullptr) {}


    void cadastrarProduto(Produto* novoProduto){
        raiz = inserirProduto(raiz, novoProduto);
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

    Produto* buscarProduto(int codigo) const{
        Nodo* resultadoBusca = buscarProdutoRecursivamente(raiz, codigo);
        return (resultadoBusca != nullptr) ? resultadoBusca->produto : nullptr;
    }

    void excluirProduto(ArvoreProdutos& arvore, int codigo) {
    Produto* produto = arvore.buscarProduto(codigo);
    if (produto != nullptr) {
        arvore.raiz = arvore.removerProduto(arvore.raiz, codigo);
        std::ofstream arquivo("produto.txt", std::ios::out | std::ios::trunc);
        if (arquivo.is_open()) {
            arvore.salvarRecursivamente(arvore.raiz, arquivo);
            arquivo.close();
        } else {
            std::cout << "Não foi possível abrir o arquivo para escrita." << std::endl;
        }
    } else {
        std::cout << "Produto não encontrado." << std::endl;
    }
    }

};

void Produto::adicionarNaArvore(ArvoreProdutos& arvore){
    Produto* novoProduto = new Produto(*this);
    arvore.cadastrarProduto(novoProduto);
}

void carregarArquivoParaArvore(ArvoreProdutos& arvoreProdutos, const std::string& nomeArquivo){
    std::ifstream arquivo(nomeArquivo, ios::binary);

    if (arquivo.is_open()){
        int codigo;
        std::string descricao;
        float valorCompra, valorVenda;
        int quantidadeMinima, quantidadeEstoque;

        while (arquivo >> codigo >> descricao >> valorCompra >> valorVenda >> quantidadeMinima >> quantidadeEstoque){
            // Criar um novo produto com as informações lidas do arquivo
            Produto* novoProduto = new Produto(codigo, descricao, valorCompra, valorVenda, quantidadeMinima, quantidadeEstoque);

            // Adicionar o produto à árvore
            arvoreProdutos.cadastrarProduto(novoProduto);
        }

        arquivo.close();
    }
    else{
        std::cerr << "Erro ao abrir o arquivo para leitura.\n";
    }
}

void consultarProduto(ArvoreProdutos& arvore){
    // Solicitar o código ao usuário
    int codigoConsulta;
    cout << "Digite o código do produto a ser consultado: ";
    while (!(cin >> codigoConsulta) || cin.get() != '\n'){
        cerr << "Entrada inválida. Digite um número válido: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    // Buscar o produto na árvore
    Produto* produtoEncontrado = arvore.buscarProduto(codigoConsulta);

    // Verificar se o produto foi encontrado
    if (produtoEncontrado != nullptr){
        // Exibir informações do produto
        cout << "Informações do Produto:\n";
        cout << "Código: " << produtoEncontrado->getCodigo() << "\n";
        cout << "Descrição: " << produtoEncontrado->getDescricao() << "\n";
        cout << "Valor de Compra: " << produtoEncontrado->getValorCompra() << "\n";
        cout << "Valor de Venda: " << produtoEncontrado->getValorVenda() << "\n";
        cout << "Quantidade Mínima: " << produtoEncontrado->getQuantidadeMinima() << "\n";
        cout << "Quantidade em Estoque: " << produtoEncontrado->getQuantidadeEstoque() << "\n";
    }else{
        cerr << "Produto não encontrado.\n";
    }
}
#endif // PRODUTO_H_INCLUDED
