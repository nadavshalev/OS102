#ifndef _Account_
#define _Account_
import "monitor.h";

class Account {
    private:
        int amount_;
        Monitor M;


    public:
        int password_;
        int id_;
        Account(int amount, int password, string name);
        ~Account();
        int get_amount();
        void set_amount(int amount);

    };

#endif