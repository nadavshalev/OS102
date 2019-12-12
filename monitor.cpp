#include "monitor.h"

Monitor::Monitor() :
     rcnt(0), wcnt(0), waitr(0), waitw(0), canread(), canwrite(), condlock()
{
    rcnt = 0;
    wcnt = 0;
    waitr = 0;
    waitw = 0;

    pthread_cond_init(&canread, NULL);
    pthread_cond_init(&canwrite, NULL);
    pthread_mutex_init(&condlock, NULL);
}

// mutex provide synchronisation so that no other thread
// can change the value of data
void Monitor::beginread()
{
    pthread_mutex_lock(&condlock);

    // if there are active or waiting writers
    if (wcnt == 1 || waitw > 0) {
        // incrementing waiting readers
        waitr++;

//            cout << "reader " << i << " is sleep reading\n";
        // reader suspended
        pthread_cond_wait(&canread, &condlock);
        waitr--;
    }

    // else reader reads the resource
    rcnt++;
    pthread_mutex_unlock(&condlock);
    pthread_cond_broadcast(&canread);
}

void Monitor::endread()
{

    // if there are no readers left then writer enters monitor
    pthread_mutex_lock(&condlock);

    if (--rcnt == 0)
        pthread_cond_signal(&canwrite);

    pthread_mutex_unlock(&condlock);
}

void Monitor::beginwrite()
{
    pthread_mutex_lock(&condlock);

    // a writer can enter when there are no active
    // or waiting readers or other writer
    if (wcnt == 1 || rcnt > 0) {
        ++waitw;
//            cout << "writer " << i << " is sleep writing\n";
        pthread_cond_wait(&canwrite, &condlock);
        --waitw;
    }
    wcnt = 1;
    pthread_mutex_unlock(&condlock);
}

void Monitor::endwrite()
{
    pthread_mutex_lock(&condlock);
    wcnt = 0;

    // if any readers are waiting, threads are unblocked
    if (waitr > 0)
        pthread_cond_signal(&canread);
    else
        pthread_cond_signal(&canwrite);
    pthread_mutex_unlock(&condlock);
}