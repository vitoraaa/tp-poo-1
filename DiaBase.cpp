#include "pch.h"
#include "DiaBase.h"



DiaBase::DiaBase() {

}
void DiaBase::addToSaldo(double valor) {
	saldo += valor;
}
DiaBase::DiaBase(int _diaBase, double _saldoDiaBase) {
	dia= _diaBase;
	saldo= _saldoDiaBase;
}
DiaBase::~DiaBase() {

}