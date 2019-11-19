#include "pch.h"
#include "ContaCorrente.h"
#include "Banco.h"

ContaCorrente::ContaCorrente(Cliente _cliente, vector <int> numContasExistentes, double _limiteCredito) {
	bool contaJaExiste = false;
	int index = 0;
	Banco banco = Banco();
	static int proximoNumContaCorrente = 0;
	do {
		contaJaExiste = false;
		index = banco.getIndexContaCorrentePorNumConta(proximoNumContaCorrente, numContasExistentes);
		if (index >= 0) {
			contaJaExiste = true;
			proximoNumContaCorrente++;
		}
	} while (contaJaExiste);

	numConta = proximoNumContaCorrente;
	proximoNumContaCorrente++;
	saldo = 0;
	cliente = _cliente;
	vector<Movimentacao> movimentacoes;
	limiteCredito = _limiteCredito;
}

ContaCorrente::ContaCorrente(Cliente _cliente, int _numConta, double _limiteCredito) {
	static int proximoNumContaCorrente = _numConta + 1;
	numConta = _numConta;
	saldo = 0;
	cliente = _cliente;
	limiteCredito = _limiteCredito;
	vector<Movimentacao> movimentacoes;
}
ContaCorrente::~ContaCorrente() {
}
int ContaCorrente::debitarConta(double _valor, string _descricaoMovimentacao)
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
void ContaCorrente::creditarConta(int _valor, string _descricaoMovimentacao)
{
	saldo += _valor;
	Movimentacao novaMovimentacao = Movimentacao(_descricaoMovimentacao, 'C', _valor, numConta);
	movimentacoes.push_back(novaMovimentacao);
}

void ContaCorrente::restaurarMovimentacao(Movimentacao _movimentacao) {
	movimentacoes.push_back(_movimentacao);
}

void ContaCorrente::restaurarSaldo(double _valor) {
	saldo += _valor;
}