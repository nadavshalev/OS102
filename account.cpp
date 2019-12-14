#include "account.h"


Account::Account(int amount, string password, int id) :
     amount_(amount),password_(password),id_(id) {}

int Account::getAmount()
{
    M.beginread();
    sleep(SLEEP_TIME);
    int amount = amount_;
    M.endread();
    return amount;
}

void Account::deposit(int amount)
{
    M.beginwrite();
    sleep(SLEEP_TIME);
    amount_ += amount;
    M.endwrite();
}
bool Account::withdrew(int amount)
{
	bool sucess = false;
    M.beginwrite();
    sleep(SLEEP_TIME);
    if(amount_ > amount){
    	amount_ -= amount;
    	sucess = true;
    }
    M.endwrite();
    return sucess;
}

bool Account::toAccount(int amount, Account& account){
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
    sleep(SLEEP_TIME);
	// extchange money
    if(amount_ > amount){
    	amount_ -= amount;
    	account.amount_ += amount;
    	sucess = true;
    }
    // unlock by reverse order
    if(id_ > account.id_){
		account.M.endwrite();
		M.endwrite();
	}
	else{
		M.endwrite();
		account.M.endwrite();
	}
	return sucess;
}

string Account::toString(){
	stringstream buffer;
	buffer << "Account " << id_ << ": Balance - " << amount_ << "$ , Account password - " << password_;
	return buffer.str();
}