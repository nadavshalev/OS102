
#include "atm.h"
#include <unistd.h>
#include <bits/stdc++.h>


//********************************************
// function name: runATM
// Description: read atm file and exec each line
//********************************************
void* runATM(void *argin){
	// get input arguments
	struct atmArgs *arg;
    arg = (struct atmArgs *) argin;
    ifstream op_file;
    // open file for stream
    op_file.open(arg->filePath.c_str(), ifstream::in);
	//ifstream file(arg->filePath);
    string str; 
    while (getline(op_file, str))
    {
        usleep(100000);
    	// split line to arguments
        string* args = tokenize(str, ' ');
        string cmd = args[0];
        // exec cmd
        runCmd(cmd, args, (*arg->accounts), (*arg->atmID), (*arg->strLog));
        delete[] args;
    }
    pthread_exit(NULL);
}

//********************************************
// function name: runCmd
// Description: exec commands
//********************************************
void runCmd(string cmd, string* args, list <Account*>& accounts, int atmID, stringstream& strLog){
	int accID = atoi(args[1].c_str());
	/************************* Open *************************/
	if (cmd == "O")
	{
		// check if eccount already exist
		if(findAccount(accounts, accID) != NULL){
			pthread_mutex_lock(&logLock);
			strLog << "Error " << atmID << "‫‪: Your‬‬ ‫‪transaction‬‬ ‫‪failed‬‬ ‫–‬ ‫‪account‬‬ ‫‪with‬‬ ‫‪the‬‬ ‫‪same‬‬ ‫‪id‬‬ ‫‪exists‬‬\n";
			pthread_mutex_unlock(&logLock);
			return;
		}
		// create new account
		Account* acc = new Account(accID, args[2], atoi(args[3].c_str()));

		// push and resort the account's list
		pthread_mutex_lock(&accountListLock);
		accounts.push_back(acc);
        accounts.sort(compare);
        pthread_mutex_unlock(&accountListLock);

		pthread_mutex_lock(&logLock);
		strLog << atmID << "‫‪‫‪: New Account‬‬ id is ‫"<< accID << "‫‪ with‬‬ ‫‪password‬‬ ‫" << args[2] << " ‫‪and‬‬ ‫‪initial‬‬ ‫‪balance‬‬ ‫" << atoi(args[3].c_str()) << "\n";
		pthread_mutex_unlock(&logLock);
		return;
	}

	// verify account axist and correct password
	Account* acc = findAccount(accounts, accID);
	if(acc == NULL){
		pthread_mutex_lock(&logLock);
		strLog << "‫‪Error‬‬ ‫‪" << atmID << "‫‪:‬‬ ‫‪Your‬‬ ‫‪transaction‬‬ ‫‪failed‬‬ ‫–‬ ‫‪account‬‬ ‫‪id‬‬ ‫"<< accID << " ‫‪does‬‬ ‫‪not‬‬ ‫‪exist‬‬\n";
		pthread_mutex_unlock(&logLock);
		return;
	}
	if(acc->password_ != args[2]){
		pthread_mutex_lock(&logLock);
		strLog << "‫‪Error‬‬ ‫‪" << atmID << "‫‪:‬‬ ‫‪Your‬‬ ‫‪transaction‬‬ ‫‪failed‬‬ ‫–‬ ‫‪‫‪password‬‬ ‫‪for‬‬ ‫‪account‬‬ ‫‪id‬‬ ‫"<< accID << " ‫‪‫‪is‬‬ ‫‪incorrect‬‬\n";
		pthread_mutex_unlock(&logLock);
		return;
	}

	/************************* Deposit ************************/
	if (cmd == "D")
	{
		int amount = atoi(args[3].c_str());
		int result = acc->deposit(amount);
		pthread_mutex_lock(&logLock);
		strLog << atmID << "‫‪‫‪: Account‬‬ ‫"<< accID << " ‫‪new‬‬ ‫‪balance‬‬ ‫‪is‬‬ ‫" << result << " after " << amount << "$‬‬ ‫‪was‬‬ deposited\n";
		pthread_mutex_unlock(&logLock);
	}
	/************************* Withdrew ************************/
	else if (cmd == "W")
	{
		int amount = atoi(args[3].c_str());
		int result = acc->withdrew(amount);
		if (result == -1){
			pthread_mutex_lock(&logLock);
			strLog << "‫‪Error‬‬ ‫‪" << atmID << "‫‪:‬‬ ‫‪Your‬‬ ‫‪transaction‬‬ ‫‪failed‬‬ ‫–‬ ‫‪‫‪‫‪balance‬‬ ‫‪is‬‬ ‫‪lower‬‬ ‫‪than‬‬ ‫"<< amount << "\n";
			pthread_mutex_unlock(&logLock);
		}
		else{
			pthread_mutex_lock(&logLock);
			strLog << atmID << "‫‪‫‪: Account‬‬ ‫"<< accID << " ‫‪new‬‬ ‫‪balance‬‬ ‫‪is‬‬ ‫" << result << " after " << amount << "$‬‬ ‫‪was‬‬ ‫‪withdrew‬‬\n";
			pthread_mutex_unlock(&logLock);
		}
	}
	/************************* Acount val ************************/
	else if (cmd == "B")
	{
		int amount = acc->getAmount();
		pthread_mutex_lock(&logLock);
        strLog << atmID << "‫‪‫‪: Account‬‬ ‫"<< accID << " ‫‪balance‬‬ ‫‪is‬‬ ‫" << amount << "\n";
        pthread_mutex_unlock(&logLock);
	}
	/************************ Transaction *************************/
	else if (cmd == "T")
	{
		// check if account 2 is axist
	    Account* acc2 = findAccount(accounts, atoi(args[3].c_str()));
        if(acc2 == NULL){
        	pthread_mutex_lock(&logLock);
            strLog << "‫‪Error‬‬ ‫‪" << atmID << "‫‪:‬‬ ‫‪Your‬‬ ‫‪transaction‬‬ ‫‪failed‬‬ ‫–‬ ‫‪account‬‬ ‫‪id‬‬ ‫"<< accID << " ‫‪does‬‬ ‫‪not‬‬ ‫‪exist‬‬\n";
            pthread_mutex_unlock(&logLock);
            return;
        }
        int amount = atoi(args[4].c_str());
		bool result = acc->toAccount(amount, *acc2);
		if (result){
			pthread_mutex_lock(&logLock);
			strLog << atmID << ": Transfer " << amount << " from account " << accID << " to account " << args[3] << " new account balance is " << acc->amount_ << " new target account balance is " << acc2->amount_ << "\n";
			pthread_mutex_unlock(&logLock);
		}
		else{
			pthread_mutex_lock(&logLock);
		    strLog << "‫‪Error‬‬ ‫‪" << atmID << "‫‪:‬‬ ‫‪Your‬‬ ‫‪transaction‬‬ ‫‪failed‬‬ ‫–‬ ‫‪‫‪‫‪balance‬‬ ‫‪is‬‬ ‫‪lower‬‬ ‫‪than‬‬ ‫"<< amount << "\n";
		    pthread_mutex_unlock(&logLock);
		}
    }	
	/************************ Command not exist *************************/
	else
	{
		// do nothing...
	}
}

//********************************************
// function name: tokenize
// Description: split to argunents
//********************************************
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

//********************************************
// function name: findAccount
// Description: find account in the list
// Retuen: pointer to the account
//********************************************
Account* findAccount(list <Account*>& accounts, int id){
	list <Account*> :: iterator it;
    for(it = accounts.begin(); it != accounts.end(); ++it){
    	if ((*it)->id_ == id)
    		return (*it);
    }
    return NULL;
}