#include "pch.h"
#include "ContaPoupanca.h"
#include "Interface.h"
#include <iostream>
#include "Cliente.h"
#include <vector>
#include "Cliente.h"
#include "Conta.h"
#include "Banco.h"
#include <sstream>

using namespace std;

ContaPoupanca::ContaPoupanca(const Cliente& _cliente, const vector <int>& numContasExistentes, const vector<DiaBase>& _diasBase = vector<DiaBase>()) {
	bool contaJaExiste = false;
	int index = 0;
	Banco banco = Banco();
	static int proximoNumConta = 0;
	do {
		contaJaExiste = false;
		index = banco.getIndexContaPoupancaPorNumConta(proximoNumConta, numContasExistentes);
		if (index >= 0) {
			contaJaExiste = true;
			proximoNumConta++;
		}
	} while (contaJaExiste);

	numConta = proximoNumConta;
	proximoNumConta++;
	saldo = 0;
	cliente = _cliente;
	vector<Movimentacao> movimentacoes;
	diasBase = _diasBase;
}
ContaPoupanca::ContaPoupanca() {
}
ContaPoupanca::ContaPoupanca(const Cliente& _cliente, const int& _numConta, const vector<DiaBase>& _diasBase = vector<DiaBase>()) {
	static int proximoNumConta = _numConta + 1;
	numConta = _numConta;
	saldo = 0;
	cliente = _cliente;
	vector<Movimentacao> movimentacoes;
	diasBase = _diasBase;
}
ContaPoupanca::~ContaPoupanca() {
}

double ContaPoupanca::getSaldo() {
	int saldo = 0;
	for (unsigned int i = 0; i < diasBase.size(); i++) {
		saldo += diasBase.at(i).getSaldo();
	}
	return saldo;
}

int ContaPoupanca::getIndexMaiorDiaBaseComSaldo() {
	DiaBase maiorDiaBase = diasBase.at(0);
	int index = 0;

	for (unsigned int i = 1; i < diasBase.size(); i++) {
		if (diasBase.at(i).getDia() > maiorDiaBase.getDia() && diasBase.at(i).getSaldo() > 0) {
			maiorDiaBase = diasBase.at(i);
			index = i;
		}
	}
	return index;
}

int ContaPoupanca::debitarConta(double valor, string descricaoMovimentacao)
{
	if (getSaldo() >= valor) {
		int index = getIndexMaiorDiaBaseComSaldo();

		if (diasBase[index].getSaldo() >= valor) {
			diasBase[index].addToSaldo(-valor);

			Movimentacao novaMovimentacao = Movimentacao(descricaoMovimentacao, 'D', valor, numConta);
			movimentacoes.push_back(novaMovimentacao);
			return 1;
		}
		else {
			valor -= diasBase[index].getSaldo();
			diasBase[index].addToSaldo(-diasBase[index].getSaldo());

			/*Movimentacao novaMovimentacao = Movimentacao(descricaoMovimentacao, 'D', maiorDiaBase.getSaldo(), numConta);
			movimentacoes.push_back(novaMovimentacao);*/

			debitarConta(valor, descricaoMovimentacao);
		}
	}
	else return 0;
}

void ContaPoupanca::creditarDiaBaseIndex(int index, double valor) {
	diasBase.at(index).addToSaldo(valor);
}

void  ContaPoupanca::creditarConta(int valor, string descricaoMovimentacao)
{
	time_t rawNow = time(0);
	struct tm dataNow;
	localtime_s(&dataNow, &rawNow);
	int hoje = dataNow.tm_mday;
	int diaBaseMovimentacao = hoje;

	if (hoje >= 29 && hoje <= 31) {
		diaBaseMovimentacao = 28;
	}
	int index = getIndexDiaBase(hoje);
	if (index >= 0) {
		creditarDiaBaseIndex(index, valor);
		Movimentacao novaMovimentacao = Movimentacao(descricaoMovimentacao, 'C', valor, numConta);
		movimentacoes.push_back(novaMovimentacao);
	}
	else {
		criarDiaBase(hoje, valor);
	}
}

void ContaPoupanca::criarDiaBase(int dia, double valor) {
	DiaBase diaBase = DiaBase(dia, valor);
}

void ContaPoupanca::restaurarMovimentacao(Movimentacao _movimentacao) {
	movimentacoes.push_back(_movimentacao);
}

void  ContaPoupanca::restaurarSaldo(double _valor) {
	saldo += _valor;
}

int ContaPoupanca::getIndexDiaBase(int dia) {
	int index = -1;

	for (unsigned int i = 0; i < diasBase.size(); i++) {
		if (diasBase.at(i).getDia() == dia)return i;
	}
	return index;
}