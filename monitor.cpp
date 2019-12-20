#include "monitor.h"

//********************************************
// function name: Monitor
// Description: init monitor class
//********************************************
Monitor::Monitor() :
     read_cnt(0), write_cnt(0), wait_readers(0), wait_writers(0), canread(), canwrite(), condlock()
{
    read_cnt = 0;
    write_cnt = 0;
    wait_readers = 0;
    wait_writers = 0;

    pthread_cond_init(&canread, NULL);
    pthread_cond_init(&canwrite, NULL);
    pthread_mutex_init(&condlock, NULL);
}

//********************************************
// function name: beginread
// Description: register reader to minitor
//********************************************
void Monitor::beginread()
{
    pthread_mutex_lock(&condlock);

    if (write_cnt == 1 || wait_writers > 0) {
        wait_readers++;
        pthread_cond_wait(&canread, &condlock);
        wait_readers--;
    }
    read_cnt++;
    pthread_mutex_unlock(&condlock);
    pthread_cond_broadcast(&canread);
}

//********************************************
// function name: endread
// Description: unregister reader to minitor
//********************************************
void Monitor::endread()
{

    pthread_mutex_lock(&condlock);
    if (--read_cnt == 0)
        pthread_cond_signal(&canwrite);
    pthread_mutex_unlock(&condlock);
}

//********************************************
// function name: beginwrite
// Description: register writer to minitor
//********************************************
void Monitor::beginwrite()
{
    pthread_mutex_lock(&condlock);
    if (write_cnt == 1 || read_cnt > 0) {
        ++wait_writers;
        pthread_cond_wait(&canwrite, &condlock);
        --wait_writers;
    }
    write_cnt = 1;
    pthread_mutex_unlock(&condlock);
}

//********************************************
// function name: Monitor
// Description: unregister writer to minitor
//********************************************
void Monitor::endwrite()
{
    pthread_mutex_lock(&condlock);
    write_cnt = 0;
    if (wait_readers > 0)
        pthread_cond_signal(&canread);
    else
        pthread_cond_signal(&canwrite);
    pthread_mutex_unlock(&condlock);
}