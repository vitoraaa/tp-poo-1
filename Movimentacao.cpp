#include "pch.h"
#include "Movimentacao.h"

using namespace std;

Movimentacao::Movimentacao(string Descricao, char DebitoCredito, double Valor, int NumConta, time_t RawDataMov)
{
	descricao = Descricao;
	debitoCredito = DebitoCredito;
	valor = Valor;
	rawDataMov = RawDataMov;
	numConta = NumConta;
}
Movimentacao::Movimentacao(string Descricao, char DebitoCredito, double Valor, int NumConta)
{
	descricao = Descricao;
	debitoCredito = DebitoCredito;
	valor = Valor;
	rawDataMov = time(0);
	numConta = NumConta;
}

Movimentacao::~Movimentacao()
{
}

Movimentacao::Movimentacao()
{
	descricao = "";
	debitoCredito = ' ';
	valor = 0;
	rawDataMov = 0;
	numConta = -1;
}

string Movimentacao::getDescricao()
{
	return descricao;
}
struct tm Movimentacao::getDataMov()
{
	struct tm dataMov;

	localtime_s(&dataMov, &rawDataMov);
	return dataMov;
}

time_t Movimentacao::getRawDataMov() {
	return rawDataMov;
}
char Movimentacao::getDebitoCredito()
{
	return debitoCredito;
}
double Movimentacao::getValor()
{
	return valor;
}
int Movimentacao::getNumConta()
{
	return numConta;
}