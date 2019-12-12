
#ifndef _Monitor_
#define _Monitor_

#include <iostream>
#include <pthread.h>
#include <unistd.h>
using namespace std;

class Monitor {
	private:
	    // no. of readers
	    int rcnt;

	    // no. of writers
	    int wcnt;

	    // no. of readers waiting
	    int waitr;

	    // no. of writers waiting
	    int waitw;

	    // condition variable to check whether reader can read
	    pthread_cond_t canread;

	    // condition variable to check whether writer can write
	    pthread_cond_t canwrite;

	    // mutex for synchronisation
	    pthread_mutex_t condlock;

	public:
	    Monitor();
	    // can change the value of data
	    void beginread();

	    void endread();

	    void beginwrite();

	    void endwrite();

};


#endif