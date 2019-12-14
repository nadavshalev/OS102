#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <list> 
#include <iterator> 
#include "monitor.h"
#include "account.h"
#include "atm.h"
using namespace std;

list <Account*> accounts;

int main(int argc, char *argv[])
{

    runATM("testFile.txt", accounts);

    // pthread_t r[5], w[5];
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

    Account a = Account(100,"qwe", 1);
    cout << a.toString() << '\n';
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