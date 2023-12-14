#include <iostream>
#include "Produto.h"
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <iomanip>
#include <algorithm>

using namespace std;

class Venda
{
public:
    Venda(int tipo, int codigoCliente, int numParcelas, float taxaJuros);
    float calculaValor();
    void gerarNumeroNotaFiscal();

    vector<Produto>& getLista() // Correção aqui
    {
        return lista;
    }

    int getTipoVenda(){
        return tipoVenda;
    }

    int getCodigoCliente(){
        return codigoCliente;
    }
    int getNumParcelas(){
        return numParcelas;
    }
    float getTaxaJuros(){
        return taxaJuros;
    }
    string getNumeroNotaFiscal(){
        return numeroNotaFiscal;
    }
    string getDataEmissao(){
        return dataEmissao;
    }

private:
    vector<Produto> lista;
    int tipoVenda;
    int codigoCliente;
    int numParcelas;
    float taxaJuros;
    string numeroNotaFiscal;
    string dataEmissao;
};



class NodoVenda
{
public:
    Venda* venda;
    NodoVenda* esquerdaPtr;
    NodoVenda* direitaPtr;

    NodoVenda(Venda* venda) : venda(venda), esquerdaPtr(nullptr), direitaPtr(nullptr) {}
};

class ArvoreVendas
{
private:
    NodoVenda* raiz;

    NodoVenda* inserirVenda(NodoVenda* raiz, Venda* novaVenda);
    void salvarRecursivamente(NodoVenda* raiz, ofstream& arquivo);
    void consultarVendas(NodoVenda* raiz) {
        if (raiz == nullptr) {
            return;
        }
        consultarVendas(raiz->esquerdaPtr);

        // Imprimimos os detalhes da venda
        cout << "Detalhes da Venda: " << endl;
        cout << "Código do Cliente: " << raiz->venda->getCodigoCliente() << endl;
        cout << "Número de Parcelas: " << raiz->venda->getNumParcelas() << endl;
        cout << "Taxa de Juros: " << raiz->venda->getTaxaJuros() << endl;
        cout << "Número da Nota Fiscal: " << raiz->venda->getNumeroNotaFiscal() << endl;

         consultarVendas(raiz->direitaPtr);
    }
public:
    ArvoreVendas() : raiz(nullptr) {}
    void cadastrarVenda(Venda* novaVenda);
    void salvarEmArquivo(string& nomeArquivo);
    void consultaVendas(){
        consultarVendas(raiz);
    }
};

class ArvoreProdutosVendidos
{
public:
    void adicionarProdutoVendido(int codigoProduto, int quantidade);
    int obterQuantidadeProdutoNaData(int codigoProduto, string data);

private:
    struct ProdutoVendido
    {
        int codigoProduto;
        int quantidade;
        string data;

        ProdutoVendido(int codigoProduto, int quantidade, string data)
            : codigoProduto(codigoProduto), quantidade(quantidade), data(data) {}
    };

    vector<ProdutoVendido> produtosVendidos;
};

Venda::Venda(int tipo, int codigoCliente, int numParcelas, float taxaJuros)
    : tipoVenda(tipo), codigoCliente(codigoCliente), numParcelas(numParcelas), taxaJuros(taxaJuros),
      numeroNotaFiscal(""), dataEmissao("")
{
    gerarNumeroNotaFiscal();

    time_t now = time(0);
    tm* localTime = localtime(&now);
    stringstream ss;
    ss << put_time(localTime, "%d/%m/%y - %H:%M:%S");
    dataEmissao = ss.str();
}


void salvarVendasEmArquivo(ArvoreVendas& arvoreVendas,string& nomeArquivo)
{
    arvoreVendas.salvarEmArquivo(nomeArquivo);
}


NodoVenda* ArvoreVendas::inserirVenda(NodoVenda* raiz, Venda* novaVenda)
{
    if (raiz == nullptr)
    {
        return new NodoVenda(novaVenda);
    }

    if (novaVenda->getNumeroNotaFiscal() < raiz->venda->getNumeroNotaFiscal())
    {
        raiz->esquerdaPtr = inserirVenda(raiz->esquerdaPtr, novaVenda);
    }
    else if (novaVenda->getNumeroNotaFiscal() > raiz->venda->getNumeroNotaFiscal())
    {
        raiz->direitaPtr = inserirVenda(raiz->direitaPtr, novaVenda);
    }

    return raiz;
}


void ArvoreVendas::cadastrarVenda(Venda* novaVenda)
{
    raiz = inserirVenda(raiz, novaVenda);
}

void ArvoreVendas::salvarRecursivamente(NodoVenda* raiz, ofstream& arquivo)
{
    if (raiz != nullptr)
    {
        arquivo << raiz->venda->getNumeroNotaFiscal() << " "
                << raiz->venda->getDataEmissao() << " "
                << raiz->venda->getTipoVenda() << " "
                << raiz->venda->getCodigoCliente() << " "
                << raiz->venda->getNumParcelas() << " "
                << raiz->venda->getTaxaJuros() << "\n";
        salvarRecursivamente(raiz->esquerdaPtr, arquivo);
        salvarRecursivamente(raiz->direitaPtr, arquivo);
    }
}

void ArvoreVendas::salvarEmArquivo(string& nomeArquivo)
{
    ofstream arquivo(nomeArquivo);

    if (arquivo.is_open())
    {
        salvarRecursivamente(raiz, arquivo);
        arquivo.close();
    }
    else
    {
        cout << "+======================================+\n";
        cerr << "| Erro ao abrir o arquivo para escrita.|\n";
        cout << "+======================================+\n";
    }
}

void ArvoreProdutosVendidos::adicionarProdutoVendido(int codigoProduto, int quantidade)
{
    time_t now = time(0);
    tm* localTime = localtime(&now);
    stringstream ss;
    ss << put_time(localTime, "%d/%m/%y");
    string data = ss.str();

    produtosVendidos.push_back(ProdutoVendido(codigoProduto, quantidade, data));
}

int ArvoreProdutosVendidos::obterQuantidadeProdutoNaData(int codigoProduto, string data)
{
    int quantidadeTotal = 0;

    for (auto& produtoVendido : produtosVendidos)
    {
        if (produtoVendido.codigoProduto == codigoProduto && produtoVendido.data == data)
        {
            quantidadeTotal += produtoVendido.quantidade;
        }
    }

    return quantidadeTotal;
}



void realizaVendas(ArvoreVendas& arvoreVendas,vector<Produto>& produtos)
{
    char continuar;
    do
    {
        int tipoVenda;
        cout << "Insira o tipo de venda (1 para à vista, 2 para a prazo): ";
        cin >> tipoVenda;

        int numParcelas = 0;
        float taxaJuros = 0.0f;

        if (tipoVenda == 2)
        {
            cout << "Insira o número de parcelas: ";
            cin >> numParcelas;

            cout << "Insira a taxa de juros (%): ";
            cin >> taxaJuros;
            taxaJuros /= 100.0f;
        }

        Venda novaVenda(tipoVenda, 1, numParcelas, taxaJuros);

        for (int j = 0; j < 3; ++j)
        {
            cout << "Insira o código do produto: " << j + 1 << ": ";
            int codigoProduto;
            cin >> codigoProduto;

            auto it = find_if(produtos.begin(), produtos.end(), [codigoProduto](Produto& p)
            {
                return p.getCodigo() == codigoProduto;
            });

            if (it != produtos.end())
            {
                novaVenda.getLista().push_back(*it);
            }
            else
            {
                cout << "+========================+\n";
                cout << "| Produto não encontrado |\n";
                cout << "+========================+\n";
                cout << "| Opções:                |\n";
                cout << "| 1. Tente novamente     |\n";
                cout << "| 2. Sair                |\n";
                cout << "+========================+\n";
                cout << "Digite: ";

                int opcao;
                cin >> opcao;

                if (opcao == 2)
                {
                    break;
                }
                else
                {
                    --j;
                }
            }
        }


        arvoreVendas.cadastrarVenda(&novaVenda);

        cout << "Deseja realizar outra venda? (S para sim, qualquer outra tecla para sair): ";
        cin >> continuar;
    }
    while (continuar == 'S' || continuar == 's');
}

void Venda::gerarNumeroNotaFiscal()
{
    // Nota fiscal é declarada a partir de um numero aleatorio
    stringstream ss;
    ss << "NF" << setfill('0') << setw(6) << rand() % 1000000;
    numeroNotaFiscal = ss.str();
}


