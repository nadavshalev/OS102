

#include "atm.h"


void runATM(string filePath,list <Account*>& accounts){
	
	ifstream file(filePath);
    string str; 
    while (getline(file, str))
    {
    	// split line to arguments
        string* args = tokenize(str, ' ');
        string cmd = args[0];
        runCmd(cmd, args, accounts);
    }
}

void runCmd(string cmd, string* args, list <Account*>& accounts){
	/************************* Open *************************/
	if (!strcmp(cmd, "O")) 
	{
	}
	/************************* Deposit ************************/
	else if (!strcmp(cmd, "D")) 
	{
	}
	/************************* Withdrew ************************/
	else if (!strcmp(cmd, "W")) 
	{
	}
	/************************* Acount val ************************/
	else if (!strcmp(cmd, "B")) 
	{
	}
	/************************ Transaction *************************/
	else if (!strcmp(cmd, "T")) 
	{
	}
	/************************ Command not exist *************************/
	else
	{
	}
}

string* tokenize(string const &str, const char delim)
{
	size_t start;
	size_t end = 0;
	int count = 0;
	string* spString = new string[5];
	while (count < 5 && ((start = str.find_first_not_of(delim, end)) != string::npos))
	{
		end = str.find(delim, start);
		spString[count] = str.substr(start, end - start);
		count++;
	}
	return spString;
}