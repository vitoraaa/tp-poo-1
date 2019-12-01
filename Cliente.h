#pragma once
#include <iostream>
#include <string>
using namespace std;
class Cliente
{
private:
	string _nome;
	string _cpfcnpj;
	string _endereco;
	string _fone;
public:

	Cliente(string nome, string cpfcnpj, string endereco, string fone);
	Cliente();
	~Cliente();

	string getNome() const;
	void setNome(string nome);
	string getCPFCNPF() const;
	void setCPFCNPF(string cpfcnpj);
	string getEndereco()const;
	void setEndereco(string endereco);
	string getFone() const;
	void setFone(string fone);
};
