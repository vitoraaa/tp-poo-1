#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Cliente.h"
#include "Conta.h"
using namespace std;
class Banco
{
private:
	string nomeBanco;
	vector <Cliente> clientes;
	vector <Conta> contas;
public:
	Banco(string _nomeBanco);
	~Banco();
	Banco();
	void cadastrarCliente(Cliente _cliente);
	void criarConta(Cliente _cliente);
	void criarConta(Cliente _cliente, int _numConta);
	int excluirCliente(string _cnp_cnpj);
	int excluirConta(int _numConta);
	int efetuarDeposito(int _numConta, int _valor);
	int efetuarSaque(int _numConta, int valor);
	int efetuarTransferencia(int _numContaOrigem, int _numContaDestino, int _valor);
	void cobrarTarifa();
	void cobrarCPMF();
	double obterSaldo(int _numConta);
	vector<Movimentacao> obterExtrato(int _numConta);
	vector<Movimentacao> obterExtrato(int _numConta, struct tm _dataInicial);
	vector<Movimentacao> obterExtrato(int _numConta, struct tm _dataInicial, struct tm _dataFinal);
	vector<Cliente> listarClientes();
	vector<Conta> listarContas();
	void restaurarMovimentacao(int _numConta, Movimentacao _movimentacao);
	void restaurarSaldo(int _numConta, double _valor);
	Cliente buscaClienteCPF_CNPJ(string _cpf_cnpj);
	int getIndexContaPorNumConta(int _numConta);
	vector<Conta> buscarContaPorCliente(Cliente _cliente);
	double calcularCPMF(int index);

};

