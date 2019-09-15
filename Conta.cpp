#include "pch.h"
#include "Conta.h"
#include "Cliente.h"
#include <vector>
#include "Movimentacao.h"


Conta::Conta(Cliente _cliente)
{
	numConta = proximoNumConta;
	proximoNumConta++;
	saldo = 0;
	cliente = _cliente;
	vector<Movimentacao> movimentacoes;
}
Conta::~Conta()
{
}


int Conta::getNumConta()
{
	return numConta;
}
double Conta::getSaldo()
{
	return saldo;
}
Cliente Conta::getCliente()
{
	Cliente cliente;

	return cliente;
}
vector<Movimentacao> Conta::getMovimentacoes()
{
	vector<Movimentacao> movimentacoes;
	return movimentacoes;
}
void Conta::debitarConta(int _valor, string _descricaoMovimentacao)
{
}
void Conta::creditarConta(int _valor, string _descricaoMovimentacao)
{
}
vector<Movimentacao> Conta::obterExtrato(time_t _dataInicial, time_t _dataFinal)
{
	vector<Movimentacao> extrato;
	return extrato;
}
vector<Movimentacao> Conta::obterExtrato(time_t _dataInicial)
{
	vector<Movimentacao> extrato;
	return extrato;
}
vector<Movimentacao> Conta::obterExtrato()
{
	vector<Movimentacao> extrato;
	return extrato;
}
