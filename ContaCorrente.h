#pragma once
#include "Conta.h"
class ContaCorrente :
	public  Conta
{
private:
	double _limiteCredito;

public:

	ContaCorrente(const Cliente& cliente, vector <int> numContasExistentes, const double& limiteCredito);
	ContaCorrente(const  Cliente& cliente, const int& numConta, const double& limiteCredito);
	~ContaCorrente();

	virtual double getSaldo()const;

	virtual bool debitarConta(const double& valor, const string& descricaoMovimentacao);

	virtual void creditarConta(const int& valor, const string& descricaoMovimentacao);

	virtual void adicionarMovimentacao(const Movimentacao& movimentacao);

	virtual void somarSaldo(const double& valor);

	double getLimiteCredito()const { return _limiteCredito; };
};
