#include "pch.h"
#include "Conta.h"
#include "Cliente.h"
#include "Movimentacao.h"


Conta::Conta(Cliente _cliente)
{
	saldo = 0;
	cliente = _cliente;
}


Conta::~Conta()
{
}
