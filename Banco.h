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
	void cadastrarCliente(Cliente _cliente);
	void criarConta(Cliente _cliente);
	int excluirCliente(string _cnp_cnpj);
	int excluirConta(int _numConta);
	void efetuarDeposito(int _numConta, int _valor);
	void efetuarSaque(int _numConta, int valor);
	void efetuarTransferencia(int _numContaOrigem, int _numContaDestino, int _valor);
	void cobrarTarifa();
	void cobrarCPMF();
	double obterSaldo(int _numConta);
	vector<Movimentacao> obterExtrato(int _numConta);
	vector<Movimentacao> obterExtrato(int _numConta, time_t _dataInicial);
	vector<Movimentacao> obterExtrato(int _numConta, time_t _dataInicial, time_t _dataFinal);
	vector<Cliente> listarClientes();
	vector<Conta> listarContas();
	void gravarDados();
	void lerDados();
	Cliente buscaClienteCPF_CNPJ(string _cpf_cnpj);
	int getIndexContaPorNumConta(int _numConta);
	vector<Conta> buscarContaPorCliente(Cliente _cliente);
	int calcularCPMF(int index);

};

