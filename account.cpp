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

void Account::deposit(int amount)
{
    M.beginwrite();
    amount_ += amount;
    M.endwrite();
}
bool Account::withdrew(int amount)
{
	bool sucess = false;
    M.beginwrite();
    if(amount_ > amount){
    	amount_ -= amount;
    	sucess = true;
    }
    M.endwrite();
    return sucess;
}

bool Account::toAcount(int amount, Account account){
	bool sucess = false;
	// lock by order
	if(id_ > account.id_){
		M.beginwrite();
		account.M.beginwrite();
	}
	else{
		account.M.beginwrite();
		M.beginwrite();
	}
	// extchange money
    if(amount_ > amount){
    	amount_ -= amount;
    	account.deposit(amount);
    	sucess = true;
    }
    // unlock by reverse order
    if(id_ > account.id_){
		account.M.beginwrite();
		M.beginwrite();
	}
	else{
		M.beginwrite();
		account.M.beginwrite();
	}
	return sucess;
}