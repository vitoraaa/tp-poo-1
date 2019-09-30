#pragma once
#include <vector>
#include <string>
#include <time.h>
#include "Cliente.h"
#include "Movimentacao.h"

using namespace std;

class Conta
{
private:
	int numConta;
	double saldo;
	Cliente cliente;
	vector<Movimentacao> movimentacoes;
	

public:
    int proximoNumConta;
	Conta(Cliente _cliente);
	~Conta();

	int getNumConta();
	double getSaldo();
	Cliente getCliente();
	vector<Movimentacao> getMovimentacoes();
	int debitarConta(int _valor, string _descricaoMovimentacao);
	void creditarConta(int _valor, string _descricaoMovimentacao);
	vector<Movimentacao> obterExtrato(time_t _dataInicial, time_t _dataFinal);
	vector<Movimentacao> obterExtrato(time_t _dataInicial);
	vector<Movimentacao> obterExtrato();
};
