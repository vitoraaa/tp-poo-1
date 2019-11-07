#pragma once
#include <iostream>
#include <string>
using namespace std;
class Cliente
{
private:
	string nome;
	string cpf_cnpj;
	string endereco;
	string fone;
public:

	Cliente(string _nome, string _cpf_cnpj, string _endereco, string _fone);
	Cliente();
	~Cliente();

	string getNome();
	void setNome(string nome);
	string getCPF_CNPF();
	void setCPF_CNPF(string CPF_CNPJ);
	string getEndereco();
	void setEndereco(string Endereco);
	string getFone();
	void setFone(string Fone);
};
