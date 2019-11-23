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
	string nomeBanco;
	vector <Cliente> clientes;
	vector <ContaCorrente> contasCorrentes;
	vector <ContaPoupanca> contasPoupanca;
public:
	Banco(string _nomeBanco);
	~Banco();
	Banco();
	void cadastrarCliente(Cliente _cliente);
	void criarContaCorrente(const Cliente _cliente, double limiteCredito = 0);
	void criarContaCorrente(Cliente _cliente, int _numConta, double limiteCredito);
	void criarContaPoupanca(Cliente _cliente, int _numConta, vector<DiaBase> diasBase);
	void criarContaPoupanca(const Cliente _cliente, double limiteCredito = 0);
	int excluirCliente(string _cnp_cnpj);
	int excluirConta(int _numConta, string tipoConta);
	int efetuarDeposito(int _numConta, int _valor, string tipoConta);
	int efetuarSaque(int _numConta, int valor, string tipoConta);
	int efetuarTransferencia(int _numContaOrigem, string tipoContaOrigem, int _numContaDestino, string tipoContaDestino, int _valor);
	void cobrarTarifa();
	void cobrarCPMF();
	double obterSaldoContaCorrente(int _numConta);
	double obterSaldoContaPoupanca(int _numConta);
	vector<Movimentacao> obterExtrato(int _numConta, string tipoConta);
	vector<Movimentacao> obterExtrato(int _numConta, struct tm _dataInicial, string tipoConta);
	vector<Movimentacao> obterExtrato(int _numConta, struct tm _dataInicial, struct tm _dataFinal, string tipoConta);
	vector<Cliente> listarClientes();
	vector<ContaCorrente> listarContasCorrentes();
	vector<ContaPoupanca> listarContasPoupanca();
	void restaurarMovimentacao(int _numConta, Movimentacao _movimentacao, string tipoConta);
	void restaurarSaldo(int _numConta, double _valor);
	Cliente buscaClienteCPF_CNPJ(string _cpf_cnpj);
	int getIndexContaCorrentePorNumConta(int _numConta);
	int getIndexContaCorrentePorNumConta(int _numConta, vector<int> numContasExistentes);
	int getIndexContaPoupancaPorNumConta(int _numConta);
	int getIndexContaPoupancaPorNumConta(int _numConta, vector<int> numContasExistentes);
	vector<ContaPoupanca> buscarContaPoupancaPorCliente(Cliente _cliente);
	vector<ContaCorrente> buscarContaCorrentePorCliente(Cliente _cliente);
	double calcularCPMF(int index, string tipoConta);
};
