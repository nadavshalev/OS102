#include "bank.h"

void runBank(list <Account*>& accounts, int& bankBalance, stringstream& strLog){
    while(true){
        sleep(3);
        list <Account*> :: iterator it;
        for(it = accounts.begin(); it != accounts.end(); ++it){
            double prec = (rand()/(RAND_MAX*1.0)) * 2 + 2;
            int amount = (*it)->commission(prec);
            bankBalance += amount;
            strLog << "Bank: commission of ‬" << prec << " where charged, the bank gained " << amount << "$ from account " << (*it)->id_ << "\n";
        }
    }
}