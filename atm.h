#ifndef _Atm_
#define _Atm_

#include "account.h"
#include <iostream>
#include <fstream>
#include <list> 
#include <iterator> 
#include <string>
#include <vector>
using namespace std;


void runATM(string filePath,list <Account*>& accounts, int atmID);
void runCmd(string cmd, string* args, list <Account*>& accounts, int atmID);

string* tokenize(string const &str, const char delim);
Account* findAccount(list <Account*>& accounts, int id);






#endif