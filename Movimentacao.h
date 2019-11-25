#pragma once
#include <time.h>
#include <string>
using namespace std;
class Movimentacao
{
private:
	time_t rawDataMov;
	string descricao;
	char debitoCredito;
	double valor;
	int numConta;

public:
	Movimentacao(string Descricao, char DebitoCredito, double Valor, int NumConta, time_t rawDataMov);
	Movimentacao(string Descricao, char DebitoCredito, double Valor, int NumConta);
	~Movimentacao();
	Movimentacao();

	string getDescricao()const;
	struct tm getDataMov()const;
	time_t getRawDataMov()const;
	char getDebitoCredito()const;
	double getValor()const;
	int getNumConta()const;
};
