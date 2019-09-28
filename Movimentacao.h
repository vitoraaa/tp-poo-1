#pragma once
#include <time.h>
#include <string>
using namespace std;
class Movimentacao
{
private:
	struct tm dataMov;
	string descricao;
	char debitoCredito;
	double valor;

public:
	Movimentacao(string Descricao, char DebitoCredito, double Valor);
	~Movimentacao();

	string getDescricao();
	struct tm getDataMov();
	char getDebitoCredito();
	double getValor();
	

};

