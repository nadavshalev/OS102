#ifndef _Bank_
#define _Bank_

#include "account.h"
#include <iostream>
#include <fstream>
#include <list>
#include <iterator>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

extern pthread_mutex_t logLock;
extern pthread_mutex_t bankCountLock;
extern bool  terminateFlag;

struct bankArgs {
	list <Account*>& accounts;
	int& bankBalance;
	stringstream& strLog;
};

void* runBank(void *argin);






#endif