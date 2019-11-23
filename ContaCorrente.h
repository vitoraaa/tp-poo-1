#pragma once
#include "Conta.h"
class ContaCorrente :
	public  Conta
{
private:
	double limiteCredito;

public:

	ContaCorrente(Cliente _cliente, const vector <int> numContasExistentes, double _limiteCredito);
	ContaCorrente(Cliente _cliente, int _numConta, double _limiteCredito);
	~ContaCorrente();

	virtual double getSaldo();

	virtual int debitarConta(double _valor, string _descricaoMovimentacao);

	virtual void creditarConta(int _valor, string _descricaoMovimentacao);

	virtual void restaurarMovimentacao(Movimentacao _movimentacao);

	virtual void restaurarSaldo(double _valor);

	double getLimiteCredito() { return limiteCredito; };
};
