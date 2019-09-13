#include "pch.h"
#include "Movimentacao.h"

using namespace std;

Movimentacao::Movimentacao(string Descricao, char DebitoCredito, double Valor)
{
	descricao = Descricao;
	debitoCredito = DebitoCredito;
	valor = Valor;
	dataMov = time(0);
}

Movimentacao::~Movimentacao()
{
}
Movimentacao::Movimentacao()
{
}

string Movimentacao::getDescricao()
{
	return descricao;
}
time_t Movimentacao::getDataMov()
{
	return dataMov;
}
char Movimentacao::getDebitoCredito()
{
	return debitoCredito;
}
double Movimentacao::getValor()
{
	return valor;
}
