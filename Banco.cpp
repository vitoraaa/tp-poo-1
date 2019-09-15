#include "pch.h"
#include "Banco.h"
#include "Cliente.h"
#include "Conta.h"

Banco::Banco(string _nomeBanco)
{
	nomeBanco = _nomeBanco;
}

Banco::~Banco()
{
}

void Banco::inserirCliente(Cliente _cliente)
{
	
}
void Banco::criarConta(Conta _conta)
{
}
void Banco::deletarCliente(int _cnp_cnpj)
{
}
void Banco::deletarConta(int _numConta)
{
}
void Banco::efetuarDeposito(int _numConta, int _valor)
{
}
void Banco::efetuarSaque(int _numConta, int valor)
{
}
void Banco::efetuarTransferencia(int _numContaOrigem, int _numContaDestino, int _valor)
{
}
void Banco::cobrarTarifa()
{
}
void Banco::cobrarCPMF()
{
}
void Banco::obterSaldo(int _numConta)
{
}
void Banco::obterExtrato(int _numConta)
{
}
void Banco::obterExtrato(int _numConta, time_t _dataInicial)
{
}
void Banco::obterExtrato(int _numConta, time_t _dataInicial, time_t _dataFinal)
{
}
vector<Cliente> Banco::listarClientes()
{
}
vector<Contas> Banco::listarContas()
{
}
void Banco::gravarDados()
{
}
void Banco::lerDados()
{
}
