#include "pch.h"
#include "Cliente.h"


Cliente::Cliente(string _nomeCliente, string _cpf_cnpj, string _endereco, string _fone)
{
	nomeCliente = _nomeCliente;
	cpf_cnpj = _cpf_cnpj;
	endereco =_endereco;
	fone = _fone;
}


Cliente::~Cliente()
{
}

string Cliente::getNomeCliente()
{
	return nomeCliente;
}
void Cliente::setNomeCliente(string NomeCliente) {
	nomeCliente = NomeCliente;
}
string Cliente::getCPF_CNPF() {
	return cpf_cnpj;
}
void Cliente::setCPF_CNPF(string CPF_CNPJ) {
	cpf_cnpj = CPF_CNPJ;
}
string Cliente::getEndereco() {
	return endereco;
}
void Cliente::setEndereco(string Endereco) {
	endereco = Endereco;
}
string Cliente::getFone() {
	return fone;
}
void Cliente::setFone(string Fone) {
	fone = Fone;
}