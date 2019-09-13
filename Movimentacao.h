#pragma once
#include<time.h>
#include <string>
using namespace std;
class Movimentacao
{
private:
	time_t dataMov;
	string descricao;
	char debitoCredito;
	double valor;

public:
	Movimentacao(string Descricao, char DebitoCredito, double Valor);
	Movimentacao();
	~Movimentacao();

	string getDescricao();
	time_t getDataMov();
	char getDebitoCredito();
	double getValor();
	

};

