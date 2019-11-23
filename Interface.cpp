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

void Interface::inicializarAplicacao() {
	lerDB();
	apresentarMenu();
}

string Interface::getOpcaoUsuario() {
	string opcaoMenu;
	std::cout << "\nDigite a letra correspondente a opcao escolhida\n";
	std::cin >> opcaoMenu;
	std::cin.clear();

	return opcaoMenu;
}

void Interface::fecharAplicacao() {
	escreverDB(false);
}

void Interface::apresentarMenu()
{
	escreverDB(false);
	string opcaoUsuario;
	system("cls");
	std::cout << "MENU\n\n";
	std::cout << "a - Cadastrar um novo cliente\n";
	std::cout << "b - Criar uma nova conta\n";
	std::cout << "c - Excluir um cliente\n";
	std::cout << "d - Excluir uma conta\n";
	std::cout << "e - Efetuar um deposito\n";
	std::cout << "f - Efetuar um saque\n";
	std::cout << "g - Efetuar uma transferencia\n";
	std::cout << "h - Cobrar tarifa\n";
	std::cout << "i - Cobrar CPMF\n";
	std::cout << "j - Obter saldo\n";
	std::cout << "k - Obter extrato\n";
	std::cout << "l - Listar clientes\n";
	std::cout << "m - Listar contas\n";
	std::cout << "n - Salvar dados\n";
	std::cout << "o - Fechar a aplicacao\n";

	opcaoUsuario = getOpcaoUsuario();

	/*std::cin.clear();
	std::cin.ignore(INT_MAX);
	std::cin >> opcaoMenu;
	std::cin.clear();
	std::cin.ignore(INT_MAX);*/

	if (opcaoUsuario == "a") {
		cadastrarCliente();
	}

	else if (opcaoUsuario == "b") {
		criarConta();
	}

	else if (opcaoUsuario == "c") {
		excluirCliente();
	}

	else if (opcaoUsuario == "d") {
		excluirConta();
	}

	else if (opcaoUsuario == "e") {
		efetuarDeposito();
	}

	else if (opcaoUsuario == "f") {
		efetuarSaque();
	}

	else if (opcaoUsuario == "g") {
		efetuarTransferencia();
	}

	else if (opcaoUsuario == "h") {
		cobrarTarifa();
	}

	else if (opcaoUsuario == "i") {
		cobrarCPMF();
	}

	else if (opcaoUsuario == "j") {
		obterSaldo();
	}

	else if (opcaoUsuario == "k") {
		obterExtrato();
	}

	else if (opcaoUsuario == "l") {
		listarClientes(true);
	}
	else if (opcaoUsuario == "m") {
		listarContasCorrentes(false);
		listarContasPoupanca(true);
	}

	else if (opcaoUsuario == "n") {
		escreverDB(true);
	}

	else if (opcaoUsuario == "o") {
		fecharAplicacao();
	}

	else

	{
		cout << "Opcao Invalida\n";
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

	std::cout << "\nInsira o nome do cliente (sem espacos)\n";
	std::cin >> nome;
	std::cin.clear();

	std::cout << "\nInsira o endereco do cliente (sem espacos)\n";
	std::cin >> endereco;
	std::cin.clear();

	std::cout << "\nInsira o CPF ou CNPJ do cliente (sem espacos)\n";
	std::cin >> cpf_cnpj;
	std::cin.clear();

	std::cout << "\nInsira o telefone do cliente (sem espacos) \n";
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
		string tipoConta = "";
		while (tipoConta == "") {
			std::cout << "\nDigite 'cc' para conta-corrente ou 'p' para poupanca  \n";
			std::cin >> tipoConta;
			std::cin.clear();
			if (tipoConta == "cc" || tipoConta == "p")break;

			tipoConta = "";
		}

		if (tipoConta == "cc") {
			double limiteCredito = 0;
			banco.criarContaCorrente(cliente, limiteCredito);
		}
		else if (tipoConta == "p") {
			double limiteCredito = 0;

			banco.criarContaPoupanca(cliente, limiteCredito);
		}
		cout << "\n\nConta criada com sucesso";
	}

	std::cout << "\n\nPressione Enter para voltar ao menu principal\n\n";
	system("pause");
	apresentarMenu();
}

void Interface::excluirConta()
{
	int numConta = -1;
	std::cout << "Exclusao de conta\n\n";

	while (!(numConta >= 0))
	{
		std::cout << "Insira o numero da conta a ser excluida\n";
		std::cin >> numConta;
		std::cin.clear();
	}

	string tipoConta = consultarUsuarioTipoConta();

	int status = banco.excluirConta(numConta, tipoConta);
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

void Interface::excluirCliente()
{
	string cpf_cnpj;

	std::cout << "Exclusao de cliente\n\n";
	listarClientes(false);

	while (cpf_cnpj.length() == 0)
	{
		std::cout << "\nInsira o CPF ou CNPJ do cliente a ser excluido\n";
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

void Interface::escreverContasCorrentesDB() {
	ofstream myfile;
	myfile.open("ContasCorrentes.txt");

	vector <ContaCorrente> contas = banco.listarContasCorrentes();

	for (unsigned int i = 0; i < contas.size(); i++) {
		string cpf_cnpj = contas[i].getCliente().getCPF_CNPF();

		myfile << contas[i].getNumConta() << "," << contas[i].getCliente().getCPF_CNPF() << "," << contas[i].getLimiteCredito() << "," << ";";
	}
	myfile.close();
}

void Interface::escreverContasPoupancaDB() {
	ofstream myfile;
	myfile.open("ContasPoupanca.txt");
	vector <ContaPoupanca> contas = banco.listarContasPoupanca();

	for (unsigned int i = 0; i < contas.size(); i++) {
		string cpf_cnpj = contas[i].getCliente().getCPF_CNPF();
		vector<DiaBase> diasBase = contas[i].getDiasBase();
		myfile << contas[i].getNumConta() << "," << contas[i].getCliente().getCPF_CNPF() << ",";

		for (unsigned int j = 0; j < diasBase.size(); j++) {
			myfile << diasBase[j].getDia() << "," << diasBase[j].getSaldo() << ",";
		}

		myfile << ";";
	}
	myfile.close();
}

void Interface::escreverClientesDB() {
	ofstream myfile;
	myfile.open("Clientes.txt");
	vector <Cliente> clientes = banco.listarClientes();
	for (unsigned int i = 0; i < clientes.size(); i++) {
		myfile << clientes[i].getNome() << "," << clientes[i].getCPF_CNPF() << "," << clientes[i].getFone() << "," << clientes[i].getEndereco() << "," << ";";
	}

	myfile.close();
}

void Interface::escreverMovimentacoesContasPoupancaDB() {
	ofstream myfile;
	myfile.open("MovimentacoesContasPoupanca.txt");
	vector <ContaPoupanca> contasPoupanca = banco.listarContasPoupanca();
	vector <Movimentacao> movimentacoes;
	unsigned int i = 0;
	unsigned int j = 0;

	for (i = 0; i < contasPoupanca.size(); i++) {
		movimentacoes = contasPoupanca[i].getMovimentacoes();

		for (j = 0; j < movimentacoes.size(); j++) {
			int numConta = movimentacoes[j].getNumConta();
			time_t rawDataMov = movimentacoes[j].getRawDataMov();
			char debitoCredito = movimentacoes[j].getDebitoCredito();
			string descricao = movimentacoes[j].getDescricao();
			double valor = movimentacoes[j].getValor();
			string tipoConta = "p";

			myfile << numConta << "," << rawDataMov << "," << debitoCredito << "," << descricao << "," << valor << "," << tipoConta << "," << ";";
		}
	}

	myfile.close();
}
void Interface::escreverMovimentacoesContasCorrentesDB() {
	ofstream myfile;
	myfile.open("MovimentacoesContasCorrentes.txt");
	vector <ContaCorrente> contasCorrentes = banco.listarContasCorrentes();
	vector <Movimentacao> movimentacoes;
	unsigned int i = 0;
	unsigned int j = 0;

	for (i = 0; i < contasCorrentes.size(); i++) {
		movimentacoes = contasCorrentes[i].getMovimentacoes();

		for (j = 0; j < movimentacoes.size(); j++) {
			int numConta = movimentacoes[j].getNumConta();
			time_t rawDataMov = movimentacoes[j].getRawDataMov();
			char debitoCredito = movimentacoes[j].getDebitoCredito();
			string descricao = movimentacoes[j].getDescricao();
			double valor = movimentacoes[j].getValor();
			string tipoConta = "cc";

			myfile << numConta << "," << rawDataMov << "," << debitoCredito << "," << descricao << "," << valor << "," << tipoConta << "," << ";";
		}
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

	file.close();
}

void Interface::lerContasCorrentesDB() {
	ifstream file;
	string stringArquivo;
	vector<string> arrayStringContas;
	vector<string> arrayStringCamposConta;
	string stringConta;
	Cliente cliente = Cliente();

	file.open("ContasCorrentes.txt");
	getline(file, stringArquivo);

	arrayStringContas = splitString(stringArquivo, ";");

	for (unsigned int i = 0; i < arrayStringContas.size(); i++) {
		stringConta = arrayStringContas[i];

		arrayStringCamposConta = splitString(stringConta, ",");

		cliente = banco.buscaClienteCPF_CNPJ(arrayStringCamposConta[1]);

		int numeroConta = stoi(arrayStringCamposConta[0]);

		double limiteCredito = stod(arrayStringCamposConta[2]);

		banco.criarContaCorrente(cliente, numeroConta, limiteCredito);
	}

	file.close();
}

void Interface::lerContasPoupancaDB() {
	ifstream file;
	string stringArquivo;
	vector<string> arrayStringContas;
	vector<string> arrayStringCamposConta;
	string stringConta;
	Cliente cliente = Cliente();

	file.open("ContasPoupanca.txt");
	getline(file, stringArquivo);

	arrayStringContas = splitString(stringArquivo, ";");

	for (unsigned int i = 0; i < arrayStringContas.size(); i++) {
		stringConta = arrayStringContas[i];

		arrayStringCamposConta = splitString(stringConta, ",");

		cliente = banco.buscaClienteCPF_CNPJ(arrayStringCamposConta[1]);

		int numeroConta = stoi(arrayStringCamposConta[0]);
		vector<DiaBase> diasBase;

		for (unsigned int i = 2; i < arrayStringCamposConta.size(); i += 2) {
			DiaBase diaBase = DiaBase(stoi(arrayStringCamposConta[i]), stod(arrayStringCamposConta[i + 1]));
			diasBase.push_back(diaBase);
		}

		banco.criarContaPoupanca(cliente, numeroConta, diasBase);
	}

	file.close();
}

void Interface::lerMovimentacoesContasCorrentesDB() {
	ifstream file;
	string stringArquivo;
	vector<string> arrayStringMovimentacoes;
	vector<string> arrayStringCamposMovimentacao;
	string stringMovimentacao;
	Movimentacao movimentacao = Movimentacao();
	string tipoConta = "cc";

	file.open("MovimentacoesContasCorrentes.txt");
	getline(file, stringArquivo);

	arrayStringMovimentacoes = splitString(stringArquivo, ";");

	for (unsigned int i = 0; i < arrayStringMovimentacoes.size(); i++) {
		stringMovimentacao = arrayStringMovimentacoes[i];

		arrayStringCamposMovimentacao = splitString(stringMovimentacao, ",");

		string descricao = arrayStringCamposMovimentacao[3];
		char debitoCredito = arrayStringCamposMovimentacao[2][0];
		double valor = stod(arrayStringCamposMovimentacao[4]);
		int numConta = stoi(arrayStringCamposMovimentacao[0]);
		time_t dataMov = stoi(arrayStringCamposMovimentacao[1]);

		Movimentacao movimentacao = Movimentacao(descricao, debitoCredito, valor, numConta, dataMov);

		banco.restaurarMovimentacao(numConta, movimentacao, tipoConta);
	}

	file.close();
}

void Interface::lerMovimentacoesContasPoupancaDB() {
	ifstream file;
	string stringArquivo;
	vector<string> arrayStringMovimentacoes;
	vector<string> arrayStringCamposMovimentacao;
	string stringMovimentacao;
	Movimentacao movimentacao = Movimentacao();
	string tipoConta = "p";

	file.open("MovimentacoesContasPoupanca.txt");
	getline(file, stringArquivo);

	arrayStringMovimentacoes = splitString(stringArquivo, ";");

	for (unsigned int i = 0; i < arrayStringMovimentacoes.size(); i++) {
		stringMovimentacao = arrayStringMovimentacoes[i];

		arrayStringCamposMovimentacao = splitString(stringMovimentacao, ",");

		string descricao = arrayStringCamposMovimentacao[3];
		char debitoCredito = arrayStringCamposMovimentacao[2][0];
		double valor = stod(arrayStringCamposMovimentacao[4]);
		int numConta = stoi(arrayStringCamposMovimentacao[0]);
		time_t dataMov = stoi(arrayStringCamposMovimentacao[1]);

		Movimentacao movimentacao = Movimentacao(descricao, debitoCredito, valor, numConta, dataMov);

		banco.restaurarMovimentacao(stoi(arrayStringCamposMovimentacao[0]), movimentacao, tipoConta);
	}

	file.close();
}

void Interface::lerDB() {
	lerClientesDB();
	lerContasCorrentesDB();
	lerContasPoupancaDB();
	lerMovimentacoesContasCorrentesDB();
	lerMovimentacoesContasPoupancaDB();
}

void Interface::escreverDB(bool voltarAoMenu) {
	escreverClientesDB();
	escreverContasCorrentesDB();
	escreverContasPoupancaDB();
	escreverMovimentacoesContasCorrentesDB();
	escreverMovimentacoesContasPoupancaDB();

	if (voltarAoMenu) apresentarMenu();
}

void Interface::efetuarDeposito()
{
	int valor = -1;
	int numConta = -1;
	int status = 0;
	std::cout << "Deposito\n\n";
	//listarContas(false);
	while (!(numConta >= 0))
	{
		std::cout << "Insira o numero da conta a ser creditada\n";
		std::cin >> numConta;
		std::cin.clear();
	}
	while (!(valor >= 0))
	{
		std::cout << "Insira o valor do deposito\n";
		std::cin >> valor;
		std::cin.clear();
	}

	string tipoConta = consultarUsuarioTipoConta();

	status = banco.efetuarDeposito(numConta, valor, tipoConta);
	if (status == 1) {
		std::cout << "\n\nDeposito de " << valor << " reais efetuado com sucesso na conta " << numConta;
	}
	else {
		std::cout << "\n\nA conta de numero " << numConta << " nao foi encontrada";
	}
	std::cout << "\n\nPressione Enter para voltar ao menu principal\n\n";
	system("pause");
	apresentarMenu();
}

void Interface::efetuarSaque()
{
	int valor = -1;
	int numConta = -1;
	std::cout << "Saque\n\n";
	//listarContas(false);
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
	string tipoConta = consultarUsuarioTipoConta();

	int status = banco.efetuarSaque(numConta, valor, tipoConta);

	if (status == 1) {
		std::cout << "\n\nSaque de " << valor << " reais efetuado com sucesso da conta " << numConta;
	}
	else if (status == 0) {
		std::cout << "\n\nA conta de numero " << numConta << " nao possui saldo suficiente ou nao existe";
	}
	std::cout << "\n\nPressione Enter para voltar ao menu principal\n\n";
	system("pause");
	apresentarMenu();
}

string Interface::consultarUsuarioTipoConta() {
	string tipoConta = "";
	while (tipoConta == "") {
		std::cout << "\nDigite 'cc' para conta-corrente ou 'p' para poupanca ou 'e' para sair \n";
		std::cin >> tipoConta;
		std::cin.clear();
		if (tipoConta == "cc" || tipoConta == "p" || tipoConta == "e")break;

		tipoConta = "";
	}
	if (tipoConta == "e")apresentarMenu();
	return tipoConta;
}

void Interface::efetuarTransferencia()
{
	int valor;
	int status;
	int numContaOrigem;
	int numContaDestino;
	system("cls");
	std::cout << "Transferencia\n";
	std::cout << "Insira o numero da conta de origem\n";
	std::cin >> numContaOrigem;

	string tipoContaOrigem = "";
	string tipoContaDestino = "";

	while (tipoContaOrigem == "") {
		std::cout << "\nInsira o tipo da conta origem. Digite 'cc' para conta-corrente ou 'p' para poupanca ou 'e' para sair \n";
		std::cin >> tipoContaOrigem;
		std::cin.clear();
		if (tipoContaOrigem == "cc" || tipoContaOrigem == "p" || tipoContaOrigem == "e")break;

		tipoContaOrigem = "";
	}
	if (tipoContaOrigem == "e")apresentarMenu();

	std::cout << "Insira o numero da conta de destino\n";
	std::cin >> numContaDestino;

	while (tipoContaDestino == "") {
		std::cout << "\nInsira o tipo da conta destino. Digite 'cc' para conta-corrente ou 'p' para poupanca ou 'e' para sair \n";
		std::cin >> tipoContaDestino;
		std::cin.clear();
		if (tipoContaDestino == "cc" || tipoContaDestino == "p" || tipoContaDestino == "e")break;

		tipoContaDestino = "";
	}
	if (tipoContaDestino == "e")apresentarMenu();

	std::cout << "Insira o valor da transferencia\n";
	std::cin >> valor;

	status = banco.efetuarTransferencia(numContaOrigem, tipoContaOrigem, numContaDestino, tipoContaDestino, valor);
	if (status == 1) {
		std::cout << "Transferencia efetuada\n";
	}
	else {
		std::cout << "Transferencia nao efetuada, confira o saldo da conta debitada e a existencia das contas informadas\n";
	}

	std::cout << "Pressione Enter para voltar ao menu principal\n\n\n";
	system("pause");
	apresentarMenu();
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
	double saldo = 0;
	system("cls");
	std::cout << "Saldo\n\n";
	//listarContas(false);
	while (!(numConta >= 0))
	{
		std::cout << "Digite o numero da conta a ser consultada\n";
		std::cin >> numConta;
		std::cin.clear();
	}
	string tipoConta = consultarUsuarioTipoConta();

	if (tipoConta == "cc") {
		saldo = banco.obterSaldoContaCorrente(numConta);
	}
	else if (tipoConta == "p") {
		saldo = banco.obterSaldoContaPoupanca(numConta);
	}

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
	string tipoConta = consultarUsuarioTipoConta();
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
			while (!(numConta >= 0))
			{
				std::cout << "Digite o numero da conta a ser consultada\n";
				std::cin >> numConta;
				std::cin.clear();
			}

			vector <Movimentacao> movimentacoes = banco.obterExtrato(numConta, tipoConta);
			listarMovimentacoes(movimentacoes);
		}
		else if (opcao == 2)
		{
			opcaoValida = true;
			struct tm dataInicial;

			int numConta = -1;
			while (!(numConta >= 0))
			{
				std::cout << "Digite o numero da conta a ser consultada\n";
				std::cin >> numConta;
				std::cin.clear();
			}

			dataInicial = montaData('i');

			vector <Movimentacao> movimentacoes = banco.obterExtrato(numConta, dataInicial, tipoConta);
			listarMovimentacoes(movimentacoes);
		}
		else if (opcao == 3)
		{
			opcaoValida = true;
			struct tm dataInicial;
			struct tm dataFinal;
			int numConta = -1;
			while (!(numConta >= 0))
			{
				std::cout << "Digite o numero da conta a ser consultada\n";
				std::cin >> numConta;
				std::cin.clear();
			}

			dataInicial = montaData('i');
			dataFinal = montaData('f');

			vector <Movimentacao> movimentacoes = banco.obterExtrato(numConta, dataInicial, dataFinal, tipoConta);
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
	std::cout << "Clientes\n";
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

void Interface::listarContasCorrentes(bool voltarAoMenu)
{
	system("cls");
	vector<ContaCorrente> contas = banco.listarContasCorrentes();
	std::cout << "Contas Correntes\n";
	std::cout << "#####################################################\n";

	for (unsigned int i = 0; i < contas.size(); i++)
	{
		std::cout << "Conta: " << contas[i].getNumConta();
		std::cout << "\nCliente: " << contas[i].getCliente().getNome();
		std::cout << "\n#####################################################\n";
	}
	if (voltarAoMenu)
	{
		std::cout << "\n\nPressione Enter para voltar ao menu principal\n\n";
		system("pause");
		apresentarMenu();
	}
}void Interface::listarContasPoupanca(bool voltarAoMenu)
{
	vector<ContaPoupanca> contas = banco.listarContasPoupanca();
	std::cout << "\n\n\nContas Poupanca\n";
	std::cout << "#####################################################\n";

	for (unsigned int i = 0; i < contas.size(); i++)
	{
		std::cout << "Conta: " << contas[i].getNumConta();
		std::cout << "\nCliente: " << contas[i].getCliente().getNome();
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
	std::cout << "Movimentacoes\n";
	std::cout << "#####################################################";
	for (unsigned int i = 0; i < movimentacoes.size(); i++)
	{
		std::cout << "\nData: " << movimentacoes[i].getDataMov().tm_mday << "/" << movimentacoes[i].getDataMov().tm_mon + 1 << "/" << movimentacoes[i].getDataMov().tm_year + 1900;
		std::cout << "\nDescricao: " << movimentacoes[i].getDescricao() << " " << movimentacoes[i].getDebitoCredito();
		std::cout << "\nValor: " << movimentacoes[i].getValor();
		std::cout << "\n#####################################################";
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

struct tm Interface::montaData(char c) {
	struct tm data;

	if (c == 'i') {
		data.tm_isdst = 0;
		data.tm_min = 0;
		data.tm_wday = 0;
		data.tm_hour = 0;
		data.tm_sec = 0;
		std::cout << "\nDigite o ano a partir do qual deseja consultar\n";
	}
	else {
		data.tm_hour = 23;
		data.tm_min = 59;
		data.tm_sec = 59;
		std::cout << "\nDigite o ano ate o qual deseja consultar\n";
	}
	std::cin >> data.tm_year;
	data.tm_year -= 1900;
	std::cin.clear();

	if (c == 'i') {
		std::cout << "\nDigite o mes a partir do qual deseja consultar\n";
	}
	else {
		std::cout << "\nDigite o mes ate o qual deseja consultar\n";
	}
	std::cin >> data.tm_mon;
	data.tm_mon--;
	std::cin.clear();

	if (c == 'i') {
		std::cout << "\nDigite o dia a partir do qual deseja consultar\n";
	}
	else {
		std::cout << "\nDigite o dia ate o qual deseja consultar\n";
	}
	std::cin >> data.tm_mday;
	std::cin.clear();

	return data;
}