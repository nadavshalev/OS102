#include "account.h"


Account::Account(int id, string password, int amount) :
     id_(id), password_(password), amount_(amount){}

int Account::getAmount()
{
    M.beginread();
    sleep(SLEEP_TIME);
    int amount = amount_;
    M.endread();
    return amount;
}

int Account::deposit(int amount)
{
    M.beginwrite();
    sleep(SLEEP_TIME);
    amount_ += amount;
    M.endwrite();
    return amount_;
}
int Account::withdrew(int amount)
{
	int result = -1;
    M.beginwrite();
    sleep(SLEEP_TIME);
    if(amount_ > amount){
    	amount_ -= amount;
    	result = amount_;
    }
    M.endwrite();
    return amount_;
}

bool Account::toAccount(int amount, Account& account){
	bool sucess = false;
    if(id_ == account.id_)
        return true;
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

int Account::commission(double prec){
    M.beginwrite();
    sleep(SLEEP_TIME);
    int amount = (int)round(amount_ * prec/100);
    amount_ -= amount;
    M.endwrite();
    return amount;
}

string Account::toString(){
	stringstream buffer;
    M.beginread();
	buffer << "Account " << id_ << ": Balance - " << amount_ << "$ , Account password - " << password_ << "\n";
    M.endread();
	return buffer.str();
}

bool compare(Account* a, Account* b)
{
    if(a->id_ < b->id_)
        return 0; //change to 1 if max heap required
    else 
        return 1; //change to 0 if max heap required
}