#pragma once
#include <vector>
#include <string>
using namespace std;
class Conta
{
private:
	int numConta=0;
	double saldo;
	Cliente cliente;
	vector <Movimentacao> movimentacoes;
	static int proximoNumConta;
public:
	Conta(Cliente Cliente);
	~Conta();
};

