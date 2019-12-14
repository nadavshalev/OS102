#ifndef _Account_
#define _Account_

#include <iostream>
#include <string>
#include <sstream>

#include "monitor.h"
#define SLEEP_TIME 1
using namespace std;

class Account {
    private:
        int amount_;

    public:
        string password_;
        int id_;
        Monitor M;
        Account(int amount, string password, int id);
        int getAmount();
        void deposit(int amount);
        bool withdrew(int amount);
        bool toAccount(int amount, Account& account);
        string toString();

    };

#endif