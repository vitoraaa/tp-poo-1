#include "pch.h"
#include "Conta.h"
#include "Cliente.h"
#include "Movimentacao.h"

Conta::Conta(Cliente _cliente)
{

	numConta = proximoNumConta;
	proximoNumConta++;
	cliente = _cliente;
	saldo = 0;
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
	Cliente cliente = new Cliente;
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
