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

Cliente Banco::buscaClienteCPF_CNPJ(string _cpf_cnpj)
{

	for (auto i = clientes.begin(); i != clientes.end(); i++)
	{

		if ((*i).getCPF_CNPF() == _cpf_cnpj)
		{
			return (*i);
		}
	}
	Cliente clienteNaoEncontrado = Cliente("CLIENTE_NAO_ENCONTRADO", "CLIENTE_NAO_ENCONTRADO", "CLIENTE_NAO_ENCONTRADO", "CLIENTE_NAO_ENCONTRADO");
	return clienteNaoEncontrado;
}
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
			if (buscarContaPorCliente(*i).size() == 0)
			{
				clientes.erase(i);
				return 1;
			}
			else
			{
				return 2;
			}
		}
	}
	return 0;
}

int Banco::excluirConta(int _numConta)
{
	auto i = contas.begin();

	for (auto i = contas.begin(); i != contas.end(); i++)
	{

		if ((*i).getNumConta() == _numConta)
		{
			contas.erase(i);
			return 1;
		}
	}
	return 0;
}
void Banco::efetuarDeposito(int _numConta, int _valor)
{
	contas[getIndexContaPorNumConta(_numConta)].creditarConta(_valor, "Deposito");	
}
void Banco::efetuarSaque(int _numConta, int _valor)
{
	contas[getIndexContaPorNumConta(_numConta)].debitarConta(_valor, "Saque");	
}
void Banco::efetuarTransferencia(int _numContaOrigem, int _numContaDestino, int _valor)
{
	string descricao; 
	descricao = "Transferencia para a conta " + std::to_string(_numContaDestino);
	contas[getIndexContaPorNumConta(_numContaOrigem)].debitarConta(_valor, descricao);
	descricao = "Transferencia da conta " + std::to_string(_numContaOrigem);
	contas[getIndexContaPorNumConta(_numContaDestino)].creditarConta(_valor, descricao);
}
void Banco::cobrarTarifa()
{
	for (int i = 0; i< contas.size(); i++){
		contas[i].debitarConta(15, "Cobranca de tarifa");
	}
}
void Banco::cobrarCPMF()
{
	for (int i = 0; i< contas.size(); i++){
		int valorCobrado = calcularCPMF(i);
		contas[i].debitarConta(valorCobrado, "Cobranca de CPMF");
	}
}
double Banco::obterSaldo(int _numConta)
{
	return contas[getIndexContaPorNumConta(_numConta)].getSaldo();
}
vector <Movimentacao> Banco::obterExtrato(int _numConta)
{
return contas[getIndexContaPorNumConta(_numConta)].getMovimentacoes();
}
vector<Movimentacao> Banco::obterExtrato(int _numConta, time_t _dataInicial)
{
	vector<Movimentacao> movimentacoes = contas[getIndexContaPorNumConta(_numConta)].getMovimentacoes();
	vector<Movimentacao> movimentacoesFiltradas;
	for ( int i = 0 ; i < movimentacoes.size(); i++){
		if (difftime(time(0),movimentacoes[i].getDataMov()) <= (difftime(time(0),_dataInicial)) ){
			movimentacoesFiltradas.push_back(movimentacoes[i]);
		}
	}
	return movimentacoesFiltradas;
}
vector<Movimentacao> Banco::obterExtrato(int _numConta, time_t _dataInicial, time_t _dataFinal)
{
	vector<Movimentacao> movimentacoes = contas[getIndexContaPorNumConta(_numConta)].getMovimentacoes();
	vector<Movimentacao> movimentacoesFiltradas;
	for ( int i = 0 ; i < movimentacoes.size(); i++){
		if (difftime(time(0),movimentacoes[i].getDataMov()) <= (difftime(time(0),_dataInicial)) ){
			movimentacoesFiltradas.push_back(movimentacoes[i]);
		}
	}
	return movimentacoesFiltradas;
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
vector<Conta> Banco::buscarContaPorCliente(Cliente _cliente)
{

	vector<Conta> contasCliente;
	for (auto i = contas.begin(); i != contas.end(); i++)
	{

		if ((*i).getCliente().getCPF_CNPF() == _cliente.getCPF_CNPF())
		{
			contasCliente.push_back(*i);
		}
	}
	return contasCliente;
}
int Banco::getIndexContaPorNumConta(int _numConta)
{
	for (int i = 0; i < contas.size(); i++)
	{

		if (contas[i].getNumConta()==_numConta)
		{
			return i;
		}
	}
	return -1;
}
int Banco::calcularCPMF(int i){
	int valorCalculado = 0;
	return valorCalculado;
}