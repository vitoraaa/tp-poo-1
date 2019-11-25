#include "pch.h"
#include "Cliente.h"

Cliente::Cliente(string nome, string cpfcnpj, string endereco, string fone)
{
	nome = nome;
	cpfcnpj = cpfcnpj;
	endereco = endereco;
	fone = fone;
}

Cliente::Cliente()
{
}

Cliente::~Cliente()
{
}

string Cliente::getNome() const
{
	return nome;
}
void Cliente::setNome(string Nome)
{
	nome = Nome;
}
string Cliente::getCPFCNPF() const
{
	return cpfcnpj;
}
void Cliente::setCPFCNPF(string CPFCNPJ)
{
	cpfcnpj = CPFCNPJ;
}
string Cliente::getEndereco() const
{
	return endereco;
}
void Cliente::setEndereco(string Endereco)
{
	endereco = Endereco;
}
string Cliente::getFone() const
{
	return fone;
}
void Cliente::setFone(string Fone)
{
	fone = Fone;
}