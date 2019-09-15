using namespace std;
#include "pch.h"
#include "Interface.h"
#include <iostream>
#include "Cliente.h"
#include "Banco.h"


Banco banco;

Interface::Interface()
{
}

Interface::~Interface()
{
}

int Interface::apresentarMenu()
{

  std::cout << "\n\nMENU\n\n";
  std::cout << "1 - Cadastrar um novo cliente\n";
  std::cout << "2 - Criar uma nova Conta\n";
  std::cout << "3 - Excluir um cliente\n";
  std::cout << "4 - Excluir uma conta\n";
  std::cout << "5 - Efetuar um deposito\n";
  std::cout << "6 - Efetuar um saque\n";
  std::cout << "7 - Efetuar uma transferencia\n";
  std::cout << "8 - Cobrar uma tarifa\n";
  std::cout << "9 - Cobrar CPMF\n";
  std::cout << "10 - Obter saldo\n";
  std::cout << "11 - Obter extrato\n";
  std::cout << "12 - Listar clientes\n";
  std::cout << "13 - Listar contas\n";

  std::cout << "\n\nEntre o numero da opcao escolhida:\n\n";
  int opcaoMenu;
  cin >> opcaoMenu;
  return opcaoMenu;
}
void Interface::cadastrarCliente()
{
  string nome;
  string endereco;
  string cpf_cnpj;
  string fone;
  std::cout<< "Cadastro de novo cliente\n"
  std::cout<< "Insira o nome do cliente\n"
  std:cin >> nome;
  std::cout<< "Insira o endereco do cliente\n"
  std:cin >> endereco;
  std::cout<< "Insira o CPF ou CNPJ do cliente\n"
  std:cin >> cpf_cnpj;
  std::cout<< "Insira o telefone do cliente\n"
  std:cin >> fone;
  Cliente cliente = Cliente(nome, cpf_cnpj, endereco, fone);
}
void Interface::criarConta()
{
string cpf_cnpj;
std::cout<< "Abertura de nova conta\n"
std::cout<< "Insira o CPF ou CNPJ do cliente da conta\n"
std:cin >> cpf_cnpj;
Cliente cliente;
//banco.listarClientes(); buscar cliente pelo cpf inserido
Conta conta = Conta(cliente);
banco.criarConta(conta);  
}

void Interface::excluirCliente()
{
  int cpf_cnpj
  std::cout<< "Exclusao de cliente\n"
  std::cout<< "Insira o CPF ou CNPJ do cliente a ser excluido\n"
  std:cin >> cpf_cnpj;  
banco.deletarCliente(cpf_cnpj);
}

void Interface::excluirConta()
{
  int numConta;
  std::cout<< "Exclusao de conta\n";
  std::cout<< "Insira o numero da conta a ser excluida\n"
  std:cin >> numConta;  
  banco.deletarConta(numConta)
}
void Interface::efetuarDeposito()
{
  int valor;
  int numConta;
  std::cout<< "Deposito\n"
  std::cout<< "Insira o numero da conta a ser creditada\n";
  std::cin>>numConta;
  std::cout<< "Insira o valor do deposito\n";
  std::cin>>valor;
  banco.efetuarDeposito(numConta,valor);

}
void Interface::efetuarSaque()
{
  int valor;
  int numConta;
  std::cout<< "Saque\n"
  std::cout<< "Insira o numero da conta\n";
  std::cin>>numConta;
  std::cout<< "Insira o valor do saque\n";
  std::cin>>valor;
  banco.efetuarSaque(numConta,valor);
}
void Interface::efetuarTransferencia()
{
  int valor;
  int numContaOrigem;
  int numContaDestino;
  std::cout<< "Transferencia\n"
  std::cout<< "Insira o numero da conta de origem\n";
  std::cin>>numContaOrigem;
  std::cout<< "Insira o numero da conta de destino\n";
  std::cin>>numContaDestino;
  std::cout<< "Insira o valor da transferencia\n";
  std::cin>>valor;
  banco.efetuarTransferencia(numContaOrigem,numContaDestino,valor);

}
void Interface::cobrarTarifa()
{
  banco.cobrarTarifa();
  std::cout<< "Tarifa cobrada\n"
  
}
void Interface::cobrarCPMF()
{
  banco.cobrarCPMF();
  std::cout<< "CPFM cobrada\n"
}
void Interface::obterSaldo()
{
  int numConta;
 std::cout<< "Saldo\n"
  std::cout<< "Insira o numero da conta a ser consultada\n";
  std::cin>>numConta;
  std::cout<< "Saldo" << banco.obterSaldo(numConta); 
}
void Interface::obterExtrato()
{
  int opcao;
  bool opcaoValida = false;
  std::cout << "Obter Extrato"
  std::cout << "Qual tipo de extrato deseja obter?\n"
  std::cout << "1 - Mes atual\n2 - A partir de uma data\n3 - Entre um periodo especifico"
  std::cin >> opcao;
while(!opcaoValida) {
  if(opcao ==1){
    opcaoValida = true;
    int numConta;
    std::cout << "Digite o numero da conta a ser consultada"
    std::cin >> numConta;
    banco.obterExtrato(numConta);
    //exibir extrato

  }else if(opcao ==2){
    opcaoValida = true;
    int numConta;
    time_t dataInicio
    std::cout << "Digite o numero da conta a ser consultada"
    std::cin >> numConta;
    std::cout << "Digite a data do inicio da consulta"
    std::cin >> dataInicio;
    banco.obterExtrato(numConta, dataInicial);
    //exibir extrato
    
  }else if(opcao == 3){
    opcaoValida = true;
    int numConta;
    time_t dataInicio
    time_t dataFim
    std::cout << "Digite o numero da conta a ser consultada"
    std::cin >> numConta;
    std::cout << "Digite a data do inicio da consulta"
    std::cin >> dataInicio;
    std::cout << "Digite a data do fim da consulta"
    std::cin >> dataFim;
    banco.obterExtrato(numConta, dataInicial,dataFim);
    //exibir extrato
    
  }
}


}
void Interface::listarClientes()
{
  vector<Cliente> clientes = banco.listarClientes()
  std::cout << "Clientes";
  for (int i; i < clientes.size; i++){
    std::cout << "\nNome: "<< clientes[i].nome
    std::cout << "\nCPF/CNPJ: "<< clientes[i].cpf_cnpj
    std::cout << "\nEndereco: "<< clientes[i].endereco
    std::cout << "\nTelefone: "<< clientes[i].fone
    std::cout << "#####################################################"
  }
}
void Interface::listarContas()
{
 vector<Conta> contas = banco.listarContas()
  std::cout << "Contas";
  for (int i; i < contas.size; i++){
    std::cout << "\nConta: "<< contas[i].numConta
    std::cout << "\nCliente: "<< contas[i].cliente.nome
    std::cout << "\nSaldo: "<< contas[i].saldo
    std::cout << "#####################################################"
  } 
}