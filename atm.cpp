

#include "atm.h"


void runATM(string filePath,list <Account*>& accounts){
	
	ifstream file(filePath);
    string str; 
    while (getline(file, str))
    {
    	// split line to arguments
        string* args = tokenize(str, ' ');
        string cmd = args[0];
    }
}

void runCmd(string cmd, string* args){
	
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