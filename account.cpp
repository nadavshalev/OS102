#include "account.h"

//********************************************
// function name: Account
// Description: init Account class
//********************************************
Account::Account(int id, string password, int amount) :
     id_(id), password_(password), amount_(amount){}

//********************************************
// function name: getAmount
//********************************************
int Account::getAmount()
{
    M.beginread();
    sleep(SLEEP_TIME);
    int amount = amount_;
    M.endread();
    return amount;
}

//********************************************
// function name: deposit
//********************************************
int Account::deposit(int amount)
{
    M.beginwrite();
    sleep(SLEEP_TIME);
    amount_ += amount;
    M.endwrite();
    return amount_;
}

//********************************************
// function name: Monitor
// Description: implement withdrew. return -1 on error
//********************************************
int Account::withdrew(int towithdrew)
{
	int result = -1;
    M.beginwrite();
    sleep(SLEEP_TIME);
    if(amount_ > towithdrew){
    	amount_ -= towithdrew;
    	result = amount_;
    }
    M.endwrite();
    return result;
}

//********************************************
// function name: toAccount
// Description: implement toAccount. return false on error
//********************************************
bool Account::toAccount(int amount, Account& account){
	bool sucess = false;
    // lock accounts
    if(id_ == account.id_)
        return true;
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

//********************************************
// function name: commission
// Description: get commition from account
//********************************************
int Account::commission(double prec){
    M.beginwrite();
    sleep(SLEEP_TIME);
    int amount = (int)round(amount_ * prec/100);
    amount_ -= amount;
    M.endwrite();
    return amount;
}

//********************************************
// function name: toString
// Description: serialize account to string
//********************************************
string Account::toString(){
	stringstream buffer;
    M.beginread();
	buffer << "Account " << id_ << ": Balance - " << amount_ << "$ ,\t Account password - " << password_ << "\n";
    M.endread();;
	return buffer.str();
}

//********************************************
// function name: compare
// Description: static. for sorting func
//********************************************
bool compare(Account* a, Account* b)
{
    if(a->id_ < b->id_)
        return 1; 
    else 
        return 0; 
}