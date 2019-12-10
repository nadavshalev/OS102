#include "account.h"
account::account(int amount, int password, int id) :
     amount_(amount),password_(password),id_(id) {}

int account::get_amount()
{
    M.beginread()
    int amount=amount_;
    M.endread()
    return amount;
}

int account::set_amount(int amount)
{
    M.beginwrite()
    amount_=amount;
    M.endwrite()
}