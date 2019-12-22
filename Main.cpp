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

list <Account*> accounts; //accounts list
stringstream strLog; // log buffer
pthread_mutex_t logLock, accountListLock, bankCountLock;
int bankCount; //bank amount
bool terminateFlag; // flag to stop bank and print threads
void* printStatus(void* argin);

//********************************************
// function name: main
// Description: main function - run the softwer
//********************************************
int main(int argc, char *argv[])
{
    // init vars
    pthread_mutex_init(&logLock, NULL);
    pthread_mutex_init(&accountListLock, NULL);
    terminateFlag = false;
    // check input vars
    if(argc < 3){
        cout << "illegal argument\n";
        return -1;
    }
    int numberATM = atoi(argv[1]);
    if(argc != numberATM + 2){
        cout << "illegal argument\n";
        return -1;
    }
    bankCount = 0;
    pthread_t bank, atms[numberATM], print2screen;
    int id[numberATM];
    struct bankArgs bArgs{
        accounts,
        bankCount,
        strLog
    };
    struct atmArgs aArgs[numberATM];

    // start atm threads
    for(int i = 0; i < numberATM; ++i){
        id[i] = i+1;
        aArgs[i].filePath = string(argv[i+2]);
        aArgs[i].accounts = &accounts;
        aArgs[i].atmID = &id[i];
        aArgs[i].strLog = &strLog;
        pthread_create(&atms[i], NULL, &runATM, (void*)&aArgs[i]);
    }

    // start bank and print threads
    pthread_create(&bank, NULL, &runBank, (void*)&bArgs);
    pthread_create(&print2screen, NULL, &printStatus, NULL);

    // wait for all accounts to finish
    for(int i = 0; i < numberATM; ++i){
        pthread_join(atms[i], NULL);
    }

    // terminate bank and print threads
    terminateFlag = true;
    pthread_join(bank, NULL);
    pthread_join(print2screen, NULL);

    accounts.erase(accounts.begin(),accounts.end());
    accounts.clear();
    return 0;
}

//********************************************
// function name: printStatus
// Description: print status to screen and save logs to file
//********************************************
void* printStatus(void* argin){
    stringstream printString;
    printString << "";
    remove("log.txt");

    while(!terminateFlag){
        // clear buffer
        printString.str("");

        // print account status to buffer 
        pthread_mutex_lock(&accountListLock);
        list <Account*> :: iterator it;
        for(it = accounts.begin(); it != accounts.end(); ++it){
            printString << (*it)->toString();
        }
        pthread_mutex_unlock(&accountListLock);

        // print buffer to screen (display all at once)
        pthread_mutex_lock(&bankCountLock);
        printString << "The bank has " << bankCount << "$\n";
        pthread_mutex_unlock(&bankCountLock);
        cout << "\033[2J\033[1;1H";
        cout << printString.str();

        // update log file
        pthread_mutex_lock(&logLock);
        ofstream out("log.txt",ios_base::app);
        out << strLog.str();
        out.close();
        strLog.str("");
        pthread_mutex_unlock(&logLock);

        // sleep for 1/2 sec
        usleep(500000);
    }   
    pthread_exit(NULL);
}