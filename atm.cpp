

#include "atm.h"


void runATM(string filePath,list <Account*>& accounts, int atmID, stringstream& strLog){
	
	ifstream file(filePath);
    string str; 
    while (getline(file, str))
    {
        sleep(0.1);
    	// split line to arguments
        string* args = tokenize(str, ' ');
        string cmd = args[0];
        runCmd(cmd, args, accounts, atmID, strLog);
    }
}

void runCmd(string cmd, string* args, list <Account*>& accounts, int atmID, stringstream& strLog){
//	strLog << cmd << "\t1: " << args[1] << "\t2: " << args[2] << "\t3: " << args[3] << "\n";
	int accID = stoi(args[1]);
	/************************* Open *************************/
	if (cmd == "O")
	{
		if(findAccount(accounts, accID) != NULL){
			strLog << "Error " << atmID << "‫‪: Your‬‬ ‫‪transaction‬‬ ‫‪failed‬‬ ‫–‬ ‫‪account‬‬ ‫‪with‬‬ ‫‪the‬‬ ‫‪same‬‬ ‫‪id‬‬ ‫‪exists‬‬\n";
			return;
		}
		Account* acc = new Account(accID, args[2], stoi(args[3]));
		accounts.push_back(acc);
		strLog << atmID << "‫‪‫‪: New Account‬‬ id is ‫"<< accID << "‫‪ with‬‬ ‫‪password‬‬ ‫" << args[2] << " ‫‪and‬‬ ‫‪initial‬‬ ‫‪balance‬‬ ‫" << stoi(args[3]) << "\n";
		return;
	}

	// verify account axist and correct pass
	Account* acc = findAccount(accounts, accID);
	if(acc == NULL){
		strLog << "‫‪Error‬‬ ‫‪" << atmID << "‫‪:‬‬ ‫‪Your‬‬ ‫‪transaction‬‬ ‫‪failed‬‬ ‫–‬ ‫‪account‬‬ ‫‪id‬‬ ‫"<< accID << " ‫‪does‬‬ ‫‪not‬‬ ‫‪exist‬‬\n";
		return;
	}
	if(acc->password_ != args[2]){
		strLog << "‫‪Error‬‬ ‫‪" << atmID << "‫‪:‬‬ ‫‪Your‬‬ ‫‪transaction‬‬ ‫‪failed‬‬ ‫–‬ ‫‪‫‪password‬‬ ‫‪for‬‬ ‫‪account‬‬ ‫‪id‬‬ ‫"<< accID << " ‫‪‫‪is‬‬ ‫‪incorrect‬‬\n";
		return;
	}

	/************************* Deposit ************************/
	if (cmd == "D")
	{
		int amount = stoi(args[3]);
		int result = acc->deposit(amount);
		strLog << atmID << "‫‪‫‪: Account‬‬ ‫"<< accID << " ‫‪new‬‬ ‫‪balance‬‬ ‫‪is‬‬ ‫" << result << " after " << amount << "$‬‬ ‫‪was‬‬ deposited\n";
	}
	/************************* Withdrew ************************/
	else if (cmd == "W")
	{
		int amount = stoi(args[3]);
		int result = acc->withdrew(amount);
		if (result == -1)
			strLog << "‫‪Error‬‬ ‫‪" << atmID << "‫‪:‬‬ ‫‪Your‬‬ ‫‪transaction‬‬ ‫‪failed‬‬ ‫–‬ ‫‪‫‪‫‪balance‬‬ ‫‪is‬‬ ‫‪lower‬‬ ‫‪than‬‬ ‫"<< amount << "\n";
		else
			strLog << atmID << "‫‪‫‪: Account‬‬ ‫"<< accID << " ‫‪new‬‬ ‫‪balance‬‬ ‫‪is‬‬ ‫" << result << " after " << amount << "$‬‬ ‫‪was‬‬ ‫‪withdrew‬‬\n";
	}
	/************************* Acount val ************************/
	else if (cmd == "B")
	{
		int amount = acc->getAmount();
        strLog << atmID << "‫‪‫‪: Account‬‬ ‫"<< accID << " ‫‪balance‬‬ ‫‪is‬‬ ‫" << amount << "\n";
	}
	/************************ Transaction *************************/
	else if (cmd == "T")
	{
	    Account* acc2 = findAccount(accounts, stoi(args[3]));
        if(acc2 == NULL){
            strLog << "‫‪Error‬‬ ‫‪" << atmID << "‫‪:‬‬ ‫‪Your‬‬ ‫‪transaction‬‬ ‫‪failed‬‬ ‫–‬ ‫‪account‬‬ ‫‪id‬‬ ‫"<< accID << " ‫‪does‬‬ ‫‪not‬‬ ‫‪exist‬‬\n";
            return;
        }
        int amount = stoi(args[4]);
		bool result = acc->toAccount(amount, *acc2);
		if (result)
			strLog << atmID << ": Transfer " << amount << " from account " << accID << " to account " << args[3] << " new account balance is " << acc->amount_ << " new target account balance is " << acc2->amount_ << "\n";
		else
		    strLog << "‫‪Error‬‬ ‫‪" << atmID << "‫‪:‬‬ ‫‪Your‬‬ ‫‪transaction‬‬ ‫‪failed‬‬ ‫–‬ ‫‪‫‪‫‪balance‬‬ ‫‪is‬‬ ‫‪lower‬‬ ‫‪than‬‬ ‫"<< amount << "\n";
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

Account* findAccount(list <Account*>& accounts, int id){
	list <Account*> :: iterator it;
    for(it = accounts.begin(); it != accounts.end(); ++it){
    	if ((*it)->id_ == id)
    		return (*it);
    }
    return NULL;
}