#include "account.h"


Account::Account(int id, string password, int amount) :
     id_(id), password_(password), amount_(amount){}

int Account::getAmount()
{
    // cout << id_ << "start R getAmount\n";
    M.beginread();
    // cout << id_ << "R getAmount\n";
    sleep(SLEEP_TIME);
    int amount = amount_;
    M.endread();
    // cout << id_ << "end R getAmount\n";
    return amount;
}

int Account::deposit(int amount)
{
    // cout << id_ << "start W deposit\n";
    M.beginwrite();
    // cout << id_ << "W deposit\n";
    sleep(SLEEP_TIME);
    amount_ += amount;
    M.endwrite();
    // cout << id_ << "end W deposit\n";
    return amount_;
}
int Account::withdrew(int towithdrew)
{
	int result = -1;
    // cout << id_ << "start W withdrew\n";
    M.beginwrite();
    // cout << id_ << "W withdrew\n";
    sleep(SLEEP_TIME);
    if(amount_ > towithdrew){
    	amount_ -= towithdrew;
    	result = amount_;
        // cout << id_ << "W withdrew inside if:"<< result << "\n";
    }
    else{
        // cout << id_ << "W withdrew outside if:"<< result << "\n";
    }
    M.endwrite();
    // cout << id_ << "end W withdrew\n";
    return result;
}

bool Account::toAccount(int amount, Account& account){
	bool sucess = false;
    // cout << id_ << "start W toAccount\n";
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
    // cout << id_ << "W toAccount\n";
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
    // cout << id_ << "end W toAccount\n";
	return sucess;
}

int Account::commission(double prec){
    // cout << id_ << "start W commission\n";
    M.beginwrite();
    // cout << id_ << "W commission\n";
    sleep(SLEEP_TIME);
    int amount = (int)round(amount_ * prec/100);
    amount_ -= amount;
    M.endwrite();
    // cout << id_ << "end W commission\n";
    return amount;
}

string Account::toString(){
	stringstream buffer;
    // cout << id_ << "start R toString\n";
    M.beginread();
    // cout << id_ << "R toString\n";
	buffer << "Account " << id_ << ": Balance - " << amount_ << "$ , Account password - " << password_ << "\n";
    M.endread();
    // cout << id_ << "end R toString\n";
	return buffer.str();
}

bool compare(Account* a, Account* b)
{
    if(a->id_ < b->id_)
        return 1; //change to 1 if max heap required
    else 
        return 0; //change to 0 if max heap required
}