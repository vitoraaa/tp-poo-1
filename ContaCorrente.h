#pragma once
#include "Conta.h"
class ContaCorrente :
	public  Conta
{
private:
	double limiteCredito;

public:

	ContaCorrente(Cliente _cliente, vector <int> numContasExistentes, double _limiteCredito);
	ContaCorrente(Cliente _cliente, int _numConta, double _limiteCredito);
	~ContaCorrente();

	double getSaldo() { return saldo; };

	int debitarConta(double _valor, string _descricaoMovimentacao);

	void creditarConta(int _valor, string _descricaoMovimentacao);

	void restaurarMovimentacao(Movimentacao _movimentacao);

	void restaurarSaldo(double _valor);

	double getLimiteCredito() { return limiteCredito; };
};
