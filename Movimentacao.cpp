#include "pch.h"
#include "Movimentacao.h"

using namespace std;

Movimentacao::Movimentacao(string Descricao, char DebitoCredito, double Valor)
{
	descricao = Descricao;
	debitoCredito = DebitoCredito;
	valor = Valor;
	time_t rawtime = time(0);
	localtime_s(&dataMov, &rawtime);

}

Movimentacao::~Movimentacao()
{
}


string Movimentacao::getDescricao()
{
	return descricao;
}
struct tm Movimentacao::getDataMov()
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
