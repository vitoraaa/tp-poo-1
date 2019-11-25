#pragma once
#include <iostream>
#include <string>
using namespace std;
class Cliente
{
private:
	string nome;
	string cpfcnpj;
	string endereco;
	string fone;
public:

	Cliente(string nome, string cpfcnpj, string endereco, string fone);
	Cliente();
	~Cliente();

	string getNome() const;
	void setNome(string nome);
	string getCPFCNPF() const;
	void setCPFCNPF(string CPFCNPJ);
	string getEndereco()const;
	void setEndereco(string Endereco);
	string getFone() const;
	void setFone(string Fone);
};
