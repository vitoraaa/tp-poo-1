#pragma once

#include "BancoServices.h"
#include "ContaPoupanca.h"
#include "Interface.h"
#include <iostream>
#include "Cliente.h"
#include <vector>
#include "Cliente.h"
#include "Conta.h"
#include "Banco.h"
#include <sstream>
static class BancoServices
{
public:
	Banco banco;
	int diaHoje();
	int getIndexConta(const int& numConta, const vector<int>& numContasPoupancaExistentes);
	void lerDB();
	void escreverDB();
	void escreverContasPoupancaDB();
	void escreverContasCorrentesDB();
	void escreverClientesDB();
	void lerContasCorrentesDB();
	void lerContasPoupancaDB();
	void lerClientesDB();
	void escreverMovimentacoesContasPoupancaDB();
	void escreverMovimentacoesContasCorrentesDB();
	void lerMovimentacoesContasCorrentesDB();
	void lerMovimentacoesContasPoupancaDB();
	vector<string> splitString(string str, string delimitador);
} BancoServices;
