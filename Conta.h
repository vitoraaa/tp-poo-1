#pragma once
#include <vector>
#include <string>
#include <time.h>
#include "Cliente.h"
#include "Movimentacao.h"

using namespace std;

class Conta
{
protected:
	int numConta;
	double saldo;
	Cliente cliente;
	vector<Movimentacao> movimentacoes;
	

public:
	Conta();
	Conta(Cliente _cliente, vector <int> numContasExistentes);
	Conta(Cliente _cliente, int _numConta);
	~Conta();

	int getNumConta();
	Cliente getCliente();
	vector<Movimentacao> getMovimentacoes();

	virtual double getSaldo() const;
	virtual int debitarConta(double _valor, string _descricaoMovimentacao) = 0 ;
	virtual void creditarConta(int _valor, string _descricaoMovimentacao) = 0 ;	
	virtual void restaurarMovimentacao(Movimentacao _movimentacao) = 0;
	virtual void restaurarSaldo(double _valor)= 0;
};
