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
	void inserirCliente(Cliente _cliente);
	void criarConta(Conta _conta);
	void deletarCliente(int _cnp_cnpj);
	void deletarConta(int _numConta);
	void efetuarDeposito(int _numConta, int _valor);
	void efetuarSaque(int _numConta, int valor);
	void efetuarTransferencia(int _numContaOrigem, int _numContaDestino, int _valor);
	void cobrarTarifa();
	void cobrarCPMF();
	void obterSaldo(int _numConta);
	void obterExtrato(int _numConta);
	void obterExtrato(int _numConta, time_t _dataInicial);
	void obterExtrato(int _numConta, time_t _dataInicial, time_t _dataFinal);
	void obterClientes();
	void gravarDados();
	void lerDados();

};

