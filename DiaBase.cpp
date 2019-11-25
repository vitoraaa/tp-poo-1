#include "pch.h"
#include "DiaBase.h"

DiaBase::DiaBase() {
}
void DiaBase::addToSaldo(double valor) {
	saldo += valor;
}
DiaBase::DiaBase(int diaBase, double saldoDiaBase) {
	dia = diaBase;
	saldo = saldoDiaBase;
}
DiaBase::~DiaBase() {
}