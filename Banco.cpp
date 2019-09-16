#include "pch.h"
#include "Banco.h"
#include "Cliente.h"
#include "Conta.h"
#include <algorithm>

Banco::Banco(string _nomeBanco)
{
	nomeBanco = _nomeBanco;
}

Banco::~Banco()
{
}

//Cliente Banco::buscaClienteCPF_CNPJ(string _cpf_cnpj)
//{
//
//	for (auto i = clientes.begin(); i != clientes.end(); i++)
//	{
//
//		if ((*i).getCPF_CNPF() == _cpf_cnpj)
//		{
//			return (*i);
//		}
//	}
//	return 
//}
void Banco::cadastrarCliente(Cliente _cliente)
{
	clientes.push_back(_cliente);
}
void Banco::criarConta(Cliente _cliente)
{
	Conta conta = Conta(_cliente);
	contas.push_back(conta);
}

int Banco::excluirCliente(string _cpf_cnpj)
{
	auto i = clientes.begin();

	for (auto i = clientes.begin(); i != clientes.end(); i++)
	{

		if ((*i).getCPF_CNPF() == _cpf_cnpj)
		{
			clientes.erase(i);
			return 1;
		}
	}
	return 0;
}
void Banco::excluirConta(int _numConta)
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
double Banco::obterSaldo(int _numConta)
{
	double saldo = 0;
		return saldo;
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
	return clientes;
}
vector<Conta> Banco::listarContas()
{
	return contas;
}
void Banco::gravarDados()
{
}
void Banco::lerDados()
{
}
