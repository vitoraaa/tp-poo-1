#include "pch.h"
#include "Banco.h"
#include "Cliente.h"
#include "Conta.h"
#include <time.h>
#include <algorithm>
#include "ContaCorrente.h"
#include "ContaPoupanca.h"

Banco::Banco(string nomeBanco)
{
	nomeBanco = nomeBanco;
}

Banco::~Banco()
{
}
Banco::Banco()
{
}

void preencherNumContaExistentes(const vector<ContaPoupanca>& contasPoupanca, vector<int>& numContasExistentes) {
	for (unsigned int i = 0; i < contasPoupanca.size(); i++) {
		numContasExistentes.push_back(contasPoupanca[i].getNumConta());
	}
}
Cliente Banco::buscaClienteCPFCNPJ(const string& cpfcnpj)
{
	for (auto i = clientes.begin(); i != clientes.end(); i++)
	{
		if ((*i).getCPFCNPF() == cpfcnpj)
		{
			return (*i);
		}
	}
	Cliente clienteNaoEncontrado = Cliente("CLIENTENAOENCONTRADO", "CLIENTENAOENCONTRADO", "CLIENTENAOENCONTRADO", "CLIENTENAOENCONTRADO");
	return clienteNaoEncontrado;
}

void Banco::cadastrarCliente(const Cliente& cliente)
{
	clientes.push_back(cliente);
}

void Banco::criarContaCorrente(const Cliente& cliente, const double& limiteCredito)
{
	vector<int> numContasExistentes;
	for (unsigned int i = 0; i < contasCorrentes.size(); i++) {
		numContasExistentes.push_back(contasCorrentes[i].getNumConta());
	}

	ContaCorrente conta = ContaCorrente(cliente, numContasExistentes, limiteCredito);
	contasCorrentes.push_back(conta);
}

void Banco::criarContaCorrente(const Cliente& cliente, const int& numConta, const double& limiteCredito = 0)
{
	ContaCorrente conta = ContaCorrente(cliente, numConta, limiteCredito);
	contasCorrentes.push_back(conta);
}

void Banco::criarContaPoupanca(const Cliente& cliente)
{
	vector<int> numContasExistentes = vector<int>();
	preencherNumContaExistentes(contasPoupanca, numContasExistentes);
	ContaPoupanca conta = ContaPoupanca(cliente, numContasExistentes);
	contasPoupanca.push_back(conta);
}

void Banco::criarContaPoupanca(const Cliente& cliente, const int& numConta, const vector<DiaBase>& diasBase)
{
	ContaPoupanca conta = ContaPoupanca(cliente, numConta, diasBase);
	contasPoupanca.push_back(conta);
}

int Banco::excluirCliente(const string& cpfcnpj)
{
	auto i = clientes.begin();

	for (auto i = clientes.begin(); i != clientes.end(); i++)
	{
		if ((*i).getCPFCNPF() == cpfcnpj)
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

int Banco::excluirConta(const int& numConta, const string& tipoConta)
{
	if (tipoConta == "cc") {
		auto i = contasCorrentes.begin();

		for (auto i = contasCorrentes.begin(); i != contasCorrentes.end(); i++)
		{
			if ((*i).getNumConta() == numConta)
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
			if ((*i).getNumConta() == numConta)
			{
				contasPoupanca.erase(i);
				return 1;
			}
		}
	}
	return 0;
}

void Banco::efetuarDeposito(const int& numConta, const int& valor, const string& tipoConta, const int& index)
{
	if (tipoConta == "cc") {
		contasCorrentes[index].creditarConta(valor, "Deposito");
	}
	else if (tipoConta == "p") {
		contasPoupanca[index].creditarConta(valor, "Deposito");
	}
}

int Banco::efetuarSaque(const int& numConta, const int& valor, const string& tipoConta, const int& index)
{
	int status = 0;

	if (tipoConta == "cc") {
		status = contasCorrentes[index].debitarConta(valor, "Saque");
		return status;
	}
	else if (tipoConta == "p") {
		status = contasPoupanca[index].debitarConta(valor, "Saque");
		return status;
	}
	return 0;
}

int Banco::efetuarTransferencia(const int& numContaOrigem, const string& tipoContaOrigem, const int& numContaDestino, const string& tipoContaDestino, const int& valor)
{
	string descricao;
	int status;
	descricao = "Transferencia para a conta " + std::to_string(numContaDestino);
	int index;

	if (tipoContaOrigem == "cc") {
		index = getIndexContaCorrentePorNumConta(numContaOrigem);
		if (index != -1) {
			status = contasCorrentes[index].debitarConta(valor, descricao);
			if (status == 1) {
				if (tipoContaDestino == "cc") {
					index = getIndexContaCorrentePorNumConta(numContaDestino);

					if (index != -1) {
						descricao = "Transferencia da conta " + std::to_string(numContaOrigem);
						contasCorrentes[index].creditarConta(valor, descricao);
						return 1;
					}
				}
				else if (tipoContaDestino == "p") {
					index = getIndexConta(numContaDestino);

					if (index != -1) {
						descricao = "Transferencia da conta " + std::to_string(numContaOrigem);
						contasPoupanca[index].creditarConta(valor, descricao);
						return 1;
					}
				}
			}
		}
	}
	else if (tipoContaOrigem == "p") {
		index = getIndexConta(numContaOrigem);
		if (index != -1) {
			status = contasPoupanca[index].debitarConta(valor, descricao);
			if (status == 1) {
				if (tipoContaDestino == "cc") {
					index = getIndexContaCorrentePorNumConta(numContaDestino);

					if (index != -1) {
						descricao = "Transferencia da conta " + std::to_string(numContaOrigem);
						contasCorrentes[index].creditarConta(valor, descricao);
						return 1;
					}
				}
				else if (tipoContaDestino == "p") {
					index = getIndexConta(numContaDestino);

					if (index != -1) {
						descricao = "Transferencia da conta " + std::to_string(numContaOrigem);
						contasPoupanca[index].creditarConta(valor, descricao);
						return 1;
					}
				}
			}
		}
	}

	return 0;
}

void Banco::cobrarTarifa()
{
	for (unsigned int i = 0; i < contasCorrentes.size(); i++) {
		contasCorrentes[i].debitarConta(15, "Cobranca de tarifa");
	}
	for (unsigned int i = 0; i < contasPoupanca.size(); i++) {
		contasPoupanca[i].debitarConta(15, "Cobranca de tarifa");
	}
}
vector<DiaBase> Banco::obterDiasBase(const int& numConta, const int& index) {
	return contasPoupanca[index].getDiasBase();
}
void Banco::cobrarCPMF()
{
	for (unsigned int i = 0; i < contasPoupanca.size(); i++) {
		double valorCobrado = calcularCPMF(i, "p");
		contasPoupanca[i].debitarConta(valorCobrado, "Cobranca de CPMF");
	}
	for (unsigned int i = 0; i < contasCorrentes.size(); i++) {
		double valorCobrado = calcularCPMF(i, "cc");
		contasCorrentes[i].debitarConta(valorCobrado, "Cobranca de CPMF");
	}
}

double Banco::obterSaldoContaCorrente(const int& numConta)
{
	int index = getIndexContaCorrentePorNumConta(numConta);
	if (index != -1) {
		return contasCorrentes[index].getSaldo();
	}
	else {
		return -1;
	}
}

double Banco::obterSaldoContaPoupanca(const int& numConta)
{
	int index = getIndexConta(numConta);
	if (index != -1) {
		return contasPoupanca[index].getSaldo();
	}
	else {
		return -1;
	}
}

vector <Movimentacao> Banco::obterExtrato(const int& numConta, const string& tipoConta)
{
	int index = 0;
	vector<Movimentacao> movimentacoesFiltradas;

	if (tipoConta == "cc") {
		index = getIndexContaCorrentePorNumConta(numConta);
		if (index >= 0) {
			vector <Movimentacao> movimentacoes = contasCorrentes[index].getMovimentacoes();

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
	}
	else if (tipoConta == "p") {
		index = getIndexConta(numConta);
		if (index >= 0) {
			vector <Movimentacao> movimentacoes = contasPoupanca[index].getMovimentacoes();

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
	}

	return movimentacoesFiltradas;
}

vector<Movimentacao> Banco::obterExtrato(const int& numConta, struct tm& dataInicial, const string& tipoConta)
{
	vector<Movimentacao> movimentacoesFiltradas;

	if (tipoConta == "cc") {
		int index = getIndexContaCorrentePorNumConta(numConta);

		if (index >= 0) {
			vector<Movimentacao> movimentacoes = contasCorrentes[index].getMovimentacoes();

			for (unsigned int i = 0; i < movimentacoes.size(); i++) {
				time_t rawDataMov = mktime(&movimentacoes[i].getDataMov());
				time_t rawDataInicial = mktime(&dataInicial);

				if (rawDataMov >= rawDataInicial) {
					movimentacoesFiltradas.push_back(movimentacoes[i]);
				}
			}
		}
	}
	else if (tipoConta == "p") {
		int index = getIndexConta(numConta);

		if (index >= 0) {
			vector<Movimentacao> movimentacoes = contasPoupanca[index].getMovimentacoes();

			for (unsigned int i = 0; i < movimentacoes.size(); i++) {
				time_t rawDataMov = mktime(&movimentacoes[i].getDataMov());
				time_t rawDataInicial = mktime(&dataInicial);

				if (rawDataMov >= rawDataInicial) {
					movimentacoesFiltradas.push_back(movimentacoes[i]);
				}
			}
		}
	}
	return movimentacoesFiltradas;
}

vector<Movimentacao> Banco::obterExtrato(const int& numConta, struct tm& dataInicial, struct tm& dataFinal, const string& tipoConta)
{
	time_t rawDataInicial = mktime(&dataInicial);
	time_t rawDataFinal = mktime(&dataFinal);
	time_t rawDataMov;
	vector<Movimentacao> movimentacoesFiltradas;

	if (tipoConta == "cc") {
		int index = getIndexContaCorrentePorNumConta(numConta);
		if (index >= 0) {
			vector<Movimentacao> movimentacoes = contasCorrentes[index].getMovimentacoes();

			for (unsigned int i = 0; i < movimentacoes.size(); i++) {
				rawDataMov = mktime(&movimentacoes[i].getDataMov());
				if (rawDataMov >= rawDataInicial && rawDataMov <= rawDataFinal) {
					movimentacoesFiltradas.push_back(movimentacoes[i]);
				}
			}
		}
	}
	else if (tipoConta == "p") {
		int index = getIndexConta(numConta);
		if (index >= 0) {
			vector<Movimentacao> movimentacoes = contasPoupanca[index].getMovimentacoes();

			for (unsigned int i = 0; i < movimentacoes.size(); i++) {
				rawDataMov = mktime(&movimentacoes[i].getDataMov());
				if (rawDataMov >= rawDataInicial && rawDataMov <= rawDataFinal) {
					movimentacoesFiltradas.push_back(movimentacoes[i]);
				}
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

vector<ContaPoupanca> Banco::buscarContaPoupancaPorCliente(const Cliente& cliente)
{
	vector<ContaPoupanca> contasCliente;
	for (auto i = contasPoupanca.begin(); i != contasPoupanca.end(); i++)
	{
		if ((*i).getCliente().getCPFCNPF() == cliente.getCPFCNPF())
		{
			contasCliente.push_back(*i);
		}
	}
	return contasCliente;
}

vector<ContaCorrente> Banco::buscarContaCorrentePorCliente(const Cliente& cliente)
{
	vector<ContaCorrente> contasCliente;
	for (auto i = contasCorrentes.begin(); i != contasCorrentes.end(); i++)
	{
		if ((*i).getCliente().getCPFCNPF() == cliente.getCPFCNPF())
		{
			contasCliente.push_back(*i);
		}
	}
	return contasCliente;
}

int Banco::getIndexContaCorrentePorNumConta(const int& numConta)
{
	for (unsigned int i = 0; i < contasCorrentes.size(); i++)
	{
		if (contasCorrentes[i].getNumConta() == numConta)
		{
			return i;
		}
	}
	return -1;
}

int Banco::getIndexContaCorrentePorNumConta(const int& numConta, const vector<int>& numContasCorrentesExistentes)
{
	for (unsigned int i = 0; i < numContasCorrentesExistentes.size(); i++)
	{
		if (numContasCorrentesExistentes[i] == numConta)
		{
			return i;
		}
	}
	return -1;
}

int Banco::getIndexConta(const int& numConta)
{
	for (unsigned int i = 0; i < contasPoupanca.size(); i++)
	{
		if (contasPoupanca[i].getNumConta() == numConta)
		{
			return i;
		}
	}
	return -1;
}

double Banco::calcularCPMF(const int& indexConta, const string& tipoConta) {
	double valorCalculado = 0;

	time_t rawNow = time(0);
	time_t rawdataAtualMenosSeteDias = rawNow - (7 * 24 * 60 * 60);
	struct tm dataAtualMenosSeteDias;
	vector<Movimentacao> movimentacoesUltimosSeteDias;

	localtime_s(&dataAtualMenosSeteDias, &rawdataAtualMenosSeteDias);

	if (tipoConta == "cc") {
		movimentacoesUltimosSeteDias = obterExtrato(contasCorrentes[indexConta].getNumConta(), dataAtualMenosSeteDias, tipoConta);
	}
	else if (tipoConta == "p") {
		movimentacoesUltimosSeteDias = obterExtrato(contasPoupanca[indexConta].getNumConta(), dataAtualMenosSeteDias, tipoConta);
	}

	for (unsigned int i = 0; i < movimentacoesUltimosSeteDias.size(); i++) {
		if (movimentacoesUltimosSeteDias[i].getDebitoCredito() == 'D') {
			valorCalculado += movimentacoesUltimosSeteDias[i].getValor() * 0.0038;
		}
	}

	return valorCalculado;
}

void Banco::adicionarMovimentacao(const int& numConta, const Movimentacao& movimentacao, const string& tipoConta) {
	int index = -1;

	if (tipoConta == "cc") {
		index = getIndexContaCorrentePorNumConta(numConta);
		if (index >= 0) {
			contasCorrentes[index].adicionarMovimentacao(movimentacao);
			if (movimentacao.getDebitoCredito() == 'C') {
				contasCorrentes[index].somarSaldo(movimentacao.getValor());
			}
			else if (movimentacao.getDebitoCredito() == 'D') {
				contasCorrentes[index].somarSaldo(-movimentacao.getValor());
			}
		}
	}
	else if (tipoConta == "p") {
		index = getIndexConta(numConta);
		if (index >= 0) {
			contasPoupanca[index].adicionarMovimentacao(movimentacao);
			if (movimentacao.getDebitoCredito() == 'C') {
				contasPoupanca[index].somarSaldo(movimentacao.getValor());
			}
			else if (movimentacao.getDebitoCredito() == 'D') {
				contasPoupanca[index].somarSaldo(-movimentacao.getValor());
			}
		}
	}
}