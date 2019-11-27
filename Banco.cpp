#include "pch.h"
#include "Banco.h"
#include "Cliente.h"
#include "Conta.h"
#include <time.h>
#include <algorithm>
#include "ContaCorrente.h"
#include "BancoServices.h"
#include "ContaPoupanca.h"

Banco::Banco(string nomeBanco)
{
	_nomeBanco = nomeBanco;
	_clientes = vector<Cliente>();
	_contasCorrentes = vector<ContaCorrente>();
	_contasPoupanca = vector<ContaPoupanca>();
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
	for (auto i = _clientes.begin(); i != _clientes.end(); i++)
	{
		if ((*i).getCPFCNPF() == cpfcnpj)
		{
			return (*i);
		}
	}
	throw runtime_error("ClienteNaoEncontrado");
}

void Banco::cadastrarCliente(const Cliente& cliente)
{
	_clientes.push_back(cliente);
}
void Banco::creditarJuros()
{
	auto hoje = BancoServices.diaHoje();

	for (unsigned int i = 0; i < _contasPoupanca.size(); i++) {
		auto index = _contasPoupanca[i].getIndexDiaBase(hoje);
		if (index >= 0)_contasPoupanca[i].creditarJuros(index);
	}
}
void Banco::criarContaCorrente(const Cliente& cliente, const double& limiteCredito)
{
	vector<int> numContasExistentes;
	for (unsigned int i = 0; i < _contasCorrentes.size(); i++) {
		numContasExistentes.push_back(_contasCorrentes[i].getNumConta());
	}

	ContaCorrente conta = ContaCorrente(cliente, numContasExistentes, limiteCredito);
	_contasCorrentes.push_back(conta);
}

void Banco::criarContaCorrente(const Cliente& cliente, const int& numConta, const double& limiteCredito = 0)
{
	ContaCorrente conta = ContaCorrente(cliente, numConta, limiteCredito);
	_contasCorrentes.push_back(conta);
}

void Banco::criarContaPoupanca(const Cliente& cliente)
{
	vector<int> numContasExistentes = vector<int>();
	preencherNumContaExistentes(_contasPoupanca, numContasExistentes);
	ContaPoupanca conta = ContaPoupanca(cliente, numContasExistentes);
	_contasPoupanca.push_back(conta);
}

void Banco::criarContaPoupanca(const Cliente& cliente, const int& numConta, const vector<DiaBase>& diasBase)
{
	ContaPoupanca conta = ContaPoupanca(cliente, numConta, diasBase);
	_contasPoupanca.push_back(conta);
}

void Banco::excluirCliente(const string& cpfcnpj)
{
	auto i = _clientes.begin();

	for (auto i = _clientes.begin(); i != _clientes.end(); i++)
	{
		if ((*i).getCPFCNPF() == cpfcnpj)
		{
			if (buscarContasPoupancaPorCliente(*i).size() == 0 && buscarContasCorrentesPorCliente(*i).size() == 0)   //o cliente nao tem nenhuma conta
			{
				_clientes.erase(i); return;
			}
			else throw exception("ClienteComContaAtiva");
		}
	}
	throw exception("ClienteNaoEncontrado");
}

void Banco::excluirConta(const int& numConta, const string& tipoConta)
{
	if (tipoConta == "cc") {
		auto i = _contasCorrentes.begin();

		for (auto i = _contasCorrentes.begin(); i != _contasCorrentes.end(); i++)
		{
			if ((*i).getNumConta() == numConta)
			{
				_contasCorrentes.erase(i); return;
			}
		}
		throw exception("ContaNaoEncontrada");
	}
	else if (tipoConta == "p") {
		auto i = _contasPoupanca.begin();

		for (auto i = _contasPoupanca.begin(); i != _contasPoupanca.end(); i++)
		{
			if ((*i).getNumConta() == numConta)
			{
				_contasPoupanca.erase(i); return;
			}
		}
		throw exception("ContaNaoEncontrada");
	}
}

void Banco::efetuarDeposito(const int& numConta, const int& valor, const string& tipoConta, const int& index)
{
	if (tipoConta == "cc") {
		_contasCorrentes[index].creditarConta(valor, "Deposito");
	}
	else if (tipoConta == "p") {
		_contasPoupanca[index].creditarConta(valor, "Deposito");
	}
}

int Banco::efetuarSaque(const int& numConta, const int& valor, const string& tipoConta, const int& index)
{
	int status = 0;

	if (tipoConta == "cc") {
		status = _contasCorrentes[index].debitarConta(valor, "Saque");
		return status;
	}
	else if (tipoConta == "p") {
		status = _contasPoupanca[index].debitarConta(valor, "Saque");
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
			status = _contasCorrentes[index].debitarConta(valor, descricao);
			if (status == 1) {
				if (tipoContaDestino == "cc") {
					index = getIndexContaCorrentePorNumConta(numContaDestino);

					if (index != -1) {
						descricao = "Transferencia da conta " + std::to_string(numContaOrigem);
						_contasCorrentes[index].creditarConta(valor, descricao);
						return 1;
					}
				}
				else if (tipoContaDestino == "p") {
					index = getIndexConta(numContaDestino);

					if (index != -1) {
						descricao = "Transferencia da conta " + std::to_string(numContaOrigem);
						_contasPoupanca[index].creditarConta(valor, descricao);
						return 1;
					}
				}
			}
		}
	}
	else if (tipoContaOrigem == "p") {
		index = getIndexConta(numContaOrigem);
		if (index != -1) {
			status = _contasPoupanca[index].debitarConta(valor, descricao);
			if (status == 1) {
				if (tipoContaDestino == "cc") {
					index = getIndexContaCorrentePorNumConta(numContaDestino);

					if (index != -1) {
						descricao = "Transferencia da conta " + std::to_string(numContaOrigem);
						_contasCorrentes[index].creditarConta(valor, descricao);
						return 1;
					}
				}
				else if (tipoContaDestino == "p") {
					index = getIndexConta(numContaDestino);

					if (index != -1) {
						descricao = "Transferencia da conta " + std::to_string(numContaOrigem);
						_contasPoupanca[index].creditarConta(valor, descricao);
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
	for (unsigned int i = 0; i < _contasCorrentes.size(); i++) {
		_contasCorrentes[i].debitarConta(15, "Cobranca de tarifa");
	}
	for (unsigned int i = 0; i < _contasPoupanca.size(); i++) {
		_contasPoupanca[i].debitarConta(15, "Cobranca de tarifa");
	}
}

vector<DiaBase> Banco::obterDiasBase(const int& numConta, const int& index) {
	return _contasPoupanca[index].getDiasBase();
}

void Banco::cobrarCPMF()
{
	for (unsigned int i = 0; i < _contasPoupanca.size(); i++) {
		double valorCobrado = calcularCPMF(i, "p");
		_contasPoupanca[i].debitarConta(valorCobrado, "Cobranca de CPMF");
	}
	for (unsigned int i = 0; i < _contasCorrentes.size(); i++) {
		double valorCobrado = calcularCPMF(i, "cc");
		_contasCorrentes[i].debitarConta(valorCobrado, "Cobranca de CPMF");
	}
}

double Banco::obterSaldoContaCorrente(const int& numConta)
{
	int index = getIndexContaCorrentePorNumConta(numConta);
	if (index != -1) {
		return _contasCorrentes[index].getSaldo();
	}
	else {
		return -1;
	}
}

double Banco::obterSaldoContaPoupanca(const int& numConta)
{
	int index = getIndexConta(numConta);
	if (index != -1) {
		return _contasPoupanca[index].getSaldo();
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
			vector <Movimentacao> movimentacoes = _contasCorrentes[index].getMovimentacoes();

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
			vector <Movimentacao> movimentacoes = _contasPoupanca[index].getMovimentacoes();

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
			vector<Movimentacao> movimentacoes = _contasCorrentes[index].getMovimentacoes();

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
			vector<Movimentacao> movimentacoes = _contasPoupanca[index].getMovimentacoes();

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
			vector<Movimentacao> movimentacoes = _contasCorrentes[index].getMovimentacoes();

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
			vector<Movimentacao> movimentacoes = _contasPoupanca[index].getMovimentacoes();

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
	return _clientes;
}

vector<ContaCorrente> Banco::listarContasCorrentes()
{
	return _contasCorrentes;
}
vector<ContaPoupanca> Banco::listarContasPoupanca()
{
	return _contasPoupanca;
}

vector<ContaPoupanca> Banco::buscarContasPoupancaPorCliente(const Cliente& cliente)
{
	vector<ContaPoupanca> contasCliente;
	for (auto i = _contasPoupanca.begin(); i != _contasPoupanca.end(); i++)
	{
		if ((*i).getCliente().getCPFCNPF() == cliente.getCPFCNPF())
		{
			contasCliente.push_back(*i);
		}
	}
	return contasCliente;
}

vector<ContaCorrente> Banco::buscarContasCorrentesPorCliente(const Cliente& cliente)
{
	vector<ContaCorrente> contasCliente;
	for (auto i = _contasCorrentes.begin(); i != _contasCorrentes.end(); i++)
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
	for (unsigned int i = 0; i < _contasCorrentes.size(); i++)
	{
		if (_contasCorrentes[i].getNumConta() == numConta)
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
	for (unsigned int i = 0; i < _contasPoupanca.size(); i++)
	{
		if (_contasPoupanca[i].getNumConta() == numConta)
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
		movimentacoesUltimosSeteDias = obterExtrato(_contasCorrentes[indexConta].getNumConta(), dataAtualMenosSeteDias, tipoConta);
	}
	else if (tipoConta == "p") {
		movimentacoesUltimosSeteDias = obterExtrato(_contasPoupanca[indexConta].getNumConta(), dataAtualMenosSeteDias, tipoConta);
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
			_contasCorrentes[index].adicionarMovimentacao(movimentacao);
			if (movimentacao.getDebitoCredito() == 'C') {
				_contasCorrentes[index].somarSaldo(movimentacao.getValor());
			}
			else if (movimentacao.getDebitoCredito() == 'D') {
				_contasCorrentes[index].somarSaldo(-movimentacao.getValor());
			}
		}
	}
	else if (tipoConta == "p") {
		index = getIndexConta(numConta);
		if (index >= 0) {
			_contasPoupanca[index].adicionarMovimentacao(movimentacao);
			if (movimentacao.getDebitoCredito() == 'C') {
				_contasPoupanca[index].somarSaldo(movimentacao.getValor());
			}
			else if (movimentacao.getDebitoCredito() == 'D') {
				_contasPoupanca[index].somarSaldo(-movimentacao.getValor());
			}
		}
	}
}