#pragma once
#include <vector>
#include <string>
#include <time.h>
#include "Cliente.h"
#include "Movimentacao.h"

using namespace std;

class Conta
{
protected:
	int _numConta;
	double _saldo;
	Cliente _cliente;
	vector<Movimentacao> _movimentacoes;

public:

	int getNumConta()const { return _numConta; };
	Cliente getCliente()const { return _cliente; };
	vector<Movimentacao> getMovimentacoes()const { return _movimentacoes; };

	virtual double getSaldo() const = 0;
	virtual bool debitarConta(const double& valor, const string& descricaoMovimentacao) = 0;
	virtual void creditarConta(const int& valor, const string& descricaoMovimentacao) = 0;
	virtual void adicionarMovimentacao(const Movimentacao& movimentacao) = 0;
	virtual void somarSaldo(const double& valor) = 0;
};
