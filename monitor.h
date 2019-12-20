
#ifndef _Monitor_
#define _Monitor_

#include <iostream>
#include <pthread.h>
#include <unistd.h>
using namespace std;

class Monitor {
	private:
	    int read_cnt;
	    int write_cnt;
	    int wait_readers;
	    int wait_writers;

	    // condition variable to check whether reader can read
	    pthread_cond_t canread;
	    // condition variable to check whether writer can write
	    pthread_cond_t canwrite;
	    // mutex for synchronisation
	    pthread_mutex_t condlock;

	public:
	    Monitor();
	    void beginread();
	    void endread();
	    void beginwrite();
	    void endwrite();

};


#endif