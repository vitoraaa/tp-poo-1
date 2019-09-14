#include "pch.h"
#include "Interface.h"
#include <iostream>
using namespace std;

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
}
void Interface::criarConta()
{
}
void Interface::excluirCliente()
{
}
void Interface::excluirConta()
{
}
void Interface::efetuarDeposito()
{
}
void Interface::efetuarSaque()
{
}
void Interface::efetuarTransferencia()
{
}
void Interface::cobrarTarifa()
{
}
void Interface::cobrarCPMF()
{
}
void Interface::obterSaldo()
{
}
void Interface::obterExtrato()
{
}
void Interface::listarClientes()
{
}
void Interface::listarContas()
{
}