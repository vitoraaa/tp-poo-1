#include "pch.h"
#include "ContaCorrente.h"
#include "Banco.h"
#include "BancoServices.h"

ContaCorrente::ContaCorrente(const Cliente& cliente, vector <int> numContasExistentes, const double& limiteCredito) {
	int index = -1;
	int numConta = 0;

	for (unsigned int i = 0; ; i++) {
		index = BancoServices.getIndexConta(i, numContasExistentes);
		if (index == -1) {
			_numConta = i;
			_saldo = 0;
			_cliente = cliente;
			vector<Movimentacao> movimentacoes = vector<Movimentacao>();
			_limiteCredito = limiteCredito;
			break;
		}
	}
}

ContaCorrente::ContaCorrente(const  Cliente& cliente, const int& numConta, const double& limiteCredito) {
	_numConta = numConta;
	_saldo = 0;
	_cliente = cliente;
	_limiteCredito = limiteCredito;
	vector<Movimentacao> movimentacoes = vector<Movimentacao>();
}

ContaCorrente::~ContaCorrente() {
}

bool ContaCorrente::debitarConta(const double& valor, const string& descricaoMovimentacao)
{
	if ((_saldo + _limiteCredito) >= valor) {
		_saldo -= valor;
		Movimentacao novaMovimentacao = Movimentacao(descricaoMovimentacao, 'D', valor, _numConta);
		_movimentacoes.push_back(novaMovimentacao);
		return true;
	}
	else return false;
}

void ContaCorrente::creditarConta(const int& valor, const string& descricaoMovimentacao)
{
	_saldo += valor;
	Movimentacao novaMovimentacao = Movimentacao(descricaoMovimentacao, 'C', valor, _numConta);
	_movimentacoes.push_back(novaMovimentacao);
}

void ContaCorrente::adicionarMovimentacao(const Movimentacao& movimentacao) {
	_movimentacoes.push_back(movimentacao);
}

void ContaCorrente::somarSaldo(const  double& valor) {
	_saldo += valor;
}

double ContaCorrente::getSaldo()const {
	return _saldo;
}