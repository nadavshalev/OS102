#ifndef _Account_
#define _Account_

#include "monitor.h"
#include <iostream>
using namespace std;

class Account {
    private:
        int amount_;
        Monitor M;

    public:
        int password_;
        int id_;
        Account(int amount, int password, int id);
        int getAmount();
        void setAmount(int amount);

    };

#endif