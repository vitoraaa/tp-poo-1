#include "pch.h"
#include "Banco.h"
#include "Cliente.h"
#include "Conta.h"
#include <time.h>
#include <algorithm>
#include "ContaCorrente.h"
#include "ContaPoupanca.h"

Banco::Banco(string _nomeBanco)
{
	nomeBanco = _nomeBanco;
}

Banco::~Banco()
{
}
Banco::Banco()
{
}

Cliente Banco::buscaClienteCPF_CNPJ(string _cpf_cnpj)
{
	for (auto i = clientes.begin(); i != clientes.end(); i++)
	{
		if ((*i).getCPF_CNPF() == _cpf_cnpj)
		{
			return (*i);
		}
	}
	Cliente clienteNaoEncontrado = Cliente("CLIENTE_NAO_ENCONTRADO", "CLIENTE_NAO_ENCONTRADO", "CLIENTE_NAO_ENCONTRADO", "CLIENTE_NAO_ENCONTRADO");
	return clienteNaoEncontrado;
}

void Banco::cadastrarCliente(const Cliente _cliente)
{
	clientes.push_back(_cliente);
}

void Banco::criarContaCorrente(const Cliente _cliente, string tipoConta, double limiteCredito = 0)
{
	vector<int> numContasExistentes;
	for (unsigned int i = 0; i < contasCorrentes.size(); i++) {
		numContasExistentes.push_back(contasCorrentes[i].getNumConta());
	}

	ContaCorrente conta = ContaCorrente(_cliente, numContasExistentes, limiteCredito);
	contasCorrentes.push_back(conta);
}
//Conta conta = Conta(_cliente, numContasExistentes);
}
void Banco::criarContaCorrente(const Cliente _cliente, int _numConta, double limiteCredito = 0)
{
	ContaCorrente conta = ContaCorrente(_cliente, _numConta, limiteCredito);
	contasCorrentes.push_back(conta);
}

void Banco::criarContaPoupanca(const Cliente _cliente, double limiteCredito = 0)
{
	vector<int> numContasExistentes;
	for (unsigned int i = 0; i < contasPoupanca.size(); i++) {
		numContasExistentes.push_back(contasPoupanca[i].getNumConta());
	}
	ContaPoupanca conta = ContaPoupanca(_cliente, numContasExistentes, vector<DiaBase>());
	contasPoupanca.push_back(conta);

	//Conta conta = Conta(_cliente, numContasExistentes);
}
void Banco::criarContaPoupanca(const Cliente _cliente, int _numConta, vector<DiaBase> diasBase)
{
	ContaPoupanca conta = ContaPoupanca(_cliente, _numConta, diasBase);
	contasPoupanca.push_back(conta);
}

int Banco::excluirCliente(const string _cpf_cnpj)
{
	auto i = clientes.begin();

	for (auto i = clientes.begin(); i != clientes.end(); i++)
	{
		if ((*i).getCPF_CNPF() == _cpf_cnpj)
		{
			if (buscarContaPoupancaPorCliente(*i).size() == 0 && buscarContaCorrentePorCliente(*i).size() == 0)   //o cliente nao tem nenhuma conta
			{
				clientes.erase(i);
				return 1;
			}
			else
			{
				return 2;
			}
		}
	}
	return 0;
}

int Banco::excluirConta(int _numConta, string tipoConta)
{
	if (tipoConta == "cc") {
		auto i = contasCorrentes.begin();

		for (auto i = contasCorrentes.begin(); i != contasCorrentes.end(); i++)
		{
			if ((*i).getNumConta() == _numConta)
			{
				contasCorrentes.erase(i);
				return 1;
			}
		}
	}
	else if (tipoConta == "p") {
		auto i = contasPoupanca.begin();

		for (auto i = contasPoupanca.begin(); i != contasPoupanca.end(); i++)
		{
			if ((*i).getNumConta() == _numConta)
			{
				contasPoupanca.erase(i);
				return 1;
			}
		}
	}
	return 0;
}

int Banco::efetuarDeposito(int _numConta, int _valor, string tipoConta)
{
	if (tipoConta == "cc") {
		int index = getIndexContaCorrentePorNumConta(_numConta);
		if (index >= 0) {
			contasCorrentes[index].creditarConta(_valor, "Deposito");
			return 1;
		}
	}
	else {
		int index = getIndexContaPoupancaPorNumConta(_numConta);
		if (index >= 0) {
			contasPoupanca[index].creditarConta(_valor, "Deposito");
			return 1;
		}
	}
	return 0;
}

int Banco::efetuarSaque(int _numConta, int _valor, string tipoConta)
{
	if (tipoConta == "cc") {
		int status;
		int index = getIndexContaCorrentePorNumConta(_numConta);
		if (index >= 0) {
			status = contasCorrentes[index].debitarConta(_valor, "Saque");
			return status;
		}
	}
	else {
		int status;
		int index = getIndexContaPoupancaPorNumConta(_numConta);
		if (index >= 0) {
			status = contasPoupanca[index].debitarConta(_valor, "Saque");
		}	return status;
	}
	return 0;
}

int Banco::efetuarTransferencia(int _numContaOrigem, int _numContaDestino, int _valor)
{
	string descricao;
	int status;
	descricao = "Transferencia para a conta " + std::to_string(_numContaDestino);
	int index = getIndexContaPorNumConta(_numContaOrigem);
	if (index != -1) {
		status = contas[index].debitarConta(_valor, descricao);
		if (status == 1) {
			index = getIndexContaPorNumConta(_numContaDestino);

			if (index != -1) {
				descricao = "Transferencia da conta " + std::to_string(_numContaOrigem);
				contas[index].creditarConta(_valor, descricao);
				return 1;
			}
		}
	}

	return 0;
}

void Banco::cobrarTarifa()
{
	for (unsigned int i = 0; i < contas.size(); i++) {
		contas[i].debitarConta(15, "Cobranca de tarifa");
	}
}

void Banco::cobrarCPMF()
{
	for (unsigned int i = 0; i < contas.size(); i++) {
		double valorCobrado = calcularCPMF(i);
		contas[i].debitarConta(valorCobrado, "Cobranca de CPMF");
	}
}

double Banco::obterSaldo(int _numConta)
{
	int index = getIndexContaPorNumConta(_numConta);
	if (index != -1) {
		return contas[index].getSaldo();
	}
	else {
		return -1;
	}
}

vector <Movimentacao> Banco::obterExtrato(int _numConta)
{
	int index = getIndexContaPorNumConta(_numConta);
	vector<Movimentacao> movimentacoesFiltradas;

	if (index >= 0) {
		vector <Movimentacao> movimentacoes = contas[index].getMovimentacoes();

		time_t rawNow = time(0);
		struct tm mesAtual;
		struct tm dataMov;
		localtime_s(&mesAtual, &rawNow);

		for (unsigned int i = 0; i < movimentacoes.size(); i++) {
			dataMov = movimentacoes[i].getDataMov();
			if (dataMov.tm_mon == mesAtual.tm_mon && dataMov.tm_year == mesAtual.tm_year) {
				movimentacoesFiltradas.push_back(movimentacoes[i]);
			}
		}
	}
	return movimentacoesFiltradas;
}

vector<Movimentacao> Banco::obterExtrato(int _numConta, struct tm _dataInicial)

{
	int index = getIndexContaPorNumConta(_numConta);
	vector<Movimentacao> movimentacoesFiltradas;

	if (index >= 0) {
		vector<Movimentacao> movimentacoes = contas[index].getMovimentacoes();

		for (unsigned int i = 0; i < movimentacoes.size(); i++) {
			time_t rawDataMov = mktime(&movimentacoes[i].getDataMov());
			time_t rawDataInicial = mktime(&_dataInicial);

			if (rawDataMov >= rawDataInicial) {
				movimentacoesFiltradas.push_back(movimentacoes[i]);
			}
		}
	}
	return movimentacoesFiltradas;
}

vector<Movimentacao> Banco::obterExtrato(int _numConta, struct tm _dataInicial, struct tm _dataFinal)
{
	time_t rawDataInicial = mktime(&_dataInicial);
	time_t rawDataFinal = mktime(&_dataFinal);
	time_t rawDataMov;
	vector<Movimentacao> movimentacoesFiltradas;
	int index = getIndexContaPorNumConta(_numConta);
	if (index >= 0) {
		vector<Movimentacao> movimentacoes = contas[index].getMovimentacoes();

		for (unsigned int i = 0; i < movimentacoes.size(); i++) {
			rawDataMov = mktime(&movimentacoes[i].getDataMov());
			if (rawDataMov >= rawDataInicial && rawDataMov <= rawDataFinal) {
				movimentacoesFiltradas.push_back(movimentacoes[i]);
			}
		}
	}

	return movimentacoesFiltradas;
}

vector<Cliente> Banco::listarClientes()
{
	return clientes;
}

vector<ContaCorrente> Banco::listarContasCorrentes()
{
	return contasCorrentes;
}
vector<ContaPoupanca> Banco::listarContasPoupanca()
{
	return contasPoupanca;
}

vector<Conta> Banco::buscarContaPorCliente(Cliente _cliente)
{
	vector<Conta> contasCliente;
	for (auto i = contas.begin(); i != contas.end(); i++)
	{
		if ((*i).getCliente().getCPF_CNPF() == _cliente.getCPF_CNPF())
		{
			contasCliente.push_back(*i);
		}
	}
	return contasCliente;
}

vector<Conta> Banco::buscarContaPorCliente(Cliente _cliente)
{
	vector<Conta> contasCliente;
	for (auto i = contas.begin(); i != contas.end(); i++)
	{
		if ((*i).getCliente().getCPF_CNPF() == _cliente.getCPF_CNPF())
		{
			contasCliente.push_back(*i);
		}
	}
	return contasCliente;
}

int Banco::getIndexContaPorNumConta(int _numConta)
{
	for (unsigned int i = 0; i < contas.size(); i++)
	{
		if (contas[i].getNumConta() == _numConta)
		{
			return i;
		}
	}
	return -1;
}
int Banco::getIndexContaPorNumConta(int _numConta, vector<int> numContasExistentes)
{
	for (unsigned int i = 0; i < numContasExistentes.size(); i++)
	{
		if (numContasExistentes[i] == _numConta)
		{
			return i;
		}
	}
	return -1;
}

double Banco::calcularCPMF(int indexConta) {
	double valorCalculado = 0;

	time_t rawNow = time(0);
	time_t rawdataAtualMenosSeteDias = rawNow - (7 * 24 * 60 * 60);
	struct tm dataAtualMenosSeteDias;
	vector<Movimentacao> movimentacoesUltimosSeteDias;

	localtime_s(&dataAtualMenosSeteDias, &rawdataAtualMenosSeteDias);

	movimentacoesUltimosSeteDias = obterExtrato(contas[indexConta].getNumConta(), dataAtualMenosSeteDias);

	for (unsigned int i = 0; i < movimentacoesUltimosSeteDias.size(); i++) {
		if (movimentacoesUltimosSeteDias[i].getDebitoCredito() == 'D') {
			valorCalculado += movimentacoesUltimosSeteDias[i].getValor() * 0.0038;
		}
	}

	return valorCalculado;
}

void Banco::restaurarMovimentacao(int _numConta, Movimentacao _movimentacao) {
	int index = getIndexContaPorNumConta(_numConta);

	if (index >= 0) {
		contas[index].restaurarMovimentacao(_movimentacao);
		if (_movimentacao.getDebitoCredito() == 'C') {
			contas[index].restaurarSaldo(_movimentacao.getValor());
		}
		else if (_movimentacao.getDebitoCredito() == 'D') {
			contas[index].restaurarSaldo(-_movimentacao.getValor());
		}
	}
}