
#include "pch.h"
#include "Interface.h"
#include <iostream>
#include "Cliente.h"
#include "Banco.h"

using namespace std;

Banco banco = Banco("Banco Vitor");

Interface::Interface()
{
}

Interface::~Interface()
{
}

void Interface::apresentarMenu()
{
  system("cls");
  std::cout << "MENU\n\n";
  std::cout << "1 - Cadastrar um novo cliente\n";
  std::cout << "2 - Criar uma nova Conta\n";
  std::cout << "3 - Excluir um cliente\n";
  std::cout << "4 - Excluir uma conta\n";
  std::cout << "5 - Efetuar um deposito\n";
  std::cout << "6 - Efetuar um saque\n";
  std::cout << "7 - Efetuar uma transferencia\n";
  std::cout << "8 - Cobrar tarifa\n";
  std::cout << "9 - Cobrar CPMF\n";
  std::cout << "10 - Obter saldo\n";
  std::cout << "11 - Obter extrato\n";
  std::cout << "12 - Listar clientes\n";
  std::cout << "13 - Listar contas\n";

  std::cout << "\n\nEntre o numero da opcao escolhida:\n\n";
  int opcaoMenu;
  cin >> opcaoMenu;
  switch (opcaoMenu)
  {
  case 1:
    cadastrarCliente();
    break;
  case 2:
    criarConta();
    break;
  case 3:
    excluirCliente();
    break;
  case 4:
    excluirConta();
    break;
  case 5:
    efetuarDeposito();
    break;
  case 6:
    efetuarSaque();
    break;
  case 7:
    efetuarTransferencia();
    break;
  case 8:
    cobrarTarifa();
    break;
  case 9:
    cobrarCPMF();
    break;
  case 10:
    obterSaldo();
    break;
  case 11:
    obterExtrato();
    break;
  case 12:
    listarClientes(true);
    break;
  case 13:
    listarContas(true);
    break;

  default:
    cout << "Opcao Invalida";
    system("pause");
    apresentarMenu();
  }
}

void Interface::cadastrarCliente()
{
  string nome;
  string endereco;
  string cpf_cnpj;
  string fone;
  system("cls");
  std::cout << "Cadastro de novo cliente\n";
  cin.clear();

  std::cout << "\nInsira o nome do cliente\n";
  cin >> nome;
  cin.clear();

  std::cout << "\nInsira o endereco do cliente\n";
  cin >> endereco;
  cin.clear();

  std::cout << "\nInsira o CPF ou CNPJ do cliente\n";
  cin >> cpf_cnpj;
  cin.clear();

  std::cout << "\nInsira o telefone do cliente\n";
  cin >> fone;
  cin.clear();

  Cliente cliente = Cliente(nome, cpf_cnpj, endereco, fone);
  banco.cadastrarCliente(cliente);

  std::cout << "\nCliente cadastrado com sucesso\n";
  std::cout << "Pressione Enter para voltar ao menu principal\n\n\n";
  system("pause");
  apresentarMenu();
}
void Interface::criarConta()
{
  string cpf_cnpj;
  std::cout << "Abertura de nova conta\n\n";

  listarClientes(false);

  while (cpf_cnpj.length() == 0)
  {
    cout << "\n\nInsira o CPF ou CNPJ do cliente da conta\n";
    cin >> cpf_cnpj;
    cin.clear();
  }
  Cliente cliente = banco.buscaClienteCPF_CNPJ(cpf_cnpj);
  if (cliente.getNome() == "CLIENTE_NAO_ENCONTRADO")
  {
    cout << "\n\nO cliente com CPF/CNPJ " << cpf_cnpj << " nao foi encontrado em nossa base de dados\n\n";
  }
  else
  {
    banco.criarConta(cliente);
    cout << "\n\nConta criada com sucesso\n\n";
  }

  std::cout << "\n\nPressione Enter para voltar ao menu principal\n\n";
  system("pause");
  apresentarMenu();
}

void Interface::excluirCliente()
{
  string cpf_cnpj;
  std::cout << "Exclusao de cliente\n\n";
  listarClientes(false);

  while (cpf_cnpj.length() == 0)
  {
    std::cout << "Insira o CPF ou CNPJ do cliente a ser excluido\n";
    cin >> cpf_cnpj;
    cin.clear();
  }
  int status = banco.excluirCliente(cpf_cnpj);
  if (status == 1)
  {
    std::cout << "O cliente de CPF/CNPJ " << cpf_cnpj << " foi excluido";
  }
  else if (status == 2)
  {
    std::cout << "O cliente de CPF/CNPJ " << cpf_cnpj << " ainda possui contas(s) ativa(s) e nao pode ser excluido";
  }
  else
  {
    std::cout << "O cliente nao foi encontrado";
  }
  std::cout << "\n\nPressione Enter para voltar ao menu principal\n\n";
  system("pause");
  apresentarMenu();
}

void Interface::excluirConta()
{
  int numConta = -1;
  std::cout << "Exclusao de conta\n\n";

  while (!numConta > 0)
  {
    std::cout << "Insira o numero da conta a ser excluida\n";
    cin >> numConta;
    cin.clear();
  }
  int status = banco.excluirConta(numConta);
  if (status == 1)
  {
    std::cout << "A conta de numero " << numConta << " foi excluida";
  }
  else
  {
    std::cout << "A conta de numero " << numConta << " nao foi encontrada";
  }
  std::cout << "\n\nPressione Enter para voltar ao menu principal\n\n";
  system("pause");
  apresentarMenu();
}
void Interface::efetuarDeposito()
{
  int valor=-1;
  int numConta=-1;
  std::cout << "Deposito\n\n";
  while (!numConta > 0)
  {
    std::cout << "Insira o numero da conta a ser creditada\n";
    cin >> numConta;
    cin.clear();
  }
  while (!valor > 0)
  {
    std::cout << "Insira o numero da conta a ser creditada\n";
    cin >> valor;
    cin.clear();
  }
  
  banco.efetuarDeposito(numConta, valor);
}
void Interface::efetuarSaque()
{
  int valor;
  int numConta;
  std::cout << "Saque\n";
  std::cout << "Insira o numero da conta\n";
  std::cin >> numConta;
  std::cout << "Insira o valor do saque\n";
  std::cin >> valor;
  banco.efetuarSaque(numConta, valor);
}
void Interface::efetuarTransferencia()
{
  int valor;
  int numContaOrigem;
  int numContaDestino;
  std::cout << "Transferencia\n";
  std::cout << "Insira o numero da conta de origem\n";
  std::cin >> numContaOrigem;
  std::cout << "Insira o numero da conta de destino\n";
  std::cin >> numContaDestino;
  std::cout << "Insira o valor da transferencia\n";
  std::cin >> valor;
  banco.efetuarTransferencia(numContaOrigem, numContaDestino, valor);
}
void Interface::cobrarTarifa()
{
  banco.cobrarTarifa();
  std::cout << "Tarifa cobrada\n";
}
void Interface::cobrarCPMF()
{
  banco.cobrarCPMF();
  std::cout << "CPFM cobrada\n";
}
void Interface::obterSaldo()
{
  int numConta;
  double saldo;
  std::cout << "Saldo\n";
  std::cout << "Insira o numero da conta a ser consultada\n";
  std::cin >> numConta;
  saldo = banco.obterSaldo(numConta);
  std::cout << "Saldo" << saldo;
}
void Interface::obterExtrato()
{
  int opcao;
  bool opcaoValida = false;
  std::cout << "Obter Extrato";
  std::cout << "Qual tipo de extrato deseja obter?\n";
  std::cout << "1 - Mes atual\n2 - A partir de uma data\n3 - Entre um periodo especifico";
  std::cin >> opcao;
  while (!opcaoValida)
  {
    if (opcao == 1)
    {
      opcaoValida = true;
      int numConta;
      std::cout << "Digite o numero da conta a ser consultada";
      std::cin >> numConta;
      banco.obterExtrato(numConta);
      //exibir extrato
    }
    else if (opcao == 2)
    {
      opcaoValida = true;
      int numConta;
      time_t dataInicio;
      std::cout
          << "Digite o numero da conta a ser consultada";
      std::cin >>
          numConta;
      std::cout << "Digite a data do inicio da consulta";
      std::cin >> dataInicio;
      banco.obterExtrato(numConta, dataInicio);
      //exibir extrato
    }
    else if (opcao == 3)
    {
      opcaoValida = true;
      int numConta;
      time_t dataInicio;
      time_t dataFim;
      std::cout
          << "Digite o numero da conta a ser consultada";
      std::cin >>
          numConta;
      std::cout << "Digite a data do inicio da consulta";
      std::cin >> dataInicio;
      std::cout << "Digite a data do fim da consulta";
      std::cin >> dataFim;
      banco.obterExtrato(numConta, dataInicio, dataFim);
      //exibir extrato
    }
  }
}
void Interface::listarClientes(bool voltarAoMenu)
{
  system("cls");
  vector<Cliente> clientes = banco.listarClientes();
  std::cout << "Clientes\n\n";
  std::cout << "#####################################################";
  for (unsigned int i = 0; i < clientes.size(); i++)
  {
    std::cout << "\nNome: " << clientes[i].getNome();
    std::cout << "\nCPF/CNPJ: " << clientes[i].getCPF_CNPF();
    std::cout << "\nEndereco: " << clientes[i].getEndereco();
    std::cout << "\nTelefone: " << clientes[i].getFone();
    std::cout << "\n#####################################################";
  }
  if (voltarAoMenu)
  {
    std::cout << "\n\nPressione Enter para voltar ao menu principal\n\n";
    system("pause");
    apresentarMenu();
  }
}
void Interface::listarContas(bool voltarAoMenu)
{
  system("cls");
  vector<Conta> contas = banco.listarContas();
  std::cout << "Contas\n\n";
  std::cout << "#####################################################";

  for (unsigned int i = 0; i < contas.size(); i++)
  {
    std::cout << "\nConta: " << contas[i].getNumConta();
    std::cout << "\nCliente: " << contas[i].getCliente().getNome();
    std::cout << "\nSaldo: " << contas[i].getSaldo();
    std::cout << "\n#####################################################\n";
  }
  if (voltarAoMenu)
  {
    std::cout << "\n\nPressione Enter para voltar ao menu principal\n\n";
    system("pause");
    apresentarMenu();
  }
}
//
//Cliente Interface::buscaCliente(string _cpf_cnpj) {
//
//		for (auto i = banco.listarClientes().begin() ; i != banco.listarClientes().end(); i++)
//		{
//
//			if ((*i).getCPF_CNPF() == _cpf_cnpj)
//			{
//				return (*i);
//			}
//		}
//
//		Cliente clienteNaoEncontrado = Cliente("CLIENTE_NAO_ENCONTRADO", "CLIENTE_NAO_ENCONTRADO", "CLIENTE_NAO_ENCONTRADO", "CLIENTE_NAO_ENCONTRADO");
//		return clienteNaoEncontrado;
//}
