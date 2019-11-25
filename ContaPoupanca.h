#pragma once
#include "Conta.h"
#include "DiaBase.h"
#include <vector>
class ContaPoupanca :
	public Conta
{
private:
	vector<DiaBase> _diasBase;

public:

	ContaPoupanca(const Cliente& cliente, const vector <int>& numContasExistentes, const vector<DiaBase> & = vector<DiaBase>());
	ContaPoupanca(const Cliente& cliente, const int& numConta, const vector<DiaBase> & = vector<DiaBase>());
	~ContaPoupanca();

	virtual double getSaldo()const;
	virtual bool debitarConta(const double& valor, const string& descricaoMovimentacao);
	virtual void creditarConta(const int& valor, const string& descricaoMovimentacao);
	virtual void adicionarMovimentacao(const Movimentacao& movimentacao);
	virtual void somarSaldo(const double& valor);

	vector<DiaBase> getDiasBase() { return _diasBase; };
	int getIndexDiaBase(const int& diaBase) const;
	void somarSaldoDiaBase(const int& index, const double& valor);
	void adicionarDiaBase(const int& dia, const double& valor);
};
