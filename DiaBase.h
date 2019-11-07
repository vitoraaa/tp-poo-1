#pragma once
class DiaBase
{
private:
	int dia;
	double saldo;
public:
	double getSaldo() const { return saldo; };
	void addToSaldo(double valor);
	int getDia() const { return dia; };

	DiaBase();
	DiaBase(int diaBase, double saldoDiaBase);
	~DiaBase();
};
