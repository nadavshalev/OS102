#include "account.h"


Account::Account(int amount, int password, int id) :
     amount_(amount),password_(password),id_(id) {}

int Account::getAmount()
{
    M.beginread();
    int amount = amount_;
    M.endread();
    return amount;
}

void Account::setAmount(int amount)
{
    M.beginwrite();
    amount_ = amount;
    M.endwrite();
}