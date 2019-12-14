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


void runATM(string filePath,list <Account*>& accounts);
void runCmd(string cmd, string* args, list <Account*>& accounts);

string* tokenize(string const &str, const char delim);






#endif