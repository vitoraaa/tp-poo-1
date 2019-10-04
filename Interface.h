#pragma once
#include <vector>
#include "Movimentacao.h"
class Interface
{
public:
	Interface();
	~Interface();
	void lerDB();
	void escreverDB(bool voltarAoMenu);
	void escreverContasDB();
	void escreverClientesDB();
	void escreverMovimentacoesDB();
	void lerContasDB();
	void lerClientesDB();
	void lerMovimentacoesDB();
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
	void inicializarAplicacao();
	void obterExtrato();
	void fecharAplicacao();
	string getOpcaoUsuario();
	struct tm montaData(char c);
	void listarClientes(bool voltarAoMenu);
	void listarContas(bool voltarAoMenu);
	void listarMovimentacoes(std::vector <Movimentacao> movimentacoes);
	vector<string> splitString(string str, string delimitador);
};
