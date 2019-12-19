#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <list> 
#include <iterator> 
#include "monitor.h"
#include "account.h"
#include "atm.h"
#include "bank.h"
using namespace std;

list <Account*> accounts;
stringstream strLog;
pthread_mutex_t logLock;

int main(int argc, char *argv[])
{

    pthread_mutex_init(&logLock, NULL);
    string filePath = "testFile.txt";

    int bc = 0;
    int numberATM = 3;

    pthread_t bank, atms[numberATM];
    int id[numberATM];

    struct bankArgs bArgs{
        accounts,
        bc,
        strLog
    };
    struct atmArgs aArgs[numberATM];

    for(int i = 0; i < numberATM; ++i){
        id[i] = i;
        aArgs[i].filePath = filePath;
        aArgs[i].accounts = &accounts;
        aArgs[i].atmID = &id[i];
        aArgs[i].strLog = &strLog;
        pthread_create(&atms[i], NULL, &runATM, (void*)aArgs);
    }

    pthread_create(&bank, NULL, &runBank, (void*)&bArgs);

    // int id[5];
    // for (int i = 0; i < 5; i++) {
    //     id[i] = i;

    // //     // creating threads which execute reader function
    //     pthread_create(&r[i], NULL, &reader, &id[i]);

    //     // creating threads which execute writer function
    //     pthread_create(&w[i], NULL, &writer, &id[i]);
    // }

    // for (int i = 0; i < 5; i++) {
    //     pthread_join(r[i], NULL);
    // }
    // for (int i = 0; i < 5; i++) {
    //     pthread_join(w[i], NULL);
    // }
    // cout << "working!\n";


    // int amount = 0;
    // bool status = false;

    // runBank(accounts, bc, strLog);


    // cout << strLog.str();
    // pthread_join(bank, NULL);
    for(int i = 0; i < numberATM; ++i){
        pthread_join(atms[i], NULL);
    }
    pthread_cancel(bank);

    ofstream out("log.txt");
    out << strLog.str();
    out.close();

    // Account b = Account(50,"asd", 2);

    // amount = a.getAmount();
    // cout << amount <<"\n";

    // a.deposit(20);
    // amount = a.getAmount();
    // cout << amount <<"\n";

    // status = a.withdrew(90);
    // amount = a.getAmount();
    // cout << status << "  " << amount <<"\n";

    // status = a.withdrew(90);
    // amount = a.getAmount();
    // cout << status << "  " << amount <<"\n";

    // status = a.toAccount(12, b);
    // amount = a.getAmount();
    // cout << status << "  " << amount <<"\n";
    // amount = b.getAmount();
    // cout << status << "  " << amount <<"\n";

}