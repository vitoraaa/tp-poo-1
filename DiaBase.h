#pragma once
class DiaBase
{
private:
	int _dia;
	double _saldo;
public:
	double getSaldo() const { return _saldo; };
	void addToSaldo(double valor);
	int getDia() const { return _dia; };

	DiaBase(int dia, double saldo);
	~DiaBase();
};
