#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Cliente.h"
#include "Conta.h"
#include "ContaCorrente.h"
#include "ContaPoupanca.h"
using namespace std;
class Banco
{
private:
	string _nomeBanco;
	vector <Cliente> _clientes;
	vector <ContaCorrente> _contasCorrentes;
	vector <ContaPoupanca> _contasPoupanca;
public:
	Banco(string nomeBanco);
	~Banco();
	Banco();
	void cadastrarCliente(const Cliente& cliente);
	void criarContaCorrente(const Cliente& cliente, const double& limiteCredito = 0);
	void criarContaCorrente(const Cliente& cliente, const int& numConta, const double& limiteCredito);
	void criarContaPoupanca(const Cliente& cliente, const int& numConta, const vector<DiaBase>& diasBase);
	void criarContaPoupanca(const Cliente& cliente);
	void excluirCliente(const string& cnpcnpj);
	void excluirConta(const int& numConta, const string& tipoConta);
	void efetuarDeposito(const int& numConta, const int& valor, const string& tipoConta, const int& index);
	int efetuarSaque(const int& numConta, const int& valor, const string& tipoConta, const int& index);
	int efetuarTransferencia(const int& numContaOrigem, const string& tipoContaOrigem, const int& numContaDestino, const string& tipoContaDestino, const int& valor);
	void cobrarTarifa();
	void cobrarCPMF();
	void creditarJuros();
	double obterSaldoContaCorrente(const int& numConta);
	vector<DiaBase> obterDiasBase(const int& numConta, const int& index);
	double obterSaldoContaPoupanca(const int& numConta);
	vector<Movimentacao> obterExtrato(const int& numConta, const string& tipoConta);
	vector<Movimentacao> obterExtrato(const int& numConta, struct tm& dataInicial, const string& tipoConta);
	vector<Movimentacao> obterExtrato(const int& numConta, struct tm& dataInicial, struct tm& dataFinal, const string& tipoConta);
	vector<Cliente> listarClientes();
	vector<ContaCorrente> listarContasCorrentes();
	vector<ContaPoupanca> listarContasPoupanca();
	void adicionarMovimentacao(const int& numConta, const Movimentacao& movimentacao, const string& tipoConta);
	//void somarSaldo(const int& numConta, const double& valor);
	Cliente buscaClienteCPFCNPJ(const string& cpfcnpj);
	int getIndexContaCorrentePorNumConta(const int& numConta);
	int getIndexContaCorrentePorNumConta(const int& numConta, const vector<int>& numContasExistentes);
	int getIndexConta(const int& numConta);
	//int getIndexConta(const int& numConta, const vector<int>& numContasExistentes);
	vector<ContaPoupanca> buscarContasPoupancaPorCliente(const Cliente& cliente);
	vector<ContaCorrente> buscarContasCorrentesPorCliente(const Cliente& cliente);
	double calcularCPMF(const int& index, const string& tipoConta);
};
