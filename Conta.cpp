#include "pch.h"
#include "Conta.h"
#include "Cliente.h"
#include "Banco.h"
#include <vector>
#include "Movimentacao.h"




Conta::Conta(Cliente _cliente,  vector <int> numContasExistentes)

{
	bool contaJaExiste = false;
	int index = 0;
	Banco banco = Banco();
	static int proximoNumConta = 0;
	do {
		contaJaExiste = false;
		index = banco.getIndexContaPorNumConta(proximoNumConta,numContasExistentes);
		if (index >= 0) {
			contaJaExiste = true;
			proximoNumConta++;
		}
	} while (contaJaExiste);

	numConta = proximoNumConta;
	proximoNumConta++;
	saldo = 0;
	cliente = _cliente;
	vector<Movimentacao> movimentacoes;
}
Conta::Conta(Cliente _cliente, int _numConta)
{
	static int proximoNumConta = _numConta + 1;
	numConta = _numConta;
	saldo = 0;
	cliente = _cliente;
	vector<Movimentacao> movimentacoes;
}
Conta::~Conta()
{
}
Conta::Conta()
{
}

int Conta::getNumConta()
{
	return numConta;
}
//double Conta::getSaldo()
//{
//	return saldo;
//}
Cliente Conta::getCliente()
{
	return cliente;
}
vector<Movimentacao> Conta::getMovimentacoes()
{
	return movimentacoes;
}
int Conta::debitarConta(double _valor, string _descricaoMovimentacao)
{
	if (saldo >= _valor) {
		saldo -= _valor;
		Movimentacao novaMovimentacao = Movimentacao(_descricaoMovimentacao, 'D', _valor, numConta);
		movimentacoes.push_back(novaMovimentacao);
		return 1;
	}
	else {
		return 0;
	}

}
void Conta::creditarConta(int _valor, string _descricaoMovimentacao)
{
	saldo += _valor;
	Movimentacao novaMovimentacao = Movimentacao(_descricaoMovimentacao, 'C', _valor, numConta);
	movimentacoes.push_back(novaMovimentacao);
}

void Conta::restaurarMovimentacao(Movimentacao _movimentacao) {
	movimentacoes.push_back(_movimentacao);
}

void Conta::restaurarSaldo(double _valor) {
	saldo += _valor;
}
