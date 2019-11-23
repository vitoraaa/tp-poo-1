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

void Banco::criarContaCorrente(const Cliente _cliente, double limiteCredito)
{
	vector<int> numContasExistentes;
	for (unsigned int i = 0; i < contasCorrentes.size(); i++) {
		numContasExistentes.push_back(contasCorrentes[i].getNumConta());
	}

	ContaCorrente conta = ContaCorrente(_cliente, numContasExistentes, limiteCredito);
	contasCorrentes.push_back(conta);
}

void Banco::criarContaCorrente(const Cliente _cliente, int _numConta, double limiteCredito = 0)
{
	ContaCorrente conta = ContaCorrente(_cliente, _numConta, limiteCredito);
	contasCorrentes.push_back(conta);
}

void Banco::criarContaPoupanca(const Cliente _cliente, double limiteCredito)
{
	const vector<DiaBase> diasBase;
	vector<int> numContasExistentes;
	for (unsigned int i = 0; i < contasPoupanca.size(); i++) {
		numContasExistentes.push_back(contasPoupanca[i].getNumConta());
	}
	ContaPoupanca conta = ContaPoupanca(_cliente, numContasExistentes, diasBase);
	contasPoupanca.push_back(conta);
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

int Banco::efetuarTransferencia(int _numContaOrigem, string tipoContaOrigem, int _numContaDestino, string tipoContaDestino, int _valor)
{
	string descricao;
	int status;
	descricao = "Transferencia para a conta " + std::to_string(_numContaDestino);
	int index;

	if (tipoContaOrigem == "cc") {
		index = getIndexContaCorrentePorNumConta(_numContaOrigem);
		if (index != -1) {
			status = contasCorrentes[index].debitarConta(_valor, descricao);
			if (status == 1) {
				if (tipoContaDestino == "cc") {
					index = getIndexContaCorrentePorNumConta(_numContaDestino);

					if (index != -1) {
						descricao = "Transferencia da conta " + std::to_string(_numContaOrigem);
						contasCorrentes[index].creditarConta(_valor, descricao);
						return 1;
					}
				}
				else if (tipoContaDestino == "p") {
					index = getIndexContaPoupancaPorNumConta(_numContaDestino);

					if (index != -1) {
						descricao = "Transferencia da conta " + std::to_string(_numContaOrigem);
						contasPoupanca[index].creditarConta(_valor, descricao);
						return 1;
					}
				}
			}
		}
	}
	else if (tipoContaOrigem == "p") {
		index = getIndexContaPoupancaPorNumConta(_numContaOrigem);
		if (index != -1) {
			status = contasPoupanca[index].debitarConta(_valor, descricao);
			if (status == 1) {
				if (tipoContaDestino == "cc") {
					index = getIndexContaCorrentePorNumConta(_numContaDestino);

					if (index != -1) {
						descricao = "Transferencia da conta " + std::to_string(_numContaOrigem);
						contasCorrentes[index].creditarConta(_valor, descricao);
						return 1;
					}
				}
				else if (tipoContaDestino == "p") {
					index = getIndexContaPoupancaPorNumConta(_numContaDestino);

					if (index != -1) {
						descricao = "Transferencia da conta " + std::to_string(_numContaOrigem);
						contasPoupanca[index].creditarConta(_valor, descricao);
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

double Banco::obterSaldoContaCorrente(int _numConta)
{
	int index = getIndexContaCorrentePorNumConta(_numConta);
	if (index != -1) {
		return contasCorrentes[index].getSaldo();
	}
	else {
		return -1;
	}
}

double Banco::obterSaldoContaPoupanca(int _numConta)
{
	int index = getIndexContaPoupancaPorNumConta(_numConta);
	if (index != -1) {
		return contasPoupanca[index].getSaldo();
	}
	else {
		return -1;
	}
}

vector <Movimentacao> Banco::obterExtrato(int _numConta, string tipoConta)
{
	int index = 0;
	vector<Movimentacao> movimentacoesFiltradas;

	if (tipoConta == "cc") {
		index = getIndexContaCorrentePorNumConta(_numConta);
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
		index = getIndexContaPoupancaPorNumConta(_numConta);
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

vector<Movimentacao> Banco::obterExtrato(int _numConta, struct tm _dataInicial, string tipoConta)
{
	vector<Movimentacao> movimentacoesFiltradas;

	if (tipoConta == "cc") {
		int index = getIndexContaCorrentePorNumConta(_numConta);

		if (index >= 0) {
			vector<Movimentacao> movimentacoes = contasCorrentes[index].getMovimentacoes();

			for (unsigned int i = 0; i < movimentacoes.size(); i++) {
				time_t rawDataMov = mktime(&movimentacoes[i].getDataMov());
				time_t rawDataInicial = mktime(&_dataInicial);

				if (rawDataMov >= rawDataInicial) {
					movimentacoesFiltradas.push_back(movimentacoes[i]);
				}
			}
		}
	}
	else if (tipoConta == "p") {
		int index = getIndexContaPoupancaPorNumConta(_numConta);

		if (index >= 0) {
			vector<Movimentacao> movimentacoes = contasPoupanca[index].getMovimentacoes();

			for (unsigned int i = 0; i < movimentacoes.size(); i++) {
				time_t rawDataMov = mktime(&movimentacoes[i].getDataMov());
				time_t rawDataInicial = mktime(&_dataInicial);

				if (rawDataMov >= rawDataInicial) {
					movimentacoesFiltradas.push_back(movimentacoes[i]);
				}
			}
		}
	}
	return movimentacoesFiltradas;
}

vector<Movimentacao> Banco::obterExtrato(int _numConta, struct tm _dataInicial, struct tm _dataFinal, string tipoConta)
{
	time_t rawDataInicial = mktime(&_dataInicial);
	time_t rawDataFinal = mktime(&_dataFinal);
	time_t rawDataMov;
	vector<Movimentacao> movimentacoesFiltradas;

	if (tipoConta == "cc") {
		int index = getIndexContaCorrentePorNumConta(_numConta);
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
		int index = getIndexContaPoupancaPorNumConta(_numConta);
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

vector<ContaPoupanca> Banco::buscarContaPoupancaPorCliente(Cliente _cliente)
{
	vector<ContaPoupanca> contasCliente;
	for (auto i = contasPoupanca.begin(); i != contasPoupanca.end(); i++)
	{
		if ((*i).getCliente().getCPF_CNPF() == _cliente.getCPF_CNPF())
		{
			contasCliente.push_back(*i);
		}
	}
	return contasCliente;
}

vector<ContaCorrente> Banco::buscarContaCorrentePorCliente(Cliente _cliente)
{
	vector<ContaCorrente> contasCliente;
	for (auto i = contasCorrentes.begin(); i != contasCorrentes.end(); i++)
	{
		if ((*i).getCliente().getCPF_CNPF() == _cliente.getCPF_CNPF())
		{
			contasCliente.push_back(*i);
		}
	}
	return contasCliente;
}

int Banco::getIndexContaCorrentePorNumConta(int _numConta)
{
	for (unsigned int i = 0; i < contasCorrentes.size(); i++)
	{
		if (contasCorrentes[i].getNumConta() == _numConta)
		{
			return i;
		}
	}
	return -1;
}

int Banco::getIndexContaCorrentePorNumConta(int _numConta, vector<int> numContasCorrentesExistentes)
{
	for (unsigned int i = 0; i < numContasCorrentesExistentes.size(); i++)
	{
		if (numContasCorrentesExistentes[i] == _numConta)
		{
			return i;
		}
	}
	return -1;
}

int Banco::getIndexContaPoupancaPorNumConta(int _numConta)
{
	for (unsigned int i = 0; i < contasPoupanca.size(); i++)
	{
		if (contasPoupanca[i].getNumConta() == _numConta)
		{
			return i;
		}
	}
	return -1;
}

int Banco::getIndexContaPoupancaPorNumConta(int _numConta, vector<int> numContasPoupancaExistentes)
{
	for (unsigned int i = 0; i < numContasPoupancaExistentes.size(); i++)
	{
		if (numContasPoupancaExistentes[i] == _numConta)
		{
			return i;
		}
	}
	return -1;
}

double Banco::calcularCPMF(int indexConta, string tipoConta) {
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

void Banco::restaurarMovimentacao(int _numConta, Movimentacao _movimentacao, string tipoConta) {
	int index = -1;

	if (tipoConta == "cc") {
		index = getIndexContaCorrentePorNumConta(_numConta);
		if (index >= 0) {
			contasCorrentes[index].restaurarMovimentacao(_movimentacao);
			if (_movimentacao.getDebitoCredito() == 'C') {
				contasCorrentes[index].restaurarSaldo(_movimentacao.getValor());
			}
			else if (_movimentacao.getDebitoCredito() == 'D') {
				contasCorrentes[index].restaurarSaldo(-_movimentacao.getValor());
			}
		}
	}
	else if (tipoConta == "p") {
		index = getIndexContaPoupancaPorNumConta(_numConta);
		if (index >= 0) {
			contasPoupanca[index].restaurarMovimentacao(_movimentacao);
			if (_movimentacao.getDebitoCredito() == 'C') {
				contasPoupanca[index].restaurarSaldo(_movimentacao.getValor());
			}
			else if (_movimentacao.getDebitoCredito() == 'D') {
				contasPoupanca[index].restaurarSaldo(-_movimentacao.getValor());
			}
		}
	}
}