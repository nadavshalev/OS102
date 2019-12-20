#include "bank.h"

void* runBank(void *argin){
    struct bankArgs *arg;
    arg = (struct bankArgs *) argin;
    while(!terminateFlag){
        sleep(3);
        list <Account*> :: iterator it;
        for(it = arg->accounts.begin(); it != arg->accounts.end(); ++it){
            double prec = (rand()/(RAND_MAX*1.0)) * 2 + 2;
            int amount = (*it)->commission(prec);
            arg->bankBalance += amount;
            pthread_mutex_lock(&logLock);
            arg->strLog << "Bank: commission of ‬" << prec << " where charged, the bank gained " << amount << "$ from account " << (*it)->id_ << "\n";
            pthread_mutex_unlock(&logLock);
        }
    }
    pthread_exit(NULL);
}