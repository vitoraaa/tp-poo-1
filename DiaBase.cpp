#include "pch.h"
#include "DiaBase.h"

void DiaBase::addToSaldo(double valor) {
	_saldo += valor;
}
DiaBase::DiaBase(int dia, double saldo) {
	_dia = dia;
	_saldo = saldo;
}
DiaBase::~DiaBase() {
}