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
int bankCount;
bool terminateFlag;
void* printStatus(void* argin);

int main(int argc, char *argv[])
{
    pthread_mutex_init(&logLock, NULL);

    terminateFlag = false;
    int numberATM = stoi(argv[1]);
    bankCount = 0;

    pthread_t bank, atms[numberATM], print2screen;
    int id[numberATM];

    struct bankArgs bArgs{
        accounts,
        bankCount,
        strLog
    };
    struct atmArgs aArgs[numberATM];

    for(int i = 0; i < numberATM; ++i){
        id[i] = i;
        aArgs[i].filePath = string(argv[i+2]);
        aArgs[i].accounts = &accounts;
        aArgs[i].atmID = &id[i];
        aArgs[i].strLog = &strLog;
        pthread_create(&atms[i], NULL, &runATM, (void*)&aArgs[i]);
    }

    pthread_create(&bank, NULL, &runBank, (void*)&bArgs);
    pthread_create(&print2screen, NULL, &printStatus, NULL);

    for(int i = 0; i < numberATM; ++i){
        pthread_join(atms[i], NULL);
    }
    terminateFlag = true;


}

void* printStatus(void* argin){
    stringstream printString;
    printString << "";
    remove("log.txt");
    int run = 0;
    while(!terminateFlag){
        printString.str("");
        list <Account*> :: iterator it;
        for(it = accounts.begin(); it != accounts.end(); ++it){
            printString << (*it)->toString();
        }
        printString << "The bank has " << bankCount << "$\n";
        cout << "\033[2J\033[1;1H";
        cout << run << "\n";
        cout << printString.str();

        pthread_mutex_lock(&logLock);
        ofstream out("log.txt",ios_base::app);
        out << strLog.str();
        out.close();
        strLog.str("");
        pthread_mutex_unlock(&logLock);

        usleep(500000);
        ++run;
    }   
    pthread_exit(NULL);
}