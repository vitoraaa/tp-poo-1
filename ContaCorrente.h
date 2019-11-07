#pragma once
#include "Conta.h"
class ContaCorrente :
	public  Conta
{
private:
	double limiteCredito;

public:

	ContaCorrente(Cliente _cliente, vector <int> numContasExistentes, double _limiteCredito);
	ContaCorrente(Cliente _cliente, int _numConta);
	~ContaCorrente();

	double getSaldo()
	{
		return saldo;
	}

	int debitarConta(double _valor, string _descricaoMovimentacao)
	{
		if (saldo >= _valor) {
			saldo -= _valor;
			Movimentacao novaMovimentacao = Movimentacao(_descricaoMovimentacao, 'D', _valor, numConta);
			movimentacoes.push_back(novaMovimentacao);
			return 1;
		}
		else {
			return 0;
		}
	}
	void creditarConta(int _valor, string _descricaoMovimentacao)
	{
		saldo += _valor;
		Movimentacao novaMovimentacao = Movimentacao(_descricaoMovimentacao, 'C', _valor, numConta);
		movimentacoes.push_back(novaMovimentacao);
	}

	void restaurarMovimentacao(Movimentacao _movimentacao) {
		movimentacoes.push_back(_movimentacao);
	}

	void restaurarSaldo(double _valor) {
		saldo += _valor;
	}
};
