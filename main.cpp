#include"cliente.cpp"
#include"cliente.h"
#include"venda.cpp"
#include"venda.h"
#include"produto.cpp"
#include"produto.h"
#include<iostream>
#include<stdlib.h>
#include<vector>

using namespace std;

vector <int> vetorProdutos;
int tamProdutos=0;

//Funcoes dos Menus Secundários

//Menu de Produtos: Funcoes
void produtoAdiciona(){
    int cod;
    string desc;
    float valcompra;
    float valvenda;
    int qtd;
    int qtdmin;

    cout<<"Codigo do produto:";
    cin>>cod;
    cout<<"Valor de compra:";
    cin>>valcompra;
    cout<<"Valor de Venda:";
    cin>>valvenda;
    cout<<"Descricao do produto:";
    cin>>desc;
    cout<<"Quantidade minima no estoque:";
    cin>>qtdmin;
    cout<<"Quantidade no estoque:";
    cin>>qtd;

    Produto novo(cod, desc, valcompra, valvenda, qtd, qtdmin);

    novo.setcod(cod);
    novo.setdesc(desc);
    novo.setvalcompra(valcompra);
    novo.setvalvenda(valvenda);
    novo.setqtd(qtd);
    novo.setqtdmin(qtdmin);

    vetorProdutos.push_back(novo.getcod());
    tamProdutos++;
}
void produtoConsulta(){
    int cod, aux=0;

    if(tamProdutos==0)
        cout<<"Estoque vazio!";
    else{
        cout<<"Produtos em estoque:"<<tamProdutos<<endl;
        cout<<"Insira o codigo do produto:";
        cin>>cod;

        for(aux;aux<=tamProdutos;aux++){
            if(cod==vetorProdutos[aux]){
                cout<<"Produto "<<vetorProdutos[aux]<<" encontrado!\n";
                //cout<<getcod();
                break;
            }
            if(aux==tamProdutos){
                cout<<"Produto nao encontrado!\n";
                break;
            }
        }
    }


}
void produtoExclui(){
}
void produtoAltera(){
}
//-------------------------





//Menus Secundários
void manutencao_produtos(){
	int aux=0;
	system("cls");
	do{
        system("cls");
		cout<<"----Manutencao de produtos----\n";
		cout<<"1: Adcionar um Produto\n";
		cout<<"2: Consultar um Produto\n";
		cout<<"3: Excluir um Produto\n";
		cout<<"4: Alterar um Produto\n";
		cout<<"0: Retornar\n\n";
		cin>>aux;

		switch (aux){
			case 1:
				produtoAdiciona();
				break;
			case 2:
				produtoConsulta();
				cout<<endl;
                system("pause");
				break;
			case 3:
				//profutoExclui();
				break;
			case 4:
				//produtoAltera();
				break;
			case 0:
				system ("cls");
				break;
            default:
				cout<<"Opcao invalida\n";
				break;
		}
	}while(aux!=0);
}

void manutencao_clientes(){
	int aux;
	system("cls");
	do{
		cout<<"----Menu de Clientes----\n";
		cout<<"1:Adicionar Cliente \n";
		cout<<"2:Consultar Cliente \n";
		cout<<"3:Excluir Cliente \n";
		cout<<"4:Alterar Cliente \n";
		cout<<"0:Retornar\n\n";
		cin>>aux;

		switch (aux){
			case 1:
				//clienteAdiciona();
				break;
			case 2:
				//clienteConsulta();
				break;
			case 3:
				//clienteExclui();
				break;
			case 4:
				//clienteAltera();
				break;
			case 0:
				system ("cls");
				break;
            default:
				cout<<"Opcao invalida/n";
				break;

		}
	}while (aux!=0);
}

void manutencao_vendas(){
	//nao precisa de menu
	//inserir codigo direto
	
	int nota_aux;
	
	
	
}

void manutencao_consultas(){
	int aux;
	system("cls");
	do{
		cout<<"----Menu de Consultas----\n";
		cout<<"1:Consultar Vendas\n";
		cout<<"2:Consultar Estoque\n";
		cout<<"0: Retornar\n\n";
		cin>>aux;

		switch (aux){
			default:
				cout<<"Opcao invalida/n";
				exit;
			case 1:
				//consulta_vendas();
				exit;
			case 2:
				//consulta_estoque();
				exit;
			case 0:
				system ("cls");

		}
	}while (aux!=0);
}

//Menu Principal
int main(){

	int n_aux=0;
	system("cls");
	do{
		cout<<"----Menu Principal----\n";
		cout<<"1:Manutencao de Produtos \n";
		cout<<"2:Manutencao de Clientes\n";
		cout<<"3:Realizar Vendas\n";
		cout<<"4:Realizar Consultas\n";
		cout<<"0:Encerrar programa\n\n";
		cin>>n_aux;

		switch (n_aux){
			case 1:
				manutencao_produtos();
				break;
			case 2:
				manutencao_clientes();
				break;
			case 3:
				manutencao_vendas();
				break;
			case 4:
				manutencao_consultas();
				break;
			case 0:
				system ("cls");
				cout<<"Programa encerrado";
				break;
            default:
				cout<<"Opcao invalida/n";
				break;

		}
	}while (n_aux!=0);

	return 0;
}
