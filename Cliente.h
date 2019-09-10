#pragma once
#include <iostream>
#include <string>
using namespace std;
class Cliente
{
private:
	string nomeCliente;
	string cpf_cnpj; 
	string endereco;
	string fone;
public:

	Cliente(string _nomeCliente,string _cpf_cnpj,string _endereço,string _fone);
	~Cliente();

	string getNomeCliente();
	void setNomeCliente(string NomeCliente);
	string getCPF_CNPF();
	void setCPF_CNPF(string CPF_CNPJ);
	string getEndereco();
	void setEndereco(string Endereco);
	string getFone();
	void setFone(string Fone);


};

