#pragma once

class Interface
{
public:
	Interface();
	~Interface();
	int apresentarMenu();
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
	void listarClientes();
	void listarContas();
};
