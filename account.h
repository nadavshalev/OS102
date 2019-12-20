#ifndef _Account_
#define _Account_

#include <iostream>
#include <string>
#include <sstream>
#include <math.h>

#include "monitor.h"
#define SLEEP_TIME 1
using namespace std;

class Account {
    public:
        string password_;
        int id_;
        int amount_;
        Monitor M;

        Account(int id, string password, int amount);
        int getAmount();
        int deposit(int amount);
        int withdrew(int amount);
        int commission(double prec);
        bool toAccount(int amount, Account& account);
        string toString();

    };

bool compare(Account* a, Account* b);

#endif