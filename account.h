#ifndef _Account_
#define _Account_

#include "monitor.h"
#include <iostream>
using namespace std;

class Account {
    private:
        int amount_;

    public:
        int password_;
        int id_;
        Monitor M;
        Account(int amount, int password, int id);
        int getAmount();
        void deposit(int amount);
        bool withdrew(int amount);
        bool toAcount(int amount, Account account);

    };

#endif