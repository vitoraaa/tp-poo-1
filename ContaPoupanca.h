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

	ContaPoupanca(Cliente _cliente, vector <int> numContasExistentes, vector<DiaBase> _diasBase);
	ContaPoupanca(Cliente _cliente, int _numConta);
	~ContaPoupanca();
	ContaPoupanca();
	virtual double getSaldo() const;
	virtual int debitarConta(double _valor, string _descricaoMovimentacao);
	virtual void creditarConta(int _valor, string _descricaoMovimentacao);
	virtual void restaurarMovimentacao(Movimentacao _movimentacao);
	virtual void restaurarSaldo(double _valor);
	DiaBase getDiasBase(int _diaBase);
	int getIndexDiaBase(int _diaBase);
	void creditarDiaBaseIndex(int index, double valor);
	void criarDiaBase(int dia, double valor);
	DiaBase getMaiorDiaBaseComSaldo();
	
	
};

