#include "ContaPoupanca.h"
#include "Interface.h"
#include <iostream>
#include "Cliente.h"
#include <vector>
#include "Cliente.h"
#include "Conta.h"
#include "Banco.h"
#include <sstream>
#include "BancoServices.h"

using namespace std;

ContaPoupanca::ContaPoupanca(const Cliente& cliente, const vector <int>& numContasExistentes, const vector<DiaBase>& diasBase) {
	int index = -1;
	int numConta = 0;

	for (unsigned int i = 0; ; i++) {
		index = BancoServices.getIndexConta(i, numContasExistentes);
		if (index == -1) {
			_numConta = i;
			_saldo = 0;
			_cliente = cliente;
			vector<Movimentacao> movimentacoes = vector<Movimentacao>();
			_diasBase = diasBase;
			break;
		}
	}
}

ContaPoupanca::ContaPoupanca(const Cliente& cliente, const int& numConta, const vector<DiaBase>& diasBase) {
	_numConta = numConta;
	_saldo = 0;
	_cliente = cliente;
	vector<Movimentacao> movimentacoes = vector<Movimentacao>();
	_diasBase = diasBase;
}

ContaPoupanca::~ContaPoupanca() {
}

double ContaPoupanca::getSaldo() const {
	double saldo = 0;
	for (unsigned int i = 0; i < _diasBase.size(); i++) {
		saldo += _diasBase.at(i).getSaldo();
	}
	return saldo;
}

bool ContaPoupanca::debitarConta(const double& valor, const string& descricaoMovimentacao)
{
	int hoje = BancoServices.diaHoje();

	if (_saldo >= valor) {
		int index = -1;
		while (index == -1) {
			index = getIndexDiaBase(hoje);
			hoje--;
		}

		if (_diasBase[index].getSaldo() >= valor) {
			_diasBase[index].addToSaldo(-valor);
			Movimentacao novaMovimentacao = Movimentacao(descricaoMovimentacao, 'D', valor, _numConta);
			_movimentacoes.push_back(novaMovimentacao);
			return true;
		}
		else {
			double valorRestante = valor - _diasBase[index].getSaldo();
			_diasBase[index].addToSaldo(-_diasBase[index].getSaldo());
			if (getSaldo() >= valorRestante) {
				debitarConta(valorRestante, descricaoMovimentacao);
			}
			else { return false; }
		}
	}
	else return 0;
}
void ContaPoupanca::creditarJuros(const int& index) {
	auto valor = _diasBase[index].getSaldo() * 0.01;
	somarSaldoDiaBase(index, valor);
	_movimentacoes.push_back(Movimentacao("Juros", 'C', valor, _numConta));
}
void ContaPoupanca::somarSaldoDiaBase(const int& index, const double& valor) {
	_diasBase.at(index).addToSaldo(valor);
}

void  ContaPoupanca::creditarConta(const int& valor, const string& descricaoMovimentacao)
{
	int diaBaseMovimentacao = BancoServices.diaHoje();

	if (diaBaseMovimentacao >= 29 && diaBaseMovimentacao <= 31) {
		diaBaseMovimentacao = 28;
	}
	int index = getIndexDiaBase(diaBaseMovimentacao);
	if (index >= 0) {
		somarSaldoDiaBase(index, valor);
	}
	else {
		adicionarDiaBase(diaBaseMovimentacao, valor);
	}
	Movimentacao novaMovimentacao = Movimentacao(descricaoMovimentacao, 'C', valor, _numConta);
	_movimentacoes.push_back(novaMovimentacao);
}

void ContaPoupanca::adicionarDiaBase(const int& dia, const double& valor) {
	DiaBase diaBase = DiaBase(dia, valor);
	_diasBase.push_back(diaBase);
}

void ContaPoupanca::adicionarMovimentacao(const Movimentacao& movimentacao) {
	_movimentacoes.push_back(movimentacao);
}

void  ContaPoupanca::somarSaldo(const double& valor) {
	_saldo += valor;
}

int ContaPoupanca::getIndexDiaBase(const int& dia)const {
	int index = -1;

	for (unsigned int i = 0; i < _diasBase.size(); i++) {
		if (_diasBase.at(i).getDia() == dia)return i;
	}
	return index;
}