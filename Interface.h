#pragma once
#include <vector>
#include "Movimentacao.h"
class Interface
{
public:
	Interface();
	~Interface();
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
	//Cliente buscaCliente(string _cpf_cnpj);
};
