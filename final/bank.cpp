#include "bank.h"

//********************************************
// function name: runBank
// Description: bank method
//********************************************
void* runBank(void *argin){
    // get input arguments
    struct bankArgs *arg;
    arg = (struct bankArgs *) argin;

    // run untile terminateFlag==true
    while(!terminateFlag){
        sleep(3);
        // get commision from each account
        list <Account*> :: iterator it;
        for(it = arg->accounts.begin(); it != arg->accounts.end(); ++it){
            double prec = (rand()/(RAND_MAX*1.0)) * 2 + 2;
            int amount = (*it)->commission(prec);
            arg->bankBalance += amount;
            pthread_mutex_lock(&logLock);
            pthread_mutex_unlock(&bankCountLock);
            arg->strLog << "Bank: commission of ‬" << prec << " where charged, the bank gained " << amount << "$ from account " << (*it)->id_ << "\n";
            pthread_mutex_unlock(&bankCountLock);
            pthread_mutex_unlock(&logLock);
        }
    }
    pthread_exit(NULL);
}