#pragma once
#include "Conta.h"
#include "DiaBase.h"
#include <vector>
class ContaPoupanca :
	public Conta
{
private:
	vector<DiaBase> diasBase;

public:

	ContaPoupanca(const Cliente& _cliente, const vector <int>& numContasExistentes, const vector<DiaBase>& _diasBase);
	ContaPoupanca(const Cliente& _cliente, const int& _numConta, const vector<DiaBase>& _diasBase);
	~ContaPoupanca();
	ContaPoupanca();
	virtual double getSaldo();
	virtual int debitarConta(double _valor, string _descricaoMovimentacao);
	virtual void creditarConta(int _valor, string _descricaoMovimentacao);
	virtual void restaurarMovimentacao(Movimentacao _movimentacao);
	virtual void restaurarSaldo(double _valor);
	vector<DiaBase> getDiasBase() { return diasBase; };
	int getIndexDiaBase(int _diaBase);
	void creditarDiaBaseIndex(int index, double valor);
	void criarDiaBase(int dia, double valor);
	int getIndexMaiorDiaBaseComSaldo();
};
