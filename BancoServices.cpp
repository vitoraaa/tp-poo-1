#include "BancoServices.h"
#include "ContaPoupanca.h"
#include "Interface.h"
#include <iostream>
#include "Cliente.h"
#include <vector>
#include "Cliente.h"
#include "Conta.h"
#include "Banco.h"
#include <sstream>
#include "Banco.h"
#include <fstream>
#include <sstream>

Banco banco = Banco("Banco Vitor");

int BancoServices::diaHoje() {
	time_t rawNow = time(0);
	struct tm dataNow;
	localtime_s(&dataNow, &rawNow);
	return  dataNow.tm_mday;
}

int BancoServices::getIndexConta(const int& numConta, const vector<int>& contas) {
	for (unsigned int i = 0; i < contas.size(); i++)
	{
		if (contas[i] == numConta)return i;
	}
	return -1;
}

void BancoServices::escreverContasCorrentesDB() {
	ofstream myfile;
	myfile.open("ContasCorrentes.txt");

	vector <ContaCorrente> contas = banco.listarContasCorrentes();

	for (unsigned int i = 0; i < contas.size(); i++) {
		string cpfcnpj = contas[i].getCliente().getCPFCNPF();

		myfile << contas[i].getNumConta() << "," << contas[i].getCliente().getCPFCNPF() << "," << contas[i].getLimiteCredito() << "," << ";";
	}
	myfile.close();
}

void BancoServices::escreverContasPoupancaDB() {
	ofstream myfile;
	myfile.open("ContasPoupanca.txt");
	vector <ContaPoupanca> contas = banco.listarContasPoupanca();

	for (unsigned int i = 0; i < contas.size(); i++) {
		string cpfcnpj = contas[i].getCliente().getCPFCNPF();
		vector<DiaBase> diasBase = contas[i].getDiasBase();
		myfile << contas[i].getNumConta() << "," << contas[i].getCliente().getCPFCNPF() << ",";

		for (unsigned int j = 0; j < diasBase.size(); j++) {
			if (diasBase[j].getSaldo() > 0) {
				myfile << diasBase[j].getDia() << "," << diasBase[j].getSaldo() << ",";
			}
		}

		myfile << ";";
	}
	myfile.close();
}

void BancoServices::escreverClientesDB() {
	ofstream myfile;
	myfile.open("Clientes.txt");
	vector <Cliente> clientes = banco.listarClientes();
	for (unsigned int i = 0; i < clientes.size(); i++) {
		myfile << clientes[i].getNome() << "," << clientes[i].getCPFCNPF() << "," << clientes[i].getFone() << "," << clientes[i].getEndereco() << "," << ";";
	}

	myfile.close();
}

void BancoServices::escreverMovimentacoesContasPoupancaDB() {
	ofstream myfile;
	myfile.open("MovimentacoesContasPoupanca.txt");
	vector <ContaPoupanca> contasPoupanca = banco.listarContasPoupanca();
	vector <Movimentacao> movimentacoes;
	unsigned int i = 0;
	unsigned int j = 0;

	for (i = 0; i < contasPoupanca.size(); i++) {
		movimentacoes = contasPoupanca[i].getMovimentacoes();

		for (j = 0; j < movimentacoes.size(); j++) {
			int numConta = movimentacoes[j].getNumConta();
			time_t rawDataMov = movimentacoes[j].getRawDataMov();
			char debitoCredito = movimentacoes[j].getDebitoCredito();
			string descricao = movimentacoes[j].getDescricao();
			double valor = movimentacoes[j].getValor();
			string tipoConta = "p";

			myfile << numConta << "," << rawDataMov << "," << debitoCredito << "," << descricao << "," << valor << "," << tipoConta << "," << ";";
		}
	}

	myfile.close();
}

void BancoServices::escreverMovimentacoesContasCorrentesDB() {
	ofstream myfile;
	myfile.open("MovimentacoesContasCorrentes.txt");
	vector <ContaCorrente> contasCorrentes = banco.listarContasCorrentes();
	vector <Movimentacao> movimentacoes;
	unsigned int i = 0;
	unsigned int j = 0;

	for (i = 0; i < contasCorrentes.size(); i++) {
		movimentacoes = contasCorrentes[i].getMovimentacoes();

		for (j = 0; j < movimentacoes.size(); j++) {
			int numConta = movimentacoes[j].getNumConta();
			time_t rawDataMov = movimentacoes[j].getRawDataMov();
			char debitoCredito = movimentacoes[j].getDebitoCredito();
			string descricao = movimentacoes[j].getDescricao();
			double valor = movimentacoes[j].getValor();
			string tipoConta = "cc";

			myfile << numConta << "," << rawDataMov << "," << debitoCredito << "," << descricao << "," << valor << "," << tipoConta << "," << ";";
		}
	}

	myfile.close();
}

void BancoServices::lerClientesDB() {
	ifstream file;
	string stringArquivo;
	vector<string> arrayStringClientes;
	vector<string> arrayStringCamposCliente;
	string stringCliente;
	Cliente cliente = Cliente();

	file.open("Clientes.txt");
	getline(file, stringArquivo);

	arrayStringClientes = splitString(stringArquivo, ";");

	for (unsigned int i = 0; i < arrayStringClientes.size(); i++) {
		stringCliente = arrayStringClientes[i];

		arrayStringCamposCliente = splitString(stringCliente, ",");

		cliente.setNome(arrayStringCamposCliente[0]);
		cliente.setCPFCNPF(arrayStringCamposCliente[1]);
		cliente.setFone(arrayStringCamposCliente[2]);
		cliente.setEndereco(arrayStringCamposCliente[3]);

		banco.cadastrarCliente(cliente);
	}

	file.close();
}

void BancoServices::lerContasCorrentesDB() {
	ifstream file;
	string stringArquivo;
	vector<string> arrayStringContas;
	vector<string> arrayStringCamposConta;
	string stringConta;
	Cliente cliente = Cliente();

	file.open("ContasCorrentes.txt");
	getline(file, stringArquivo);

	arrayStringContas = splitString(stringArquivo, ";");

	for (unsigned int i = 0; i < arrayStringContas.size(); i++) {
		stringConta = arrayStringContas[i];

		arrayStringCamposConta = splitString(stringConta, ",");
		try {
			cliente = banco.buscaClienteCPFCNPJ(arrayStringCamposConta[1]);
		}
		catch (exception excecao) {
			if (string(excecao.what()) == "ClienteNaoEncontrado") continue;
		}

		int numeroConta = stoi(arrayStringCamposConta[0]);

		double limiteCredito = stod(arrayStringCamposConta[2]);

		banco.criarContaCorrente(cliente, numeroConta, limiteCredito);
	}

	file.close();
}

void BancoServices::lerContasPoupancaDB() {
	ifstream file;
	string stringArquivo;
	vector<string> arrayStringContas;
	vector<string> arrayStringCamposConta;
	string stringConta;
	Cliente cliente = Cliente();

	file.open("ContasPoupanca.txt");
	getline(file, stringArquivo);

	arrayStringContas = splitString(stringArquivo, ";");

	for (unsigned int i = 0; i < arrayStringContas.size(); i++) {
		stringConta = arrayStringContas[i];

		arrayStringCamposConta = splitString(stringConta, ",");
		try {
			cliente = banco.buscaClienteCPFCNPJ(arrayStringCamposConta[1]);
		}
		catch (exception excecao) {
			if (string(excecao.what()) == "ClienteNaoEncontrado") continue;
		}

		int numeroConta = stoi(arrayStringCamposConta[0]);
		vector<DiaBase> diasBase;

		for (int j = 2; j < arrayStringCamposConta.size(); j += 2) {
			DiaBase diaBase = DiaBase(stoi(arrayStringCamposConta[j]), stod(arrayStringCamposConta[j + 1]));
			diasBase.push_back(diaBase);
		}

		banco.criarContaPoupanca(cliente, numeroConta, diasBase);
	}

	file.close();
}

void BancoServices::lerMovimentacoesContasCorrentesDB() {
	ifstream file;
	string stringArquivo;
	vector<string> arrayStringMovimentacoes;
	vector<string> arrayStringCamposMovimentacao;
	string stringMovimentacao;
	Movimentacao movimentacao = Movimentacao();
	string tipoConta = "cc";

	file.open("MovimentacoesContasCorrentes.txt");
	getline(file, stringArquivo);

	arrayStringMovimentacoes = splitString(stringArquivo, ";");

	for (unsigned int i = 0; i < arrayStringMovimentacoes.size(); i++) {
		stringMovimentacao = arrayStringMovimentacoes[i];

		arrayStringCamposMovimentacao = splitString(stringMovimentacao, ",");

		string descricao = arrayStringCamposMovimentacao[3];
		char debitoCredito = arrayStringCamposMovimentacao[2][0];
		double valor = stod(arrayStringCamposMovimentacao[4]);
		int numConta = stoi(arrayStringCamposMovimentacao[0]);
		time_t dataMov = stoi(arrayStringCamposMovimentacao[1]);

		Movimentacao movimentacao = Movimentacao(descricao, debitoCredito, valor, numConta, dataMov);

		banco.adicionarMovimentacao(numConta, movimentacao, tipoConta);
	}

	file.close();
}

void BancoServices::lerMovimentacoesContasPoupancaDB() {
	ifstream file;
	string stringArquivo;
	vector<string> arrayStringMovimentacoes;
	vector<string> arrayStringCamposMovimentacao;
	string stringMovimentacao;
	Movimentacao movimentacao = Movimentacao();
	string tipoConta = "p";

	file.open("MovimentacoesContasPoupanca.txt");
	getline(file, stringArquivo);

	arrayStringMovimentacoes = splitString(stringArquivo, ";");

	for (unsigned int i = 0; i < arrayStringMovimentacoes.size(); i++) {
		stringMovimentacao = arrayStringMovimentacoes[i];

		arrayStringCamposMovimentacao = splitString(stringMovimentacao, ",");

		string descricao = arrayStringCamposMovimentacao[3];
		char debitoCredito = arrayStringCamposMovimentacao[2][0];
		double valor = stod(arrayStringCamposMovimentacao[4]);
		int numConta = stoi(arrayStringCamposMovimentacao[0]);
		time_t dataMov = stoi(arrayStringCamposMovimentacao[1]);

		Movimentacao movimentacao = Movimentacao(descricao, debitoCredito, valor, numConta, dataMov);

		banco.adicionarMovimentacao(stoi(arrayStringCamposMovimentacao[0]), movimentacao, tipoConta);
	}

	file.close();
}

void BancoServices::lerDB() {
	lerClientesDB();
	lerContasCorrentesDB();
	lerContasPoupancaDB();
	lerMovimentacoesContasCorrentesDB();
	lerMovimentacoesContasPoupancaDB();
}

void BancoServices::escreverDB() {
	escreverClientesDB();
	escreverContasCorrentesDB();
	escreverContasPoupancaDB();
	escreverMovimentacoesContasCorrentesDB();
	escreverMovimentacoesContasPoupancaDB();
}

vector<string> BancoServices::splitString(string str, string delimitador) {
	vector<string> arraySubStrings;
	string subString;
	size_t pos = 0;

	while ((pos = str.find(delimitador)) != std::string::npos) {
		subString = str.substr(0, pos);
		arraySubStrings.push_back(subString);
		str.erase(0, pos + delimitador.length());
	}

	return arraySubStrings;
}