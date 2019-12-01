#include "pch.h"
#include "Cliente.h"

Cliente::Cliente(string nome, string cpfcnpj, string endereco, string fone)
{
	_nome = nome;
	_cpfcnpj = cpfcnpj;
	_endereco = endereco;
	_fone = fone;
}

Cliente::Cliente()
{
}

Cliente::~Cliente()
{
}

string Cliente::getNome() const
{
	return _nome;
}
void Cliente::setNome(string nome)
{
	_nome = nome;
}
string Cliente::getCPFCNPF() const
{
	return _cpfcnpj;
}
void Cliente::setCPFCNPF(string cpfcnpj)
{
	_cpfcnpj = cpfcnpj;
}
string Cliente::getEndereco() const
{
	return _endereco;
}
void Cliente::setEndereco(string endereco)
{
	_endereco = endereco;
}
string Cliente::getFone() const
{
	return _fone;
}
void Cliente::setFone(string Fone)
{
	_fone = Fone;
}