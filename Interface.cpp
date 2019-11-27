#include "pch.h"
#include "Interface.h"
#include <iostream>
#include "Cliente.h"
#include "Conta.h"
#include "Banco.h"
#include <fstream>
#include <sstream>
#include "BancoServices.h"

using namespace std;
#pragma region Declarações funções não-membro
void listarDiasBase(const int& numConta);
void listarContas();
void apresentarMenu();
void cadastrarCliente();
void criarConta();
void excluirCliente();
void excluirConta();
void efetuarDeposito();
void efetuarSaque();
void efetuarTransferencia();
void cobrarTarifa();
void cobrarCPMF();
void finalizarAcaoUsuario();
void obterSaldo();
void obterExtrato();
void fecharAplicacao();
string getOpcaoUsuario();
string consultarUsuarioTipoConta();
struct tm montaData(char c);
void listarClientes();
void creditarJuros();
void listarContasCorrentes();
void listarContasPoupanca();
void listarMovimentacoes(vector <Movimentacao> movimentacoes);
void inicializarCabecalho(string titulo, bool limparTela = true);
#pragma endregion

Interface::Interface()
{
}

Interface::~Interface()
{
}

void Interface::inicializarAplicacao() {
	BancoServices.lerDB();
	apresentarMenu();
}

void fecharAplicacao() {
	BancoServices.escreverDB();
}

void apresentarMenu()
{
	BancoServices.escreverDB();

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
	std::cout << "j - Creditar juros\n";
	std::cout << "k - Obter saldo\n";
	std::cout << "l - Obter extrato\n";
	std::cout << "m - Listar clientes\n";
	std::cout << "n - Listar contas\n";
	std::cout << "o - Salvar dados\n";
	std::cout << "p - Fechar a aplicacao\n";

	opcaoUsuario = getOpcaoUsuario();

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
		creditarJuros();
	}
	else if (opcaoUsuario == "k") {
		obterSaldo();
	}

	else if (opcaoUsuario == "l") {
		obterExtrato();
	}

	else if (opcaoUsuario == "m") {
		listarClientes();
	}

	else if (opcaoUsuario == "n") {
		listarContas();
	}

	else if (opcaoUsuario == "o") {
		BancoServices.escreverDB();
		apresentarMenu();
	}

	else if (opcaoUsuario == "p") {
		fecharAplicacao();
	}

	else

	{
		cout << "Opcao Invalida\n";
		system("pause");
		apresentarMenu();
	}
}

void cadastrarCliente() {
	string nome;
	string endereco;
	string cpfcnpj;
	string fone;

	inicializarCabecalho("Menu");
	std::cout << "Cadastro de novo cliente\n";
	std::cin.clear();

	std::cout << "\nInsira o nome do cliente (sem espacos)\n";
	std::cin >> nome;
	std::cin.clear();

	std::cout << "\nInsira o endereco do cliente (sem espacos)\n";
	std::cin >> endereco;
	std::cin.clear();

	std::cout << "\nInsira o CPF ou CNPJ do cliente (sem espacos)\n";
	std::cin >> cpfcnpj;
	std::cin.clear();

	std::cout << "\nInsira o telefone do cliente (sem espacos) \n";
	std::cin >> fone;
	std::cin.clear();

	Cliente cliente = Cliente(nome, cpfcnpj, endereco, fone);
	BancoServices.banco.cadastrarCliente(cliente);

	std::cout << "\nCliente cadastrado com sucesso\n";
	finalizarAcaoUsuario();
}

void criarConta()
{
	inicializarCabecalho("Criacao de conta");
	string cpfcnpj;

	while (cpfcnpj.length() == 0)
	{
		cout << "\n\nInsira o CPF ou CNPJ do cliente da conta\n";
		std::cin >> cpfcnpj;
		std::cin.clear();
	}
	try {
		Cliente cliente = BancoServices.banco.buscaClienteCPFCNPJ(cpfcnpj);
		string tipoConta = consultarUsuarioTipoConta();

		if (tipoConta == "cc") {
			double limiteCredito = 0;
			std::cout << "\nDigite o limite de credito para a nova conta \n";
			std::cin >> limiteCredito;
			std::cin.clear();

			BancoServices.banco.criarContaCorrente(cliente, limiteCredito);
		}
		else if (tipoConta == "p") {
			BancoServices.banco.criarContaPoupanca(cliente);
		}

		cout << "\n\nConta criada com sucesso";
	}
	catch (exception excecao) {
		if (string(excecao.what()) == "ClienteNaoEncontrado")
			cout << "\n\nO cliente com CPF/CNPJ " << cpfcnpj << " nao foi encontrado em nossa base de dados\n\n";
	}
	finalizarAcaoUsuario();
}

void excluirConta() {
	inicializarCabecalho("Exclusao de conta");
	int numConta = -1;

	while (!(numConta >= 0))
	{
		std::cout << "Insira o numero da conta a ser excluida\n";
		std::cin >> numConta;
		std::cin.clear();
	}

	string tipoConta = consultarUsuarioTipoConta();
	try {
		BancoServices.banco.excluirConta(numConta, tipoConta);
		std::cout << "A conta de numero " << numConta << " foi excluida";
	}
	catch (exception excecao) {
		if (string(excecao.what()) == "ContaNaoEncontrada")
			std::cout << "A conta de numero " << numConta << " nao foi encontrada";
	}

	finalizarAcaoUsuario();
}

void efetuarSaque() {
	inicializarCabecalho("Saque");
	int valor = -1;
	int numConta = -1;
	int index = -1;
	while (!(numConta >= 0))
	{
		std::cout << "Insira o numero da conta\n";
		std::cin >> numConta;
		std::cin.clear();
	}

	string tipoConta = consultarUsuarioTipoConta();

	if (tipoConta == "cc") {
		index = BancoServices.banco.getIndexContaCorrentePorNumConta(numConta);
		if (index < 0) {
			std::cout << "\n\nA conta de numero " << numConta << " nao foi encontrada";
			std::cout << "\n\nPressione Enter para voltar ao menu principal\n\n";
			system("pause");
			apresentarMenu();
		}
	}
	else if (tipoConta == "p") {
		index = BancoServices.banco.getIndexConta(numConta);
		if (index < 0) {
			std::cout << "\n\nA conta de numero " << numConta << " nao foi encontrada";
			std::cout << "\n\nPressione Enter para voltar ao menu principal\n\n";
			system("pause");
			apresentarMenu();
		}
	}

	while (!(valor > 0))
	{
		std::cout << "Insira o valor do saque\n";
		std::cin >> valor;
		std::cin.clear();
	}

	int status = BancoServices.banco.efetuarSaque(numConta, valor, tipoConta, index);

	if (status == 1) {
		std::cout << "\n\nSaque de " << valor << " reais efetuado com sucesso da conta " << numConta;
	}
	else if (status == 0) {
		std::cout << "\n\nA conta de numero " << numConta << " nao possui saldo suficiente ou nao existe";
	}
	finalizarAcaoUsuario();
}

void efetuarDeposito() {
	inicializarCabecalho("Deposito");
	int valor = -1;
	int numConta = -1;
	int index = -1;
	string tipoConta = consultarUsuarioTipoConta();
	while (!(numConta >= 0))
	{
		std::cout << "Insira o numero da conta a ser creditada\n";
		std::cin >> numConta;
		std::cin.clear();
	}

	if (tipoConta == "cc") {
		index = BancoServices.banco.getIndexContaCorrentePorNumConta(numConta);
		if (index < 0) {
			std::cout << "\n\nA conta de numero " << numConta << " nao foi encontrada";
			std::cout << "\n\nPressione Enter para voltar ao menu principal\n\n";
			system("pause");
			apresentarMenu();
		}
	}
	else if (tipoConta == "p") {
		index = BancoServices.banco.getIndexConta(numConta);
		if (index < 0) {
			std::cout << "\n\nA conta de numero " << numConta << " nao foi encontrada";
			std::cout << "\n\nPressione Enter para voltar ao menu principal\n\n";
			system("pause");
			apresentarMenu();
		}
	}

	while (!(valor >= 0))
	{
		std::cout << "Insira o valor do deposito\n";
		std::cin >> valor;
		std::cin.clear();
	}

	BancoServices.banco.efetuarDeposito(numConta, valor, tipoConta, index);

	std::cout << "\n\nDeposito de " << valor << " reais efetuado com sucesso na conta " << numConta;
	finalizarAcaoUsuario();
}

void efetuarTransferencia()
{
	int valor;
	int status;
	int numContaOrigem;
	int numContaDestino;
	inicializarCabecalho("Transferencia");
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

	status = BancoServices.banco.efetuarTransferencia(numContaOrigem, tipoContaOrigem, numContaDestino, tipoContaDestino, valor);
	if (status == 1) {
		std::cout << "Transferencia efetuada\n";
	}
	else {
		std::cout << "Transferencia nao efetuada, confira o saldo da conta debitada e a existencia das contas informadas\n";
	}
	finalizarAcaoUsuario();
}

void cobrarTarifa()
{
	inicializarCabecalho("Cobrando tarifa");
	BancoServices.banco.cobrarTarifa();
	finalizarAcaoUsuario();
}

void cobrarCPMF()
{
	inicializarCabecalho("Cobrando CPMF");
	BancoServices.banco.cobrarCPMF();
	finalizarAcaoUsuario();
}

void obterSaldo()
{
	inicializarCabecalho("Saldo");
	int numConta = -1;
	double saldo = 0;
	string tipoConta = consultarUsuarioTipoConta();
	while (!(numConta >= 0))
	{
		std::cout << "\nDigite o numero da conta a ser consultada\n";
		std::cin >> numConta;
		std::cin.clear();
	}

	if (tipoConta == "cc") {
		saldo = BancoServices.banco.obterSaldoContaCorrente(numConta);
	}
	else if (tipoConta == "p") {
		saldo = BancoServices.banco.obterSaldoContaPoupanca(numConta);
	}

	if (saldo != -1) {
		cout << "Saldo total : " << saldo << "\n";
		if (tipoConta == "p")listarDiasBase(numConta);
	}
	else {
		cout << "\n\nNao foi possivel encontrar a conta " << numConta << "\n\n";
	}
	finalizarAcaoUsuario();
}

void obterExtrato()
{
	inicializarCabecalho("Extrato");
	int opcao;
	bool opcaoValida = false;

	string tipoConta = consultarUsuarioTipoConta();
	std::cout << "\nQual tipo de extrato deseja obter?\n";
	std::cout << "\n1 - Mes atual\n2 - A partir de uma data\n3 - Entre um periodo especifico\n";
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
				std::cout << "\nDigite o numero da conta a ser consultada\n";
				std::cin >> numConta;
				std::cin.clear();
			}

			vector <Movimentacao> movimentacoes = BancoServices.banco.obterExtrato(numConta, tipoConta);
			listarMovimentacoes(movimentacoes);
			if (tipoConta == "p")listarDiasBase(numConta);
		}
		else if (opcao == 2)
		{
			opcaoValida = true;
			struct tm dataInicial;

			int numConta = -1;
			while (!(numConta >= 0))
			{
				std::cout << "\nDigite o numero da conta a ser consultada\n";
				std::cin >> numConta;
				std::cin.clear();
			}

			dataInicial = montaData('i');

			vector <Movimentacao> movimentacoes = BancoServices.banco.obterExtrato(numConta, dataInicial, tipoConta);
			listarMovimentacoes(movimentacoes);
			if (tipoConta == "p")listarDiasBase(numConta);
		}
		else if (opcao == 3)
		{
			opcaoValida = true;
			struct tm dataInicial;
			struct tm dataFinal;
			int numConta = -1;
			while (!(numConta >= 0))
			{
				std::cout << "\nDigite o numero da conta a ser consultada\n";
				std::cin >> numConta;
				std::cin.clear();
			}

			dataInicial = montaData('i');
			dataFinal = montaData('f');

			vector <Movimentacao> movimentacoes = BancoServices.banco.obterExtrato(numConta, dataInicial, dataFinal, tipoConta);
			listarMovimentacoes(movimentacoes);
			if (tipoConta == "p")listarDiasBase(numConta);
		}
	}

	finalizarAcaoUsuario();
}

void listarClientes()
{
	inicializarCabecalho("Clientes");

	vector<Cliente> clientes = BancoServices.banco.listarClientes();
	for (unsigned int i = 0; i < clientes.size(); i++)
	{
		std::cout << "\nNome: " << clientes[i].getNome();
		std::cout << "\nCPF/CNPJ: " << clientes[i].getCPFCNPF();
		std::cout << "\nEndereco: " << clientes[i].getEndereco();
		std::cout << "\nTelefone: " << clientes[i].getFone();
		std::cout << "\n#####################################################";
	}

	finalizarAcaoUsuario();
}

void listarContas() {
	string tipoConta = consultarUsuarioTipoConta();
	if (tipoConta == "cc") {
		listarContasCorrentes();
	}
	else if (tipoConta == "p") {
		listarContasPoupanca();
	}
	finalizarAcaoUsuario();
}

void listarContasCorrentes()
{
	vector<ContaCorrente> contas = BancoServices.banco.listarContasCorrentes();
	if (contas.size() > 0) inicializarCabecalho("Contas correntes");

	for (unsigned int i = 0; i < contas.size(); i++)
	{
		std::cout << "Conta: " << contas[i].getNumConta();
		std::cout << "\nCliente: " << contas[i].getCliente().getNome();
		std::cout << "\n#####################################################\n";
	}
}

void listarContasPoupanca()
{
	vector<ContaPoupanca> contas = BancoServices.banco.listarContasPoupanca();
	if (contas.size() > 0)inicializarCabecalho("Contas poupanca");

	for (unsigned int i = 0; i < contas.size(); i++)
	{
		std::cout << "Conta: " << contas[i].getNumConta();
		std::cout << "\nCliente: " << contas[i].getCliente().getNome();
		std::cout << "\n#####################################################\n";
	}
}

void inicializarCabecalho(string titulo, bool limparTela)
{
	if (limparTela)system("cls");
	std::cout << "\n" << titulo;
	std::cout << "\n#####################################################\n\n\n";
}

void listarMovimentacoes(vector <Movimentacao> movimentacoes) {
	inicializarCabecalho("Movimentacoes");
	for (unsigned int i = 0; i < movimentacoes.size(); i++)
	{
		std::cout << "\nData: " << movimentacoes[i].getDataMov().tm_mday << "/" << movimentacoes[i].getDataMov().tm_mon + 1 << "/" << movimentacoes[i].getDataMov().tm_year + 1900;
		std::cout << "\nDescricao: " << movimentacoes[i].getDescricao() << " " << movimentacoes[i].getDebitoCredito();
		std::cout << "\nValor: " << movimentacoes[i].getValor();
		std::cout << "\n#####################################################";
	}
}

void excluirCliente()
{
	inicializarCabecalho("Exclusao de clientes", false);
	string cpfcnpj;

	while (cpfcnpj.length() == 0)
	{
		std::cout << "\nInsira o CPF ou CNPJ do cliente a ser excluido\n";
		std::cin >> cpfcnpj;
		std::cin.clear();
	}
	try {
		BancoServices.banco.excluirCliente(cpfcnpj);
		std::cout << "O cliente de CPF/CNPJ " << cpfcnpj << " foi excluido";
	}
	catch (exception excecao) {
		if (string(excecao.what()) == "ClienteComContaAtiva")
		{
			std::cout << "O cliente de CPF/CNPJ " << cpfcnpj << " ainda possui contas(s) ativa(s) e nao pode ser excluido";
		}
		else if (string(excecao.what()) == "ClienteNaoEncontrado")
		{
			std::cout << "O cliente nao foi encontrado";
		}
	}

	finalizarAcaoUsuario();
}

void listarDiasBase(const int& numConta) {
	inicializarCabecalho("Dias base", false);
	int index = BancoServices.banco.getIndexConta(numConta);
	if (index >= 0) {
		vector<DiaBase> diasBase = BancoServices.banco.obterDiasBase(numConta, index);
		if (diasBase.size() > 0) {
			for (unsigned int i = 0; i < diasBase.size(); i++) {
				std::cout << "\nDia : " << diasBase[i].getDia() << " Saldo : " << diasBase[i].getSaldo();
			}
		}
	}
	//cout << "\nTotal : " << BancoServices.banco.listarContasPoupanca()[index].getSaldo();
}

struct tm montaData(char c) {
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

string getOpcaoUsuario() {
	string opcaoMenu;
	std::cout << "\nDigite a letra correspondente a opcao escolhida\n";
	std::cin >> opcaoMenu;
	std::cin.clear();

	return opcaoMenu;
}

string consultarUsuarioTipoConta() {
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

void finalizarAcaoUsuario()
{
	cout << "\n\n";
	system("pause");
	apresentarMenu();
}

void creditarJuros() {
	inicializarCabecalho("Juros cobrados");
	BancoServices.banco.creditarJuros();
	finalizarAcaoUsuario();
}