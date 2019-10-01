#pragma once
#include <vector>
#include "Movimentacao.h"
class Interface
{
public:
	Interface();
	~Interface();
	void lerDados();
	void escreverDados();
	void escreverDadosContas();
	void escreverDadosClientes();
	void lerContasDB();
	void lerClientesDB();
	void apresentarMenu();
	void cadastrarCliente();
	void criarConta();
	void excluirCliente();
	void excluirConta();
	void efetuarDeposito();
	void efetuarSaque();
	void efetuarTransferencia();
	void cobrarTarifa();
	void cobrarCPMF();
	void obterSaldo();
	void obterExtrato();
	void listarClientes(bool voltarAoMenu);
	void listarContas(bool voltarAoMenu);
	void listarMovimentacoes(std::vector <Movimentacao> movimentacoes);
	vector<string> splitString(string str, string delimitador);
	//Cliente buscaCliente(string _cpf_cnpj);
};
