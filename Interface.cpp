
#include "pch.h"
#include "Interface.h"
#include <iostream>
#include "Cliente.h"
#include "Conta.h"
#include "Banco.h"
#include <fstream>
#include <sstream>

using namespace std;

Banco banco = Banco("Banco Vitor");

Interface::Interface()
{
}

Interface::~Interface()
{
}

void Interface::escreverDadosContas() {

	ofstream myfile;
	myfile.open("Contas.txt");
	vector <Conta> contas = banco.listarContas();
	for (unsigned int i = 0; i < contas.size(); i++) {
		string cpf_cnpj = contas[i].getCliente().getCPF_CNPF();
		myfile << contas[i].getNumConta() << "," << contas[i].getCliente().getCPF_CNPF() << "," << contas[i].getSaldo() << "," << ";";

	}
	myfile.close();
}

void Interface::escreverDadosClientes() {

	ofstream myfile;
	myfile.open("Clientes.txt");
	vector <Cliente> clientes = banco.listarClientes();
	for (unsigned int i = 0; i < clientes.size(); i++) {

		myfile << clientes[i].getNome() << "," << clientes[i].getCPF_CNPF() << "," << clientes[i].getFone() << "," << clientes[i].getEndereco() << "," << ";";

	}

	myfile.close();
}

void Interface::lerClientesDB() {

	ifstream file;
	string stringArquivo;
	vector<string> arrayStringClientes;
	vector<string> arrayStringCamposCliente;
	string stringCliente;
	Cliente cliente = Cliente();

	file.open("Clientes.txt");
	getline(file, stringArquivo);

	arrayStringClientes = splitString(stringArquivo, ";");

	for (unsigned int i = 0; i < arrayStringClientes.size(); i++) {

		stringCliente = arrayStringClientes[i];

		arrayStringCamposCliente = splitString(stringCliente, ",");

		cliente.setNome(arrayStringCamposCliente[0]);
		cliente.setCPF_CNPF(arrayStringCamposCliente[1]);
		cliente.setFone(arrayStringCamposCliente[2]);
		cliente.setEndereco(arrayStringCamposCliente[3]);

		banco.cadastrarCliente(cliente);


	}



}


vector<string> Interface::splitString(string str, string delimitador) {

	vector<string> arraySubStrings;
	string subString;
	size_t pos = 0;

	while ((pos = str.find(delimitador)) != std::string::npos) {
		subString = str.substr(0, pos);
		arraySubStrings.push_back(subString);
		str.erase(0, pos + delimitador.length());
	}

	return arraySubStrings;

}

void Interface::lerContasDB() {
	ifstream file;
	string stringArquivo;
	vector<string> arrayStringContas;
	vector<string> arrayStringCamposConta;
	string stringConta;
	Cliente cliente = Cliente();

	file.open("Contas.txt");
	getline(file, stringArquivo);

	arrayStringContas = splitString(stringArquivo, ";");

	for (unsigned int i = 0; i < arrayStringContas.size(); i++) {

		stringConta = arrayStringContas[i];

		arrayStringCamposConta = splitString(stringConta, ",");

		cliente = banco.buscaClienteCPF_CNPJ(arrayStringCamposConta[1]);
		banco.criarConta(cliente);
		banco.efetuarDeposito(stoi(arrayStringCamposConta[0]), stoi(arrayStringCamposConta[2]));

	}

}

void Interface::lerDados() {
	lerClientesDB();
	lerContasDB();
	/*std::cout << "\n\nPressione Enter para voltar ao menu principal\n\n";
	system("pause");*/
	//apresentarMenu();
}

void Interface::escreverDados() {

	escreverDadosClientes();
	escreverDadosContas();


	/*std::cout << "\n\nPressione Enter para voltar ao menu principal\n\n";
	system("pause");*/

	apresentarMenu();

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
	std::cout << "14 - Salvar dados\n";




	std::cout << "\n\nEntre o numero da opcao escolhida:\n\n";
	int opcaoMenu;
	std::cin >> opcaoMenu;
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
	case 14:
		escreverDados();
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
	std::cin.clear();

	std::cout << "\nInsira o nome do cliente\n";
	std::cin >> nome;
	std::cin.clear();

	std::cout << "\nInsira o endereco do cliente\n";
	std::cin >> endereco;
	std::cin.clear();

	std::cout << "\nInsira o CPF ou CNPJ do cliente\n";
	std::cin >> cpf_cnpj;
	std::cin.clear();

	std::cout << "\nInsira o telefone do cliente\n";
	std::cin >> fone;
	std::cin.clear();

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
		std::cin >> cpf_cnpj;
		std::cin.clear();
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
		std::cin >> cpf_cnpj;
		std::cin.clear();
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

	while (!(numConta > 0))
	{
		std::cout << "Insira o numero da conta a ser excluida\n";
		std::cin >> numConta;
		std::cin.clear();
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
	int valor = -1;
	int numConta = -1;
	std::cout << "Deposito\n\n";
	listarContas(false);
	while (!(numConta >= 0))
	{
		std::cout << "Insira o numero da conta a ser creditada\n";
		std::cin >> numConta;
		std::cin.clear();
	}
	while (!(valor > 0))
	{
		std::cout << "Insira o valor do deposito\n";
		std::cin >> valor;
		std::cin.clear();
	}

	banco.efetuarDeposito(numConta, valor);
	std::cout << "\n\nDeposito de " << valor << " reais efetuado com sucesso na conta " << numConta;
	std::cout << "\n\nPressione Enter para voltar ao menu principal\n\n";
	system("pause");
	apresentarMenu();

}

void Interface::efetuarSaque()
{
	int valor = -1;
	int numConta = -1;
	std::cout << "Saque\n\n";
	listarContas(false);
	while (!(numConta >= 0))
	{
		std::cout << "Insira o numero da conta\n";
		std::cin >> numConta;
		std::cin.clear();
	}
	while (!(valor > 0))
	{
		std::cout << "Insira o valor do saque\n";
		std::cin >> valor;
		std::cin.clear();
	}
	int status = banco.efetuarSaque(numConta, valor);

	if (status == 1) {
		std::cout << "\n\n Saque de " << valor << " reais efetuado com sucesso na conta " << numConta;
	}
	else if (status == 0) {
		std::cout << "\n\nA conta " << numConta << " n�o possui saldo suficiente para este saque";
	}
	std::cout << "\n\nPressione Enter para voltar ao menu principal\n\n";
	system("pause");
	apresentarMenu();
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
	std::cout << "Pressione Enter para voltar ao menu principal\n\n\n";
	system("pause");
	apresentarMenu();

}

void Interface::cobrarCPMF()
{
	banco.cobrarCPMF();
	std::cout << "CPFM cobrada\n";
	std::cout << "Pressione Enter para voltar ao menu principal\n\n\n";
	system("pause");
	apresentarMenu();
}

void Interface::obterSaldo()
{
	int numConta = -1;
	double saldo;
	system("cls");
	std::cout << "Saldo\n\n";
	listarContas(false);
	while (!(numConta >= 0))
	{
		std::cout << "Digite o numero da conta a ser consultada\n";
		std::cin >> numConta;
		std::cin.clear();
	}
	saldo = banco.obterSaldo(numConta);
	if (saldo != -1) {
		std::cout << "\n\nSaldo\n\n" << saldo;
	}
	else {
		cout << "\n\nNao foi possivel encontrar a conta " << numConta << "\n\n";
	}
	std::cout << "\n\nPressione Enter para voltar ao menu principal\n\n";
	system("pause");
	apresentarMenu();

}

void Interface::obterExtrato()
{
	int opcao;
	bool opcaoValida = false;
	std::cout << "Obter Extrato\n\n";
	std::cout << "Qual tipo de extrato deseja obter?\n";
	std::cout << "1 - Mes atual\n2 - A partir de uma data\n3 - Entre um periodo especifico\n";
	std::cin.clear();
	std::cin >> opcao;
	std::cin.clear();


	while (!opcaoValida)
	{
		if (opcao == 1)
		{
			opcaoValida = true;
			int numConta = -1;
			listarContas(false);
			while (!(numConta >= 0))
			{
				std::cout << "Digite o numero da conta a ser consultada\n";
				std::cin >> numConta;
				std::cin.clear();
			}
			vector <Movimentacao> movimentacoes = banco.obterExtrato(numConta);
			listarMovimentacoes(movimentacoes);


		}
		else if (opcao == 2)
		{
			opcaoValida = true;
			struct tm dataInicial;

			int numConta = -1;
			listarContas(false);
			while (!(numConta >= 0))
			{
				std::cout << "Digite o numero da conta a ser consultada\n";
				std::cin >> numConta;
				std::cin.clear();
			}
			dataInicial.tm_isdst = 0;
			dataInicial.tm_min = 0;
			dataInicial.tm_wday = 0;
			dataInicial.tm_hour = 0;
			dataInicial.tm_min = 0;
			dataInicial.tm_sec = 0;
			std::cout << "\nDigite o ano a partir do qual deseja consultar\n";
			std::cin >> dataInicial.tm_year;
			dataInicial.tm_year -= 1900;
			std::cin.clear();
			std::cout << "\nDigite o mes a partir do qual deseja consultar\n";
			std::cin >> dataInicial.tm_mon;
			dataInicial.tm_mon--;
			std::cin.clear();
			std::cout << "\nDigite o dia a partir do qual deseja consultar\n";
			std::cin >> dataInicial.tm_mday;
			std::cin.clear();

			vector <Movimentacao> movimentacoes = banco.obterExtrato(numConta, dataInicial);
			listarMovimentacoes(movimentacoes);
		}
		else if (opcao == 3)
		{
			opcaoValida = true;
			int numConta = -1;
			listarContas(false);
			while (!(numConta >= 0))
			{
				std::cout << "Digite o numero da conta a ser consultada\n";
				std::cin >> numConta;
				std::cin.clear();
			}
			vector <Movimentacao> movimentacoes = banco.obterExtrato(numConta);
			listarMovimentacoes(movimentacoes);
		}
	}

	std::cout << "\n\nPressione Enter para voltar ao menu principal\n\n";
	system("pause");
	apresentarMenu();
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
	std::cout << "#####################################################\n";

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


void Interface::listarMovimentacoes(vector <Movimentacao> movimentacoes) {
	system("cls");
	std::cout << "Movimentacoes\n\n";
	std::cout << "#####################################################";
	for (unsigned int i = 0; i < movimentacoes.size(); i++)
	{
		std::cout << "\nData: " << movimentacoes[i].getDataMov().tm_mday << "/" << movimentacoes[i].getDataMov().tm_mon + 1 << "/" << movimentacoes[i].getDataMov().tm_year + 1900;
		std::cout << "\nDescricao: " << movimentacoes[i].getDescricao() << " " << movimentacoes[i].getDebitoCredito();
		std::cout << "\nValor: " << movimentacoes[i].getValor();
		std::cout << "\n#####################################################";
	}
}
